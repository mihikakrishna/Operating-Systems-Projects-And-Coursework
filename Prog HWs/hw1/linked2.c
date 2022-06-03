#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main (int argc, char *argv[]) 
{
    struct stat fileStat1, fileStat2;
    int fd1, fd2 = 0;
    char buf[PATH_MAX];
    char buf1[PATH_MAX];
    char buf2[PATH_MAX];

    if ( ( fd1 = open (argv[1] , O_RDONLY) ) == -1){
        perror ( "open " );
        exit (1) ;
    }

    if ( ( fd2 = open (argv[2] , O_RDONLY) ) == -1){
        perror ( "open " );
        exit (1) ;
    }

    if((lstat(argv[1], &fileStat1)<0) || (lstat(argv[2], &fileStat2)<0)) return 1;
    
    if ((S_ISLNK(fileStat1.st_mode) || S_ISLNK(fileStat2.st_mode) && (realpath(argv[1],buf) == realpath(argv[2],buf))))
    {

        readlink(argv[2],buf1,sizeof(buf1)-1);
        printf("%s\n", buf1);
        if(S_ISLNK(fileStat1.st_mode) && buf1 == argv[2]){
            printf("%s is a symbolic link to %s\n", argv[1], argv[2]);
            return 0;
        }
        readlink(argv[1],buf2,sizeof(buf2)-1);
        if(S_ISLNK(fileStat1.st_mode) && buf2 == argv[1]){
            printf("%s is a symbolic link to %s\n", argv[2], argv[1]);
            return 0;
        }
        printf("These files are linked\n");
        return 0;
    }

    int inode1 = fileStat1.st_ino;
    int inode2 = fileStat2.st_ino;

    if (inode1 == inode2)
    {
        printf("These files are linked\n");
        return 0;
    }
    
    printf("The files are not linked\n");
    return 0;

}