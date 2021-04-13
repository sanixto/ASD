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

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px,int py);

//объявляем строку-имя программы
char ProgName[] = "Лабораторна робота 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style = CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if ( !RegisterClass(&w) ) return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd = CreateWindow(ProgName, //Имя программы
                        "LAB 3 Gakavy IP-04", //Заголовок окна
                         WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
                         400, //положение окна на экране по х
                         100, //положение по у
                         900, //ширина
                         600, //висота
                         (HWND)NULL, //идентификатор родительского окна
                         (HMENU)NULL, //идентификатор меню
                         (HINSTANCE)hInstance, //идентификатор экземпляра программы
                         (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
 //   UpdateWindow(hWnd);

//Цикл одержання повідомлень

    while ( GetMessage(&lpMsg, hWnd, 0, 0) ) //Получаем сообщение из очереди
    {
      TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
      DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
    }
    return(lpMsg.wParam);
}

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
{
  HDC hdc; //создаём контекст устройства
  PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
  /*
  void arrow(float fi, int px, int py)
  {
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry; //px,py,
    // px=150; py=60;
    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
    //  return 0;
  }
  */
//Цикл обработки сообщений
  switch(messg)
  {
  //сообщение рисования
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

  //srand(0404);
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

  //Arc(hdc, nx[0], ny[0]-40, nx[2], ny[2]+40, nx[2], ny[2], nx[0], ny[0]);

  for (int i = 0; i < n; i++)
  {
      for (int j = 0; j < n; j++)
      {
        Ellipse(hdc, nx[i] - dx, ny[i] - dy, nx[i] + dx, ny[i] + dy);
        TextOut(hdc, nx[i] - dtx, ny[i] - dy / 2,  nn[i], 2);
      }
  }

/*
    SelectObject(hdc, KPen);
    MoveToEx(hdc, nx[0], ny[0], NULL); //сделать текущими координаты x1, y1
    LineTo(hdc, nx[1], ny[1]);
*/
  //arrow(0, nx[1] - dx, ny[1]);

  //  BOOL Arc(HDC hdc, int xLeft, int yTop, int xRight, int yBottom,
  //int xStart, int yStart, int xEnd, int yEnd);

  //Arc(hdc, nx[0], ny[0] - 40, nx[2], ny[2] + 40, nx[2], ny[2], nx[0], ny[0]);
  //arrow(-45.0,nx[2]-dx*0.5,ny[2]-dy*0.8);

  EndPaint(hWnd, &ps);//малювання закінчене
  break;

  //сообщение выхода - разрушение окна
  case WM_DESTROY:
  PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
  break;

  default:
  return( DefWindowProc(hWnd, messg, wParam, lParam) );
  //освобождаем очередь приложения от нераспознаных
  }
    return 0;
}
