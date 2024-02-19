#include <stdio.h>
#include "get_next_line.h"
#include <fcntl.h>

void leak(){
   system("leaks p");
}
int main(void) {
   atexit(leak);
   char *buffer;
   int fd = open("file.txt", O_RDONLY);
   buffer = get_next_line(fd);
   printf("%s\n", buffer);
   buffer = get_next_line(fd);
   printf("%s", buffer);
   close(fd);
   return (0);

}