//#include <stdio.h>
#include "function.h"

int maximum_arr(int size, int arr[])
{

int max=arr[0];

	for(int i=0;i<size;i++)
	{
		if(arr[i]>max)
		{
		max=arr[i];
		}
	}

//	printf("\nThe Maximum value is: %d ",max);
return max;
}
