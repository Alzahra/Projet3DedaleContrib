#include <windows.h>
#include <Winuser.h>
#include <cmath>
#include <gl\glut.h>
#include <vector>
#include <cstdlib>
#include <gl\glaux.h>


using namespace std;

float       dx = 0.99;
int         fire = 0;

const int WSCREEN = 1920;
const int HSCREEN = 1084;

float shottime = 0;
float lifetime = 2000;
float shot =0;   // выстрел свободен

struct P
{
    float x;
    float y;
    float z;
    float vx;
    float vy;
    float vz;
    float rad;
    float life;
    float r;
    float g;
    float b;

};
vector<P> p;

static HGLRC hRC;       // Постоянный контекст рендеринга
static HDC hDC;         // Приватный контекст устройства GDI
BOOL    keys[256];      // Массив для процедуры обработки клавиатуры
const float PI =3.141592653; //Замечательно число Пи
const float height = 0; //Высота персонажа, тут нуль, дабы смещения не происходило.

float x,y,z=100;        //Положение камеры в пространстве
float distans=200;
float angleX=0;
float angleY=0;         // Углы поворота камеры
POINT mousexy;          // Сюда мы пишем положение мыши на экране.
double Playerspeed=3;

int xmax = 1000;
int xmin = -1000;
int ymax = 1000;
int ymin = 0;
int zmax = 1000;
int zmin = -1000;


void moving ()  // движение частиц
 {
        if (GetAsyncKeyState(VK_LBUTTON) && !shot)
    {
        P p0 = {
              x,
              y+50,
              z,
              -20*sin(angleX/180*PI),
               20*tan(angleY/180*PI),
              -20*cos(angleX/180*PI),
              20,
              lifetime,
              rand() % 255,      // случайный цвет красного
              rand() % 255,       // случайный цвет синего
              rand() % 255      // случайный цвет голубого
              };

        p.push_back(p0);
        shot = 1;
        shottime = 2;
        // PlaySound(TEXT("SystemStart"), NULL, SND_ALIAS);
        // PlaySound(TEXT("gun4.wav"), NULL, SND_ALIAS);
    }

    if (shot) shottime--;
    if (!shottime) shot = 0;

    for (vector<P>::iterator i = p.begin(); i != p.end(); ++i)

        {
        float   x = i->x;  float  y = i->y;  float  z = i->z;
        float   vx= i->vx; float vy = i->vy; float vz = i->vz;

        if (x > xmax -i->rad) { x = xmax - i->rad; vx*=-0.5;}
        if (x <= xmin + i->rad) { x = xmin + i->rad; vx*=-0.5;}

       // if (y > ymax - i->rad) { y = ymax - i->rad; vy*=-0.5;}
        if (y < ymin + i->rad) { y = ymin + i->rad; vy*=-0.5;
                                                        vx*=0.95;
                                                        vz*=0.95;}

        if (z > zmax - i->rad) { z = zmax - i->rad; vz*=-0.5;}
        if (z < zmin + i->rad) { z = zmin + i->rad; vz*=-0.5;}
        vy = vy - 0.05;
        x+=vx;
        y+=vy;
        z+=vz;

        i->vx=vx;
        i->vy=vy;
        i->vz=vz;

        i->x=x;
        i->y=y;
        i->z=z;
        }
 }


void line (GLfloat x1,GLfloat y1,GLfloat z1,GLfloat r1,GLfloat g1,GLfloat b1, GLfloat x2,GLfloat y2,GLfloat z2,GLfloat r2,GLfloat g2,GLfloat b2)
 {
      glBegin(GL_LINES);
      glColor3ub (r1,g1,b1); glVertex3f(x1,y1,z1);         // Право верх квадрата (Верх)
      glColor3ub (r2,g2,b2); glVertex3f(x2,y2,z2);           // Лево верх
      glEnd();
 }




