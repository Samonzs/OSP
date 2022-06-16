/* sample-code.c
 * Dr Evan Crawford (e.crawford@westernsydney.edu.au)
 * COMP 30015 Operating Systems Programming
 * Practical Case Study B
 * This is the sample file
 * 
 * Ali Salman 20056663
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

#define MAX_LINE 4096
#define MAX_WORDS MAX_LINE/2
/* a line can have at most MAX_LINE/2 words, why? */

void tokenize(char *line, char **words, int *nwords);
/* break line into words separated by whitespace, placing them in the
   array words, and setting the count to nwords */
int find_and_execute(char *line, char **words, int *nwords)
{
        
        pid_t child = fork();
        int status;


                if (child == -1)
                {
                        perror("fork error");
                        exit(1);
                }
                else if (child == 0) // child process
                {      
                        execvp(line, words);
                        perror(line);
                        exit(1); 
                }
                else // parent process
                {       
                        wait(&status);
                        printf("Exit Status: ");
                        printf("%d\n", status);
                }
                
        return 1;
}



int main()
{       
        char line[MAX_LINE], *words[MAX_WORDS], message[MAX_LINE];
        int stop=0,nwords=0;


        while(1)

        {       
                printf("OSP CLI $");
                
                if (strcmp(line,"exit") == 0 || (NULL == fgets(line , MAX_LINE, stdin)))
                {
                        printf("\nExitting Program...\n");
                        exit(0);
                }

    
                tokenize(line,words,&nwords);
                
                if(strcmp(line, "cd") == 0)
                {
                        chdir(words[1]);
                }
                else
                {
                        find_and_execute(line,words,&nwords);
                }

        }

        return 0;

}

/* this function works, it is up to you to work out why! */
void tokenize(char *line, char **words, int *nwords)
{
        // this function basically splits the characters by every space, \t or \n, and then counting the 
        // amount of words we have stored in our variable and making sure it doesnt exceed MAXWORDS hence the nwords < MAX_WORDS
        // and the words seperate in the loop until NULL is reached (end of string characters) and then add to the counter so that we count how many times we are looping or storing words in the pointer variable.
        *nwords=1;

        //seperate the characters by " \t\n"
        for(words[0]=strtok(line," \t\n");

        // keep looping whilst not exceeding maximum words
            (*nwords<MAX_WORDS)

            &&
        // iterates through the next characters untill the end has reached hence the NULL
            (words[*nwords]=strtok(NULL, " \t\n"));
        
        //a counter to the variable so it updates the count
            *nwords=*nwords+1
           ); /* empty body */
        return;
}