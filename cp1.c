#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 256

int main(int argc, char *argv[])
{
    if(argc<3){
        printf("cp needs 2 arguments at least\n");
        exit(1);
    }

    if(!strcmp(argv[1],argv[2])){
        printf("%s and %s are the same file\n",argv[1],argv[2]);
        return 0;
    }

    int source,target;
    char buffer[BUFFER_SIZE];
    int actual_len;

    if((source=open(argv[1],O_RDONLY))==-1){
        printf("open file %s failed! ",argv[1]);
        perror(argv[1]);
        exit(1);
    }
    if((target=creat(argv[2],0644))==-1){
        printf("create file %s failed! ",argv[2]);
        perror(argv[2]);
        exit(1);
    }

    while((actual_len=read(source,buffer,BUFFER_SIZE))>0){
        if(write(target,buffer,actual_len)==-1){
            printf("write to target file %s failed! ",argv[2]);
            perror(argv[2]);
            close(target);
            close(source);
            exit(1);
        }
    }
    close(target);
    close(source);
    return 0;
}