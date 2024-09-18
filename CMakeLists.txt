cmake_minimum_required(VERSION 3.22)
project(mcbc6 C)

set(CMAKE_C_STANDARD 11)
# Enable stack protection and debug symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -g -Wall")

add_executable(mcbc6 main.c
        TVarInt/sharedmain.c
        Client/client.h
        Parser/parser.h
        Parser/parser.c
        TVarInt/TVarint.c
        crossSocket/crossSocket.h
        crossSocket/crossSocket.c
        pDef_v1_12_2_2.c
        file_io/file_io.c)
