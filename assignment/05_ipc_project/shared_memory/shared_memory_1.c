#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define KEY 1234 // 공유 메모리 KEY Init

int main()
{
    int shmid;                   // 공유 메모리 ID
    int *num;                    // 공유 메모리에서 필요한 값만 가져와 사용하는 변수
    void *memory_segment = NULL; // 공유 메모리 주소 값

    if ((shmid = shmget(KEY, sizeof(int), IPC_CREAT | 0666)) == -1) // IPC_CREATE | 0666 : 권한 옵션
        return -1;

    printf("shmid : %d\n", shmid);

    if ((memory_segment = shmat(shmid, NULL, 0)) == (void *)-1) //memory attach
        return -1;

    num = (int *)memory_segment;
    (*num)++;
    printf("num : %d\n", (*num));

    return 0;
}