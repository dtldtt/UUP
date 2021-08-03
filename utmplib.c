#include "utmplib.h"

void utmp_open(char* file,int flag)
{
    if((utmpfp=open(file,flag))==-1){
        printf("open file %s failed! ",file);
        perror(file);
        exit(1);
    }
    
}

int utmp_read( struct utmp* buffer, int size)
{
    
    int read_size;
    if((read_size=read(utmpfp,buffer,size))==-1){
        printf("read file failed\n");
        exit(1);
    }
    
    return read_size;
}

int utmp_lseek(int offset,int base)
{
    return lseek(utmpfp,offset,base);
}

int utmp_write(struct utmp* buffer,int size)
{
    return write(utmpfp,buffer,size);
}

void utmp_close()
{
    if(close(utmpfp)==-1){
        printf("Close file error\n");
        exit(1);
    }
}

