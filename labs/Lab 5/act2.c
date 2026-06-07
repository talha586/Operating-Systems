#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void* myturn(void * arg){
for(int i=0;i<10;i++){
sleep(1);
printf("My Turn from Child Thread\n");
}
return NULL;
}
void yourturn(){
for(int i = 0; i < 3; i++){
sleep(2);
printf("Your Turn from Parent Thread\n");
}
}
int main(){
pthread_t newthread;
pthread_create(&newthread, NULL, myturn, NULL);
yourturn();
pthread_join(newthread, NULL);
pthread_cancel(newthread);
printf("Parent: Child thread has been successfully canceled andjoined.\n");
return 0;
}
