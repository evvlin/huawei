#include <stdio.h>
void ChangeValues(int *value1, int *value2);
void BubbleSort(int data[], int n);

int main()
{
    int data[] = {1, 3, 2, 77, 65, 33, 9};
    int n = sizeof(data) / sizeof(data[0]);
    
    BubbleSort(data, n);
    
    for(int i = 0; i < n; i++)
    {
        printf("%d", data[i]);
    }

    return 0;

}

void BubbleSort(int data[], int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if (data[i] > data[i + 1])
            {
                ChangeValues(&data[i], &data[i + 1]);
            }
        }
    }
}

void ChangeValues(int *value1, int *value2)
{
    int temp = *value2;
    *value2 = *value1;
    *value1 = temp;
}