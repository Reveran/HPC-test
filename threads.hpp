#include <pthread.h>

struct args {
    int chunkSize;
    int thread;
    int size;
    int* product;
    int* aMatrix;
    int* bMatrix;
};

void * threadCalc(void * input)
{
    int chunkSize = ((struct args *)input)->args::chunkSize;
    int thread = ((struct args *)input)->args::thread;
    int size = ((struct args *)input)->args::size;
    int* product = ((struct args *)input)->args::product;
    int* aMatrix = ((struct args *)input)->args::aMatrix;
    int* bMatrix = ((struct args *)input)->args::bMatrix;

    for (int sizecol = 0; sizecol < chunkSize; sizecol++)
    {
        int index = (thread * chunkSize) + sizecol;
        int col = index % size;
        int row = index / size;
        for (int inner = 0; inner < size; inner++)
        {
            product[index] += aMatrix[row * size + inner] * bMatrix[inner * size + col];
        }
    }
    return 0;
}

void MultiplyWithThreads(int size, int threadCount)
{
    struct timeval start, end;

    int chunkSize = (size * size) / threadCount;

    int cont = 0;

    int *aMatrix = (int *)malloc((size * size) * sizeof(int));
    int *bMatrix = (int *)malloc((size * size) * sizeof(int));
    int *product = (int *)malloc((size * size) * sizeof(int));

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

    pthread_t * threadaPool = (pthread_t *)malloc((threadCount) * sizeof(pthread_t));
    struct args *threadData = (struct args *)malloc(sizeof(struct args));

    threadData->size = size;
    threadData->chunkSize = chunkSize;
    threadData->product = product;
    threadData->aMatrix = aMatrix;
    threadData->bMatrix = bMatrix;

    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);

    for (int thread = 0; thread < threadCount; thread++)
    {
        threadData->thread = thread;
        pthread_create(&threadaPool[thread], NULL, threadCalc, threadData);
    }
    for (int thread = 0; thread < threadCount; thread++)
    {
        pthread_join(threadaPool[thread], NULL);
    }
    gettimeofday(&end, NULL);
    printf("%f", calcTime(start, end));
}
