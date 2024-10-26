#include "file_io.h"

// Function to write a buffer to a file
int file_io_write_buffer_to_file(const char *file_path, const char *buffer, size_t buffer_size) {
    FILE *file = fopen(file_path, "wb");
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    size_t written_size = fwrite(buffer, 1, buffer_size, file);
    fclose(file);

    if (written_size != buffer_size) {
        perror("Error writing to file");
        return -1;
    }

    return 0; // Success
}

int file_io_write_hex_to_file(const char *file_path, const char *buffer, int buffer_size) {
    if(buffer_size <= 0)
        return 0;
    FILE *file = fopen(file_path, "a");  // Open file in write mode (overwrite)
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    for (size_t i = 0; i < buffer_size; i++) {
        // Write each byte as a two-character hex value followed by a space
        if (fprintf(file, "%02X ", (unsigned char)buffer[i]) < 0) {
            perror("Error writing to file");
            fclose(file);
            return -1;
        }

        // Add a newline after every 16 bytes for readability (optional)
        if ((i + 1) % 32 == 0) {
            if (fprintf(file, "\n") < 0) {
                perror("Error writing newline to file");
                fclose(file);
                return -1;
            }
        }
    }

    fclose(file);
    return 0; // Success
}

#include <stdarg.h>
int file_io_write_formatted_to_file(const char *file_path, const char *format, ...) {
    FILE *file = fopen(file_path, "a");  // Open in append mode to add formatted data
    if (!file) {
        perror("Error opening file for writing");
        return -1;
    }

    va_list args;
    va_start(args, format);

    // Write the formatted string to the file using vfprintf
    if (vfprintf(file, format, args) < 0) {
        perror("Error writing formatted data to file");
        va_end(args);
        fclose(file);
        return -1;
    }

    va_end(args);
    fclose(file);
    return 0; // Success
}
// Function to read a buffer from a file
char *file_io_read_buffer_from_file(const char *file_path, size_t *buffer_size) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        perror("Error opening file for reading");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    *buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(*buffer_size);
    if (!buffer) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, *buffer_size, file);
    fclose(file);

    if (read_size != *buffer_size) {
        perror("Error reading from file");
        free(buffer);
        return NULL;
    }

    return buffer; // Success
}
