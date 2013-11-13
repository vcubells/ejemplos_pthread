//
//  main.c
//  3.2.27_pthread_condattr_init
//
//  Created by Vicente Cubells Nonell on 12/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

int main(int argc, char **argv)
{
    int pshared;
    clockid_t clock_id;
    
    pthread_cond_t cond;
    
    pthread_condattr_t condattr;
	
    // Inicializar los atributos de la variable de condición
    pthread_condattr_init(&condattr);
    
    // Obtener el valor del atributo PROCESS_SHARED predeterminado
    pthread_condattr_getpshared(&condattr, &pshared);
    
    printf("Valor predeterminado de PROCESS_SHARED (1-PTHREAD_PROCESS_SHARED / 2-PTHREAD_PROCESS_PRIVATE) = %d \n", pshared);
    
    // Obtener el valor del atributo CLOCK_ID predeterminado
    pthread_condattr_getclock(&condattr, &clock_id);
    
    printf("Valor predeterminado de CLOCK_ID = %d \n", clock_id);
    
    // Inicializar dinámicamente la variable de condición
    pthread_cond_init(&cond, &condattr);
    
    // Destruir los atributos de la variable pues ya no se requieren
    pthread_condattr_destroy(&condattr);
    
	/*
     ... Creación, uso y destrucción de hilos que uilizan
     la variable de condición
     */
    
    // Destruir la variable de condición
    pthread_cond_destroy(&cond);
    
	//Garantizar que se liberen los recursos de los hilos
	pthread_exit(NULL);
    
	return 0;
}