GLvoid DrawGLScene()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Очистка экрана

            HCURSOR oldCursor = SetCursor(NULL);
            GetCursorPos(&mousexy);
            angleX+=0.1*(WSCREEN/2-mousexy.x);
            angleY+=0.1*(HSCREEN/2-mousexy.y);
            SetCursorPos (WSCREEN/2,HSCREEN/2);
            if (angleY<-80.0) angleY=-80.0;
            if (angleY> 80.0) angleY=80.0;

            if (angleX >= 360) angleX -= 360;
            if (angleX < 0) angleX += 360;


            // поверхность земли
            glLoadIdentity();
      //      gluLookAt(x,y,z,x-sin(angleX/180*PI),y+(tan(angleY/180*PI)),z-cos(angleX/180*PI), 0, 1, 0);

       gluLookAt(x,y,z,
                      x - sin(angleX/180*PI),
                      y + tan(angleY/180*PI),
                      z - cos(angleX/180*PI),
                      0, 1, 0);


  /*          gluLookAt(p[0].x - sin(angleX/180*PI)*-distans,
                      p[0].y + tan(angleY/180*PI)*-distans,
                      p[0].z - cos(angleX/180*PI)*-distans,
                      p[0].x,p[0].y,p[0].z,
                      0, 1, 0);*/

            glBegin(GL_QUADS);
                glColor3f(1.0f,1.0f,1.0f);              // Оранжевый
                glVertex3f( xmin, 0,  zmin);          // Верх право квадрата (Низ)
                glVertex3f( xmax, 0,  zmin);          // Верх лево
                glVertex3f( xmax, 0,  zmax);          // Низ лево
                glVertex3f( xmin, 0,  zmax);          // Низ право
            glEnd();

           // поверхность земли
            for (vector<P>::iterator i = p.begin(); i != p.end(); ++i)
            {
            glPushMatrix();
            glTranslatef    (i->x, i->y, i->z);
            glColor3ub      (i->r, i->g, i->b);
         //   glutSolidSphere (p[i].rad,15,15);
            auxSolidSphere (i->rad);
            glPopMatrix();
            }

     for (vector<P>::iterator i = p.begin(); i != p.end(); ++i)
        for (vector<P>::iterator j = p.begin(); j != p.end(); ++j)
             {
              if (i!=j)

              {
                float d = sqrt((i->x - j->x) * (i->x - j->x) + (i->y - j->y) * (i->y - j->y) + (i->z - j->z) * (i->z - j->z) );

                if (d<200) {line   (i->x,i->y,i->z,i->r,i->g,i->b, j->x,j->y,j->z,j->r,j->g,j->b);}
				if (d < i->rad + j->rad)
				{
					float f = (i->rad + j->rad - d);
					i->vx += f * (i->x - j->x) / d / i->rad;
					i->vy += f * (i->y - j->y) / d / i->rad;
					i->vz += f * (i->z - j->z) / d / i->rad;

					j->vx -= f * (i->x - j->x) / d / j->rad;
					j->vy -= f * (i->y - j->y) / d / j->rad;
					j->vz -= f * (i->z - j->z) / d / j->rad;

					i->vx *= 0.95;
					i->vy *= 0.95;
					j->vx *= 0.95;
					j->vy *= 0.95;
				}
           }

        }
}

GLvoid InitGL(GLsizei Width, GLsizei Height)                                        // Вызвать после создания окна GL
{
                  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                             // Очистка экрана в черный цвет
                  glClearDepth(1.0);                                                // Разрешить очистку буфера глубины
                  glDepthFunc(GL_LESS);                                             // Тип теста глубины
                  glEnable(GL_DEPTH_TEST );                                          // разрешить тест глубины
                  glShadeModel(GL_SMOOTH);                                          // разрешить плавное цветовое сглаживание
                  glMatrixMode(GL_PROJECTION);                                      // Выбор матрицы проекции
                  glLoadIdentity();                                                 // Сброс матрицы проекции
                  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000000.0f); // Вычислить соотношение геометрических размеров для окна
                  glMatrixMode(GL_MODELVIEW);                                        // Выбор матрицы просмотра модели
}

