void MultiplySecuential(int size)
{

    struct timeval start, end;

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

    while (cont < size * size)
    {
        product[cont] = 0;
        cont++;
    }
    cont = 0;

    gettimeofday(&start, NULL);
    std::ios_base::sync_with_stdio(false);

    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            // Multiply the row of A by the column of B to get the row, column of product.
            for (int inner = 0; inner < size; inner++)
            {
                product[size * row + col] += aMatrix[row * size + inner] * bMatrix[inner * size + col];
            }
        }
    }

    gettimeofday(&end, NULL);
    printf("%f", calcTime(start, end));
}