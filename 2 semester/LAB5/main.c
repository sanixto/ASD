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

int *p[n];
int *stack[n];
int max = 0;
int pos = 0;
int top = 0;
int algorithm;
char text[9];

int *qToGet()
{
  if(pos == max) return 0;
  pos++;
  return p[pos - 1];
}

void queue(int *q)
{
  p[max] = q;
  max++;
}

struct stack
{
  float elem[n];
  int top;
};

void push(int i)
{
  stack[top] = i;
  top++;
}

int peek(void)
{
  return stack[top - 1];
}

int pop(void)
{
  top--;
  if(top < 0)  return 0;
  return stack[top];
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[] = "Лабораторна робота 5";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
  HWND hWnd;
  MSG lpMsg;
  WNDCLASS w;
  w.lpszClassName=ProgName;
  w.hInstance=hInstance;
  w.lpfnWndProc=WndProc;
  w.hCursor=LoadCursor(NULL, IDC_ARROW);
  w.hIcon=0;
  w.lpszMenuName=0;
  w.hbrBackground = LTGRAY_BRUSH;
  w.style=CS_HREDRAW|CS_VREDRAW;
  w.cbClsExtra=0;
  w.cbWndExtra=0;

  if( !RegisterClass(&w) ) return 0;

  hWnd = CreateWindow(ProgName,
            "Lab5. Hakaviy O. IP-04",
            WS_OVERLAPPEDWINDOW,
            400, 100, 1200, 800,
            (HWND)NULL, (HMENU)NULL,
            (HINSTANCE)hInstance,
            (HINSTANCE)NULL);

  ShowWindow(hWnd, nCmdShow);

  while( GetMessage(&lpMsg, hWnd, 0, 0) )
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

  void arrow(float fi, int px,int py)
  {
    fi = 3.1416 *(180.0 - fi)/180.0;
    int lx,ly,rx,ry;
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
  void drawTree(HDC hdc, int i, int j, int *nx, int *ny)
  {
    int nx0, ny0, R;
    int nxs, nys;
    double k, m;

    if (i == j)
    {
      Arc(hdc, nx[j], ny[j], nx[j] + 40, ny[j] + 40, nx[j], ny[j], nx[j], ny[j]);
      arrow(-7, nx[j], ny[j]);
      return;
    }
    if   (i > j)
    {
      nxs = (nx[i]+nx[j])/2.6 - (ny[i]-ny[j])/6;
      nys = (ny[i]+ny[j])/2.6 - (nx[i]-nx[j])/6;
      MoveToEx (hdc, nx[j], ny[j], NULL);
      LineTo (hdc, nxs, nys);
      MoveToEx (hdc, nxs, nys, NULL);
      LineTo (hdc, nx[i], ny[i]);
      R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
      k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
      m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
      arrow((360 - (340/pi*(m + k))), nx[j], ny[j]);
      return;
    }
    if ((i <= 0.3*n) && (j <= 0.3*n))
    {
      nxs = (nx[i]+nx[j])/2.6 - (ny[i]-ny[j])/6;
      nys = (ny[i]+ny[j])/2.6 - (nx[i]-nx[j])/6;
      MoveToEx (hdc, nx[j], ny[j], NULL);
      LineTo (hdc, nxs, nys);
      MoveToEx (hdc, nxs, nys, NULL);
      LineTo (hdc, nx[i], ny[i]);
      R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
      k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
      m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
      arrow((280 - (240/pi*(m + k))), nx[j], ny[j]);
      return;
    }
    if ((i >= 0.3*n) && (i <= 0.6*n) && (j >= 0.3*n) && (j <= 0.6*n))
    {
      nxs = (nx[i]+nx[j])/1.7 - (ny[i]-ny[j])/6;
      nys = (ny[i]+ny[j])/1.7 - (nx[i]-nx[j])/6;
      MoveToEx (hdc, nx[j], ny[j], NULL);
      LineTo (hdc, nxs, nys);
      MoveToEx (hdc, nxs, nys, NULL);
      LineTo (hdc, nx[i], ny[i]);
      R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
      k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
      m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
      arrow((180 - (100/pi*(m + k))), nx[j], ny[j]);
      return;
    }
    if (((i >= 0.6*n) || (i == 0)) && ((j >= 0.6*n) || (j == 0)))
    {
      nxs = (nx[i]+nx[j])/1.8 - (ny[i]-ny[j])/8;
      nys = (ny[i]+ny[j])/1.8 - (nx[i]-nx[j])/8;
      MoveToEx (hdc, nx[j], ny[j], NULL);
      LineTo (hdc, nxs, nys);
      MoveToEx (hdc, nxs, nys, NULL);
      LineTo (hdc, nx[i], ny[i]);
      R = (pow(nx[i] - nx0, 2) + pow(ny[i] - ny0, 2))/sqrt(3);
      k = atan2(ny[j] - ny[i], nx[j] - nx[i]);
      m = atan2(sqrt(pow(nx[j] - nx[i], 2) + pow(ny[j] - ny[i], 2)), R/2);
      arrow((180 - (340/pi*(m + k))), nx[j], ny[j]);
      return;
    }


    MoveToEx(hdc, nx[i], ny[i], NULL);
    LineTo(hdc, nx[j], ny[j]);
    arrow((180 - (290/pi*(m + k))), nx[j], ny[j]);
  }

  int graphTree[n][n] =  {
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 }
    };

  void BFS (HDC hdc, double **A, int a, int *nx, int *ny)
  {
    int BFSM[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    int k = 1,dx = 16, dy = 16, dtx = 5;
    sprintf_s(text, 4, " %d ", a);
    TextOut(hdc, nx[a - 1] + dtx, ny[a - 1] + dy, text, 4);
    sprintf_s(text, 8, "V%d= %d", 1, a);
    TextOutA(hdc, 25, 0, text, 8);
    BFSM[a - 1] = 1;
    queue(a);
    while (max != pos)
    {
      i = qToGet();
      for(int j = 0; j < n; j++)
      {
        if (A[i-1][j]==1 && BFSM[j]==0)
        {
          k++;
          BFSM[j]=k;
          queue(j + 1);
          drawTree(hdc, i - 1, j, nx, ny);
          graphTree[i - 1][j] = 1;
          Ellipse(hdc, nx[i-1] - dx, ny[i - 1] - dy, nx[i-1] + dx, ny[i-1] + dy);
          TextOut(hdc, nx[i-1] - dtx, ny[i-1] - dy/2,  nn[i-1], 2);
          Ellipse(hdc, nx[j] - dx, ny[j] - dy, nx[j] + dx, ny[j] + dy);
          TextOut(hdc, nx[j] - dtx, ny[j] - dy/2, nn[j], 2);
          sprintf_s(text, 4, " %d ", k);
          TextOut(hdc, nx[j] + dtx, ny[j] + dy, text, 4);
          sprintf_s(text, 9, "V%d= %d ", k, j + 1);
          TextOutA(hdc, 25 + 70*(k-1), 0, text, 9);
          system("pause");
          system("cls");
        }
      }
    }
  }

  void DFS (HDC hdc, double **A, int a, int *nx, int *ny)
  {
    int DFSM[n] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int i;
    char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    int k = 1, dx = 16, dy = 16, dtx = 5;
    sprintf_s(text, 4, " %d ", a);
    TextOut(hdc, nx[a-1] + dtx, ny[a-1] + dy, text, 4);
    sprintf_s(text, 8, "V%d= %d", 1, a);
    TextOutA(hdc, 25, 0, text, 8);
    DFSM[a-1] = 1;
    push(a);
    while (top != 0)
    {
      i=peek();
      for(int j = 0; j < n; j++)
      {
        if ((A[i-1][j] == 1) && (DFSM[j] == 0))
        {
          k++;
          DFSM[j]=k;
          push(j+1);
          drawTree(hdc, i-1, j, nx, ny);
          graphTree[i-1][j] = 1;
          Ellipse(hdc, nx[i-1]-dx,ny[i-1]-dy,nx[i-1]+dx,ny[i-1]+dy);
          TextOut(hdc, nx[i-1]-dtx,ny[i-1]-dy/2,  nn[i-1], 2);
          Ellipse(hdc, nx[j]-dx,ny[j]-dy,nx[j]+dx,ny[j]+dy);
          TextOut(hdc, nx[j]-dtx,ny[j]-dy/2,  nn[j], 2);
          sprintf_s(text, 4, " %d ", k);
          TextOut(hdc, nx[j]+dtx,ny[j]+dy, text, 4);
          sprintf_s(text, 9, "V%d= %d ", k, j+1);
          TextOutA(hdc, 25+70*(k-1), 0, text, 9);
          system("pause");
          system("cls");
          break;
        }
        if (j == 11) pop();
      }
    }
  }

  switch(messg)
  {
    case WM_PAINT :
    hdc = BeginPaint(hWnd, &ps);
    printf ("Enter 0(DFS) or 1(BFS): ");
    scanf ("%d", &algorithm);
    char *nn[n] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    int nx[n] = {};
    int ny[n] = {};

    for(int i = 0; i < n; i++)
    {
      if(i == 0)
      {
        nx[i] = 100;
        ny[i] = 450;
      } else if(i < 4)
      {
        nx[i] = nx[i - 1] + 100;
        ny[i] = ny[i - 1] - 100;
      } else if(i < 7)
      {
        nx[i] = nx[i - 1] + 100;
        ny[i] = ny[i - 1] + 100;
      } else
      {
        nx[i] = nx[i - 1] - 150;
        ny[i] = ny[i - 1];
      }
    }

    int i, dx = 16, dy = 16, dtx = 5;
    HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
    HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
    HPEN RPen = CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

    srand(0404);
    double** T = randm(n, n);
    double coef = 1 - 4*0.005 - 0.15;
    double** A = mulmr(coef, T);

    SelectObject(hdc, KPen);

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (A[i][j] == 1) drawTree(hdc, i, j, nx, ny);
      }
    }

    SelectObject(hdc, BPen);

    for(int i = 0; i < n; i++)
    {
      Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
      TextOut(hdc, nx[i] - dtx, ny[i] - dy/2,  nn[i], 2);
    }

    SelectObject(hdc, RPen);
    if (algorithm == 0)
    {
      top=0;
      DFS (hdc, A, 1, nx, ny);
      TextOutA(hdc, 650, 25, "Matrix for graphtree - DFS", 26);
    } else
    {
      max = 0; pos = 0;
      BFS (hdc, A, 1, nx, ny);
      TextOutA(hdc, 650, 25, "Matrix for graphtree - BFS", 26);
    }
    TextOutA(hdc, 25, 25, "Matrix for oriented graph", 25);
    for(int i = 0; i < n; i++)
    {
      for(int j = 0; j < n; j++)
      {
        sprintf_s(text, 2, "%g", A[i][j]);
        TextOutA(hdc, 25 + 15 * j, 25 * i + 50, text, 1);
        sprintf_s(text, 2, "%d", graphTree[i][j]);
        TextOutA(hdc, 650 + 15 * j, 25 * i + 50, text, 1);
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