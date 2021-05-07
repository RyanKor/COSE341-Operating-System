/**
 * Basic execl() Usage.
 *
 * By walking through this example you’ll learn:
 * - How to use execl().
 * - What happens to the process that invoked execl().
 * 
 */

#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    printf("%s executing `ls -l`.\n", "Before");

    // HINT: The /bin/ls -l should be executed.
    execl("/bin/ls", "ls", "-l", (char*)0);

    printf("%s executing `ls -l`.\n", "After");

    return 0;
}

/*
Expected output:
Before executing `ls -l`.
total 20
-rwxr-xr-x 1 root root 15484 Apr 25 01:37 main
-rw-r--r-- 1 root root   453 Apr 25 01:37 main.c
*/