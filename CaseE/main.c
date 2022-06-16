#include<stdio.h>
/* stdio.h will be found in the system path */
#include"fs.h"
/* fs.h will be found in the local path */
#include <string.h>
#include <dirent.h> 
#include <fcntl.h>

#include <ctype.h>

int main(int argv, char *av[])

{  
    char fileName[9], extension[4];

    int fileLocation = 0;

    int choice = 0;
	do

    {
        printf("Please choose a task (enter the number)\n\n");
        printf("1. Intialise Disk\n");
        printf("2. List Files in the Directory\n");
        printf("3. Display the Free Bitmap\n");
		printf("4. Open/Create File\n");
        printf("5. Read File\n");
		printf("6. Write File\n");
		printf("7. Delete File\n");
        scanf("%d",&choice);

       
    
        switch(choice)
        {
            /*Intialising the disk (store directory in arrays)*/
            case 1:

                printf("Initialising the disk ...\n");
                memset(&bitmap[0], 0, sizeof(bitmap));
                memset(&directory[0], 0, sizeof(directory));
                printf("\nDisk sucessfully initialised.\n");
				break;

            case 2:

                for(int i = 0; i < 32; i++)
                {
                    if(strcmp(directory[i].name, "")  != 0) /*  prints out directory name that contains a value (we dont want to print empty names) */
                    {
                        printf("Name:%s\n", directory[i].name);
                        printf("Extension:%s\n", directory[i].extension);        
                        printf("Blockcount:%d\n", directory[i].blockcount);
                    }
                }      
           
            break;

            case 3:

                    for(int i = 0; i < sizeof(bitmap); i++) 
                    {   
                        uint8_t value = bitmap[i];   /* byte values of bitmap are different each time you run the program (percieved from case a) */

                        for(int i = 0; i <= 7; i++) 
                        {
                            int index = 7-i;

                            int res = value >> index;  
                            
                            int mask = 1; 

                            res = res & mask; 
                            
                            printf("%d", res);
                        }     
                        
                        printf("\n");

                    }   
                break;

            case 4:

                printf("Please enter a file name to open:\n");

                scanf("%s",fileName);

                if(strlen(fileName) > 9)
                {
                    printf("Cant exceed 9 characters\n");       /* validate user input */
                    break;
                }

                printf("Now please enter a Extension to open:\n");

                scanf("%s",extension);

                if(strlen(extension) > 4)

                {
                    printf("Cant exceed 4 extensions\n");
                    break;

                }

                for(int i = 0; i < 32; i++)
                {                   
                    if(strcmp(directory[i].name, "") == 0)  /* check for slot in directory */
                    {
                        strcat(directory[i].name, fileName);
                        strcat(directory[i].extension, extension);
                        fileLocation = -1;
                        break;
                    }

                    if(strcmp(directory[i].name, fileName) == 0)    /* check for existing file name */
                    {
                        printf("\nThis FileName already exists\n");
                        break; 
                        
                    }

                }

                if(fileLocation == -1)
                {
                   printf("\nNew File Created.\n\n");
                }

           
                break;

            case 5:
                
                

                if(fileLocation == 0)
                {
                    printf("No File has been opened.\n");
                }
                else
                {
                    for (int i = 0; i < sizeof(directory[fileLocation].blockcount); i++)
                    {
                        printf("%d", directory[fileLocation].block[i]); /* selecting our opened file from filelocation vairable and displaying the first available blocks in that file */
                        printf("\n");
                    }
                    
                }
                break;

            case 6:

            if(fileLocation == 0)
            {
                printf("No File has been opened.\n");
            }
            
            if(directory[fileLocation].blockcount  == 24)
            {
                
                printf("\nBlockcount is full\n");
                break;
            }
            
            break;
            case 7:
            break;
            default: printf("Invalid Option\n"); break;

		}
	}
    
    while(choice < 7 && choice >=1);
    

	return 0;
}
