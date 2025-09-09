#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdint.h>

#define MEM_SUCCESS 0
#define MEM_ERROR_OUT_OF_BOUNDS 1
#define MEM_ERROR_NOT_INITIALIZED 2

extern "C" {
#ifdef __cplusplus
    #define EXPORT extern "C" __declspec(dllexport)
#else
    #define EXPORT __declspec(dllexport)
#endif

EXPORT int memory_init(size_t size);

// Освобождает память
EXPORT void memory_destroy();

// Если что это даёт 0 при успехе и -1 при ошибке
// This return 0 if all ok and return -1 if error
EXPORT int memory_write_byte(uint64_t address, uint8_t value);
EXPORT int memory_write_halfword(uint64_t address, uint16_t value);
EXPORT int memory_write_word(uint64_t address, uint32_t value);
EXPORT int memory_write_qword(uint64_t address, uint64_t value);

// Это тоже
EXPORT int memory_read_byte(uint64_t address, uint8_t* value);
EXPORT int memory_read_halfword(uint64_t address, uint16_t* value);
EXPORT int memory_read_word(uint64_t address, uint32_t* value);
EXPORT int memory_read_qword(uint64_t address, uint64_t* value);

EXPORT size_t memory_get_size();
EXPORT uint8_t* memory_get_buffer();
}

#endif