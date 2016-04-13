#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv)
{
    srand(time(NULL));
    int num;
    int i;
    int nums[10];
    for(i = 0; i < 10; i++)
    {
        nums[i] = rand()%2;
        //printf("%d\n", num);
    }
    
    for(i = 0; i < 10; i++)
    {
        printf(" %d\n", nums[i]);
    }
    
    /*
    printf("About to Fork...\n");
    
    pid_t pid = fork();
    
    i = 0;
    if(pid == 0)
    {
        for(; i < 100; i++)
        {
            printf("parent: %d\n", i);
        }
    }
    else
    {
        for(; i < 100; i++)
        {
            printf("child (%d): %d\n", pid, i);
        }
    }
    */
}