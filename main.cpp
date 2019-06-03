#include<GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

#define PI 3.1415926
int WinWidth, WinHeight;

// 绘制立方体
// 立方体的8个顶点坐标
static GLfloat vertex_list[][3] = {
        -3.0f, -3.0f, -3.0f,
        3.0f, -3.0f, -3.0f,
        -3.0f, 3.0f, -3.0f,
        3.0f, 3.0f, -3.0f,
        -3.0f, -3.0f, 3.0f,
        3.0f, -3.0f, 3.0f,
        -3.0f, 3.0f, 3.0f,
        3.0f, 3.0f, 3.0f,
};

static GLint index_list[][4] = {
        0, 2, 3, 1,
        0, 4, 6, 2,
        0, 1, 5, 4,
        4, 5, 7, 6,
        1, 3, 7, 5,
        2, 6, 7, 3,
};
// 绘制立方体
void DrawCube(void)
{
    int i, j;
    // 定义不同的颜色
    GLfloat colors[][3] = { { 0.0, 0.0, 1.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0, 0.0 },
                            { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 1.0 },
                            { 1.0, 0.5, 0.5 }, { 0.0, 0.5, 0.5 } };

    glBegin(GL_QUADS);
    for (i = 0; i < 6; ++i)
    {
        glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        for (j = 0; j < 4; ++j)
        {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
}

static float rotate1 = 0;
static float rotate2 = 0;
static int times = 0;
static int deltaX=0;
static int deltaY=0;
static int xb=0;
static int yb=0;


void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();

    times++;
    if (times > 100)
    {
        times = 0;
    }
    if (times % 100 == 0)
    {
        if(deltaX !=0)
        {
            for(int i = 0;i < 8; i++)
            {
                float a = vertex_list[i][0] * 1.0;
                float c = vertex_list[i][2] * 1.0;
                vertex_list[i][2] = (float)(c * cos((float)deltaX / 25.0 / 360.0) - a * sin((float)deltaX / 25.0 / 360.0));
                vertex_list[i][0] = (float)(c * sin((float)deltaX / 25.0 / 360.0) + a * cos((float)deltaX / 25.0 / 360.0));
            }
        }
        if( deltaY !=0)
        {
            for(int i = 0; i < 8; i++)
            {
                float b = vertex_list[i][1]* 1.0;
                float c = vertex_list[i][2]* 1.0;
                vertex_list[i][1] = (float)(b * cos(((float)deltaY / 25.0 / 360.0)) - c * sin(((float)deltaY / 25.0 / 360.0)));
                vertex_list[i][2] = (float)(b * sin(((float)deltaY / 25.0 / 360.0)) + c * cos(((float)deltaY / 25.0 / 360.0)));
            }
            yb=deltaY;
        }

    }

    glColor3f(0, 0, 1);
    DrawCube();
    glPopMatrix();
    glutSwapBuffers();
}

void Reshape(int w, int h)
{
    WinWidth = w;
    WinHeight = h;
    // //改变显示区域，起始位置为客户端窗口左下角（非坐标原点）
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //宽高比改为当前值，视线区域与屏幕大小一致；
    gluPerspective(45, 1.0*WinWidth / WinHeight, 1, 1000);
    // 开启更新深度缓冲区的功能
    glEnable(GL_DEPTH_TEST);
    // 摄像机视图观看，从 （0，5，20） 往（0，0，0）处看，（0，1，0）为正方向
    gluLookAt(0, 5, 20, 0, 0, 0, 0, 1, 0);
}

void passivemotion( int x, int y ) {

    int centerX = 400;
    int centerY = 400;

    deltaX = (x - centerX);
    deltaY = (y - centerY);

    if(deltaX >=xb && deltaX>=0)
    {
        for(int i = 0;i < 8; i++)
        {
            float a = vertex_list[i][0] * 1.0;
            float c = vertex_list[i][2] * 1.0;
            vertex_list[i][2] = (float)(c * cos((float)deltaX / 25.0 / 360.0) - a * sin((float)deltaX / 25.0 / 360.0));
            vertex_list[i][0] = (float)(c * sin((float)deltaX / 25.0 / 360.0) + a * cos((float)deltaX / 25.0 / 360.0));
        }
        xb=deltaX;
    }
    if(deltaX >=xb && deltaX<0)
    {
        for(int i = 0;i < 8; i++)
        {
            float a = vertex_list[i][0] * 1.0;
            float c = vertex_list[i][2] * 1.0;
            vertex_list[i][2] = (float)(c * cos(-(float)deltaX / 25.0 / 360.0) - a * sin(-(float)deltaX / 25.0 / 360.0));
            vertex_list[i][0] = (float)(c * sin(-(float)deltaX / 25.0 / 360.0) + a * cos(-(float)deltaX / 25.0 / 360.0));
        }
        xb=deltaX;
    }
    if(deltaX <xb && deltaX>=0)
    {
        for(int i = 0;i < 8; i++)
        {
            float a = vertex_list[i][0] * 1.0;
            float c = vertex_list[i][2] * 1.0;
            vertex_list[i][2] = (float)(c * cos(-(float)deltaX / 25.0 / 360.0) - a * sin(-(float)deltaX / 25.0 / 360.0));
            vertex_list[i][0] = (float)(c * sin(-(float)deltaX / 25.0 / 360.0) + a * cos(-(float)deltaX / 25.0 / 360.0));
        }
        xb=deltaX;
    }
    if(deltaX <xb && deltaX<0)
    {
        for(int i = 0;i < 8; i++)
        {
            float a = vertex_list[i][0] * 1.0;
            float c = vertex_list[i][2] * 1.0;
            vertex_list[i][2] = (float)(c * cos((float)deltaX / 25.0 / 360.0) - a * sin((float)deltaX / 25.0 / 360.0));
            vertex_list[i][0] = (float)(c * sin((float)deltaX / 25.0 / 360.0) + a * cos((float)deltaX / 25.0 / 360.0));
        }
        xb=deltaX;

    }

   if( deltaY >=yb && deltaY>=0)
    {
        for(int i = 0; i < 8; i++)
        {
            float b = vertex_list[i][1]* 1.0;
            float c = vertex_list[i][2]* 1.0;
            vertex_list[i][1] = (float)(b * cos(((float)deltaY / 25.0 / 360.0)) - c * sin(((float)deltaY / 25.0 / 360.0)));
            vertex_list[i][2] = (float)(b * sin(((float)deltaY / 25.0 / 360.0)) + c * cos(((float)deltaY / 25.0 / 360.0)));
        }
        yb=deltaY;
    }
    if( deltaY <yb && deltaY>=0)
    {
        for(int i = 0; i < 8; i++)
        {
            float b = vertex_list[i][1]* 1.0;
            float c = vertex_list[i][2]* 1.0;
            vertex_list[i][1] = (float)(b * cos(-((float)deltaY / 25.0 / 360.0)) - c * sin(-((float)deltaY / 25.0 / 360.0)));
            vertex_list[i][2] = (float)(b * sin(-((float)deltaY / 25.0 / 360.0)) + c * cos(-((float)deltaY / 25.0 / 360.0)));
        }
        yb=deltaY;
    }
    if( deltaY >=yb && deltaY<0)
    {
        for(int i = 0; i < 8; i++)
        {
            float b = vertex_list[i][1]* 1.0;
            float c = vertex_list[i][2]* 1.0;
            vertex_list[i][1] = (float)(b * cos(-((float)deltaY / 25.0 / 360.0)) - c * sin(-((float)deltaY / 25.0 / 360.0)));
            vertex_list[i][2] = (float)(b * sin(-((float)deltaY / 25.0 / 360.0)) + c * cos(-((float)deltaY / 25.0 / 360.0)));
        }
        yb=deltaY;
    }
    if( deltaY <yb && deltaY<0)
    {
        for(int i = 0; i < 8; i++)
        {
            float b = vertex_list[i][1]* 1.0;
            float c = vertex_list[i][2]* 1.0;
            vertex_list[i][1] = (float)(b * cos(((float)deltaY / 25.0 / 360.0)) - c * sin(((float)deltaY / 25.0 / 360.0)));
            vertex_list[i][2] = (float)(b * sin(((float)deltaY / 25.0 / 360.0)) + c * cos(((float)deltaY / 25.0 / 360.0)));
        }
        yb=deltaY;
    }
}

int main(int argc, char **argv)
{
    WinWidth = 800;
    WinHeight = 800;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WinWidth, WinHeight);
    glutCreateWindow("tuxingxuekeshe");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(&Reshape);
    glutPassiveMotionFunc(&passivemotion);
    glutIdleFunc(renderScene);
    glutMainLoop();
    return 0;
}