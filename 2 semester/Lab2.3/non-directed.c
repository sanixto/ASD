#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#define n 10

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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Лабораторна робота 3";

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
                         400, 100, 900, 600,
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

  switch(messg)
  {
  case WM_PAINT :

  hdc = BeginPaint(hWnd, &ps);
  char * nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  int nx[n] = {};
  int ny[n] = {};
  int num = 100;
  int dx = 16, dy = 16, dtx = 5;

  HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
  HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

  SelectObject(hdc, BPen);

  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      nx[i] = 400;
      ny[i] = 100;
    } else if (i <= 0.3*n)
    {
      nx[i] = nx[i - 1] + num;
      ny[i] = ny[i - 1] + num;
    } else if (i <= 0.7*n)
    {
      nx[i] = nx[i - 1] - 1.5*num;
      ny[i] = ny[i - 1];
    } else
    {
      nx[i] = nx[i - 1] + num;
      ny[i] = ny[i - 1] - num;
    }
  }

  srand(0404);
  double ** T = randm(n, n);
  double cf = 1.0 - 4*0.005 - 0.25;
  double ** A = mulmr(cf, T);

  printf("Matrix non-directed \n");

  for (int i = 0; i < n; i++)
  {
      for (int j = 0; j < n; j++)
      {
          printf("%.0f ", A[i][j]);
      }
      printf("\n");
  }

  SelectObject(hdc, KPen);

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (A[i][j] == 1)
      {
        MoveToEx(hdc, nx[i], ny[i], NULL);
        if (i == j)
        {
          if (i <= 0.3*n)
          {
            Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] - 40, nx[j], ny[j], nx[j], ny[j]);
          } else if (i <= 0.7*n)
          {
            Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] + 40, nx[j], ny[j], nx[j], ny[j]);
          } else
          {
            Arc(hdc, nx[j], ny[j], nx[j] - 40, ny[j] - 40, nx[j], ny[j], nx[j], ny[j]);
          }
        } else if (labs(i - j) == 1 || labs(i - j) == n - 1 )
        {
          LineTo(hdc, nx[j], ny[j]);
        } else if (
                   ((i <= 0.3*n) && (j <= 0.3*n)) ||
                   (((i >= 0.3*n) && (i <= 0.7*n)) && ((j >= 0.3*n) && (j <= 0.7*n))) ||
                   ((i >= 0.7*n) && (j >= 0.7*n)) ||
                   ((i >= 0.7*n) && (j == 0)) ||
                   ((i == 0) && (j >= 0.7*n))
                  )
        {
            int nx0 = (nx[i] + nx[j]) / 2 + (ny[i] - ny[j]);
            int ny0 = (ny[i] + ny[j]) / 2 - (nx[i] - nx[j]);
            int R = sqrt(pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2));
            Arc(hdc, nx0 - R, ny0 - R, nx0 + R, ny0 + R, nx[j], ny[j], nx[i], ny[i]);
        }else
        {
          LineTo(hdc, nx[j], ny[j]);
        }
      }
    }
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
      TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2,  nn[i], 2);
    }
  }

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