//
// Created by Ignacio on 9/17/2024.
//

#ifndef MCBC4_PDEF_V12_2_2_C
#define MCBC4_PDEF_V12_2_2_C

#define v1_12_2_CPID_SERVERBOUND_KEEPALIVE 0x0B // client packet id
#define v1_12_2_CPID_CLIENTBOUND_KEEPALIVE 0x1F
#define v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS 0x02
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY 0x1A
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN 0x00
#define v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION 0x03

#define v1_12_2_CPID_CLIENTBOUND_CHUNKDATA 0x20
#define v1_12_2_CPID_CLIENTBOUND_PLAYER_POSITION_AND_LOOK 0x2F

#include <string.h>
#include <stdio.h>

#include "../../Defs/ChunkHashFunc.h"
#include "../../crossSocket/crossSocket.h"
#include "../../Defs/ClientDef.h"
#include "../../Defs/ChunkDef.h"
#include "../../Parser/parser.h"
#include "../../TVarInt/sharedmain.h"
#include "zlib.h"


extern packetHandler_t *internal_v1_12_2_defaultGeneralHandler[CSTATE_TOTALCOUNT];

#endif //MCBC4_PDEF_V12_2_2_C
