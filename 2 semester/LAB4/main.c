#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define n 10
#define pi 3.1416

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

double ** mulmr(double coef, double ** matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      matrix[i][j] *= coef;
      matrix[i][j] = (matrix[i][j] > 1.0) ? 1 : 0;
    }
  }
  return matrix;
}

double ** cloneMatrix(double ** matrix, double ** matrixToCopy)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      matrix[i][j] = matrixToCopy[i][j];
    }
  }
  return matrix;
}

double ** symmetryMatrix(double **matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] == 1)
      {
          matrix[j][i] = 1;
      }
    }
  }
  return matrix;
}

void printMatrix(double ** matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%.0f ", matrix[i][j]);
    }
    printf("\n");
  }
}

void showVertexDegree(double ** matrix)
{
  int degree = 0, inDeg = 0, outDeg = 0;
  int f = 1, tmp = 0;

  printf("\n\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] == 1) outDeg++;
      if (matrix[j][i] == 1) inDeg++;
    }
    degree = inDeg + outDeg;
    if (matrix[i][i] == 1) degree--;
    if ((degree != tmp) && (i > 0)) f = 0;
    printf("Graph vertex is %d , degree = %d, input degree = %d , output degree = %d   ", i + 1, degree, inDeg, outDeg);
    printf("\n\n");
    tmp = degree;
    inDeg = 0;
    outDeg = 0;
    degree = 0;
  }
  if (f == 0)
  {
    printf("Graph isn't homogeneous");
  } else
  {
    printf("Graph is homogeneous, degree = %d", tmp);
  }
}

void showHangingAndIsolatedVertex(double ** matrix)
{
  int degree = 0;

  printf("\n\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if ((matrix[i][j] == 1) || (matrix[j][i] == 1)) degree++;
    }
    if (matrix[i][i] == 1) degree--;
    if (degree == 1) printf("Vertex %d is hanging \n", i + 1);
    if (degree == 0) printf("Vertex %d is isolated \n", i + 1);
    degree = 0;
  }
}

void printWaysMatrix(double ** matrix)
{
  printf("\n\n");
  printf("2-length ways\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] == 1)
      {
        for (int k = 0; k < n; k++)
        {
          if (matrix[j][k] == 1) printf("| %d->%d->%d  |", i + 1, j + 1, k + 1);
        }
      }
    }
    printf("\n");
  }
  printf("\n\n");
  printf("3-length ways\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] == 1)
      {
        for (int c1 = 0; c1 < n; c1++)
        {
          if (matrix[j][c1] == 1)
          {
            for (int c2 = 0; c2 < n; c2++)
            {
              if (matrix[c1][c2] == 1)
              {
                printf("| %d->%d->%d->%d |", i + 1, j + 1, c1 + 1, c2 + 1);
              }
            }
          }
        }
      }
    }
    printf_s("\n");
  }
}

