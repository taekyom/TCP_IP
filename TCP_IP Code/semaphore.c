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
    sem_init(&sem_one, 0, 0); //�������� ������Ʈ ����
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

        sem_wait(&sem_two); //�������� ���� 0����(accu�Լ��� post���� Ű�� ����)
        scanf("%d", &num);
        sem_post(&sem_one); //�������� ���� 1�� : Ű�� ����
    }
    return NULL;
}
void* accu(void* arg)
{
    int sum = 0, i;
    for (i = 0; i < 5; i++)
    {
        sem_wait(&sem_one); //read �Լ��� post���� ���� Ű�� ����
        sum += num;
        sem_post(&sem_two); //Ű�� ��ȯ
    }
    printf("result : %d \n", sum);
    return NULL;
}