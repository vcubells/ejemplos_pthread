//
//  main.c
//  3.4.25_pthread_cond_wait
//
//  Created by Vicente Cubells Nonell on 12/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

/*
 Solución al problema del productor-consumidor utilizando variables de condición
 - 1 productor y 1 consumidor
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NTHREADS 2
#define ITEMS 50
#define BSIZE 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce = PTHREAD_COND_INITIALIZER;

int in = 0, out = 0, count = 0;
int buffer[BSIZE];

void * consumidor(void *);
void * productor(void *);

int main(int argc, const char * argv[])
{
	pthread_t hilos[NTHREADS];
	int result, i;
	
	// Crear hilos
	result = pthread_create(&hilos[0], NULL, productor, NULL);
	if (result)
		printf("Error al crear el productor \n");
	
	result = pthread_create(&hilos[1], NULL, consumidor, NULL);
	if (result)
		printf("Error al crear el consumidor \n");
	
	// Esperar que terminen los hilos
	for(i = 0; i < NTHREADS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

void * productor(void * arg)
{
	//Producir elementos
	int items[ITEMS];
	int i = 0;
	
    printf("/// Productor inició .... \n");
	
    
	for(; i < ITEMS; ++i)
	{
		items[i] = i;
	}
    
	i = 0;
	
    while ( i < ITEMS)
	{
		sleep(rand() % 5);
		
        pthread_mutex_lock(&mutex);
		
        if (count < BSIZE)
		{
			buffer[in] = items[i];
			printf("--- Se produjo el elemento %d \n", buffer[in]);
			++in;
			in %= BSIZE;
			++count;
            
            // Si el buffer estaba vacío y se produce un elemento
            // se le envía una señal al consumidor
			if (count == 1) pthread_cond_signal(&consume);
			++i;
		}
		else {
			printf("---------Productor se durmió ----------\n");
			pthread_cond_wait(&produce, &mutex);
			printf("---------Productor se despertó ----------\n");
		}
		pthread_mutex_unlock(&mutex);
	}
    
    pthread_exit(NULL);
}

void * consumidor(void * arg)
{
	int i = 0;
	printf("/// Consumidor inició .... \n");
	while ( i < ITEMS)
	{
		sleep(rand() % 5);
		pthread_mutex_lock(&mutex);
		if (count > 0)
		{
			printf("*** Se consumió el elemento %d \n", buffer[out]);
			++out;
			out %= BSIZE;
			--count;
			if (count == (BSIZE-1)) pthread_cond_signal(&produce);
			++i;
		}
		else {
			printf("---------Consumidor se durmió ----------\n");
			pthread_cond_wait(&consume, &mutex);
			printf("---------Consumidor se despertó ----------\n");
		}
		pthread_mutex_unlock(&mutex);
	}
    
    pthread_exit(NULL);
}


