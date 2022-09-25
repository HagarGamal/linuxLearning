#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
int main(int argc, char ** argv)
{
  char buf[100];
  int fd1 = open(argv[1], O_RDONLY, 0644);
  int fd2 = open(argv[2], O_WRONLY| O_CREAT, 0644);

  char * errorOpenMsg = "can not open the file\n";
  if(fd1 == -1 || fd2 == -1)
  {
	write(1,errorOpenMsg, strlen(errorOpenMsg));
	return -1;
  }
  else
  {
    int count;
     while((count = read(fd1,buf, 100 )) !=0)
     {
       write(fd2, buf, count);
     }
  }
  close(fd1);
  close(fd2);
}

