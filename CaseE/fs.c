/* fs.c
   Some useful functions for OSP Practical Case Study E
*/
/* This File Has Not Been Modified! Ali Salman 20056663 */

#include"fs.h"

uint8_t bitmap[85];
struct entry directory[32];

int toggle_bit(int block)
{

	int elem=block/8;
	int pos=block%8;
	int mask=1<<pos;

	bitmap[elem]^=mask;

	return bitmap[elem]&mask;
}


int block_status(int block)
{
	int elem=block/8;
	int pos=block%8;
	int mask=1<<pos;

	return bitmap[elem]&mask;
}


