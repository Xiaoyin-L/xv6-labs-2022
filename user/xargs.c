#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define MSSIZE 16

int main(int argc, char *argv[])
{
    sleep(10);
    
    //Q1 read first argument output
    char buf[MSSIZE];
    read(0,&buf,MSSIZE);
    //printf("first input: %c\n%c",buf[0],buf[1]);


    int xargc=0; // run new argument
    char *xargv[MAXARG];
    for(int i=1;i<argc;i++){
        //printf("%d %s\n",i,argv[i]);
        xargv[xargc++] = argv[i];
        //printf("%d\n",xargc);
    }
    
    
    char *p = buf;
    for(int i = 0;i<MSSIZE;i++){
        //printf("%c\n",buf[i]);
        if(buf[i] == '\n'){
            int pid = fork();
            if(pid == 0){
                buf[i] = 0;
                xargv[xargc] = p;//combine first and second argument
                xargc++;
                xargv[xargc] = 0;
                xargc++;

                exec(xargv[0],xargv);//Q3 establish exec() run second argument 

                exit(0);
            }
            else {
                p = &buf[i+1];
                wait(0);
            }
        }
    }
      
    exit(0);
}

