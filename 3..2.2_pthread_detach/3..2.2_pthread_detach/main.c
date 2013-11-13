//
//  main.c
//  3.2.2_pthread_detach
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
    
    pthread_t tid;
    
    printf("Creando hilo ...\n");
    
    pthread_create(&tid, NULL, hilo, NULL);
    
    pthread_detach(tid);
    
    printf("Soy el proceso principal y ya termino...\n");
    
    pthread_exit(NULL);
    
    return 0;
}

