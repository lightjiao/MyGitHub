#include <stdio.h>
#include <string.h>
#include <unistd.h>

int a2A(char buf[])
{
    int i = 0;
    while(1)
    {
        if( (buf[i] <= 'z') && (buf[i] >= 'a' ))
        {
            buf[i] -= 'a' - 'A';
        }
        else
        {
            break;
        }
        i++;
    }
    return 0;
}

int main()
{
    char buf[1024] = {0};
    while(1)
    {
        fgets(buf,1024,stdin);
        if(0 == strlen(buf))
        {
            break;
        }
        a2A(buf);
        write(STDOUT_FILENO,buf,strlen(buf));
        //printf("%s",buf);
        //fflush(stdout);
        buf[0] = 0;
    }
    return 0;
}
