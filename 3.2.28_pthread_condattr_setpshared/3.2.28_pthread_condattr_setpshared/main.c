//
//  main.c
//  3.2.28_pthread_condattr_setpshared
//
//  Created by Vicente Cubells Nonell on 12/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

int main(int argc, char **argv)
{
    int pshared;
    
    pthread_cond_t cond;
    
    pthread_condattr_t condattr;
	
    // Inicializar los atributos de la variable de condición
    pthread_condattr_init(&condattr);
    
    // Obtener el valor del atributo PROCESS_SHARED predeterminado
    pthread_condattr_getpshared(&condattr, &pshared);
    
    printf("Valor predeterminado de PROCESS_SHARED (1-PTHREAD_PROCESS_SHARED / 2-PTHREAD_PROCESS_PRIVATE) = %d \n", pshared);
    
    // Modificar el atributo PROCESS_SAHRED
    pthread_condattr_setpshared(&condattr, PTHREAD_PROCESS_SHARED);
    
    // Inicializar dinámicamente la variable de condición
    pthread_cond_init(&cond, &condattr);
    
    // Obtener el valor del atributo PROCESS_SHARED con que se crea la variable
    pthread_condattr_getpshared(&condattr, &pshared);
    
    printf("Variable creada con PROCESS_SHARED (1-PTHREAD_PROCESS_SHARED / 2-PTHREAD_PROCESS_PRIVATE) = %d \n", pshared);
    
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

