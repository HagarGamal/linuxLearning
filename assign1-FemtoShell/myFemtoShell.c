#include"stdio.h"
#include"string.h"


int main()
{ 
  char input[50];
  printf("Enter your cmd:  ");
  scanf("%s", input);
  while(strcmp(input, "exit"))
  {
    if(strlen(input) > 20)
    {
	printf("max length exceeded: up to 50 char\n");
	return 0;
    }
    printf("You said:  %s\n Enter your cmd: ", input);
    scanf("%s", input);
  }
  printf("Good Bye\n");

  return 0;
}
