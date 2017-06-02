#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
 
#define NITER 1000000
 
//Variables globales
int count = 0;
sem_t mutex;
 
 
void * ThreadAdd(void * a){
 
    int i, tmp;
    while(1){
 
    sem_wait(&mutex);
 
        tmp = count;      /* copia el conteo global localmente */
        tmp = tmp+1;      /* incrementa la copia local */
        count = tmp;      /* guarda el conteo local en la variable global */
	printf("Soy el hilo 1 y estoy subiendo la cuenta a [%d]",count);
	getchar();
 
    sem_post(&mutex);
   
    }
}

void * ThreadAdd2(void * a){
 
    int i, tmp;
    while(1){
 
    sem_wait(&mutex);
 
        tmp = count;      /* copia el conteo global localmente */
        tmp = tmp+1;      /* incrementa la copia local */
        count = tmp;      /* guarda el conteo local en la variable global */
	printf("Soy el hilo 2 y estoy subiendo la cuenta a [%d]",count);
	getchar();
 
    sem_post(&mutex);
   
    }
}
 
int main(int argc, char * argv[]){
     //inicializamos nuestro semaforo a 1
     //y el cero indica que el semaforo solo
     //estara disponible para este proceso
    sem_init(&mutex, 0, 1);
 
    pthread_t tid1, tid2;
 
    if(pthread_create(&tid1, NULL, ThreadAdd, NULL)){
 
      printf("\n Error creando el primer hilo");
      exit(1);
    }
 
    if(pthread_create(&tid2, NULL, ThreadAdd2, NULL)){
 
      printf("\n ERROR creando el segundo hilo");
      exit(1);
    }
 
    if(pthread_join(tid1, NULL)){   /* espera a que el primer hilo termine */
     
      printf("\n ERROR uniendo los hilos");
      exit(1);
    }
 
    if(pthread_join(tid2, NULL)){        /* espera a que el segundo hilo termine */
     
      printf("\n ERROR uniendo los hilos");
      exit(1);
    }
 
    /*if (count <  (2 * NITER) )
        printf("\n La cuenta es [%d], deberia ser %d\n", count, 2*NITER);
    else
        printf("\n OK! la cuenta es [%d] \n", count);*/
   
    pthread_exit(NULL);
}
