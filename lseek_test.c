#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main(int argc, char* argv[])
{
    if(argc!=2){
        printf("we need 2 arguments\n");
        exit(1);
    }

    int fd=open(argv[1],O_RDWR);
    if(fd==-1){
        printf("Open file failed ");
        perror(argv[1]);
        exit(1);
    }

    char buff_rd[20];
    char buff_wr[20];

    strcpy(buff_wr,"hello test");

    if(lseek(fd,20000,SEEK_END)==-1){
        printf("lseek failed");
        perror(argv[1]);
        exit(1);
    }

    if(read(fd,buff_rd,19)==-1){
        printf("Read file failed ");
        perror(argv[1]);
        exit(1);
    }
    buff_rd[19]=0;
    printf("buff_rd is %s\n",buff_rd);

    if(write(fd,buff_wr,strlen(buff_wr))==-1){
        printf("Write file failed ");
        perror(argv[1]);
        exit(1);
    }

    if(close(fd)==-1){
        printf("close file failed");
        perror(argv[1]);
        exit(1);
    }

    return 0;


}