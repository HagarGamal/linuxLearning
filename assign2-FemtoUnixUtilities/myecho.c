#include <string.h>
#include <unistd.h>
#include<stdio.h>

int main(int argc, char ** argv)
{
    for(int i = 1; i < argc; i++ )
    {
       write(1, argv[i], strlen(argv[i]));
       write(1, " ", 1);
    }
    write(1, "\n", 1);
    return 0;
}
