//
//  main.c
//  3.2.24_pthread_cond_init
//
//  Created by Vicente Cubells Nonell on 12/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//
#include <stdio.h>
#include <pthread.h>

/* Inicialización estática */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


int main(int argc, const char * argv[])
{
	pthread_cond_t conddinamica;
    
    /* Inicialización dinámica sin atributos */
    pthread_cond_init(&conddinamica, NULL);
    
    /*
        ... Creación, uso y destrucción de hilos que uilizan
        la variable de condición
     */
    
	pthread_cond_destroy(&conddinamica);
	
    //Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
}

