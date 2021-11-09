#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if(argc == 1)
    {
	    fprintf(stderr, "El programa necesita un nombre de directorio como argumento\n");
	    return -1;
    }
    
    DIR* directorio = opendir(argv[1]);

    if(directorio == NULL)
    {
        perror("Error en la apertura del directorio: ");
        return -1;
    }

    struct dirent* entrada;
    struct stat buf;
    unsigned int size = 0;

    while((entrada = readdir(directorio)) != NULL)
    {
        char path[PATH_MAX];
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path, entrada->d_name);

        if(lstat(path, &buf) == -1)
        {
            perror("Error en stat: ");
            return -1;
        }

        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) 
        {
            continue;
        }

        if(S_ISDIR(buf.st_mode))
        {
            printf("%s/\n", entrada->d_name);
        }
        else if(S_ISREG(buf.st_mode))
        {
            if(S_IXUSR & buf.st_mode)
            {
                printf("%s*\n", entrada->d_name);
            }
            else
            {
                printf("%s\n", entrada->d_name);
            }
            size += buf.st_size;
        }
        else if(S_ISLNK(buf.st_mode))
        { 
            char* sym = malloc(PATH_MAX);

            if(readlink(path, sym, PATH_MAX) == -1)
            {
                perror("Error en symlink: ");
                return -1;
            }

            printf("%s -> %s\n", entrada->d_name, sym);
            size += buf.st_size;
        }
    }
    
    printf("Total size of files inside directory: %i KB\n", size/1024);

    return 0;
} 
