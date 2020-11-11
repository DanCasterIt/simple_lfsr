#include <stdio.h>
#include <stdint.h>

void LFSR(uint32_t* data, uint8_t* polynomial_degrees, uint32_t degrees_quantity, uint32_t iterations);
void to_bin (void * number, unsigned char num_size, char *string);

int main (int argv, char *argc[])	{
	uint32_t data = 0xFFFF0000;
	uint8_t degrees[] = {7, 6, 5, 0};
	char string[8 * sizeof(uint32_t) + 1];
	to_bin((void*) &data, sizeof(uint32_t), string);
	printf("%s\n", string);
	LFSR(&data, degrees, 4, 50);
	to_bin((void*) &data, sizeof(uint32_t), string);
	printf("%s\n", string);
	return 0;
}

void to_bin (void * number, unsigned char num_size, char *string)	{
	int i, e, f;
	unsigned char *num;
	for(f = 0, e = 8 * num_size -1; f < num_size;  f++)	{
		num = number + f;
		for(i = 0; i < 8; i++, e--)	string[e] = ((*num >> i) & 1) ? '1' : '0';
	}
	string[8 * num_size] = '\0';
}

void LFSR(uint32_t* data, uint8_t* polynomial_degrees, uint32_t degrees_quantity, uint32_t iterations)	{
	uint32_t i, e, polynomial = 0, temp = 0, xors;
	char string[8 * sizeof(uint32_t) + 1];
	for(i = 0; i < degrees_quantity; i++)	polynomial = polynomial | (1 << polynomial_degrees[i]);
	for(i = 0; i < iterations; i++)	{
		temp = *data & polynomial;
		xors = (temp << 31-polynomial_degrees[0]) & 0x80000000;
		for(e = 1; e < degrees_quantity; e++)	xors = xors ^ ((temp << 31-polynomial_degrees[e]) & 0x80000000);
		*data = (*data >> 1) | xors;
	}
}
