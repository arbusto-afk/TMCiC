#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>

// Function to write a buffer to a file
int file_io_write_buffer_to_file(const char *file_path, const char *buffer, size_t buffer_size);

// Function to read a buffer from a file
char *file_io_read_buffer_from_file(const char *file_path, size_t *buffer_size);

int file_io_write_formatted_to_file(const char *file_path, const char *format, ...);

/*
 * Appends
 * if buffer_size <= 0 returns without doing anything
 */
int file_io_write_hex_to_file(const char *file_path, const char *buffer, int buffer_size);
#endif // FILE_IO_H
