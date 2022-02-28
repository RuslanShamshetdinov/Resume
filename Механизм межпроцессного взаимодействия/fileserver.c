#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define FIFO_FILE "/tmp/fifo_twoway"
int func_rashet(char *str, int len, char *str_1)
{
   int answer;
   int res_2;
   char operation[10] = "+-*/";
   char *pch = strtok(str, operation);
   int res_1 = atoi(pch);
   while (pch != NULL)
   {
      pch = strtok(NULL, operation);
      if (pch != NULL)
      {
         res_2 = atoi(pch);
      }
   }
   if (strstr(str_1, operation))
   {
      answer = res_1 + res_2;
   }
   if (strstr(str_1, "-"))
   {
      answer = res_1 - res_2;
   }
   if (strstr(str_1, "*"))
   {
      answer = res_1 * res_2;
   }
   if (strstr(str_1, "/"))
   {
      answer = res_1 / res_2;
   }
   return answer;
}
int main()
{
   int fd;
   char readbuf[80];
   char new_readbuf[80];
   int read_bytes;
   /* Create the FIFO if it does not exist */
   mkfifo(FIFO_FILE, S_IFIFO | 0640); // В текущем каталоге будет создан канал FIFO с правами доступа 0640.
   while (1)
   {
      fd = open(FIFO_FILE, O_RDWR);                    // Файл  открыт  только  для чтения
      read_bytes = read(fd, readbuf, sizeof(readbuf)); // Функция read делает попытку считать  sizeof(readbuf)  байт  из файла,  связанного с fd,  в буфер readbuf.
      readbuf[read_bytes] = '\0';
      strcpy(new_readbuf, readbuf);
      printf("%s\n", new_readbuf);
      int length = strlen(readbuf);
      printf("Received string: %s\n", readbuf);
      if (strcmp(readbuf, "end") == 0)
      {
         close(fd);
         break;
      }
      int answer = func_rashet(readbuf, length, new_readbuf);
      char stroka[100] = {0};
      sprintf(stroka, "%d", answer);
      write(fd, stroka, strlen(stroka)+1);
      sleep(2);
   }
   return 0;
}