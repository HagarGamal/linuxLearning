#include <unistd.h>
#define bufSize 100
#include <string.h>

int main()
{
  char currentPath[bufSize];
  char *ret = getcwd(currentPath, bufSize);
  if(ret == NULL)
  {
    char * failureMsg = "failure: check getcwd errors in man";
    int msgSize = strlen(failureMsg);
    write(1, failureMsg, msgSize);
    return -1;
  }
  else
  {
    write(1, currentPath, bufSize);
    write(1, "\n", 1);
  }
  return 0;
}
