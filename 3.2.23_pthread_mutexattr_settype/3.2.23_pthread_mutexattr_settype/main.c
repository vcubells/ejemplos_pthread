//
//  main.c
//  3.2.23_pthread_mutexattr_settype
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
    int type;
    
    pthread_mutexattr_t mutexattr;
	
    // Inicializar los atributos del mutex
    pthread_mutexattr_init(&mutexattr);
    
    // Obtener el valor del atributo TYPE predeterminado
    pthread_mutexattr_gettype(&mutexattr, &type);
    
    printf("Valor predeterminado de TYPE (0-PTHREAD_MUTEX_NORMAL / 1-PTHREAD_MUTEX_ERRORCHECK / 2-PTHREAD_MUTEX_RECURSIVE) = %d \n", type);
    
    // Modificar el atributo TYPE
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
    
    // Inicializar dinámicamente el mutex
    pthread_mutex_init(&mutex, &mutexattr);
    
    // Obtener el valor del atributo TYPE con que se crea el mutex
    pthread_mutexattr_gettype(&mutexattr, &type);
    
    printf("Mutex creado con TYPE (0-PTHREAD_MUTEX_NORMAL / 1-PTHREAD_MUTEX_ERRORCHECK / 2-PTHREAD_MUTEX_RECURSIVE) = %d \n", type);
    
    // Destruir los atributos del mutex pues ya no se requieren
    pthread_mutexattr_destroy(&mutexattr);
    
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