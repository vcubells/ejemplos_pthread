//
//  main.c
//  3.2.29_pthread_condattr_setclock
//
//  Created by Vicente Cubells Nonell on 12/11/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

/*
 *  No funciona en todas las plataformas.
 *  Para un listado de las plataformas que no lo soportan referirse a:
 *  https://www.gnu.org/software/gnulib/manual/html_node/pthread_005fcondattr_005fsetclock.html
 */
#include <stdio.h>
#include <pthread.h>
#include <time.h>
int main(int argc, char **argv)
{
    clockid_t clock_id;
    
    pthread_cond_t cond;
    
    pthread_condattr_t condattr;
	
    // Inicializar los atributos de la variable de condición
    pthread_condattr_init(&condattr);
    
    // Obtener el valor del atributo CLOCK_ID predeterminado
    pthread_condattr_getclock(&condattr, &clock_id);
    
    printf("Valor predeterminado de CLOCK_ID = %d \n", clock_id);
    
    // Obtener el valor del atributo CLOCK_ID predeterminado
    pthread_condattr_getclock(&condattr, &clock_id);
    
    // Modificar el atributo CLOCK_ID
    clock_id = clock();
    pthread_condattr_setclock(&condattr, clock_id);
    
    // Inicializar dinámicamente la variable de condición
    pthread_cond_init(&cond, &condattr);
    
    // Obtener el valor del atributo CLOCK_ID con que se crea la variable
    pthread_condattr_getclock(&condattr, &clock_id);
    
    printf("Variable creada con CLOCK_ID = %d \n", clock_id);
    
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


