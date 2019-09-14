/*************************************************************************
	> File Name: wirte_pi_log.c
	> Author: 
	> Mail: 
	> Created Time: 2019年03月05日 星期二 18时58分36秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#define FILE_MAX_SIZE (1024 * 1024)

void get_local_time(char *buffer) {
    time_t rawime;
    struct tm* timeinfo;

    time(&rawime);
    timeinfo = localtime(&rawime);
    sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", (timeinfo->tm_year+1900), timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}




long get_file_size(char *filename) {
    long length = 0;
    FILE *fp = NULL;

    fp = fopen(filename, "rb");
    if(fp != NULL) {
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
    }
    if(fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    return length;
}


void write_log_file(char *filename, long max_size, char *buffer,unsigned buf_size) {
    if(filename != NULL && buffer != NULL) {
        long length = get_file_size(filename);
        if(length > max_size) {
            unlink(filename);
        }
        
        FILE *fp;
        fp = fopen(filename, "at+");
        if(fp != NULL) {
            char now[32];
            memset(now, 0, sizeof(now));
            get_local_time(now);
            fwrite(now, strlen(now) + 1, 1, fp);
            fwrite(buffer, buf_size, 1, fp);

            fclose(fp);
            fp = NULL;
        }
    }
}



int main() {
    int i;
    for(i = 0; i < 10; i++) {
        char buffer[32];
        memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "=====>%d\n", i);
        write_log_file("log.txt", FILE_MAX_SIZE, buffer, strlen(buffer));
        sleep(1);
    }
    return 0;
}
