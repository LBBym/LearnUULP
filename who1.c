/*
 * who1.c - a first version of the who program
 * 				open, read UTMP file, and show results
 */
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SHOWHOST	//include remote machine on output

void show_info(struct utmp *);
void show_time(long);


int main(int argc, char const *argv[])
{
	struct utmp    current_record;  //read info into here
	int            utmpfd;          //read from this descriptor
	int            reclen = sizeof(current_record);

	if ( (utmpfd = open(UTMP_FILE, O_RDONLY) ) == -1 )
	{
		perror(UTMP_FILE);			//UTMP_FILE is in utmp.h
		exit(1);
	}

	while( read(utmpfd, &current_record, reclen) == reclen )
	{
		show_info(&current_record);
	}
	close(utmpfd);
	return 0;
}


/*
 * show_info()
 * displays contents of the utmp struct in human readable form
 * * note * these sizes should not be hardwired
 */
show_info(struct utmp * utbufp)
{
	if( utbufp->ut_type != USER_PROCESS) return; //user only

	printf("% -8.8s", utbufp->ut_user);
	printf(" ");
	printf("% -8.8s", utbufp->ut_line);
	printf(" ");
	show_time(utbufp->ut_time);
# ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void show_time(long timeval)
/*
 * diapalys time in a formate fit for human consumption
 * uses ctime to build a string then picks parts out of it
 * Note: %12.12s prints a string 12 chars wide and LIMITS
 * it to 12 chars.
 */
{
	char * cp; 		//to hold the address of time
	cp = ctime(&timeval); 	//convert time to string
	printf("%12.12s", cp + 4 );
}