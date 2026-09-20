#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

size_t ReadFromFile(const char *name, char *index[], const int a);


int CompareString(const void *a, const void *b);
int strlen( const char *str);
int strcmp(const char* str1, const char *str2);
char *strcpy(const char *start, char *destination);
char *strdup(const char *str);
void ChangeValues(void **value1, void **value2);
void Sort(char* index[], int n, int (*CompareFunc)(const void *a, const void *b));

const int MAX_LEN = 100;



int main()
{
  const int number = 12;
  char *index[number]= {};
  printf("1\n");
  ReadFromFile("onegin.txt", index, number);
    
  Sort(index, number, &CompareString);

  for(int i = 0; i < number; i++)
  {
    printf("%s ", index[i]);
  }
  return 0;
}


size_t ReadFromFile(const char *name, char *index[], const int a)
{
  FILE* file = fopen(name, "r");
  if(file == NULL)
  {
    printf("file is govno\n");
    return 1; 
  }

  char buffer[MAX_LEN]; 
  int i = 0;
  
  while(i < a)
  {
    if (fgets(buffer, MAX_LEN, file) == NULL)
    {
      break;
    } 
  
    index[i] = strdup(buffer); 
    
    i++;
  }
  fclose(file);

  return 0;
}


int strlen( const char *str)
{
  int length = 0;

  while ( str[length] != '\0')
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

        str1++;
        str2++;
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

void Sort(char* index[], int n, int (*CompareFunc)(const void *a, const void *b))
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
