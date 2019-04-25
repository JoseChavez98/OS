#include <stdio.h>
#include <zconf.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_MAGOS 5
#define MAKIS 20


int palos = 5;
int contador=0;
pthread_mutex_t mutex1;
pthread_barrier_t barrera;

struct Mago{
    int id;
    int makis;
};

struct Mago magos[NUM_MAGOS];

void cogerPalos();
void dejarPalos();
void hablar(struct Mago *);
void comer(struct Mago *);
int checkdining();

void *cena(void * arg) {

    struct Mago *mago = (struct Mago *) arg;

    while (checkdining()==1) {

        pthread_mutex_lock(&mutex1);
        contador++;
        pthread_mutex_unlock(&mutex1);

        if (palos>=2) {

            if(mago->makis>0) {

                cogerPalos();
                comer(mago);
                dejarPalos();

            }else{

                hablar(mago);

            }

        } else {

            hablar(mago);
        }
    }
}


int main(){

    int iter = 0;
    float average_dinner_time = 0.0;
    float final_dinner_time = 0.0;
    float floting=0.0;

    int times_test=20000;


    while (iter<times_test) {

        int dinner_time = 0;

        palos = 5;
        contador=0;

        struct Mago uno;
        struct Mago dos;
        struct Mago tres;
        struct Mago cuatro;
        struct Mago cinco;

        magos[0] = uno;
        magos[1] = dos;
        magos[2] = tres;
        magos[3] = cuatro;
        magos[4] = cinco;

        pthread_mutex_init(&mutex1, NULL);
        pthread_barrier_init(&barrera, NULL, NUM_MAGOS);

        pthread_t Magos[NUM_MAGOS];

        for (int i = 0; i < NUM_MAGOS; i++) {

            magos[i].id = i;
            magos[i].makis = MAKIS;
            pthread_create(&Magos[i], NULL, cena, (void *) (&magos[i]));

        }

        for (int i = 0; i < NUM_MAGOS; i++)
            pthread_join(Magos[i], NULL);


        pthread_mutex_destroy(&mutex1);

        dinner_time = (contador / 5) + 1;
        floting=dinner_time*4;
        final_dinner_time = floting/60;
        average_dinner_time+=final_dinner_time;
        //printf("final dinner time : %f minutos\n", final_dinner_time);
        iter++;

    }

    printf("average time of dinner : %f minutos",(average_dinner_time/times_test));

    return 0;
}

void cogerPalos(){
    pthread_mutex_lock(&mutex1);
    palos = palos - 2;
    pthread_mutex_unlock(&mutex1);
}

void dejarPalos(){
    pthread_mutex_lock(&mutex1);
    palos +=2;
    pthread_mutex_unlock(&mutex1);
}

void hablar(struct Mago *mago){
    //sleep(1);
    //printf("Mago %d hablando\n",mago->id+1);
}

void comer(struct Mago *mago){
    mago->makis--;
    //sleep(1);
    //printf("Mago %d comiendo\n",mago->id+1);
}

int checkdining(){
    for( int i=0 ;i<NUM_MAGOS;i++){
        if(magos[i].makis!=0){
            return 1;
        }
        return 0;
    }
}

