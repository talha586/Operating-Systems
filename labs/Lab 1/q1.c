#include<stdio.h>
#include<stdlib.h>

int main()
{
int size;
	do
        {
	printf("Enter the size of array:");
	scanf("%d",&size);
	}while(size<=0);

	printf("\nArray size is %d ",size);

int arr[size];

	for(int i=0;i<size;i++)
	{
	printf("\nEnter value: ");
	scanf("%d",&arr[i]);
	}

	printf("Array is: ");
	for(int i=0;i<size;i++)
	{
	printf(" %d ",arr[i]);
	}

int max=arr[0];
	for(int i=1;i<size;i++)
	{
		if(arr[i]>max)
		{
		max=arr[i];
		}
	}

	printf("\nThe Maximum value is: %d ",max);
return 0;
}

