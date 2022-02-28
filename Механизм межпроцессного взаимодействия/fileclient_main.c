#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "fileclient.h"
#define FIFO_FILE "/tmp/fifo_twoway"
int main()
{
    int fd;
    int stringlen;
    char readbuf[80];
    char stroka[80];
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
    fd = open(FIFO_FILE, O_RDWR);
    if (fd == -1)
    {
        perror("open failed on input file");
    }
    while (1)
    {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';
        if (strcmp(readbuf, "end") != 0)
        {
            write(fd, readbuf, strlen(readbuf));
            int answer = func_check(readbuf);
            if (answer == 1)
            {
                sleep(2);
                int read_bytes = read(fd, stroka, sizeof(stroka));
                printf("%s\n", stroka);
            }
        }
        else
        {
            write(fd, readbuf, strlen(readbuf));
            close(fd);
            break;
        }
    }
    return 0;
}