#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "x86.h"


int main(int argc, const char *argv[]) {

    int pid[NPROC];
    int count = atoi(argv[1]);
    for(int i = 0; i < count; ++i) 
    {
        pid[i] = fork();
        if(!pid[i]) 
        {
            int rand = ((i + 1) * 76235 + (count - i) * 42423);
            char *data = malloc(sizeof(char) * rand);
            memset(data, rand, sizeof(char) * rand);
            while(1);
        }
    }
    sleep(50);

    int size;
    struct proc_info *process = malloc(sizeof(struct proc_info) * NPROC);
    proc_dump(process, &size);
    for (int i = 0; i < size; ++i) 
        printf(1, "id: %d, memsize: %d\n", process[i].pid, process[i].memsize);
    
    for(int i = 0; i < count; ++i) 
    {
        kill(pid[i]);
        wait();
    }
    free(process);
    
    exit();
}
