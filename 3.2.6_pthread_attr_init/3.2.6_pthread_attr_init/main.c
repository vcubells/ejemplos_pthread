//
//  main.c
//  3.2.6_pthread_attr_init
//
//  Created by Vicente Cubells Nonell on 11/10/13.
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
	pthread_t tid;
	
	pthread_attr_t attr;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
	
	printf("Creando hilo ...\n");
    
    pthread_create(&tid, &attr, hilo, NULL);
    
    pthread_join(tid, NULL);
    
    printf("Soy el proceso principal y ya termino...\n");
	
	// Liberar atributos del hilo
	pthread_attr_destroy(&attr);
	
    pthread_exit(NULL);
    
	return 0;
}
