#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>


char ls(int path) {
    int path, e;
    bool Long = false;
    bool Recursive = false;
    bool Directories = false;
    bool inode = false;
    bool numerical = false;
    bool dot = false; 

    int d = opendir(path);
    while (e = readdir(d)) {
        создать структуру stat
        struct stat file_stat = {};
        
        использовать макрос S_ISREG(m)
        bool IsFile = isfile(e);    //проверка, является ли путь файлом
        bool IsKatalog = isdir(e);  //проверка, является ли путь каталогом

        if (Directories == true) 
        {
            if (IsKatalog == true) 
            {
                IsKatalog == false;
                IsFile == true;
            }
        }
        if (inode == true) 
        {
            int index_node
            print("%d\n", index_node);
        }
        if (numerical == true) 
        {

        }
    }
    closedir(d);
}

int main(int argc, char* argv[]) {
    #include <unistd.h>
    int ch;
    bool Long = false;
    bool Recursive = false;
    bool Directories = false;
    bool inode = false;
    bool numerical = false;
    bool dot = false;   
    while ((ch = getopt(argc, argv, "ldaRin")) != -1) {
        switch (ch) {
        case 'l':
            Long = true;
            break;
        case 'd': 
            Directories = true;
            break;     
        case 'a': 
            dot = true;
            break;   
        case 'R': 
            Recursive = true;
            break; 
        case 'i': 
            inode = true;
            break;
        case 'n': 
            numerical = true;
            break;
        case '?':
            break;
        }                
    }
    argc -= optind;
    argv += optind;

    for (int i=1; i <= argc; i++) {
        ls(argv[i]);
    }

}