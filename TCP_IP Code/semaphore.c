#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

void* read(void* arg);
void* accu(void* arg);
static sem_t sem_one;
static sem_t sem_two;
static int num;

int main(int argc, char* argv[])
{
    pthread_t id_t1, id_t2;
    sem_init(&sem_one, 0, 0); //세마포어 오브젝트 생성
    sem_init(&sem_two, 0, 1);

    pthread_create(&id_t1, NULL, read, NULL);
    pthread_create(&id_t2, NULL, accu, NULL);

    pthread_join(id_t1, NULL);
    pthread_join(id_t2, NULL);

    sem_destroy(&sem_one);
    sem_destroy(&sem_two);
    return 0;
}

void* read(void* arg)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        fputs("Input Num: ", stdout);

        sem_wait(&sem_two); //세마포어 값을 0으로(accu함수의 post에서 키를 받음)
        scanf("%d", &num);
        sem_post(&sem_one); //세마포어 값을 1로 : 키를 생성
    }
    return NULL;
}
void* accu(void* arg)
{
    int sum = 0, i;
    for (i = 0; i < 5; i++)
    {
        sem_wait(&sem_one); //read 함수의 post에서 받은 키를 생성
        sum += num;
        sem_post(&sem_two); //키를 반환
    }
    printf("result : %d \n", sum);
    return NULL;
}