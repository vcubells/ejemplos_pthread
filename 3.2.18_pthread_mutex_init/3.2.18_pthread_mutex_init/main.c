//
//  main.c
//  3.2.18_pthread_mutex_init
//
//  Created by Vicente Cubells Nonell on 30/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

#define NTHREADS 2
#define VECES 5

pthread_mutex_t mutex;

int suma = 0;

void * hilo(void * id)
{
    int i;
    
    int tid = (int) id;
	
	for(i = 0; i < VECES; ++i)
	{
		pthread_mutex_lock(&mutex);
        
        suma += 1;
		
        printf("(Sumador %d) Suma = %d \n", tid, suma);
        
        pthread_mutex_unlock(&mutex);
	}
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t hilos[NTHREADS];
	int result, i;
    
    // Inicializar dinámicamente el mutex
    pthread_mutex_init(&mutex, NULL);
    
	// Crear hilos
	result = pthread_create(&hilos[0], NULL, hilo, (void *) 0);
	if (result)
		printf("Error al crear el hilo 1 \n");
	
	result = pthread_create(&hilos[1], NULL, hilo, (void *) 1);
	if (result)
		printf("Error al crear el hilo 2 \n");
	
	// Esperar que terminen los hilos
	for(i = 0; i < NTHREADS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i);
	}
	
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    // Destruir el mutex
    pthread_mutex_destroy(&mutex);
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
    
	return 0;
}