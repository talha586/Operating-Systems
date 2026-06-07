//#include <stdio.h>
#include "function.h"

int average_arr(int size, int arr[])
{

int avg=0;

        for(int i=0;i<size;i++)
        {
                avg+=arr[i];
        }

avg=avg/size;

   //     printf("\nThe Maximum value is: %d ",avg);
return avg;
}


