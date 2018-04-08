/* write0.c
 *
 * purpose: send messages to another terminal
 *  method: open the other terminal for output then
 *		copy from stdin to that terminal
 *   shows: a terminal is just a file supporting regular i/o
 *	 usage: write0 ttyname
 */
#include <stdio.h>
#include <fcntl.h>

#define BUFSIZE 512


void main(int argc, char const *argv[])
{
	int fd;
	char buf[BUFSIZE];
	/* check args */
	if(argc != 2)
	{
		fprintf(stderr, "usage: write0 ttyname\n");
		exit(1);
	}
	/* open device */
	fd = open(argv[1], O_WRONLY);
	if(fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	/* loop until EOF on input*/
	while(fgets(buf, BUFSIZE, stdin) != EOF)
		if(write(fd, buf, strlen(buf)) == -1)
			break;
	close(fd);
}