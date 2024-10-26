cmake_minimum_required(VERSION 3.22)
project(mcbc6 C)

set(CMAKE_C_STANDARD 11)
# Enable stack protection and debug symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -g -Wall")

# Find and link zlib
find_package(ZLIB REQUIRED)

# Find and link the math library
find_library(MATH_LIBRARY m)

add_executable(mcbc6 main.c
        TVarInt/sharedmain.c
        Defs/ClientDef.h
        Parser/parser.h
        Parser/parser.c
        TVarInt/TVarint.c
        crossSocket/crossSocket.h
        crossSocket/crossSocket.c
        Versions/v1_12_2/defaultGeneralHandler.c
        file_io/file_io.c
        Parser/Interpreter/Interpreter.c
        Versions/v1_12_2/HshakeAndLogin/HshakeAndLogin.c
        Defs/ChunkDef.h
        Defs/ChunkDef.h
        Defs/TPoint2d.h
        Defs/ChunkHashFunc.c
        Defs/ChunkHashFunc.h
        stdPackets/Deserializer/setCompression.c
        stdPackets/Deserializer/setCompression.c
        stdPackets/Deserializer/disconnect.c
        stdPackets/Deserializer/keepAlive.c
        Versions/v1_12_2/Deserializer/v1_12_2_chunkData.c
        stdPackets/Deserializer/playerPositionAndLook.c
        stdPackets/Deserializer/playerPositionAndLook.h
        stdPackets/Serializer/teleportConfirm.c
        stdPackets/Serializer/teleportConfirm.h
        stdPackets/stdPackets.h
        Defs/Physics.h
        Defs/Physics.h
        Std/internal_std_getChunk.c
        Public/public_getBlockAtCoords.c
        Std/internal_std_getClientChunk.c
        Std/internal_std_getClientChunk.h
        Std/internal_std_isOnGround.c
        Std/internal_std_isOnGround.h
        Defs/isInSortedArr.c
        Defs/isInSortedArr.h
        Std/internal_std_getBlockAtVec3.c
        Std/internal_std_getBlockAtVec3.h
        Defs/ColliderDefs.c
        Defs/ColliderDefs.h
        Defs/PacketDef.h
        Defs/StdIdDef.h
        Versions/v1_12_2/Deserializer/v1_12_2_blockChange.c
        Versions/v1_12_2/Deserializer/v1_12_2_blockChange.h
        Versions/v1_12_2/Deserializer/v1_12_2_chunkData.c
        Versions/v1_12_2/Deserializer/v1_12_2_multiBlockChange.c
        Versions/v1_12_2/Deserializer/v1_12_2_multiBlockChange.h
)

# Link zlib and math to the executable
target_link_libraries(mcbc6 ZLIB::ZLIB ${MATH_LIBRARY})
