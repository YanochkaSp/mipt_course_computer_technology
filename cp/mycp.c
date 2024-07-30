#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

void cp(size_t in, size_t trg_fd){
    char buf[4097];
    size_t nbyte = 4096;
    ssize_t num_bytes = read(in, buf, nbyte);
    buf[4096] = 0;
    while (num_bytes == 4096) {
        //fprintf(trg_fd, "%s", buf);
        write(trg_fd, buf, num_bytes);
        num_bytes = read(in, buf, nbyte);
    }
    //fprintf(trg_fd, "%s", buf);
    write(trg_fd, buf, num_bytes);
    
}

int main(int argc, char* argv[]) {
    char rez = 0;
    bool f = false;
    bool v = false;
    bool i = false;
    int otkuda = 0;
    int kuda = 0;
    char answer[1000];

    while (optind < argc){
        if ((rez = getopt(argc, argv,"fvi"))!=-1) {
            
            switch (rez) {
            case 'f':
                f = true;
                break;
            case 'v': 
                v = true;
                break;     
            case 'i': 
                i = true;
                break;   
            case '?':
                break;
            }
        }else {
        //printf("%s ", argv[optind]);
        if (otkuda != 0) {
            kuda = optind;
        }else {
            otkuda = optind;
        }
      
        optind++;  // Skip to the next argument
        }
    }
    //printf("%s %s", argv[kuda], argv[otkuda]);

    if (kuda - otkuda > 1) {
        while (otkuda != kuda){
            char name_with_folder[1000]; 
            name_with_folder[0] = 0;
            strcat(name_with_folder, argv[kuda]);
            strcat(name_with_folder, "/");
            strcat(name_with_folder, argv[otkuda]);
            // access(name_with_folder, F_OK);
            // printf("%d\n", access(name_with_folder, F_OK));
            if (access(argv[otkuda], F_OK) == -1){
                printf("File %s not exist\n", argv[otkuda]);
                otkuda += 1;
                continue;
            }
            if (!access(name_with_folder, F_OK) && i == true) {
                printf("Do you want to rewrite %s (Any word or no) ?", argv[otkuda]);
                scanf("%s", answer);
                if (!strcmp(answer, "no")) {
                    otkuda += 1;
                    continue;
                }
            }
                

            size_t src_fd = open(argv[otkuda], O_RDONLY);
            size_t trg_fd = open(name_with_folder, O_WRONLY | O_CREAT | O_TRUNC, 0600); 

            cp(src_fd, trg_fd);
            close(src_fd);
            close(trg_fd); 
            
            if (v == true) {
                printf("File %s was copied in %s\n", argv[otkuda], argv[kuda]);
            }
            otkuda += 1;
        }
    }
    else {
        if (access(argv[otkuda], F_OK) == -1){
            printf("File %s not exist\n", argv[otkuda]);
            return 1;
        }
        size_t src_fd = open(argv[otkuda], O_RDONLY);
        size_t trg_fd = open(argv[kuda], O_WRONLY | O_CREAT | O_TRUNC, 0600); 

        cp(src_fd, trg_fd);
        close(src_fd);
        close(trg_fd);   
    }  
}