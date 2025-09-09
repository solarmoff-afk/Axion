/*
    Исходный код библиотеки для эмуляции оперативной памяти

    Её задачи
        1. Инициализировать память
        2. Уничтожать память
        3. Записывать в память
        4. Чтения из памяти
        5. Получения размера памяти

    Функции могут возвращать коды, вот справка:
        1. Код 0: Успех операции
        2. Кож -1: Провал операции
*/

#include "memory.h"
#include <stdlib.h>
#include <string.h> // for/для memcpy

static uint8_t* g_buffer = NULL;
static size_t g_size = 0;

int memory_init(size_t size) {
    /*
        Это защита от повторной инициализации памяти. Если
        память УЖЕ была инициализована - g_buffer не будет
        нулевым, а значит мы инициализируем памяь повторно.
        Для безопасности мы очистим память, которая
        была выделена на буфер.
    */
    
    if (g_buffer != NULL) {
        free(g_buffer);
    }

    g_size = size;
    g_buffer = (uint8_t*)malloc(g_size);

    if (g_buffer == NULL) {
        g_size = 0;
        return -1;
    }
    
    memset(g_buffer, 0, g_size);
    return 0;
}

void memory_destroy() {
    if (g_buffer != NULL) {
        free(g_buffer);
        g_buffer = NULL;
        g_size = 0;
    }
}

int memory_write_byte(uint64_t address, uint8_t value) {
    /*
        Это условие - защита от выхода за границы памяти. Мы делаем
        проверку что адрес больше, чем размер памяти (g_size) который
        мы устанавливаем во время вызова функции инициализации. В том
        случае, если уловие верно - мы посылаем код -1, который
        означает ошибку
    */
    
    if (address >= g_size)
        return -1;

    g_buffer[address] = value;
    return 0;
}

int memory_write_halfword(uint64_t address, uint16_t value) {
    if (address + sizeof(uint16_t) > g_size)
        return -1;

    memcpy(g_buffer + address, &value, sizeof(uint16_t));
    return 0;
}

int memory_write_word(uint64_t address, uint32_t value) {
    if (address + sizeof(uint32_t) > g_size)
        return -1;

    memcpy(g_buffer + address, &value, sizeof(uint32_t));
    return 0;
}

int memory_write_qword(uint64_t address, uint64_t value) {
    if (address + sizeof(uint64_t) > g_size)
        return -1;
    
        memcpy(g_buffer + address, &value, sizeof(uint64_t));
    return 0;
}

int memory_read_byte(uint64_t address, uint8_t* value) {
    if (address >= g_size)
        return -1;

    *value = g_buffer[address];
    return 0;
}

int memory_read_halfword(uint64_t address, uint16_t* value) {
    if (address + sizeof(uint16_t) > g_size)
        return -1;

    memcpy(value, g_buffer + address, sizeof(uint16_t));
    return 0;
}

int memory_read_word(uint64_t address, uint32_t* value) {
    if (address + sizeof(uint32_t) > g_size)
        return -1;

    memcpy(value, g_buffer + address, sizeof(uint32_t));
    return 0;
}

int memory_read_qword(uint64_t address, uint64_t* value) {
    if (address + sizeof(uint64_t) > g_size) 
        return -1;

    memcpy(value, g_buffer + address, sizeof(uint64_t));
    return 0;
}

size_t memory_get_size() {
    return g_size;
}

uint8_t* memory_get_buffer() {
    return g_buffer;
}