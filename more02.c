#include <stdio.h>
#include <stdlib.h>
#define PAGELEN 24
#define LINELEN 512
void do_more(FILE * );
int see_more(FILE * );


int main(int ac, char *av[])
{
	FILE * fp;
	if (ac == 1)
	{
		do_more(stdin);
	}
	else
		while(--ac)
			if ((fp = fopen(*++av, "r")) != NULL)
			{
				do_more(fp);
				fclose(fp);
			}
			else
				exit(1);
	return 0;
}


void do_more(FILE *fp)
/*
 * read PAGELEN lines,then call see_more() for further instruction
 */
{
	char line[LINELEN];
	int num_of_lines = 0;
	int see_more(FILE *), reply;
	FILE * fp_tty;
	fp_tty = fopen("/dev/tty", "r");
	if (fp_tty == NULL)
	{
		exit(1);
	}
	while(fgets(line, LINELEN, fp)){	//more input
		if (num_of_lines == PAGELEN){	//full screen?
			reply = see_more(fp_tty);			//y: ask user
			if (reply == 0)				//n: done
			{
				break;
			}
			num_of_lines -=reply;		//reset count
		}
		if (fputs(line, stdout) == EOF)	//show line
		{
			exit(1);					//or die
		}
		num_of_lines++;					//count it
	}
}


int see_more(FILE * cmd)
/*
 * print message, wait for response, return # of lines to advance
 * q means no, space means yes, CR means one line
 */
{
	int c;
	printf("\033[7m more?\033[m");		//reverse on a vt100
	while((c = getc(cmd)) != EOF)		//get response
	{
		if (c == 'q')
		{
			return 0;
		}
		if (c == ' ')
		{
			return PAGELEN;
		}
		if (c == '\n')
		{
			return 1;
		}
	}
	return 0;
}