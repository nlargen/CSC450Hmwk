#include <stdio.h>


void mergesort(int arr[], int first, int second);

void main(void)
{
    int array[10]; 
    int i = 0; 
    for(; i< 10; i++)
    {
        array[i] = rand()%10; 
        printf("%d", array[i]);
    }
    //printf("Enter number of elements to be sorted: ");
    //scanf(%d, &n); 
    //printf("\nEnter the elements to be sorted: \n");
    mergesort(array, 0, 10); 
}

void mergesort(int arr[], int first, int second)
{
    int i = 0; 
    int length = second - first +1; 
    int pivot = 0; 
    int merge1 = 0; 
    int merge2 = 0; 
    int temp[10]; 
    
    if(first == second)
    return; 
    
    pivot = (first + second) / 2; 
    mergesort(arr, first, pivot); 
    mergesort(arr, pivot +1, second);
    
    for(i = 0; i < length; i++)
    {
    temp[i] = arr[first + i];
    }
    
    merge1 = 0; 
    merge2 = pivot - first + 1; 
    for(i = 0; i < length; i++)
    {
        if(merge2 <= second - first)
    {
    if(merge1 <= pivot - first)
    {
    if(temp[merge1] > temp[merge2])
    {
    arr[i + first] = temp[merge2++];
    }
    else
    {
    arr[i + first] = temp[merge1++];
    }
    }
else
{
arr[i + first] = temp[merge2++];
}
}
else
{
arr[i + first] = temp[merge1++];
}
}
    
}