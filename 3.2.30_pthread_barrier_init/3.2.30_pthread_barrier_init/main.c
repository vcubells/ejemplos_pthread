//
//  main.c
//  3.2.30_pthread_barrier_init
//
//  Created by Vicente Cubells Nonell on 13/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define CICLISTAS 5
#define ETAPAS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

int ganador[ETAPAS] = {0};

void * ciclista(void * id)
{
    int i;
    
    int tid = (int) id;
	
	for(i = 0; i < ETAPAS; ++i)
	{
        printf("(Ciclista %d) Inicio etapa %d \n", tid, i+1);
        
        sleep(rand() % 10);
        
        pthread_mutex_lock(&mutex);
        
        if ( ganador[i] == 0 )
        {
            ganador[i] = tid;
            printf("(Ciclista %d) 1er lugar en la etapa %d \n", tid, i+1);
        }
        
        pthread_mutex_unlock(&mutex);
        
        printf("(Ciclista %d) Terminé etapa %d y espero por los demás \n", tid, i+1);
        
        pthread_barrier_wait(&barrier);
       
	}
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_t hilos[CICLISTAS];
	int result, i;
    
    // Inicializar la barrera
    pthread_barrier_init(&barrier, NULL, CICLISTAS);
    
	// Crear hilos
	for(i = 0; i < CICLISTAS; ++i)
	{
        result = pthread_create(&hilos[i], NULL, ciclista, (void *) i+1);
        if (result)
            printf("Error al crear el hilo %d  \n", i+1);
	
	}
	
	// Esperar que terminen los hilos
	for(i = 0; i < CICLISTAS; ++i)
	{
		result = pthread_join(hilos[i], NULL);
		if (result)
			printf("Error al adjuntar el hilo %d \n", i+1);
	}
	
    printf("Se acabó la carrera, mostramos los ganadores de cada etapa ...\n");
    
    // Mostrar los ganadores de cada etapa
	for(i = 0; i < CICLISTAS; ++i)
	{
        printf("Etapa %d, Ganador %d \n", i+1, ganador[i]);
	}
    
    // Destruir la barrera
    pthread_barrier_destroy(&barrier);
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
    
	return 0;
}

