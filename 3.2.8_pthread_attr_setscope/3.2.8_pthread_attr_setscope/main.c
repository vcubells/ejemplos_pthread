//
//  main.c
//  3.2.8_pthread_attr_setscope
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
    
    int scope;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&tid1, &attr, hilo, NULL);
    
    pthread_attr_getscope(&attr, &scope);
    
    printf("Creando hilo uno con SCOPE (1-PTHREAD_SCOPE_SYSTEM / 2-PTHREAD_SCOPE_PROCESS) = %d \n", scope);
    
    // Establecer el valor del atributo SCOPE
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    
    pthread_create(&tid2, &attr, hilo, NULL);
    
    pthread_attr_getscope(&attr, &scope);
    
    printf("Creando hilo dos con SCOPE (1-PTHREAD_SCOPE_SYSTEM / 2-PTHREAD_SCOPE_PROCESS) = %d \n", scope);
    
    // Esperando que los hilos terminen
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("Soy el proceso principal y ya termino...\n");
	
	// Liberar atributos del hilo
	pthread_attr_destroy(&attr);
	
    pthread_exit(NULL);
    
	return 0;
}


