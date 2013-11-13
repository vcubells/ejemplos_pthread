//
//  main.c
//  3.2.31_pthread_barrierattr_init
//
//  Created by Vicente Cubells Nonell on 13/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

#define NHILOS 5

int main(int argc, char **argv)
{
    int pshared;
    
    pthread_barrier_t barrier;
    
    pthread_barrierattr_t barrierattr;
	
    // Inicializar los atributos de la barrera
    pthread_barrierattr_init(&barrierattr);
    
    // Obtener el valor del atributo PROCESS_SHARED predeterminado
    pthread_barrierattr_getpshared(&barrierattr, &pshared);
    
    printf("Valor predeterminado de PROCESS_SHARED (1-PTHREAD_PROCESS_SHARED / 2-PTHREAD_PROCESS_PRIVATE) = %d \n", pshared);

    
    // Inicializar la barrera
    pthread_barrier_init(&barrier, &barrierattr, NHILOS);
    
    // Destruir los atributos de la barrera pues ya no se requieren
    pthread_barrierattr_destroy(&barrierattr);
    
	/*
     ... Creación, uso y destrucción de hilos que uilizan
     la barrera
     */
    
    // Destruir la barrera
    pthread_barrier_destroy(&barrier);
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
    
	return 0;
}

