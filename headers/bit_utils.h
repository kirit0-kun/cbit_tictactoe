#include <stdint.h>
#include <string.h>

#ifndef TEST_HEADER
#define TEST_HEADER

#define SET_BIT(BF,N) _SET_BIT(BF,N)
#define CLR_BIT(BF,N) _CLR_BIT(BF,N) 
#define GET_BITS(BF,N,S) _GET_BITS(BF,N,S) 
#define IS_BIT_SET(BF, N) _IS_BIT_SET(BF, N) 

#define BITS_IN_BYTE 8

void set_bit(void* data, int offset);
void clr_bit(void* data, int offset);
void set_bits(void* board, int offset, int value, uint8_t size);
uint8_t is_bit_set(const void* data, int offset);
uint64_t get_bits(void* data, int offset, uint8_t size);
void print_bits(const void* data, size_t bits);

#endif //TEST_HEADER