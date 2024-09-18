
#include <stdio.h>
#include "sharedmain.h"
#include "TVarInt.h"
#include <string.h>


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