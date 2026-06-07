#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<stdbool.h>
void* PrintNumber()
{
	for(int i=1;i<=10;i++)
	{
		printf(" %d", i);
	}
	pthread_exit(NULL);
}

void* PrintFibonacii()
{
	int arr[10];
	arr[0]=0;
	arr[1]=1;

	printf("\n");

	for(int i=2;i<10;i++)
	{
		arr[i]=arr[i-2]+arr[i-1];
	}

	for(int i=0;i<10;i++)
	{
		printf("%d ",arr[i]);
	}
	pthread_exit(NULL);
}

void* PrintPrime()
{
	printf("\n");
	int arr[10];
	int count=0;
	int num=2;
	while(count<10)
	{
	bool isPrime= true;
		for(int i=2;i*i<=num;i++)
		{
			if(num%i==0)
			{
				isPrime=false;
				break;
			}
		}
		
		if(isPrime)
		{
			arr[count]=num;
			count++;
		}
	num++;
	}

	for(int i=0;i<10;i++)
	{
		printf("%d ",arr[i]);
	}
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid1,tid2,tid3;
	pthread_create(&tid1,NULL,PrintNumber,NULL);
	pthread_create(&tid2,NULL,PrintFibonacii,NULL);
	pthread_create(&tid3,NULL,PrintPrime,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);

return 0;
}
