#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int utmpfp;

void utmp_open(char* ,int);
int utmp_read( struct utmp*, int);
int utmp_lseek(int offset,int base);
int utmp_write(struct utmp*,int);
void utmp_close();