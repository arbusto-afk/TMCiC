//
// Created by Ignacio on 29/9/2024.
//

#include "playerPositionAndLook.h"
#include "stdio.h"

void internal_std_packet_playerPositionAndLook(const uint8_t * data, int dataLen, struct client * c)
{
    printf("\nreceived protmov packet: <");
    for(int i = 0; i < dataLen; i++)
        printf("%02x ", data[i]);
    printf(">\n");
     //read_
     unsigned char flags = read_int8fromNetworkEndian(data + TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE * 2);
     if(flags & 0x01)
         c->x += read_doubleFromNetworkEndian(data);
     else
         c->x = read_doubleFromNetworkEndian(data);

     if(flags & 0x02)
         c->y += read_doubleFromNetworkEndian(data + TYPELONG_BYTESIZE);
     else
         c->y = read_doubleFromNetworkEndian(data + TYPELONG_BYTESIZE);

     if(flags & 0x04)
        c->z += read_doubleFromNetworkEndian(data + TYPELONG_BYTESIZE * 2);
     else
         c->z = read_doubleFromNetworkEndian(data + TYPELONG_BYTESIZE * 2);
    if(flags & 0x08)
        c->yaw += read_floatFromNetworkEndian(data + TYPELONG_BYTESIZE * 3);
    else
        c->yaw = read_floatFromNetworkEndian(data + TYPELONG_BYTESIZE * 3);
    if(flags & 0x10)
        c->pitch += read_floatFromNetworkEndian(data + TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE);
    else
        c->pitch = read_floatFromNetworkEndian(data + TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE);


    int teleportId2 = sharedMain_readVarInt(data + TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE * 2 + 2,
                                           dataLen - TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE * 2).value;
    int teleportId = sharedMain_readVarInt(data + TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE * 2 + 1,
                                           dataLen - TYPELONG_BYTESIZE * 3 + TYPEFLOAT_BYTESIZE * 2).value;
   // if(teleportId != 0) {

        printf("Received new protmove packet with tp id %d\n", teleportId);
    internal_std_packet_serialize_teleportConfirm(c, teleportId);
    internal_std_packet_serialize_teleportConfirm(c, teleportId2);
  //  }
}
