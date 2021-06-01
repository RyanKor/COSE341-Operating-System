#include "message_buffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int shmid;
void *memory_segment = NULL;

int init_buffer(MessageBuffer **buffer)
{
    /*---------------------------------------*/
    /* TODO 1 : init buffer                  */

    shmid = shmget(KEY, sizeof(int), IPC_CREAT | 0666); // 해당 선언문이 없을 경우, 에러 발생. shmid가 갱신이 안됨
    if (shmid == -1)
        return -1;
    memory_segment = shmat(shmid, NULL, 0);
    *buffer = (MessageBuffer *)memory_segment;
    (*buffer)->in = 0;
    (*buffer)->out = 0;
    /* TODO 1 : END                          */
    /*---------------------------------------*/
    printf("init buffer\n");
    return 0;
}

int attach_buffer(MessageBuffer **buffer)
{
    /*---------------------------------------*/
    /* TODO 2 : attach buffer                */
    /* do not consider "no buffer situation" */
    shmid = shmget(KEY, sizeof(int), 0); // 이미 존재하고 있는 메모리 가져오기
    if (shmid == -1)
        return -1;
    memory_segment = shmat(shmid, NULL, 0);
    *buffer = (MessageBuffer *)memory_segment;
    if (memory_segment == (void *)-1) //memory attach
        return -1;
    /* TODO 2 : END                          */
    /*---------------------------------------*/

    printf("attach buffer\n");
    printf("\n");
    return 0;
}

int detach_buffer()
{
    if (shmdt(memory_segment) == -1)
    {
        printf("shmdt error!\n\n");
        return -1;
    }

    printf("detach buffer\n\n");
    return 0;
}

int destroy_buffer()
{
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        printf("shmctl error!\n\n");
        return -1;
    }

    printf("destroy shared_memory\n\n");
    return 0;
}

int produce(MessageBuffer **buffer, int sender_id, char *data)
{
    if (is_full(**buffer))
    {
        printf("full!\n\n");
        return -1;
    }

    if (strlen(data) > 100)
    {
        printf("len(data) > 100\n\n");
        return -1;
    }

    /*---------------------------------------*/
    /* TODO 3 : produce message              */
    strcpy((*buffer)->messages[(*buffer)->in].data, (char *)data);
    (*buffer)->messages[(*buffer)->in].sender_id = sender_id;
    (*buffer)->in = ((*buffer)->in + 1) % BUFFER_SIZE;
    /* TODO 3 : END                          */
    /*---------------------------------------*/

    printf("produce message\n");
    return 0;
}

int consume(MessageBuffer **buffer, Message **message)
{

    if (is_empty(**buffer))
    {
        return -1;
    }
    /*---------------------------------------*/
    /* TODO 4 : consume message              */
    memory_segment = shmat(shmid, NULL, 0);
    *message = (Message *)memory_segment;
    strcpy((*message)->data, (*buffer)->messages[(*buffer)->out].data);
    (*message)->sender_id = (*buffer)->messages[(*buffer)->out].sender_id;

    (*buffer)->out = ((*buffer)->out + 1) % BUFFER_SIZE;

    /* TODO 4 : END                          */
    /*---------------------------------------*/
    return 0;
}

int is_empty(MessageBuffer buffer)
{
    /*---------------------------------------*/
    /* TODO 5 : is empty?                    */
    if (buffer.in == buffer.out)
        return -1;

    return 0;
    /* TODO 5 : END                          */
    /*---------------------------------------*/
}

int is_full(MessageBuffer buffer)
{
    /*---------------------------------------*/
    /* TODO 6 : is full?                     */
    if ((buffer.in + 1) % BUFFER_SIZE == buffer.out)
        return -1;

    return 0;
    /* TODO 6 : END                          */
    /*---------------------------------------*/
}
