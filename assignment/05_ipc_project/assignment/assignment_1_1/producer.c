#include "message_buffer.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    MessageBuffer *buffer;
    Message *msg;

    pid = getpid();
    attach_buffer(&buffer);
    printf("%d", pid);
    produce(&buffer, (int)pid, argv[1]);

    return 0;
}