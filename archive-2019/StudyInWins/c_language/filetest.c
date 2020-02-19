#include <stdio.h>
#include "string.c"

void read_file(char *a)
{
    char buf[1024];
    FILE *fp;
    fp = fopen(a,"r");
    if(NULL == fp)
    {
        printf("file not exit!\n");
        return ;
    }
    while(1)
    {
        fgets(buf,1024,fp);
        if(feof(fp))
        {
            break;
        }
        printf(buf);
    }
    fclose(fp);
    return ;
}

void write_file(char *a)
{
    char buf[1024];
    FILE *fp;
    fp = fopen(a,"w+");
    if(NULL == fp)
    {
        printf("cannot open file!\n");
        return ;
    }
    while(1)
    {
        fgets(buf,1024,stdin);
        if(mystrcmp("quit\n",buf) == 0)
        {
            break;
        }
        fputs(buf,fp);
    }
    fclose(fp);
    return;
}

void copy_file(char *s,char *d)
{
    char buf[1024];
    FILE *fd,*fs;

    fs = fopen(s,"r");
    if(NULL == fs)
    {
        printf("cannot open file %sto read.\n",s);
        return ;
    }
    fd = fopen(d,"w+");
    if(NULL == fd)
    {
        printf("cannot open  file %sto write.\n",d);
        fclose(fs);
        return ;
    }
    
    while(1)
    {
        fgets(buf,1024,fs);
        if(feof(fs))
        {
            break;
        }
        fputs(buf,fd);
    }
    fclose(fs);
    fclose(fd);
    return ;
    
}

void encry(char *a,int n,char *b)
{
    int i,l;
    l=strl(b);
    for(i=0;i<n;i++)
    {
        a[i] ^= b[i%l];
    }
    return ;
}

void sec_copyfile(char *s,char *d)
{
    char buf[1024],code[1024];
    int n;
    FILE *fs,*fd;
    
    fs = fopen(s,"r");
    if(NULL == fs)
    {
        printf("cannot open file %sto read.\n",s);
        return ;
    }
    fd = fopen(d,"w+");
    if(NULL == fd)
    {
        printf("cannot open  file %sto write.\n",d);
        fclose(fs);
        return ;
    }
    
    printf("please input the security code:\n");
    fgets(code,1024,stdin);
    code[strl(code)-1] = 0;

    while(1)
    {
        n = fread(buf,1,1024,fs);
        if(0 == n)
        {
            break;
        }
        encry(buf,n,code);
        fwrite(buf,1,n,fd);
    }
    fclose(fs);
    fclose(fd);
    return ;

}

int main(int argc,char **argv)
{
    if(argc < 3)
    {
        printf("too little !\n");
        return;
    }
    sec_copyfile(argv[1],argv[2]);
    
    return ;
}