GLvoid ReSizeGLScene(GLsizei Width, GLsizei Height)
{
        if (Height==0) Height=1;                                                    // Предотвращение деления на ноль, если окно слишком мало

        glViewport(0, 0, Width, Height);                                            // Сброс текущей области вывода и перспективных преобразований
        glMatrixMode(GL_PROJECTION);                                                // Выбор матрицы проекций
        glLoadIdentity();                                                           // Сброс матрицы проекции
        gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000000.0f);           // Вычисление соотношения геометрических размеров для окна
        glMatrixMode(GL_MODELVIEW);                                                 // Выбор матрицы просмотра модели
}


LRESULT CALLBACK WndProc(HWND    hWnd, UINT    message, WPARAM  wParam, LPARAM  lParam)

{
        RECT    Screen;         // используется позднее для размеров окна
        GLuint  PixelFormat;
        static  PIXELFORMATDESCRIPTOR pfd=
        {
        sizeof(PIXELFORMATDESCRIPTOR),  // Размер этой структуры
        1,                              // Номер версии (?)
        PFD_DRAW_TO_WINDOW |            // Формат для Окна
        PFD_SUPPORT_OPENGL |            // Формат для OpenGL
        PFD_DOUBLEBUFFER,               // Формат для двойного буфера
        PFD_TYPE_RGBA,                  // Требуется RGBA формат
        16,                             // Выбор 16 бит глубины цвета
        0, 0, 0, 0, 0, 0,               // Игнорирование цветовых битов (?)
        0,                              // нет буфера прозрачности
        0,                              // Сдвиговый бит игнорируется (?)
        0,                              // Нет буфера аккумуляции
        0, 0, 0, 0,                     // Биты аккумуляции игнорируются (?)
        16,                             // 16 битный Z-буфер (буфер глубины)
        0,                              // Нет буфера траффарета
        0,                              // Нет вспомогательных буферов (?)
        PFD_MAIN_PLANE,                 // Главный слой рисования
        0,                              // Резерв (?)
        0, 0, 0                         // Маски слоя игнорируются (?)
        };


 switch (message)        // Тип сообщения
        {
        case WM_CREATE:

        hDC = GetDC(hWnd);      // Получить контекст устройства для окна
        PixelFormat = ChoosePixelFormat(hDC, & pfd);
        // Найти ближайшее совпадение для нашего формата пикселов

        if (!PixelFormat) {MessageBox(0,"Can't Find A Suitable PixelFormat.","Error",MB_OK|MB_ICONERROR); PostQuitMessage(0);  break;}  // Это сообщение говорит, что программа должна завершится
        if (!SetPixelFormat(hDC,PixelFormat,&pfd)){MessageBox(0,"Can't Set ThePixelFormat.","Error",MB_OK|MB_ICONERROR);PostQuitMessage(0);break;}
        hRC = wglCreateContext(hDC);
        if(!hRC) {MessageBox(0,"Can't Create A GL Rendering Context.","Error",MB_OK|MB_ICONERROR); PostQuitMessage(0); break;}
        if(!wglMakeCurrent(hDC, hRC)) {MessageBox(0,"Can't activate GLRC.","Error",MB_OK|MB_ICONERROR); PostQuitMessage(0); break; }
        GetClientRect(hWnd, & Screen);
        InitGL(Screen.right, Screen.bottom);
        break;
  case WM_DESTROY:
  case WM_CLOSE:
                ChangeDisplaySettings(NULL, 0);
                wglMakeCurrent(hDC,NULL);
                wglDeleteContext(hRC);
                ReleaseDC(hWnd,hDC);
                PostQuitMessage(0);
                break;

  case WM_KEYDOWN:
                keys[wParam] = TRUE;
                break;

  case WM_KEYUP:
                keys[wParam] = FALSE;
                break;

  case WM_SIZE:
                ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));
                break;

        default:
        return (DefWindowProc(hWnd, message, wParam, lParam));
        }
        return (0);
}
void  lifeball()
{
      for (vector<P>::iterator i = p.begin(); i != p.end();)
    {
            i -> life --;
            if (i -> life ==0) i = p.erase(i);
            else ++i;
    }
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
        MSG                         msg;    // Структура сообщения Windows
        WNDCLASS                    wc; // Структура класса Windows для установки типа окна
        HWND                        hWnd;   // Сохранение дискриптора окна

        wc.style                = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.lpfnWndProc          = (WNDPROC) WndProc;
        wc.cbClsExtra           = 0;
        wc.cbWndExtra           = 0;
        wc.hInstance            = hInstance;
        wc.hIcon                = NULL;
        wc.hCursor              = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground        = NULL;
        wc.lpszMenuName         = NULL;
        wc.lpszClassName        = "OpenGL WinClass";

     if(!RegisterClass(&wc)){MessageBox(0,"Failed To Register The WindowClass.","Error",MB_OK|MB_ICONERROR);return FALSE;}
     hWnd = CreateWindow("OpenGL WinClass","Jeff Molofee's GL Code Tutorial ... NeHe '99", WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
                              0, 0, WSCREEN, HSCREEN, NULL, NULL, hInstance, NULL);


      if(!hWnd) {MessageBox(0,"Window Creation Error.","Error",MB_OK|MB_ICONERROR);return FALSE;}

      DEVMODE dmScreenSettings;                       // Режим работы

      memset(&dmScreenSettings, 0, sizeof(DEVMODE));          // Очистка для хранения установок
            dmScreenSettings.dmSize = sizeof(DEVMODE);              // Размер структуры Devmode
            dmScreenSettings.dmPelsWidth    = WSCREEN;                  // Ширина экрана
            dmScreenSettings.dmPelsHeight   = HSCREEN;                  // Высота экрана
            dmScreenSettings.dmFields       = DM_PELSWIDTH | DM_PELSHEIGHT; // Режим Пиксела
            ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
                    // Переключение в полный экран

            ShowWindow(hWnd, SW_SHOW);
            UpdateWindow(hWnd);
            SetFocus(hWnd);
    while (1)
    {
                while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
                    { if (GetMessage(&msg, NULL, 0, 0)) { TranslateMessage(&msg); DispatchMessage(&msg);}
                       else { return TRUE;}
                    }

        DrawGLScene();                                      // Нарисовать сцену
        SwapBuffers(hDC);                                   // Переключить буфер экрана
        if (keys[VK_ESCAPE]) SendMessage(hWnd,WM_CLOSE,0,0);                 // Если ESC - выйти


            if (keys[0x57]) //w
                {
                x -= (float)sin(angleX/180*PI) * Playerspeed;
                y += (float)tan(angleY/180*PI) * Playerspeed;
                z -= (float)cos(angleX/180*PI) * Playerspeed;
                }
            if (keys[0x53])//s
                {
                x += (float)sin(angleX/180*PI) * Playerspeed;
                y -= (float)tan(angleY/180*PI) * Playerspeed;
                z += (float)cos(angleX/180*PI) * Playerspeed;

                }
            if (keys[0x44]) //right
                {
                x += (float)sin(( angleX + 90)/180*PI) * Playerspeed;
                z += (float)cos(( angleX + 90)/180*PI) * Playerspeed;
                }
            if (keys[0x41])//left
                {
                x += (float)sin(( angleX - 90)/180*PI) * Playerspeed;
                z += (float)cos(( angleX - 90)/180*PI) * Playerspeed;
                }
                if (y <5) y=5;
                moving();
                lifeball();
        }
}
