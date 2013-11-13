//
//  main.c
//  3.2.3_pthread_equal
//
//  Created by Vicente Cubells Nonell on 09/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

void * hilo(void * arg)
{
    printf("Yo soy el hilo creado...\n");
    
    pthread_exit(0);
}

int main(int argc, const char * argv[])
{
    
    pthread_t tid1, tid2;
    
    /* Crear el hilo uno */
    printf("Creando hilo 1 ...\n");
    
    pthread_create(&tid1, NULL, hilo, NULL);
    
    /* Crear el hilo dos */
    printf("Creando hilo 2 ...\n");
    
    pthread_create(&tid2, NULL, hilo, NULL);
    
    /* Verificar si ambos son el mismo hilo o no */
    if (pthread_equal(tid1, tid2))
    {
        printf("Los hilos son iguales \n");
    }
    else
    {
        printf("Los hilos son diferentes \n");
    }
    
    /* Esperando por la terminación de los hilos */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    printf("Soy el proceso principal y ya termino...\n");
    
    pthread_exit(NULL);
    
    return 0;
}