int ** reachAndStrongConnectMatrix(double ** matrix)
{
  printf("\n\nThe reach matrix is:\n");
  int reachabilityMatrix[n][n];
  int transitiveMatrix[n][n];
  int strongConnectivityMatrix[n][n];

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      reachabilityMatrix[i][j] = matrix[i][j];

  for (int k = 0; k < n; k++)
  {
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        reachabilityMatrix[i][j] = reachabilityMatrix[i][j] ||
          (reachabilityMatrix[i][k] && reachabilityMatrix[k][j]);
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d ", reachabilityMatrix[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      transitiveMatrix[i][j] = reachabilityMatrix[j][i];
    }
  }

  int counter = 1;
  int countery = 1;

  double ** used_verticles = (double * ) malloc(n * sizeof(double * ));
  for (int i = 0; i < n; i++)
    used_verticles[i] = (double * ) malloc(n * sizeof(double));

  double ** components = (double * ) malloc(n * sizeof(double * ));
  for (int i = 0; i < n; i++)
    components[i] = (double * ) malloc(n * sizeof(double));

  double powered[n][n];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      powered[i][j] = 0;
      for (int k = 0; k < n; k++)
        powered[i][j] += reachabilityMatrix[i][k] * reachabilityMatrix[k][i];
    }
  }

  for (int count = 0; count < n; count++)
  {
    counter = 1;
    for (int i = 0; i < n; i++)
    {
      if (used_verticles[i] == 1) continue;

      for (int j = 0; j < n; j++)
      {
        if (powered[count][j] != powered[i][j]) break;
        if (j == n - 1)
        {
          used_verticles[i] = 1;
          components[countery][i] = 1;
          printf("Komponent %d\n", countery);
          counter++;
        }

      }
    }

    if (
        components[countery][0] || components[countery][1] || components[countery][2] ||
        components[countery][3] || components[countery][4] || components[countery][5] ||
        components[countery][6] || components[countery][7] || components[countery][8] ||
        components[countery][9] || components[countery][10]
       )
      countery++;
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (reachabilityMatrix[i][j] == 1 && transitiveMatrix[i][j] == 1)
      {
        strongConnectivityMatrix[i][j] = 1;
      } else
      {
        strongConnectivityMatrix[i][j] = 0;
      }
    }
  }
  printf("\n");
  printf("Connectivity matrix is: \n");

  for (int i = 0; i < n; i++) //Вивід матриці зв'язності
  {
    for (int j = 0; j < n; j++)
    {
      printf("%d ", strongConnectivityMatrix[i][j]);
    }
    printf("\n");
  }
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Лабораторна робота 4";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
  HWND hWnd;
  MSG lpMsg;

  WNDCLASS w;

  w.lpszClassName = ProgName;
  w.hInstance = hInstance;
  w.lpfnWndProc = WndProc;
  w.hCursor = LoadCursor(NULL, IDC_ARROW);
  w.hIcon = 0;
  w.lpszMenuName = 0;
  w.hbrBackground = LTGRAY_BRUSH;
  w.style = CS_HREDRAW|CS_VREDRAW;
  w.cbClsExtra = 0;
  w.cbWndExtra = 0;

  if ( !RegisterClass(&w) ) return 0;

  hWnd = CreateWindow(ProgName,
                      "LAB 3 Gakavy IP-04",
                      WS_OVERLAPPEDWINDOW,
                      200, 100, 1400, 600,
                      (HWND)NULL, (HMENU)NULL,
                      (HINSTANCE)hInstance,
                      (HINSTANCE)NULL);

  ShowWindow(hWnd, nCmdShow);

  while ( GetMessage(&lpMsg, hWnd, 0, 0) )
  {
    TranslateMessage(&lpMsg);
    DispatchMessage(&lpMsg);
  }
  return(lpMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;

  void arrow(float fi, int px, int py)
  {
    fi = pi * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry;
    px = px - 16 * cos(fi);
    py = py - 16 * sin(fi);
    lx = px - 15 * cos(fi + 0.3);
    rx = px - 15 * cos(fi - 0.3);
    ly = py - 15 * sin(fi + 0.3);
    ry = py - 15 * sin(fi - 0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
    return 0;
  }

  switch(messg)
  {
  case WM_PAINT :

  hdc = BeginPaint(hWnd, &ps);
  char * nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  int nxA[n] = {};
  int nyA[n] = {};
  int nxB[n] = {};
  int nyB[n] = {};

  int num = 100;
  int dx = 16, dy = 16, dtx = 5;
  HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
  HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      nxA[i] = 350;
      nyA[i] = 100;
      nxB[i] = 1000;
      nyB[i] = 100;
    } else if (i <= 0.3*n)
    {
      nxA[i] = nxA[i - 1] + num;
      nyA[i] = nyA[i - 1] + num;
      nxB[i] = nxB[i - 1] + num;
      nyB[i] = nyB[i - 1] + num;
    } else if (i <= 0.7*n)
    {
      nxA[i] = nxA[i - 1] - 1.5*num;
      nyA[i] = nyA[i - 1];
      nxB[i] = nxB[i - 1] - 1.5*num;
      nyB[i] = nyB[i - 1];
    } else
    {
      nxA[i] = nxA[i - 1] + num;
      nyA[i] = nyA[i - 1] - num;
      nxB[i] = nxB[i - 1] + num;
      nyB[i] = nyB[i - 1] - num;
    }
  }

  srand(0404);
  double ** T = randm(n, n);
  double coef = 1.0 - 4*0.01 - 0.3;
  double ** A = mulmr(coef, T);
  double ** B = randm(n, n);
  B = cloneMatrix(B, A);
  B = symmetryMatrix(B);

  void drawGraphDirected(double ** matrix)
  {
    SelectObject(hdc, KPen);
    int nx0, ny0, R;
    double frsAdd, secAdd;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (matrix[i][j] == 1)
        {
          if ((i <= 0.3*n) && (j<= 0.3*n))
          {
            if (i == j)
            {
              Arc(hdc, nxA[j], nyA[j], nxA[j] + 40, nyA[j] - 40, nxA[j], nyA[j], nxA[j], nyA[j]);
              arrow(87, nxA[j], nyA[j]);
              continue;
            }
            if ((i - j == 1) && (matrix[j][i] != 1))
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(-45, nxA[j], nyA[j]);
              continue;
            }

            if (i - j == -1)
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(-225, nxA[j], nyA[j]);
              continue;
            }
            nx0 = (nxA[i] + nxA[j]) / 2 + (nyA[i] - nyA[j]);
            ny0 = (nyA[i] + nyA[j]) / 2 - (nxA[i] - nxA[j]);
            R = sqrt(pow(nxA[i] - nx0, 2) + pow(nyA[i] - ny0, 2));
            frsAdd = atan2(nyA[j] - nyA[i], nxA[j] - nxA[i]);
            secAdd = atan2(sqrt(pow(nxA[j] - nxA[i], 2) + pow(nyA[j] - nyA[i], 2)), R);
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxA[j], nyA[j], nxA[i], nyA[i]);
            arrow((180 - (180/pi*(frsAdd + secAdd/2))), nxA[j], nyA[j]);
            continue;        }
            if (((i >= 0.3*n) && (i <= 0.7*n)) && ((j >= 0.3*n) && (j<= 0.7*n)))
            {
              if (i == j)
              {
                Arc(hdc, nxA[j], nyA[j], nxA[j] + 40, nyA[j] + 40, nxA[j], nyA[j], nxA[j], nyA[j]);
                arrow(-87, nxA[j], nyA[j]);
                continue;
              }
            if ((i - j == 1) && (matrix[j][i] != 1))
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(180, nxA[j], nyA[j]);
              continue;
            }
            if (i - j == -1)
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(0, nxA[j], nyA[j]);
              continue;
            }
            nx0 = (nxA[i] + nxA[j]) / 2 + (nyA[i] - nyA[j]);
            ny0 = (nyA[i] + nyA[j]) / 2 - (nxA[i] - nxA[j]);
            R = sqrt(pow(nxA[i] - nx0, 2) + pow(nyA[i] - ny0, 2));
            frsAdd = atan2(nyA[j] - nyA[i], nxA[j] - nxA[i]);
            secAdd = atan2(sqrt(pow(nxA[j] - nxA[i], 2) + pow(nyA[j] - nyA[i], 2)), R);
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxA[j], nyA[j], nxA[i], nyA[i]);
            arrow((180 - (180/pi*(frsAdd + secAdd/2))), nxA[j], nyA[j]);
            continue;
          }
          if (
              ((i >= 0.7*n) && (j >= 0.7*n)) ||
              ((i == 0) && (j >= 0.7*n)) ||
              ((i >= 0.7*n) && (j == 0))
             )
          {
            if (i == j)
            {
              Arc(hdc, nxA[j], nyA[j], nxA[j] + 40, nyA[j] - 40, nxA[j], nyA[j], nxA[j], nyA[j]);
              arrow(87, nxA[j], nyA[j]);
              continue;
            }
            if (
                ((i - j == 1) && (A[j][i] != 1)) ||
                ((i - j == -n + 1) && (A[j][i] != 1))
               )
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(45, nxA[j], nyA[j]);
              continue;
            }
            if ((i - j == -1) || (i - j == n - 1))
            {
              MoveToEx(hdc, nxA[i], nyA[i], NULL);
              LineTo(hdc, nxA[j], nyA[j]);
              arrow(225, nxA[j], nyA[j]);
              continue;
            }
            nx0 = (nxA[i] + nxA[j]) / 2 + (nyA[i] - nyA[j]);
            ny0 = (nyA[i] + nyA[j]) / 2 - (nxA[i] - nxA[j]);
            R = sqrt(pow(nxA[i] - nx0, 2) + pow(nyA[i] - ny0, 2));
            frsAdd = atan2(nyA[j] - nyA[i], nxA[j] - nxA[i]);
            secAdd = atan2(sqrt(pow(nxA[j] - nxA[i], 2) + pow(nyA[j] - nyA[i], 2)), R);
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxA[j], nyA[j], nxA[i], nyA[i]);
            arrow((180 - (180/pi*(frsAdd + secAdd/2))), nxA[j], nyA[j]);
            continue;
          }
          if ((matrix[i][j] == matrix[j][i]) && (i < j))
          {
            nx0 = (nxA[i] + nxA[j]) / 2 + (nyA[i] - nyA[j]);
            ny0 = (nyA[i] + nyA[j]) / 2 - (nxA[i] - nxA[j]);
            R = sqrt(pow(nxA[i] - nx0, 2) + pow(nyA[i] - ny0, 2));
            frsAdd = atan2(nyA[j] - nyA[i], nxA[j] - nxA[i]);
            secAdd = atan2(sqrt(pow(nxA[j] - nxA[i], 2) + pow(nyA[j] - nyA[i], 2)), R);
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxA[j], nyA[j], nxA[i], nyA[i]);
            arrow((180 - (180/pi*(frsAdd + secAdd/2))), nxA[j], nyA[j]);
            continue;
          }
          MoveToEx(hdc, nxA[i], nyA[i], NULL);
          LineTo(hdc, nxA[j], nyA[j]);
          arrow((180 - (atan2(nyA[j]-nyA[i],nxA[j]-nxA[i]) * 180 / pi)),nxA[j],nyA[j]);
        }
      }
    }

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        Ellipse(hdc, nxA[i] - dx, nyA[i] - dy, nxA[i] + dx, nyA[i] + dy);
        TextOut(hdc, nxA[i] - dtx, nyA[i] - dy / 2,  nn[i], 2);
      }
    }
  }

  void drawGraphNonDirected(double ** matrix)
  {
    SelectObject(hdc, KPen);
    int nx0, ny0, R;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = k; j < n; j++)
      {
        if (matrix[i][j] == 1)
        {
          if ((i <= 0.3*n) && (j<= 0.3*n))
          {
            if (i == j)
            {
              Arc(hdc, nxB[j], nyB[j], nxB[j] + 40, nyB[j] - 40, nxB[j], nyB[j], nxB[j], nyB[j]);
              continue;
            }
            if (i - j == 1)
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            if (i - j == -1)
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            nx0 = (nxB[i] + nxB[j]) / 2 + (nyB[i] - nyB[j]);
            ny0 = (nyB[i] + nyB[j]) / 2 - (nxB[i] - nxB[j]);
            R = sqrt(pow(nxB[i] - nx0, 2) + pow(nyB[i] - ny0, 2));
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxB[j], nyB[j], nxB[i], nyB[i]);
            continue;        }
          if (((i >= 0.3*n) && (i <= 0.7*n)) && ((j >= 0.3*n) && (j<= 0.7*n)))
          {
            if (i == j)
            {
              Arc(hdc, nxB[j], nyB[j], nxB[j] + 40, nyB[j] + 40, nxB[j], nyB[j], nxB[j], nyB[j]);
              continue;
            }
            if (i - j == 1)
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            if (i - j == -1)
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            nx0 = (nxB[i] + nxB[j]) / 2 + (nyB[i] - nyB[j]);
            ny0 = (nyB[i] + nyB[j]) / 2 - (nxB[i] - nxB[j]);
            R = sqrt(pow(nxB[i] - nx0, 2) + pow(nyB[i] - ny0, 2));
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxB[j], nyB[j], nxB[i], nyB[i]);
            continue;
          }
          if (
              ((i >= 0.7*n) && (j >= 0.7*n)) ||
              ((i == 0) && (j >= 0.7*n)) ||
              ((i >= 0.7*n) && (j == 0))
             )
          {
            if (i == j)
            {
              Arc(hdc, nxB[j], nyB[j], nxB[j] + 40, nyB[j] - 40, nxB[j], nyB[j], nxB[j], nyB[j]);
              continue;
            }
            if ((i - j == 1) || (i - j == -n + 1))
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            if ((i - j == -1) || (i - j == n - 1))
            {
              MoveToEx(hdc, nxB[i], nyB[i], NULL);
              LineTo(hdc, nxB[j], nyB[j]);
              continue;
            }
            nx0 = (nxB[i] + nxB[j]) / 2 + (nyB[i] - nyB[j]);
            ny0 = (nyB[i] + nyB[j]) / 2 - (nxB[i] - nxB[j]);
            R = sqrt(pow(nxB[i] - nx0, 2) + pow(nyB[i] - ny0, 2));
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nxB[j], nyB[j], nxB[i], nyB[i]);
            continue;
          }
          MoveToEx(hdc, nxB[i], nyB[i], NULL);
          LineTo(hdc, nxB[j], nyB[j]);
        }
      }
      k++;
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        Ellipse(hdc, nxB[i] - dx, nyB[i] - dy, nxB[i] + dx, nyB[i] + dy);
        TextOut(hdc, nxB[i] - dtx, nyB[i] - dy / 2,  nn[i], 2);
      }
    }
  }

  printf("Directed matrix:\n");
  printMatrix(A);
  printf("\n");

  printf("Non-directed matrix:\n");
  printMatrix(B);
  //drawGraphDirected(A);
  //drawGraphNonDirected(B);
  showVertexDegree(A);
  showHangingAndIsolatedVertex(A);


  T = randm(n, n);
  double newCoef = 1 - 4 * 0.005 - 0.27;
  A = mulmr(newCoef, T);
  
  printf("\n\n");
  printf("New directed matrix:\n");
  printMatrix(A);
  
  printf("\n");
  drawGraphDirected(A);
  showVertexDegree(A);
  printWaysMatrix(A);
  reachAndStrongConnectMatrix(A);


  EndPaint(hWnd, &ps);
  break;

  case WM_DESTROY:
  PostQuitMessage(0);
  break;

  default:
  return( DefWindowProc(hWnd, messg, wParam, lParam) );
  }
  return 0;
}