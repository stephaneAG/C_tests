//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <unistd.h>

#include <sys/types.h>
#include <string.h>

 
int main (int argc, char *argv[] ) {
	
	char buf[20]; // reserve space for te buffer
	size_t nbytes;
	ssize_t bytes_written;
	int fd;

	fd = 1; // set the file descriptor to stdout
	
	strcpy(buf, "This is a test\n");
	nbytes = strlen(buf);


	bytes_written = write(fd, buf, nbytes);
	
		
	return 0;
}