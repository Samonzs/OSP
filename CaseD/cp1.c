/* cp1.c -- simple copy program example
 * Ali Salman 20056663@student.westernsydney.edu.au
 * COMP 30015 Operating Systems Programming
 * Practical Case Study D
 * This sample file was adapted from:
 * Molay, B. (2003). cp1.c. In Understanding unix/linux programming.
 * Source Code, Prentice Hall.
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libgen.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644

void oops(char *, char *);

int main(int ac, char *av[])
{
	struct stat in, out;
	int in_fd;
	int out_fd;
	int n_chars;
	char buf[BUFFERSIZE]; 
	
	char * src_path, dst_path;


	if (ac != 3)
	{
		fprintf(stderr, "usage: %s source destination\n", *av);
		exit(1);
	}

	if ((in_fd = open(av[1], O_RDONLY)) == -1)
	{
		oops("Cannot open ", av[1]);
	}

	if ((out_fd = creat(av[2], COPYMODE)) == -1) 
	{
		oops("Cannot creat", av[2]);
	}

	// First question, validating same file input
	if(stat(av[1], &in) > 0)
	{
		oops("error", av[1]);
	}

	if(stat(av[2], &out) > 0)
	{
		oops("error", av[2]);
	}	

	dev_t dev1 = in.st_dev;
	dev_t dev2 = out.st_dev;

	ino_t inode1 = in.st_ino;
	ino_t inode2 = out.st_ino;

	if(inode1 == inode2 && dev1 == dev2) 
	{
		printf("Cannot copy same name files\n");
		exit(1);
	}
	// second question, copying file permissions to destination file
	if(chmod(av[2], in.st_mode) == -1)
	{
		oops("permission copy error", av[2]);	
	}

	while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
	{
		if (write(out_fd, buf, n_chars) != n_chars)
		{
			oops("Write error to ", av[2]);
		}
	}

	if (n_chars == -1)
	{
		oops("Read error from ", av[1]);
	}

	if (close(in_fd) == -1 || close(out_fd) == -1)
	{
		oops("Error closing files", "");
	}

	return 0;
}

void oops(char *s1, char *s2)
{
	fprintf(stderr, "Error: %s ",  s1);
	perror(s2);
	exit(1);
}