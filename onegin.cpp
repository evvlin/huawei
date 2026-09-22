#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>

size_t ReadFromFile(char *text, char **index, const size_t size_of_file, const int number_of_strings);
int CompareString(const void *a, const void *b);
int strlen( const char *str);
int strcmp(const char* str1, const char *str2);
char *strcpy(const char *start, char *destination);
char *strdup(const char *str);
void ChangeValues(void **value1, void **value2);
void Sort_by_the_start(char* index[], int n, int (*CompareFunc)(const void *a, const void *b));
void Sort_by_the_end(char* index[], int n, int (*CompareFunc)(const void *a, const void *b));

const int MAX_LEN = 100;

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
    int n = 0;
    int j = 0;
    char ch;

    while (j < size_of_file && (ch = fgetc(file)) != EOF) 
    {
        text[j] = ch;
        j++;
    }

    for (int i = 0; i < size_of_file; i++) 
    {
        if (text[i] == '\n' || text[i] == '\r') 
        {
            text[i] = '\0';
            n++;
        }
    }
    const int number_of_strings = n;

    char **index = (char **)calloc(number_of_strings + 1, sizeof(char *));

    
    ReadFromFile(text, index, size_of_file, number_of_strings);
    Sort_by_the_end(index, number_of_strings, &CompareString);

    for (int i = 0; i < number_of_strings; i++) 
    { 
        printf("%s\n", index[i]);
    }

    
    return 0;
}


size_t ReadFromFile(char *text, char **index, const size_t size_of_file, const int number_of_strings) 
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


int strlen( const char *str)
{
  int length = 0;

  while(str[length] != '\0')
  {
    length++;
  }

  return length;
}

int strcmp(const char* str1, const char *str2)
{
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


char *strcpy(const char *start, char *destination)
{
  char *link = destination;
  while(*start != '\0')
  {
     *destination = *start;
     destination++;
     start++;
  }

 *destination = '\0';
 return link;
}

char *strdup(const char *str)
{
    
    size_t len = strlen(str);
    char *line = (char *)calloc(len + 1, sizeof(char)); 
    
    strcpy(str, line); 
    
    return line;
}


int CompareString(const void *a, const void *b)         
{
    char *value_a = *(char **) a;
    char *value_b = *(char **) b;

    return strcmp(value_a, value_b);

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
            if (strlen(index[i]) > 0 && strlen(index[i + 1]) > 0)
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
}
