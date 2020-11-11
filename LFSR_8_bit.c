#include <stdio.h>
#include <stdint.h>

void LFSR(uint8_t* data, uint8_t* polynomial_degrees, uint8_t degrees_quantity, uint16_t iterations);
void to_bin (void * number, unsigned char num_size, char *string);

int main (int argv, char *argc[])	{
	uint8_t data = 234;
	int i;
	uint8_t degrees[] = {8, 6, 5, 4, 0};
	char string[8 * sizeof(uint8_t) + 1];
	for(i = 0; i < 1; i++)	{
		printf("Iteration: %d - ", i);
		to_bin((void*) &data, sizeof(uint8_t), string);
		printf("%s -> ", string);
		LFSR(&data, degrees, 5, 255);
		to_bin((void*) &data, sizeof(uint8_t), string);
		printf("%s\n", string);
	}
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

void LFSR(uint8_t* data, uint8_t* polynomial_degrees, uint8_t degrees_quantity, uint16_t iterations)	{
	uint16_t i, e, polynomial = 0, temp = 0, xors;
	char string[8 * sizeof(uint8_t) + 1];
	for(i = 0; i < degrees_quantity; i++)	polynomial = polynomial | (1 << polynomial_degrees[i]);
	for(i = 0; i < iterations; i++)	{
		temp = *data & polynomial;
		xors = (temp << 7-polynomial_degrees[0]) & 0x80;
		for(e = 1; e < degrees_quantity; e++)	xors = xors ^ ((temp << 7-polynomial_degrees[e]) & 0x80);
		*data = (*data >> 1) | xors;
	}
}
