#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

bool in (char* s,char ** array,int len) { 
    int i;
    for(i = 0; i < len; ++i)
    {
        if(strcmp(array[i], s) == 0)
        {
            return true;
        }
    }
    return false;
}
int main (int argc, char *argv[]) {
    printf("You have entered %d arguments:\n", argc);
    if (argc < 1) return -1;
    char  *cmds = (char *)malloc(sizeof(char) *sizeof(argv[0]));

    if (cmds==NULL) {
        printf("Allocation Failed");
        exit(0);
    }
    char  * cmds_predfined[]={"mkdir","cd"};
    for (int i =1 ; i < argc; i++) {
        if (sizeof(argv[i]) > sizeof(cmds)) {
            int len=strlen(argv[i]);
            cmds = (char *)realloc(cmds, len * sizeof(char));
        }
        if (i == argc-1 || in(argv[i],cmds_predfined,2) == true) {
            sprintf(cmds + strlen(cmds), "%s ", argv[i]);
        }else{
            sprintf(cmds + strlen(cmds), "%s && ", argv[i]);
        }
               
    }
    system(cmds);
    printf("\n%s\n",cmds);
    free(cmds);
    return 0;
}
// pwd give the path of dir 