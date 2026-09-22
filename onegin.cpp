#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

size_t Massiv_filling(char *text, char **index, const size_t size_of_file, const int number_of_strings);
int Compare_string_by_the_start(const void *a, const void *b);
int Compare_string_by_the_end(const void *a, const void *b);
int strcmp(const char* str1, const char *str2);
char *strcpy(const char *start, char *destination);
char *strdup(const char *str);
void ChangeValues(void **value1, void **value2);
void Sort_by_the_start(char* index[], int n, int (*CompareFunc)(const void *a, const void *b));
void Sort_by_the_end(char* index[], int n, int (*CompareFunc)(const void *a, const void *b));
int OutPutSort(char **index, char **index_sort_by_the_start, char **index_sort_by_the_end, const int number_of_strings);

int main() 
{
    FILE *file = fopen("onegin.txt", "r");
    if (file == NULL) {
        printf("file is govno\n");
        return 1;
    }

    struct stat file_status;
    stat("onegin.txt", &file_status);
    const size_t size_of_file = file_status.st_size;

    char *text = (char *)calloc(size_of_file + 1, sizeof(char));
    fread(text, sizeof(char), size_of_file, file);

    int schitaem_stroki = 0;
    for (int i = 0; i < size_of_file; i++) 
    {
        if (text[i] == '\n' || text[i] == '\r') 
        {
            text[i] = '\0';
            schitaem_stroki++;
        }
    }

    const int number_of_strings = schitaem_stroki;
    char **index = (char **)calloc(number_of_strings + 1, sizeof(char *));
    char **index_sort_by_the_end = (char **)calloc(number_of_strings + 1, sizeof(char *));
    char **index_sort_by_the_start = (char **)calloc(number_of_strings + 1, sizeof(char *));

    Massiv_filling(text, index, size_of_file, number_of_strings);
    memcpy(index_sort_by_the_end, index, (number_of_strings + 1) * sizeof(char *));
    memcpy(index_sort_by_the_start, index, (number_of_strings + 1) * sizeof(char *));

    OutPutSort(index, index_sort_by_the_start, index_sort_by_the_end, number_of_strings);
    
    free(text);
    fclose(file);
    return 0;
}


int OutPutSort(char **index, char **index_sort_by_the_start, char **index_sort_by_the_end, const int number_of_strings)
{
    FILE *fp = fopen("onegin_sorted.txt", "w");
    Sort_by_the_start(index_sort_by_the_start, number_of_strings, &Compare_string_by_the_start);

    for (int k = 0; k < number_of_strings; k++) 
    { 
        if(strlen(index_sort_by_the_start[k]) > 0)
        {
            fprintf(fp, "%s\n", index_sort_by_the_start[k]);
        }
    }

    Sort_by_the_end(index_sort_by_the_end, number_of_strings, &Compare_string_by_the_end);

    for (int i = 0; i < number_of_strings; i++) 
    { 
        if(strlen(index_sort_by_the_start[i]) > 0)
        {
            fprintf(fp, "%s\n", index_sort_by_the_end[i]);
        }
    }

    for (int p = 0; p < number_of_strings; p++) 
    { 
        if(strlen(index[p]) > 0)
        {
            fprintf(fp, "%s\n", index[p]);
        }
    }

    fclose(fp);

}

size_t Massiv_filling(char *text, char **index, const size_t size_of_file, const int number_of_strings) 
{
    char *cursor = text; 
    int j = 0;
    int l = 1;

    index[0] = text;
    while (j < size_of_file && l < number_of_strings) 
    {
        if (text[j] == '\0') 
        {
            cursor = &text[j + 1];
            index[l++] = cursor;
        }
        j++;
    }
    return 0;
}

// int strlen(const char *str)
// {
//   int length = 0;

//   while(str[length] != '\0')
//   {
//     length++;
//   }

//   return length;
// }

int Compare_string_by_the_start(const void *a, const void *b)         
{
    char *str1 = *(char **) a;
    char *str2 = *(char **) b;

    while (*str1 != '\0' || *str2 != '\0')
    {
        while (*str1 != '\0' && !isalpha((unsigned char)*str1))
        {
            str1++;
        }
        
        while (*str2 != '\0' && !isalpha((unsigned char)*str2))
        {
            str2++;
        }

        if (*str1 == '\0' && *str2 == '\0')
        {
            break;
        }

        char char1 = tolower((unsigned char)*str1);
        char char2 = tolower((unsigned char)*str2);

        if (char1 != char2)
        {
            return (unsigned char)char1 - (unsigned char)char2;
        }

        if(*str1 != '\0') str1++;
        if(*str2 != '\0') str2++;
    }
   return (unsigned char)tolower((unsigned char)*str1) - (unsigned char)tolower((unsigned char)*str2); 
}

int Compare_string_by_the_end(const void *a, const void *b)         
{
    char *str1 = *(char **) a;
    char *str2 = *(char **) b;

    while (*str1 != '\0' || *str2 != '\0')
    {
        while (*str1 != '\0' && !isalpha((unsigned char)*str1))
        {
            str1--;
        }
        
        while (*str2 != '\0' && !isalpha((unsigned char)*str2))
        {
            str2--;
        }

        if (*str1 == '\0' && *str2 == '\0')
        {
            break;
        }

        char char1 = tolower((unsigned char)*str1);
        char char2 = tolower((unsigned char)*str2);

        if (char1 != char2)
        {
            return (unsigned char)char1 - (unsigned char)char2;
        }

        if(*str1 != '\0') str1--;
        if(*str2 != '\0') str2--;
    }
   return (unsigned char)tolower((unsigned char)*str1) - (unsigned char)tolower((unsigned char)*str2); 
}

void ChangeValues(void **value1, void **value2) 
{
    void *temp = *value2;
    *value2 = *value1;
    *value1 = temp;
}

void Sort_by_the_start(char* index[], int n, int (*CompareFunc)(const void *a, const void *b))
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if ((*CompareFunc)(&index[i], &index[i + 1]) > 0)
            {
                ChangeValues((void **)&index[i], (void **)&index[i + 1]);
            }
        }
    }
}

void Sort_by_the_end(char* index[], int n, int (*CompareFunc)(const void *a, const void *b))
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < n - 1; i++)
        {
            char *ptr1 = index[i] + strlen(index[i]) - 1;
            char *ptr2 = index[i + 1] + strlen(index[i + 1]) - 1;
            if ((*CompareFunc)(&ptr1, &ptr2) > 0)
            {
                ChangeValues((void **)&index[i], (void **)&index[i + 1]);
            }

        }
    }
}
