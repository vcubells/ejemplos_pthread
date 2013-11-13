//
//  main.c
//  3.2.15_pthread_mutex_deadlock
//
//  Created by Vicente Cubells Nonell on 30/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 50

pthread_mutex_t mutex_s = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_r = PTHREAD_MUTEX_INITIALIZER;

int suma = 0;
int resta = VECES;

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
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

void * sumar(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex_s);
        pthread_mutex_lock(&mutex_r);
        
		suma = resta + 1;
        
        printf("Sumador ejecuta sin bloqueos iteración %d de %d\n", i+1, VECES);
        
        pthread_mutex_unlock(&mutex_r);
        pthread_mutex_unlock(&mutex_s);
	}
	
	pthread_exit(NULL);
}

void * restar(void * arg)
{
	int i;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex_s);
        pthread_mutex_lock(&mutex_r);
        
        resta = suma - 1;
		
        printf("Restador ejecuta sin bloqueos iteración %d de %d\n", i+1, VECES);
        
        pthread_mutex_unlock(&mutex_r);
        pthread_mutex_unlock(&mutex_s);
    }
	
	pthread_exit(NULL);
}
