//
//  main.c
//  3.2.12_pthread_attr_setinheritsched
//
//  Created by Vicente Cubells Nonell on 14/10/13.
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
 	int politica, scope, inheritsched;
    struct sched_param schedparam;
	
	// Se obtiene el tid del hilo
	pthread_t tid = pthread_self();
    
    // Se obtienen los atributos de calendarización predeterminados
    pthread_attr_getschedpolicy(&attr, &politica);
	pthread_getschedparam(tid, &politica, &schedparam);
    pthread_attr_getscope(&attr, &scope);
    pthread_attr_getinheritsched(&attr, &inheritsched);
    
    printf("--- Creado el hilo %li con: --- \n", (long) tid);
    printf("SCOPE (1-PTHREAD_SCOPE_SYSTEM / 2-PTHREAD_SCOPE_PROCESS) = %d \n", scope);
    printf("SCHEDPOLICY (1-SCHED_OTHER / 2-SCHED_RR / 4-SCHED_FIFO): %d\n", politica);
    printf("INHERITSCHED (1-PTHREAD_INHERIT_SCHED / 2-PTHREAD_EXPLICIT_SCHED) = %d\n", inheritsched);
	printf("SCHEDPRIORITY = %d \n", schedparam.sched_priority);
   
	
	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t tid1, tid2;
	
	// Inicializar atributos del hilo
	pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&tid1, &attr, hilo, NULL);
    
    // Esperar a que termine el hilo uno
    pthread_join(tid1, NULL);
    
    // Establecer atributos de calendarización del nuevo hilo
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    
    pthread_create(&tid2, &attr, hilo, NULL);

    // Esperar a que termine el hilo dos
	pthread_join(tid2, NULL);
	
	pthread_exit(NULL);
}

