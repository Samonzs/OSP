/* fs.h
 * Various definitions for OSP Practical Case Study E
 */
#ifndef FS_H
#define FS_H
/* Prevent multiple inclusion */

#include<stdint.h>

/* The bitmap */
extern uint8_t bitmap[85];
/* 170Kb disk with 256b blocks->  680 bits for bitmap -> 85 bytes
 */

/* The directory entry */
struct entry
{
	int8_t  user;
	char  name[9];
	char  extension[4];
	int16_t blockcount;
	int16_t block[24];
};


/* The Directory */
extern struct entry directory[32];

/* extern means its defined in another
   file, prevents multiple definition
   errors
*/

int toggle_bit(int block);
/* Toggles the value of the bit 'block', in
   the external array 'bitmap'.
   returns the current value of the bit
   Does NOT validate 'block'!!!
*/
int block_status(int block);
/* Returns the status of 'block',
   in the external array bitmap
   returns 0 if bitmap bit is 0,
   not 0 if bitmap bit is 1
   Does NOT validate block!!!
*/
#endif

