#include <sys/types.h>
#include <string.h>
#include "utmplib.h"


#define BUFNUM 10

int utmp_logout(char *);

int main()
{
    utmp_logout("pts/2");
    return 0;
}

int utmp_logout(char *cur_line)
{
    utmp_open(UTMP_FILE,O_RDWR);
    int size=sizeof(struct utmp) * BUFNUM,read_size;
    char  buffer[size];
    read_size=utmp_read((struct utmp*)buffer,size);
    
    int i;
    for(i=0;i<read_size/sizeof(struct utmp);i++){
        struct utmp* current=(struct utmp*)&buffer[i*(int)sizeof(struct utmp)];
        if(strcmp(current->ut_line,cur_line)==0){
            if(utmp_lseek(-sizeof(struct utmp),SEEK_CUR)==-1){
                printf("Lseek error:");
                perror(UTMP_FILE);
                exit(1);
            }
            current->ut_type=DEAD_PROCESS;
            if(time(&(current->ut_time))==-1){
                printf("set time error:");
                exit(1);
            }
            strcpy(current->ut_line,"");
            strcpy(current->ut_user,"");
            
            if(utmp_write(current,sizeof(struct utmp))==-1){
                printf("write file error:");
                perror(UTMP_FILE);
                exit(1);
            }
            break;
        }
    }

    utmp_close();

}