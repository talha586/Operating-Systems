#include <stdio.h>
#include "function.h"

int main()
{
	int size;

	do
	{
	printf("Enter the size of array: ");
	scanf("%d", &size);
	}while(size<=0);

int arr[size];

	for(int i=0;i<size;i++)
	{
	printf("Enter the value: ");
	scanf("%d",&arr[i]);
	}

	int max_val=maximum_arr(size,arr);
	int min_val=minimum_arr(size,arr);
	int avg_val=average_arr(size,arr);

	printf("\nThe Maximum value is: %d ",max_val);
	printf("\nThe Minimum value is: %d ",min_val);
	printf("\nThe Average value is: %d ",avg_val);

return 0;
}
