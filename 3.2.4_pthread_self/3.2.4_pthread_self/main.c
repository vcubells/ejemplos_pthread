//
//  main.c
//  3.2.4_pthread_self
//
//  Created by Vicente Cubells Nonell on 09/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

void * hilo(void * id)
{
	pthread_t tid;
	
	tid = pthread_self();
	
	printf("En el hilo con identificador %ld \n", (long) tid);
    
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid1, tid2;
	
	pthread_create(&tid1, NULL, hilo, NULL);
	pthread_create(&tid2, NULL, hilo, NULL);
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
	
    pthread_exit(NULL);
    
	return 0;
    
}
