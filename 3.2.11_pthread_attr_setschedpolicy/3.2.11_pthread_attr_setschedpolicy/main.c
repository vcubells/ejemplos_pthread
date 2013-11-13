//
//  main.c
//  3.2.11_pthread_attr_setschedpolicy
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

pthread_attr_t attr;

//Hilo donde se cambian las políticas de planificación
void * hilo(void * null)
{
 	int politica;
	
	// Se obtiene el tid del hilo
	pthread_t tid = pthread_self();
	
	//Se cambia la política del hilo
	pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    
	// Se obtiene la política nueva del hilo y se imprime
	pthread_attr_getschedpolicy(&attr, &politica);
	
	printf("Soy el hilo %ld y mi política ahora es (1-SCHED_OTHER / 2-SCHED_RR / 4-SCHED_FIFO): %d\n", (long)tid, politica);
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid;
    int politica;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&tid, &attr, hilo, NULL);
    
    // Se obtiene la política conque se crea el hilo
	pthread_attr_getschedpolicy(&attr, &politica);
    
	printf("La política es (1-SCHED_OTHER / 2-SCHED_RR / 4-SCHED_FIFO): %d\n", politica);
	
	pthread_join(tid, NULL);
	
	pthread_exit(NULL);
}




