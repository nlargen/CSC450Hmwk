#include <stdio.h>
#include <stdlib.h>
 
void merge (int *a, int n, int m) 
{
    int i, j, k;
    int *x = malloc(n * sizeof (int));
    for (i = 0, j = m, k = 0; k < n; k++)
    {
        //thank you csc250 for teaching me these
        x[k] = j == n ? a[i++]  : i == m  ? a[j++] : a[j] < a[i] ? a[j++] :  a[i++];
    }
    
    for (i = 0; i < n; i++) 
    {
        a[i] = x[i];
    }
    free(x);
}
 
void sort (int *a, int n) 
{
    if (n < 2)
        return;
    //if the array is less than two why do anything 
    int m = n / 2;
    sort(a, m);
    sort(a + m, n - m);
    merge(a, n, m);
}
 
int main ()
{
    int a[10];
    int l; 
    for(l = 0; l < 10; l++)
    {
         a[l] = rand()%32; 
    }
    int n = sizeof a / sizeof a[0];
    int i;
    
    for (i = 0; i < n; i++)
    {
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    }
    sort(a, n);
    for (i = 0; i < n; i++)
    {
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    }   
    return 0;
}
