#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!=2){
        printf("Error: we need 2 arguements\n");
        printf("E.g.: test_rd_wr cp1.c\n");
        exit(1);
    }
    int fd_rd1=open(argv[1],O_RDONLY);
    int fd_wr=open(argv[1],O_WRONLY);
    int fd_rd2=open(argv[1],O_RDONLY);

    if(fd_rd1==-1 || fd_wr==-1 || fd_rd2==-1){
        printf("Cannot open file ");
        perror(argv[1]);
        exit(1);
    }

    char buffer1[21],buffer2[21],buffer3[21];
    

    if(read(fd_rd1,buffer1,20)==-1){
        printf("Read file error ");
        perror(argv[1]);
        exit(1);
    }
    buffer1[20]=0;
    printf("buffer1 is %s\n",buffer1);

    strcpy(buffer2,"testing 123...");
    printf("buffer2 is %s\n",buffer2);

    if(write(fd_wr,buffer2,strlen(buffer2))==-1){
        printf("Write file failed ");
        perror(argv[1]);
        exit(1);
    }

    if(read(fd_rd2,buffer3,20)==-1){
        printf("Read file error ");
        perror(argv[1]);
        exit(1);
    }
    buffer3[20]=0;
    printf("buffer3 is %s\n",buffer3);

    if(close(fd_rd1)==-1 || close(fd_rd2)==-1 ||close(fd_wr)){
        printf("Close files failed");
        perror(argv[1]);
        exit(1);
    }

    return 0;

}