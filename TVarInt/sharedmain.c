
#include <stdio.h>
#include "sharedmain.h"

int32_t read_int32fromNetworkEndian(const uint8_t* data) {
    // Directly shift and combine the bytes
    return (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
}
int read_boolean(const uint8_t* data) {
    // Return 1 for true (0x01) and 0 for false (0x00)
    return (*data == 0x01) ? 1 : 0;
}

int read_uint8fromNetworkEndian(const uint8_t* data)
{
    return (*data);
}
int8_t read_int8fromNetworkEndian(const uint8_t* data) {
    return (int8_t)data[0]; // Cast the first byte to int8_t to interpret it as a signed byte
}

int64_t read_int64fromNetworkEndian(const uint8_t *data)
    {
        return ((int64_t)data[0] << 56) |
               ((int64_t)data[1] << 48) |
               ((int64_t)data[2] << 40) |
               ((int64_t)data[3] << 32) |
               ((int64_t)data[4] << 24) |
               ((int64_t)data[5] << 16) |
               ((int64_t)data[6] <<  8) |
               ((int64_t)data[7]);
    }
double read_doubleFromNetworkEndian(const uint8_t *data) {
    uint64_t temp;
    memcpy(&temp, data, sizeof(temp));  // Copy directly from network buffer
    temp = be64toh(temp);               // Convert from big-endian to host-endian
    double result;
    memcpy(&result, &temp, sizeof(result));  // Interpret the result as double
    return result;
}

// Function to convert 32-bit big-endian float to little-endian float
float read_floatFromNetworkEndian(const uint8_t *data) {
    uint32_t temp;
    memcpy(&temp, data, sizeof(temp));  // Copy directly from network buffer
    temp = be32toh(temp);               // Convert from big-endian to host-endian
    float result;
    memcpy(&result, &temp, sizeof(result));  // Interpret the result as float
    return result;
}


static TVarInt sharedMain_returnVarInt(int value)
{
    unsigned char *buf = malloc(VARINTMAXLEN);
    sharedMain_writeVarInt(buf, value);
    TVarInt res = sharedMain_readVarInt(buf, VARINTMAXLEN);
    res.byteAfterEnd = NULL;
    free(buf);
    return res;
}

unsigned char *sharedMain_writeString(unsigned char * buf, const char * str){
    int len = strlen(str);
    buf = sharedMain_writeVarInt(buf, len);
    memcpy(buf, str, len);
    return buf + len;
}

int sharedMain_getSizeAsVarInt(int n)
{
    return sharedMain_returnVarInt(n).byteSize;
}