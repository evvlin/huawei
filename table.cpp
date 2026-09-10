#include <stdio.h>
#include <stdlib.h>

int offset(int x, int y, int data[]);
void PrintMtx(int data[], int size);

int main(void)
{
    int n = 0;
    printf("number of teams:\n");
    scanf("%d", &n);

    size_t match = n * (n - 1) / 2;
    int *data = (int*) calloc(match, sizeof(int));

    printf("enter %zu score:\n", match);
    for(size_t i = 0; i < match; i++)
    {
        scanf("%d", &data[i]);
    }

    PrintMtx(data, n);
    return 0;
}

int offset(int x, int y, int data[])
{
    int shift = x * (x - 1)/2 + y;
    return *((int*)data + shift);
}

void PrintMtx(int data[], int size)
{
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (x == y)
            {
                printf("- ");
            }
            if (y < x)
            {
                printf("%-2d", offset(x, y, data));
            }
            if (x < y)
            {
                printf("%-2d", offset(y, x, data));
            }
        }
        printf("\n");
    }
}