#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define Shmem 12
#define goatone 1 
#define goattwo 1 

int winner(char* shm);

int main(int argc, char** argv)
{
    char c; 
    int shmid, i; 
    key_t key; 
    char *shm, *s; 
    srand(time(NULL)); 
    
    key = 4567; 
    
    if ((shmid = shmget(key, Shmem, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget"); 
        return -1; 
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
    {
        perror("shmat"); 
        return -1; 
    }
    
    for(i = 0; i < 9; i++)
    {
        shm[i] = '-'; 
    }
    shm[10] = 'x'; 
    shm[11] = 'p'; 
    
    int pid = fork(); 
    
    if(pid != 0)
    {
        while (goatone == goattwo && shm[11] == 'p')
        {
            //parent 
            
            if(shm[10] == 'x')
            {
                while(goatone == goattwo)
                {
                    for(i = 0; i < 9; i++)
                    {
                        if(shm[i] == '-')
                        break; 
                    }
                    if(i == 9)
                    {
                        shm[11] = 'd'; 
                        break; 
                    }
                    
                    int r = rand() % 9; 
                    
                    if(shm[r] == '-')
                    {
                        printf("Gotta move x at: %d\n", r); 
                        shm[r] = 'x';
                        shm[10] = 'o'; 
                        break; 
                    }
                    //check for a winner 
                    
                    int win = winner(shm); 
                    if(win !=0)
                    {
                        if(win == 1)
                            printf("x is the weiner\n"); 
                        else 
                            printf("o is the weiner\n");
                            shm[11] = 'w'; 
                            break; 
                    }
                }
            }
        }
        if(shm[11] == 'd')
        {
             int win = winner(shm); 
                if(win == 1)
                {
                    printf(" x wins\n");
                }
                else if(win == 2)
                {
                    printf("o wins\n"); 
                }
                else 
                {
                    printf("Its a Draw!!\n"); 
                }
                    
        }
                for( i = 0; i < 9; i++)
                {
                    if(i == 3 || i == 6)
                    {
                        printf("\n");
                        printf("%c\n", shm[i]);
                    }
                }
                
    }
        else 
        {
                while(goatone == goattwo && shm[11] == 'p')
                {
                    if(shm[10] == 'o')
                    {
                        while(goatone == goattwo)
                        {
                            for(i = 0; i < 9; i++)
                            {
                                if(shm[i] == '-')
                                {
                                    break; 
                                }
                            }
                            // if board is complete end game 
                            if(i == 9)
                            {
                                shm[11] == 'd'; 
                                break; 
                                
                            }
                            
                            int r = rand() % 9; 
                            //moving 
                            if(shm[r] == '-')
                            {
                                printf("Move o at: %d\n" , r);
                                shm[r] = 'o'; 
                                shm[10] = 'x'; 
                                break; 
                            }
                            
                            //check again to see if we have a winner 
                            int win = winner(shm); 
                            if(win != 0)
                            {
                                if(win == 1)
                                {
                                    printf("x wins\n");
                                }    
                                else 
                                {
                                    printf("o wins\n");
                                    shm[11] = 'w'; 
                                    break;
                                }
                            }
                        }
                    }
                }
                exit(1);
            }
            return 0; 
        }

int isxoriso(char x)
{
    if(x =='x')
    {
        return 0; 
    }
    else if (x == 'o')
    {
        return 1; 
    }
    else
    {
        return -1; 
    }
}
int winner(char* shm)
{
    if(shm[0] == shm[1] && shm[1] == shm[2] && shm[2] != '-')
    {
        return 1 + isxoriso(shm[0]); 
    }
    if(shm[3] == shm[4] && shm[4] == shm[5] && shm[5] != '-')
    {
        return 1 + isxoriso(shm[3]); 
    }
    if(shm[6] == shm[7] && shm[7] == shm[8] && shm[8] != '-')
    {
        return 1 + isxoriso(shm[6]); 
    }
    if(shm[0] == shm[3] && shm[3] == shm[6] && shm[6] != '-')
    {
        return 1 + isxoriso(shm[0]); 
    }
    if(shm[1] == shm[4] && shm[4] == shm[7] && shm[7] != '-')
    {
        return 1 + isxoriso(shm[1]); 
    }
    if(shm[2] == shm[5] && shm[5] == shm[8] && shm[8] != '-')
    {
        return 1 + isxoriso(shm[2]); 
    }
    if(shm[0] == shm[4] && shm[4] == shm[8] && shm[8] != '-')
    {
        return 1 + isxoriso(shm[0]); 
    }
    if(shm[2] == shm[4] && shm[4] == shm[6] && shm[6] != '-')
    {
        return 1 + isxoriso(shm[2]); 
    }
    return 0; 
}
