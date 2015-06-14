#include <stdio.h>
#include  <fcntl.h>
int  write(  int  handle,  void  *buffer,  int  nbyte  );
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
// exemple form Wiki
size_t write(int fd, const void *buf, size_t nbytes);

