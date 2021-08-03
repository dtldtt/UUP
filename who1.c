#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "utmplib.h"


#define SHOWHOST
#define UTMPNUM 6


int main()
{
    extern int errno;
    //char buffer[256];
    
    int size = sizeof(struct utmp)*UTMPNUM;
    struct utmp records[size];
    int ret;
    
    utmp_open(UTMP_FILE,O_RDONLY);
    
    while((ret=utmp_read(records,size)) == size) {
        int i;
        
        for(i=0;i<UTMPNUM;i++){
            if(records[i].ut_type!=USER_PROCESS) continue;
            struct tm *tmp_time = gmtime(&(records[i].ut_time));
            //printf("%-10.10s %-10.10s %-12s (%s)\n",records[i].ut_user,records[i].ut_line,ctime(&(records[i].ut_time))+4,records[i].ut_host);
            printf("%-10.10s %-10.10s %d-%02d-%02d %02d:%02d  (%s)\n",records[i].ut_user,records[i].ut_line,tmp_time->tm_year,tmp_time->tm_mon,tmp_time->tm_mday,tmp_time->tm_hour,tmp_time->tm_min,records[i].ut_host);
        }
    }

    if(ret>0){
        int i;
        for(i=0;i<ret/(sizeof(struct utmp));i++){
            if(records[i].ut_type!=USER_PROCESS) continue;
            printf("%-10.10s %-10.10s %-12.12s (%s)\n",records[i].ut_user,records[i].ut_line,ctime(&(records[i].ut_time))+4,records[i].ut_host);
        }
    }
    
    utmp_close();

    return 0;
    
}