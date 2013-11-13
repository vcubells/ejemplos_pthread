//
//  main.c
//  3.2.14_pthread_mutex_lock
//
//  Created by Vicente Cubells Nonell on 30/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//
/*
 Solución al problema de la región crítica utilizando bloqueos con mutexes
 - Funciones pthread_mutex_lock() y pthread_mutex_unlock()
 - Inicialización estática de los mutexes con la macro PTHREAD_MUTEX_INITIALIZER
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 50

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int suma = 0;

void * sumar(void *);
void * restar(void *);

int main(int argc, const char * argv[])
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	// Crear hilos
	result = pthread_create(&hilos[0], NULL, sumar, NULL);
	if (result)
		printf("Error al crear el sumador \n");
	
	result = pthread_create(&hilos[1], NULL, restar, NULL);
	if (result)
		printf("Error al crear el restador \n");
	
	// Esperar que terminen los hilos
	for(i = 0; i < NTHREADS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    printf("Suma = %d y debía ser %d \n", suma, 0 );
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

void * sumar(void * arg)
{
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex);
        a = suma;
		++a;
		
        suma = a;
		printf("(Sumador) Suma = %d \n", suma);
        
        pthread_mutex_unlock(&mutex);
        
        // Cambio de contexto simulando que los hilos trabajan a velocidades diferentes
		usleep(rand()%500);
	}
	
	pthread_exit(NULL);
}

void * restar(void * arg)
{
	int a, i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex);
        a = suma;
		--a;
        
		suma = a;
		printf("(Restador) Suma = %d \n", suma);
        
        pthread_mutex_unlock(&mutex);
        
        // Cambio de contexto simulando que los hilos trabajan a velocidades diferentes
		usleep(rand()%500);
	}
	
	pthread_exit(NULL);
}