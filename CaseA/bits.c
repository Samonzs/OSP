// Ali Salman 20056663

#include<stdio.h>
#include<stdint.h>
#include"bits.h"

void print_bits(uint8_t value) 
{
    
    for(int i = 0; i <= 7; i++) {

        int index = 7-i;

        int res = value >> index;  
        
        int mask = 1; 

        res = res & mask; 
        
        printf("%d", res);

    }
}

uint8_t reverse_bits(uint8_t value)
{
	uint8_t res = 0;

	for(int i = 0; i < 7; i++) {
      
        int index = 7-i;
    
        int current_bit = value >> i & 1; 

        res = res | current_bit << index;  


	}

	return res;
}

uint8_t check_bit(uint8_t value, uint8_t bit)
{
    int checked = 0;
    
    int i = value >> bit; 

    if(i & 1) {
        checked = 1;
    }
    return checked;
}

/*
the following function was adapted and inspired from:
https://stackoverflow.com/questions/47981/how-do-you-set-clear-and-toggle-a-single-bit
*/

uint8_t toggle_bit(uint8_t *value, uint8_t bit)
{   

	*value = *value ^ (1 << bit);
    
	return *value;
}

/*
the following function was adapated and inspired from:
/https://stackoverflow.com/questions/8011700/how-do-i-extract-specific-n-bits-of-a-32-bit-unsigned-integer-in-c
*/


uint8_t get_subfield(uint8_t value, uint8_t start, uint8_t stop)
{  
   uint8_t mask;

   mask = (1 << stop) - 1;

   uint8_t lastBits = (value >> start) & mask;

   return lastBits;
}




