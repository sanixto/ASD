#include <stdio.h>
#include <math.h>

int main()
{
  int n;
  int counter = 0;
  double sum = 0;
  double product = 1;

  printf("Enter n \n");
  scanf("%d", &n);

   for (int i = 1; i <= n; i++) 
   { 
     sum += (2 * i + 1);  
     product *= (2 * i * log(i + 3) / sum);  
     counter += 12; // <= ++ + * + * * * + / jmp log(function)
   }
  printf("Product = %.7f \n", product);
  printf("Number of operations = %d \n", counter); 
  return 0;
}
