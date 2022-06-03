#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h> 

/* Group Members: Adil Bukhari, Niharika Misal, Mihika Krishna*/

int main (int argc, char *argv[]) 
{
    struct stat fileStat1, fileStat2;
    char buf1[PATH_MAX];
    char buf2[PATH_MAX];
    char buf3[PATH_MAX];
    char buf4[PATH_MAX];
    
    if (argc < 3)
    {
        printf("Usage: ./linked file1 file2\n");
        return 0;
    }

    if (open(argv[1], O_RDONLY) == -1)
    {
        perror (argv[1]);
        exit (1);
    }

    if (open(argv[2], O_RDONLY) == -1)
    {
        perror (argv[2]);
        exit (1);
    }

    if((lstat(argv[1], &fileStat1)<0) || (lstat(argv[2], &fileStat2)<0)) return 1;

    if (S_ISLNK(fileStat1.st_mode) || S_ISLNK(fileStat2.st_mode))
    {
        realpath(argv[1],buf1);
        realpath(argv[2],buf2);
        readlink(argv[1],buf3,PATH_MAX);
        readlink(argv[2],buf4,PATH_MAX);

        if (strcmp(buf1,buf2) == 0){
            if(strcmp(buf3,argv[2]) == 0){
                if (S_ISLNK(fileStat1.st_mode) && S_ISLNK(fileStat2.st_mode)){
                    printf("These files are linked.\n");
                    return 0;
                }
                printf("%s is a symbolic link to %s\n", argv[1], argv[2]);
                return 0;
            }
            if(strcmp(buf4,argv[1]) == 0){
                if (S_ISLNK(fileStat1.st_mode) && S_ISLNK(fileStat2.st_mode)){
                    printf("These files are linked.\n");
                    return 0;
                }
                printf("%s is a symbolic link to %s\n", argv[2], argv[1]);
                return 0;
            }
            if (strcmp(buf3,buf4) != 0){
                printf("These files are linked.\n");
                return 0;
            }
        }
    }

    realpath(argv[1],buf1);
    realpath(argv[2],buf2);

    if((lstat(buf1, &fileStat1)<0) || (lstat(buf2, &fileStat2)<0)) return 1;

    if (fileStat1.st_ino == fileStat2.st_ino)
    {
        printf("These files are linked.\n");
        return 0;
    }

    printf("The files are not linked.\n");
    return 0;

}
