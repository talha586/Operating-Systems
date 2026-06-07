#include<stdio.h>
#include<stdlib.h>

int main(int size, char* arr[])
{
int sum=0;

	for(int i=1;i<size;i++)
	{

	int val=atoi(arr[i]);
	sum+=val;

	}

printf("The Sum is %d :\n", sum);
return sum;
}

