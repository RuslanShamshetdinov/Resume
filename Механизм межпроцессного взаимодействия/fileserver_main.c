#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "fileserver.h"
#define FIFO_FILE "/tmp/fifo_twoway"
int main()
{
    int fd;
    char readbuf[80];
    char new_readbuf[80];
    int read_bytes;
    mkfifo(FIFO_FILE, S_IFIFO | 0640);
    while (1)
    {
        fd = open(FIFO_FILE, O_RDWR);           
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';
        strcpy(new_readbuf, readbuf);
        int length = strlen(readbuf);
        printf("Received string: %s\n", readbuf);
        if (strcmp(readbuf, "end") == 0)
        {
            close(fd);
            break;
        }
        int flag = func_check(readbuf);
        if (flag == 1)
        {
            int answer = func_rashet(readbuf, length, new_readbuf);
            char stroka[100] = {0};
            sprintf(stroka, "%d", answer);
            write(fd, stroka, strlen(stroka) + 1);
            sleep(2);
        }
    }
    return 0;
}