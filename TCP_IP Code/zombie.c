//ps au�� Ȯ��

#include<stdio.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid = fork();

    if (pid == 0) //if child process
    {
        puts("Hi, I am a chile process");
    }
    else
    {
        printf("Child Process ID:%d \n", pid);
        sleep(30);
    }

    if (pid == 0)
        puts("End child process");
    else
        puts("End parent process");
    return 0;
}
