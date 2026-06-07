#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void* print_square(void* num)
{

	int s_num=(*(int*)num);
	s_num=s_num*s_num;
	printf("The Square: %d \n",s_num);
	pthread_exit(NULL);
}

int main()
{
	pthread_t tid;
	int* num=malloc(sizeof(int));
	*num=5;
	pthread_create(&tid,NULL,print_square,num);
	pthread_join(tid,NULL);
return 0;
}
