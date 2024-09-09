#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <iostream>

#define BUF_SIZE 1024
#define SHM_KEY 0x1234

int fill_buffer(char * bufptr, int size) {
    char ch = 'A';
    int filled_count;

    //printf("size is %d\n", size);
    memset(bufptr, ch, size - 1);
    bufptr[size-1] = '\0';
    if (ch > 122)
        ch = 65;
    if ( (ch >= 65) && (ch <= 122) ) {
        if ( (ch >= 91) && (ch <= 96) ) {
            ch = 65;
        }
    }
    filled_count = strlen(bufptr);

    //    printf("buffer count is: %d\n", filled_count);
    //    printf("buffer filled is:%s\n", bufptr);
    ch++;
    return filled_count;
}

int write_shm()
{
    int shmid, numtimes;
    //    struct shmseg *shmp;
    //    char *bufptr;
    shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory");
        return 1;
    }

    // Attach to the segment to get a pointer to it.
    char* data = (char*)shmat(shmid, NULL, 0);
    if (data == nullptr) {
        perror("Shared memory attach");
        return 1;
    }
    /* Transfer blocks of data from buffer to shared memory */
    //    bufptr = shmp->buf;
    //    spaceavailable = BUF_SIZE;
    //    for (numtimes = 0; numtimes < 2; numtimes++) {
    //    shmp->complete = 0;
    fill_buffer(data, BUF_SIZE);
    //        printf("Writing Process: Shared Memory Write: Wrote %d bytes\n", shmp->cnt);
    //        bufptr = shmp->buf;
    //        spaceavailable = BUF_SIZE;
    //        sleep(1);
    //    }
    printf("Writing Process: Wrote %d times\n", numtimes);
    //    shmp->complete = 1;

    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    //    if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
    //        perror("shmctl");
    //        return 1;
    //    }
    //    printf("Writing Process: Complete\n");
    return 0;
}

int read_shm()
{
    /* Filename: shm_read.c */

    int shmid;
    shmid = shmget(SHM_KEY, BUF_SIZE, 0644|IPC_CREAT);
    if (shmid == -1) {
        perror("Shared memory");
        return 1;
    }

    // Attach to the segment to get a pointer to it.
    char * data = (char*)shmat(shmid, NULL, 0);
    if (data == nullptr) {
        perror("Shared memory attach");
        return 1;
    }
    std::cout << "reading data: " << data << std::endl;
    /* Transfer blocks of data from shared memory to stdout*/
    //    while (shmp->complete != 1) {
    //        printf("segment contains : \n\"%s\"\n", shmp->buf);
    //        if (shmp->cnt == -1) {
    //            perror("read");
    //            return 1;
    //        }
    //        printf("Reading Process: Shared Memory: Read %d bytes\n", shmp->cnt);
    //        sleep(3);
    //    }
    //    printf("Reading Process: Reading Done, Detaching Shared Memory\n");
    if (shmdt(data) == -1) {
        perror("shmdt");
        return 1;
    }

    if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
        perror("shmctl");
        return 1;
    }
    printf("Reading Process: Complete\n");
    return 0;
}

int main(int argc, char *argv[])
{
    write_shm();
    read_shm();

    return 0;
}

