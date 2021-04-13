#include <stdio.h>
#include <math.h>

int main()
{
  int n;
  int counter = 0;
  double product = 1;

  printf("Enter n \n");
  scanf("%d", &n);

   for (int i = 1; i <= n; i++) 
   {
     double sum = 0;

     for (int j = 1; j <= i; j++) 
     {   
         sum += (2 * j + 1);
         counter += 6; // <= ++ + * + jmp
     }
     product *= (2 * i * log(i + 3) / sum);
     counter += 9; // <= ++ * * * + / jmp log(function)
   }
  printf("Product = %.7f\n", product);
  printf("Number of operations = %d \n", counter); 
}