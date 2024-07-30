#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <uuid/uuid.h>

int main(){
    uid_t user_id_effective = getuid();
    gid_t group_id_effective = getgid();
    struct group * gr_gid = getgrent();
    //struct group * gr_nam = getgrnam(const char *name);
    //struct group * gr_git = getgrgid(gid_t gid);
     

    gid_t grouplist[100];

    int num_groups =  getgroups(100, grouplist);

    for (int i=0; i<100; i++) {
        printf("%p/n", getgroups);
    }
    
}








 

