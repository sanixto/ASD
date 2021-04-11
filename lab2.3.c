#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define n 3

double ** randm(int rows, int columns) 
{
  double ** matrix = (double **)malloc(rows * columns * sizeof(double));

  for (int i = 0; i < rows; i++)  
  {
    matrix[i] = (double*)malloc(rows * sizeof(double));

    for (int j = 0; j < columns; j++)  
    {
      matrix[i][j] =  2.0 / RAND_MAX * rand();
    }
  }
  return matrix;
}

double ** mulmr(double coef, double ** mat) 
{ 
  for (int i = 0; i < n; i++) 
  {
      for (int j = 0; j < n; j++)
      {
        mat[i][j] *= coef;
        mat[i][j] = (mat[i][j] > 1.0) ? 1 : 0;
      }
  } 
  return mat;     
}

int main() 
{
  double ** T = randm(n, n);
  mulmr(0.73, T);
}