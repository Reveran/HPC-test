#include <sys/shm.h>
#include <sys/wait.h>

void MultiplyWithProcess(int size, int processCount)
{
    struct timeval start, end;

    int chunkSize = (size * size) / processCount;

    int cont = 0;

    int *aMatrix, *bMatrix, *product;
    int shmidA, shmidB, shmidP;
    key_t keyA = 5674;
    key_t keyB = 5675;
    key_t keyP = 5676;

    if ((shmidA = shmget(keyA, (size * size) * sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget Matrix A");
        exit(1);
    }
    if ((shmidB = shmget(keyB, (size * size) * sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget Matrix B");
        shmctl(shmidA, IPC_RMID, NULL);
        exit(1);
    }
    if ((shmidP = shmget(keyP, (size * size) * sizeof(int), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget Matrix P");
        shmctl(shmidA, IPC_RMID, NULL);
        shmctl(shmidB, IPC_RMID, NULL);
        exit(1);
    }

    if ((aMatrix = (int *)shmat(shmidA, NULL, 0)) == (int *)-1)
    {
        perror("shmat Matrix A");
        shmctl(shmidA, IPC_RMID, NULL);
        shmctl(shmidB, IPC_RMID, NULL);
        shmctl(shmidP, IPC_RMID, NULL);
        exit(1);
    }
    if ((bMatrix = (int *)shmat(shmidB, NULL, 0)) == (int *)-1)
    {
        perror("shmat Matrix B");
        shmctl(shmidA, IPC_RMID, NULL);
        shmctl(shmidB, IPC_RMID, NULL);
        shmctl(shmidP, IPC_RMID, NULL);
        exit(1);
    }
    if ((product = (int *)shmat(shmidP, NULL, 0)) == (int *)-1)
    {
        perror("shmat Matrix P");
        shmctl(shmidA, IPC_RMID, NULL);
        shmctl(shmidB, IPC_RMID, NULL);
        shmctl(shmidP, IPC_RMID, NULL);
        exit(1);
    }

    // int* bMatrix = (int *)malloc((size * size) * sizeof(int));
    // int* product = (int *)malloc((size * size) * sizeof(int));

    srand(time(0));

    while (cont < size * size)
    {
        aMatrix[cont] = (rand() % 1000) + 1;
        cont++;
    }
    cont = 0;

    while (cont < size * size)
    {
        bMatrix[cont] = (rand() % 1000) + 1;
        cont++;
    }
    cont = 0;

    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);

    for (int process = 0; process < processCount; process++)
    {
        pid_t c_pid = fork();

        if (c_pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (c_pid > 0)
        {
            while (wait(NULL) > 0)
                ;
        }
        else
        {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int sizecol = 0; sizecol < chunkSize; sizecol++)
            {
                int index = (process * chunkSize) + sizecol;
                int col = index % size;
                int row = index / size;
                for (int inner = 0; inner < size; inner++)
                {
                    product[index] += aMatrix[row * size + inner] * bMatrix[inner * size + col];
                }
            }
            exit(EXIT_SUCCESS);
        }
    }
    gettimeofday(&end, NULL);
    shmctl(shmidA, IPC_RMID, NULL);
    shmctl(shmidB, IPC_RMID, NULL);
    shmctl(shmidP, IPC_RMID, NULL);
    printf("%f", calcTime(start, end));
}
