cmake_minimum_required(VERSION 3.22)
project(mcbc6 C)

set(CMAKE_C_STANDARD 11)
# Enable stack protection and debug symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -g -Wall")

# Find and link zlib
find_package(ZLIB REQUIRED)

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
        Versions/v1_12_2/Interpreter/Interpreter.c
        Versions/v1_12_2/HshakeAndLogin/HshakeAndLogin.c
        Defs/ChunkDef.h
        Defs/ChunkDef.h
        Defs/TPoint2d.h
        Defs/ChunkHashFunc.c
        Defs/ChunkHashFunc.h
        stdPackets/setCompression.c
        stdPackets/setCompression.c
        stdPackets/disconnect.c
        stdPackets/keepAlive.c
        Versions/v1_12_2/chunkData.c
        stdPackets/playerPositionAndLook.c
        stdPackets/playerPositionAndLook.h
        stdPackets/Serialize/teleportConfirm.c
        stdPackets/Serialize/teleportConfirm.h
        stdPackets/stdPackets.h
)

# Link zlib to the executable
target_link_libraries(mcbc6 ZLIB::ZLIB)