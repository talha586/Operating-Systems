//#include<stdio.h>
#include "function.h"

int minimum_arr(int size, int arr[])
{

int min=arr[0];

        for(int i=0;i<size;i++)
        {
                if(arr[i]<min)
                {
                min=arr[i];
                }
        }
       // printf("\nThe Maximum value is: %d ",min);
return min;
}

