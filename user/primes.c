#include "kernel/types.h"
#include "user/user.h"

#define WR 1
#define RD 0


void child_recursion(int p_left[2]){
    int num,data;
    if(read(p_left[RD],&num,sizeof(int)) == sizeof(int)){
        fprintf(2,"prime %d\n",num);
        
        close(p_left[WR]);

        int p_right[2];
        pipe(p_right);

        while(read(p_left[RD],&data,sizeof(int)) == sizeof(int)){
            if(data % num != 0){
                write(p_right[WR],&data,sizeof(int));
            }
        }
        close(p_left[RD]);
        close(p_right[WR]);

        if(fork() == 0){
            

            child_recursion(p_right);
        }
        else {

            close(p_right[RD]);
            
         
            wait((int*)0);
        }
    }
    exit(0);
}


int main(int argc, char const *argv[])
{
    int p_left[2];
    pipe(p_left);

    
    for(int i=2;i<35;i++){
        write(p_left[WR],&i,sizeof(int));
    }

    if(fork() == 0){
        child_recursion(p_left);
    }
    else {
        close(p_left[RD]);
        close(p_left[WR]);
        wait(0);
        exit(0);
    }
    exit(0);
}