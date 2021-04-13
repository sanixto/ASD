#include<stdio.h>

int main()
{
  double x, y;
  printf("Enter x \n");
  scanf("%lf", &x);

  if (x > -15)
  {
    if (x <= 3)
    {
      y = 4 * x * x + 2;
      printf("y = %.2f\n", y);
    } else  if (x > 20)
    {
      y = 3 * x * x * x / 4 - 5;
      printf("y= %.2f\n", y);
    } else
    {
      printf("Error\n");
    }
  } else if (x <= -30)
  {
    y = 3 * x * x * x / 4 - 5;
    printf("y = %.2lf\n", y);
  } else 
  {
    printf("Error\n");
  }
return 0;
}
