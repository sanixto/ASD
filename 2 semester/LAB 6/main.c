#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#define n 10
#define pi 3.14159

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

char text[7]; int visited = 0;
int *stack[n]; int tos = 0; sum = 0;
int dx = 16, dy = 16, dtx = 5;
int graphTree[n][n] = {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
    };
int W[n][n] = {0}, mW[n][n]={0}, cycleVisited[n][n]={};;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Лабараторна робота 6";


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
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
           "Lab 6. Hakaviy O.",
           WS_OVERLAPPEDWINDOW,
           300, 100, 1200, 800,
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  PAINTSTRUCT ps;


  void drawtree(HDC hdc, int *uW[n][n], int i, int j, int *nx, int *ny, int tW)
  {
    int scaler = 1.1;
    int nx0, ny0, nxS, nyS, R, oR;
    if (i > j) return;
    if (i == j)
    {
        Arc(hdc, nx[j], ny[j], nx[j] - 40, ny[j] - 40, nx[j], ny[j], nx[j], ny[j]);
        if (tW) Rectangle(hdc, nx[i] - dx,ny[i] - dy, nx[i] + dx, ny[i] + dy);
        sprintf_s(text, 3, "%d", uW[i][j]);
        TextOut(hdc, nx[i] - 6*dtx, ny[i] - 2*dy,  text, 3);
        return;
    }
    if (i > j)
    {
      nx0 = (nx[i]+nx[j])/2 - (ny[i]-ny[j])/(scaler*0.6);
      ny0 = (ny[i]+ny[j])/2 + (nx[i]-nx[j])/(scaler*0.6);
      R = sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
      Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[i], ny[i], nx[j], ny[j]);
      nxS = (nx[i]+nx[j])/2;
      nyS = (ny[i]+ny[j])/2;
      oR = sqrt(pow(nxS-nx0, 2) + pow(nyS-ny0, 2));
      if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
      sprintf_s(text, 3, "%d", uW[i][j]);
      TextOut(hdc, nx0-nxS*R/oR-dtx,ny0-nyS*R/oR-dy/2,  text, 3);
      return;
    }
    if (((i == 0) && (j == 9))||
        ((i == 9) && (j == 0))||
        (i == j + 1)||(i == j - 1))
    {
      MoveToEx(hdc, nx[i], ny[i], NULL);
      LineTo(hdc, nx[j], ny[j]);
      if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
      sprintf_s(text, 3, "%d", uW[i][j]);
      TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
      return;
    }
    if ((i < 0.4*n) && ((j < 0.4*n))){
        nx0 = (nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
        ny0 = (ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
        R = sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
        Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
        nxS = (nx[i]+nx[j])/2;
        nyS = (ny[i]+ny[j])/2;
        oR = sqrt(pow(nxS-nx0, 2) + pow(nyS-ny0, 2));
        if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
        sprintf_s(text, 3, "%d", uW[i][j]);
        TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
        return;
    }
    if ((i >= 3*n) &&(i < 0.8*n)&& (j >= 0.3*n) && (j < 0.8*n))
    {
      nx0 = (nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
      ny0 = (ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
      R = sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
      Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
      nxS = (nx[i]+nx[j])/2;
      nyS = (ny[i]+ny[j])/2;
      oR = sqrt(pow(nxS-nx0, 2) + pow(nyS-ny0, 2));
      if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
      sprintf_s(text, 3, "%d", uW[i][j]);
      TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
      return;
    }
    if (((i >= 0.8*n) || (i == 0)) && ((j >= 0.8*n) || (j == 0)))
    {
      nx0 =( nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
      ny0 = (ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
      R = sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
      Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
      nxS = (nx[i]+nx[j])/2;
      nyS = (ny[i]+ny[j])/2;
      oR = sqrt(pow(nxS-nx0, 2) + pow(nyS-ny0, 2));
      if (tW) Rectangle(hdc, nx0-(nx0-nxS)*R/oR-dx,ny0-(ny0-nyS)*R/oR-dy,nx0-(nx0-nxS)*R/oR+dx,ny0-(ny0-nyS)*R/oR+dy);
      sprintf_s(text, 3, "%d", uW[i][j]);
      TextOut(hdc, nx0-(nx0-nxS)*R/oR-dtx,ny0-(ny0-nyS)*R/oR-dy/2,  text, 3);
      return;
    }
    MoveToEx(hdc, nx[i], ny[i], NULL);
    LineTo(hdc, nx[j], ny[j]);
    if (tW) Rectangle(hdc, (nx[i]+nx[j])/2-dx,(ny[i]+ny[j])/2-dy,(nx[i]+nx[j])/2+dx,(ny[i]+ny[j])/2+dy);
    sprintf_s(text, 3, "%d", uW[i][j]);
    TextOut(hdc, (nx[i]+nx[j])/2-dtx,(ny[i]+ny[j])/2-dy/2,  text, 3);
  }


  void push(int i)
  {
    stack[tos] = i;
    tos++;
  }

  int peek(void)
  {
    return stack[tos-1];
  }

  int pop(void)
  {
    tos--;
    if(tos < 0) return 0;
    return stack[tos];
  }

  int DFS (int M[n][n], int start)
  {
    int DFSM[n] = {0,0,0,0,0,0,0,0,0,0};
    int i;
    int k = 1;
    DFSM[start] = 1;
    push(start);
    while (tos != 0)
    {
      i = peek();
      for(int j = 0; j < n; j++)
      {
        if (M[i][j])
        {
          if (DFSM[j] == 0)
          {
            k++;
            DFSM[j] = k;
            push(j);
            break;
          }
        }
        if (j == 9) pop();
      }
    }

    for (int i = 0; i < n; i++)
    {
        if (DFSM[i] == 0) return 1;
    }
    return 0;
  }

  void weightMatrix(double **A, int* W[n][n])
  {
    int num;
    int Wt[n][n];
    int B[n][n];
    int C[n][n];
    int D[n][n];

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        num = roundf((rand() / (float)RAND_MAX) * 100) * A[i][j];
        Wt[i][j] = num;
        if (num == 0) B[i][j] = 0;
        else B[i][j] = 1;
      }
    }

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (B[i][j] != B[j][i]) C[i][j] = 1;
        else C[i][j] = 0;

        if (B[i][j] == B[j][i] && B[i][j] == 1 && j <= i) D[i][j] = 1;
        else D[i][j] = 0;
      }
    }

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        Wt[i][j] = (C[i][j] + D[i][j]) * Wt[i][j];
      }
    }
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (Wt[i][j])
        {
          W[j][i] = Wt[i][j];
          W[i][j] = Wt[i][j];
        }
      }
    }
  }

  int closing(int start, int end, int* VisitedM)
  {
    if (start == end) return 1;
    if (VisitedM[start] && VisitedM[end]) return 1;
    return 0;
  }

  void kraskal(double **A, int* W[n][n])
  {
    int MinWt, start, end, sumVisited;
    int VisitedM[n] = {};
    while (visited < n - 1)
    {
      MinWt = 100;
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (W[i][j] && W[i][j] < MinWt)
          {
            start = i;
            end = j;
            MinWt = W[i][j];
          }
        }
      }

      if (closing(start, end, VisitedM))
      {
        cycleVisited[start][end] = W[start][end];
        cycleVisited[end][start] = W[end][start];
        W[start][end] = 0;
        W[end][start] = 0;
      } else
      {
        VisitedM[start] = 1;
        VisitedM[end] = 1;
        mW[start][end] = W[start][end];
        mW[end][start] = W[start][end];
        W[start][end] = 0;
        W[end][start] = 0;
        visited++;
      }
      tos=0;
      if (sum == n)
      {
        MinWt = 100;
        for (int i = 0; i < n; i++)
        {
          for (int j = 0; j < n; j++)
          {
            if (cycleVisited[i][j] && cycleVisited[i][j] < MinWt)
            {
              start = i;
              end = j;
              MinWt = cycleVisited[i][j];
            }
          }
        }
        mW[start][end] = cycleVisited[start][end];
        mW[end][start] = cycleVisited[start][end];

        if (DFS(mW, start))
        {
          cycleVisited[start][end] = 0;
          cycleVisited[end][start] = 0;
          mW[start][end] = 0;
          mW[end][start] = 0;
        } else
        {
          cycleVisited[start][end] = 0;
          cycleVisited[end][start] = 0;
          visited++;
          }
      }

      sum=0;
      for (int i = 0; i < n; i++)
            sum += VisitedM[i];
    }
  }


  switch(messg)
  {
    case WM_PAINT :
      hdc = BeginPaint(hWnd, &ps);

      char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
      int nx[n] = {};
      int ny[n] = {};
      int num = 100;
      int len = 600;

      for (int i = 0; i < n; i++)
      {
        if(i == 0)
        {
          nx[i] = num;
          ny[i] = num + sqrt(3)*len/2;
        } else if (i < 4)
        {
          nx[i] = nx[i - 1] + len/4*cos(pi/3);
          ny[i] = ny[i - 1] - len/4*sin(pi/3);
        } else if (i < 7)
        {
          nx[i] = nx[i - 1] + len/4*cos(pi/3);
          ny[i] = ny[i - 1] + len/4*sin(pi/3);
        } else
        {
          nx[i] = nx[i - 1] - len/5;
          ny[i] = ny[i - 1];
        }
      }

      HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
      HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
      HPEN RPen = CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

      srand(0414);
      double** T = randm(n, n);
      double coefficient = 1 - 4*0.005 - 0.05;
      double** A = mulmr(coefficient, T);

      TextOutA(hdc, 650, 25, "Matrix for graph", 17);
      for(int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
        {
          sprintf_s(text, 2, "%g", A[i][j]);
          TextOutA(hdc, 650 + 20 * j, 25 * i+50, text, 2);
        }
      }

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (A[i][j]) A[j][i] = A[i][j];
        }
      }

      weightMatrix(A, W);
      kraskal(A, W);

      TextOutA(hdc, 950, 25, "Matrix for non-oriented graph", 30);
      TextOutA(hdc, 950, 375, "Matrix for graph's kistyak", 27);
      for (int i = 0; i < n; i++)
      {
        for(int j = 0; j < n; j++)
        {
          sprintf_s(text, 2, "%g", A[i][j]);
          TextOutA(hdc, 950 + 20 * j, 25 * i+50, text, 2);
          sprintf_s(text, 3, "%2d", mW[i][j]);
          TextOutA(hdc, 950 + 20 * j, 25 * i+400, text, 3);
        }
      }

      SelectObject(hdc, KPen);

      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (A[i][j] == 1) drawtree(hdc, W, i, j, nx, ny, 0);
        }
      }

      SelectObject(hdc, BPen);

      for (int i = 0; i < n; i++)
      {
        Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
        TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
      }
      system("pause");
      system("cls");
      SelectObject(hdc, RPen);
      int sumWeight = 0;
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < n; j++)
        {
          if (mW[i][j] != 0)
          {
            drawtree(hdc, mW, i, j, nx, ny, 1);
            Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
            TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
            sumWeight+=mW[i][j];
            sprintf_s(text, 20, "Total Weight: %4d", sumWeight);
            TextOutA(hdc, 25 , 25, text, 20);
            system("pause");
            system("cls");
          }
        }
      }

      EndPaint(hWnd, &ps);
    break;

    case WM_DESTROY:
      PostQuitMessage(0);
    break;

    default:
    return(DefWindowProc(hWnd, messg, wParam, lParam));
  }
  return 0;
}
