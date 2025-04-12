#include "kernel/types.h"
#include "user/user.h"

//argv = {"program","argv"}


int main(int argc, char const *argv[] ) //argv = {"sleep","cahr"}
{
    if(argc != 2){//parameter error
        fprintf(2,"Error usage: sleep <time>\n");
        exit(-1);
    }
    else {
        if(sleep(atoi(argv[1])) < 0){
            fprintf(2,"Error usage: sleep <time>\n");
            exit(-1);
        }
        else {
            exit(0);
        }
        
    }
}