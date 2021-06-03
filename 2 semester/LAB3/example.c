#include<windows.h>
#include<math.h>

//Создаём прототип функции окна, которая будет определена ниже
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//void arrow(float fi, int px,int py);

//объявляем строку-имя программы
char ProgName[]="Лабораторна робота 3";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName=ProgName; //имя программы - объявлено выше
    w.hInstance=hInstance; //идентификатор текущего приложения
    w.lpfnWndProc=WndProc; //указатель на функцию окна
    w.hCursor=LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon=0; //иконки у нас не будет пока
    w.lpszMenuName=0; //и меню пока не будет
    w.hbrBackground = LTGRAY_BRUSH; //WHITE_BRUSH;// цвет фона окна
    w.style=CS_HREDRAW|CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;

   // HWND hWnd;
    //MSG lpMsg;

//Создадим окно в памяти, заполнив аргументы CreateWindow
    hWnd=CreateWindow(ProgName, //Имя программы
        "Лабораторна робота 3. Виконав А.М.Сергієнко", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
        100, //положение окна на экране по х
        100, //положение по у
        360, //ширина
        250, //висота
        (HWND)NULL, //идентификатор родительского окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
    ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
 //   UpdateWindow(hWnd);

//Цикл одержання повідомлень

    while(GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
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

    void arrow(float fi, int px,int py){
            fi = 3.1416*(180.0 - fi)/180.0;
            int lx,ly,rx,ry; //px,py,
           // px=150; py=60;
            lx = px+15*cos(fi+0.3);
            rx = px+15*cos(fi-0.3);
            ly = py+15*sin(fi+0.3);
            ry = py+15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
         //  return 0;
      }

//Цикл обработки сообщений
    switch(messg){
    //сообщение рисования
        case WM_PAINT :


            hdc=BeginPaint(hWnd, &ps);
            char *nn[3] = {"1", "2", "3"};
            int nx[3] = {100,200,300};
            int ny[3] = {70,70,70};
            int dx = 16, dy = 16, dtx = 5;
            int i;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            SelectObject(hdc, KPen);
            MoveToEx(hdc, nx[0], ny[0], NULL); //сделать текущими координаты x1, y1
            LineTo(hdc, nx[1], ny[1]);

             arrow(0,nx[1]-dx,ny[1]);

    //  BOOL Arc(HDC hdc, int xLeft, int yTop, int xRight, int yBottom,
   //int xStart, int yStart, int xEnd, int yEnd);

            Arc(hdc, nx[0], ny[0]-40, nx[2], ny[2]+40,    nx[2], ny[2], nx[0], ny[0]);
             arrow(-45.0,nx[2]-dx*0.5,ny[2]-dy*0.8);

            SelectObject(hdc, BPen);
            for(i=0;i<=2;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i],1);
            }



            EndPaint(hWnd, &ps);//малювання закінчене
            break;

//сообщение выхода - разрушение окна
        case WM_DESTROY:
            PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}
