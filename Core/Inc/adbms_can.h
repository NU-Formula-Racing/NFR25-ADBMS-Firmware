#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>


/* Purpose of the simple CAN library is to encode / decode CAN signals so that it aligns
   with the 8 8-bit frames that's being sent and received by the CAN. 
*/

typedef struct {
    union {
        uint64_t as_uint64;
        uint8_t bytes[8];    
    } raw_data;
    int length;
} RawCanSignal;

void setData(RawCanSignal *data, void *value, size_t size, int len) {
    memcpy(&(data->raw_data), value, size);
    data->length = len;
}

void printBytes(RawCanSignal *data) {
    printf("Bytes: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", data->raw_data.bytes[i]);
    }
    printf("\n");
}


uint64_t generateMask(int pos, int len) {
    return (0xFFFFFFFFFFFFFFFFull << (64-len) >> (64-len-pos));
}

void encodeSignals(uint8_t *data, int count, ...) {
    va_list args;
    va_start(args, count);
    RawCanSignal arr[count];
    uint64_t buffer = 0;
    
    for(size_t i=0; i<count; i++){
        RawCanSignal temp = va_arg(args, RawCanSignal);
        arr[i] = temp;
    }
    
    int len_ptr = 0;
    for(size_t i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        // arr[i].raw_data.as_uint64
        uint64_t mask = generateMask(len_ptr, arr[i].length);
        buffer |= (arr[i].raw_data.as_uint64 << len_ptr) & mask;
        len_ptr += arr[i].length;
    }
    
    //printf("%lu\n", buffer);
    
    for(size_t i=0; i<8; i++){
        data[i] = (buffer >> (i*8)) & 0xFF;
    }
}