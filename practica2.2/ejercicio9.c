#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
	fprintf(stderr, "El programa necesita un nombre de fichero como argumento\n");
	return -1;
    }

    char* archivo = argv[1];
    struct stat statbuf;

    int r = stat(archivo, &statbuf);

    if(r == -1)
    {
	perror("Error de stat: ");
	return -1;
    }
    
    unsigned int major = major(statbuf.st_dev);
    unsigned int minor = minor(statbuf.st_dev);
    printf("\nMajor number: %i\n"
	    "Minor number: %i\n"
	    "Inode number: %ld\n",
	    major, minor, statbuf.st_ino);
    
    //Para sacar el file type de st_mode
    printf("File type: ");
    switch (statbuf.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
    }

    printf("Last modification time: %s\n", ctime(&statbuf.st_mtime));

    return 0;
} 
