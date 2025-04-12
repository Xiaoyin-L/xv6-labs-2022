#include "kernel/types.h"
#include "user/user.h"


#define RD 0
#define WR 1


int main(int argc, char const *argv[])
{
    char buf = 's';
    int p1[2],p2[2];
    pipe(p1);
    pipe(p2);
       
    if(argc != 1){
        fprintf(2,"Input Error");
        exit(-1);
    }

    int pid = fork();
    int exit_status = 0;
    
    if(pid < 0){
        //fork error
        close(p1[RD]);
        close(p1[WR]);
        close(p2[RD]);
        close(p2[WR]);
        fprintf(2,"Error fork\n");
        exit(-1);
    }
    else if(pid == 0){
        //child process
        close(p1[WR]);
        close(p2[RD]);

        if(read(p1[RD],&buf,sizeof(char)) != sizeof(char)){
            fprintf(2,"Error chile read\n");
            exit_status = -1;
        }
        else {
            fprintf(1, "%d: received ping\n", getpid());
        }

        if(write(p2[WR],&buf,sizeof(char)) != sizeof(char)){
            fprintf(2, "Error child write\n");
            exit_status = -1;
        }
        
        close(p2[WR]);
        close(p1[RD]);

        exit(exit_status);

    }
    else {
        //parent process
        close(p1[RD]);
        close(p2[WR]);

        if(write(p1[WR],&buf,sizeof(char)) != sizeof(char)){
            fprintf(2,"Error parent write\n");
            exit_status = -1;
        }

        wait(0);

        if(read(p2[RD],&buf,sizeof(char)) != sizeof(char)){
            fprintf(2,"Error parent read\n");
            exit_status = -1;
        }
        else {
            fprintf(1, "%d: received pong\n", getpid());
            exit_status = 0;
        }
        
        
        close(p1[WR]);
        close(p2[RD]);

        exit(exit_status);

    }


}