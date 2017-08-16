#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<dirent.h>
#include<stdlib.h>


int get_file_num(const char *filepath)
{
    int total = 0;
    DIR *dir = opendir(filepath);
    if(NULL == dir)
    {
        perror("open dir error\n");
        exit(1);
    }
    //read
    char path[1024];
    struct dirent* ptr =NULL;
    while((ptr = readdir(dir))!=NULL)
    {
        if(strcmp(".",ptr->d_name)==0 || strcmp("..",ptr->d_name)==0)
        {
            continue;
        }
        if(ptr->d_type == DT_DIR)
        {
            sprintf(path,"%s/%s",filepath,ptr->d_name);
            get_file_num(path);
        }
        if(ptr->d_type == DT_REG)
        {
            total++;
        }
    }
    closedir(dir);
    return total;
}
int main(int argc,const char* argv[])
{
    if(argc < 2)
    {
        printf("pls enter ./a.out path\n");
        exit(1);
    }
    int total = get_file_num(argv[1]);
    printf("%s has regile number:%d\n",argv[1],total);
    return 0;
}
