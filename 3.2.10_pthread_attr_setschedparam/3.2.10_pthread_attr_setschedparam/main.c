//
//  main.c
//  3.2.10_pthread_attr_setschedparam
//
//  Created by Vicente Cubells Nonell on 11/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

/*
 * Para poder cambiar los parámetros de calendarización de un hilo debe ejecutarse el programa con privilegios de administración
 * En Ubuntu: sudo nombre_ejecutable
 * En otras distros: Ejecutarlo bajo la identidad del usuario root
 */

#include <stdio.h>
#include <pthread.h>
#include <sched.h>

//Hilo donde se cambia la prioridad
void * hilo(void * null)
{
 	int politica;
    struct sched_param schedparam;
	
	// Se obtiene el tid del hilo
	pthread_t tid = pthread_self();
	
	//Se cambia la prioridad del hilo
	schedparam.sched_priority = 5;
	pthread_setschedparam(tid, SCHED_FIFO, &schedparam);
    
	// Se obtiene la prioridad del hilo y se imprime
	pthread_getschedparam(tid, &politica, &schedparam);
	
	printf("La prioridad del hilo ahora es: %d \n", schedparam.sched_priority);
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid;
    pthread_attr_t attr;
    int politica;
    
    struct sched_param schedparam;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&tid, &attr, hilo, NULL);
    
    // Se obtiene la prioridad conque se crea el hilo
	pthread_getschedparam(tid, &politica, &schedparam);
    
	printf("La prioridad del hilo es: %d \n", schedparam.sched_priority);
	
	pthread_join(tid, NULL);
	
	pthread_exit(NULL);
}



