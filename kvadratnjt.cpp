#include <TXLib.h>
#include <stdio.h>
#include <math.h>


double func_d( double a, double b, double c)
{
  return b * b - 4 * a * c;
}

int main( )
{
  double a, b, c, diskr;

printf(" ax^2 + bx + c = 0, введите a, b, c:\n");
scanf("%lf %lf %lf", &a, &b, &c);

if (a==0)
{
  if (b == 0)
    if (c == 0)
      printf("бесконечно решений\n");
    else
      printf("нет решений");
  else
    printf("x = %.2lf", -c / b);
}

diskr = func_d(a, b, c);

if (a != 0)
{
if (diskr < 0)
{
  printf("нет действительных корней");
}

if (diskr == 0)
{
  printf("x = %.2lf", -b / 2 * a);
}

if (diskr > 0)
{
  printf("x1 = %.2lf\n", (-b + sqrt(diskr)) / 2 * a);
  printf("x2 = %.2lf", (-b - sqrt(diskr)) / 2 * a);
}
}

getchar();

return 0;
}


