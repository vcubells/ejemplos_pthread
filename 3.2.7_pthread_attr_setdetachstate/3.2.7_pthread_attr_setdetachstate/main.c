//
//  main.c
//  3.2.7_pthread_attr_setdetachstate
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
    
	printf("Soy el hilo con identificador %ld \n", (long) tid);
    
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid1, tid2;
	
	pthread_attr_t attr;
    
    int detachstate;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
    
    pthread_create(&tid1, NULL, hilo, NULL);
    
    pthread_attr_getdetachstate(&attr, &detachstate);
    
    printf("Creando hilo uno con DETACHSTATE (1-JOINABLE / 2-DETACHED) = %d \n", detachstate);

    // Establecer el valor del atributo DETACHSTATE
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    
    pthread_create(&tid2, &attr, hilo, NULL);
    
    pthread_attr_getdetachstate(&attr, &detachstate);
    
    printf("Creando hilo dos con DETACHSTATE (1-JOINABLE / 2-DETACHED) = %d \n", detachstate);
    
    // Esperando que los hilos terminen
    pthread_join(tid1, NULL);
    pthread_detach(tid2);
    
    printf("Soy el proceso principal y ya termino...\n");
	
	// Liberar atributos del hilo
	pthread_attr_destroy(&attr);
	
    pthread_exit(NULL);
    
	return 0;
}

