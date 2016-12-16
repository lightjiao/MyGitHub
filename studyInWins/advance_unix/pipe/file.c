#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


int showallfile(char *path)
{
    char newpath[1024];
    struct dirent *pent;
    struct stat sta;
    DIR *pdir;
    
    if(path[strlen(path)-1] == '/')
    {
        path[strlen(path)-1] = 0;
    }

    pdir = opendir(path);

    while(1)
    {
        pent = readdir(pdir);
        if(NULL == pent)
        {
            break;
        }
        if(0 == strcmp(pent->d_name,"."))
        {
            printf("%s\n",pent->d_name);
            continue;
        }
        if(0 == strcmp(pent->d_name,".."))
        {
            printf("%s\n",pent->d_name);
            continue;
        }
        strcpy(newpath,path);
        strcat(newpath,"/");
        strcat(newpath,pent->d_name);

        lstat(newpath,&sta);
        
        if(S_ISDIR(sta.st_mode))
        {
            printf("%s\n",pent->d_name);
            showallfile(newpath);
        }
        else
        {
            printf("%s\n",pent->d_name);
        }
    }
    return ;
}

int main(int argc,char **argv)
{   
    struct stat stabuf;
    DIR *pdir;
    struct dirent *pent;
    
    stat(argv[1],&stabuf);

    if(argc < 2)
    {
        return -1;
    }
    
    if(S_ISREG(stabuf.st_mode))
    {
        printf("%s is a regular file!\n",argv[1]);
    }
    else if(S_ISDIR(stabuf.st_mode))
    {
        showallfile(argv[1]);
    }
    else if(S_ISCHR(stabuf.st_mode))
    {
        printf("%s is a character file!\n",argv[1]);
    }

    return 0;
}


