cmake_minimum_required(VERSION 3.22)
project(mcbc6 C)

set(CMAKE_C_STANDARD 11)
# Enable stack protection and debug symbols
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all -g -Wall")

# Find and link zlib
find_package(ZLIB REQUIRED)

add_executable(mcbc6 main.c
        TVarInt/sharedmain.c
        Defs/clientDef.h
        Parser/parser.h
        Parser/parser.c
        TVarInt/TVarint.c
        crossSocket/crossSocket.h
        crossSocket/crossSocket.c
        Versions/v1_12_2/pDef_v1_12_2_2.c
        file_io/file_io.c
        Versions/v1_12_2/Interpreter/Interpreter.c
        Versions/v1_12_2/HshakeAndLogin/HshakeAndLogin.c
)

# Link zlib to the executable
target_link_libraries(mcbc6 ZLIB::ZLIB)