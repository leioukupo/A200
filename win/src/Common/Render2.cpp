/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : Render.cpp
  @Author        : Chen Shangwei
  @Date          : 2015-06-05
  @Description   : ImiNeck Sample
  @Version       : 0.1.0

  @History       :
  1.2015-06-05 Chen Shangwei Created file
********************************************************************************/

#if defined(_WIN32)

#include "glew.h"

#endif

#include "freeglut.h"
#include <stdio.h>
#include <string.h>
#include <cmath>

#include "Render2.h"


#if defined(_WIN32)
#define IMISnprintf _snprintf_s
#else
#define IMISnprintf snprintf
#endif


//��꽻���йص�
int mousetate = 0; //��굱ǰ��״̬
GLfloat Oldx = 0.0; // ���֮ǰ��λ��
GLfloat Oldy = 0.0;
//��ʵ�ֽǶȴ�С��صĲ�����ֻ��Ҫ�����Ϳ������
float xRotate = 17.0f;
float yRotate = 21.0f;
float scale = 1.0;

float fieldAngle = 60.0;

GLuint showFaceList, showWireList, showPointList;


POSITION2 SampleRender2::m_CursorPos;

SampleRender2 *SampleRender2::g_pSampleRender = NULL;

void SampleRender2::glutKeyboard(unsigned char key, int x, int y) {
    g_pSampleRender->onKey(key, x, y);
}

SampleRender2::SampleRender2(const char *pRenderName, const uint32_t winSizeX, const uint32_t winSizeY) :
        m_strRenderName(pRenderName),
        m_nTexMapX(winSizeX),
        m_nTexMapY(winSizeY),
        m_pTexMap(NULL),
        m_NeedImage(NULL),
        m_pUserCookie(NULL),
        m_keyboard(NULL),
        m_glWin(0),
        m_nWindowWidth(winSizeX),
        m_nWindowHeight(winSizeY),
        m_bShowPoint(true),
        m_bShowMesh(false) {
    g_pSampleRender = this;
    memset(&m_hint, 0, sizeof(m_hint));
}

SampleRender2::~SampleRender2() {
    if (NULL != m_pTexMap) {
        delete[] m_pTexMap;
        m_pTexMap = NULL;
    }

    g_pSampleRender = NULL;
}

bool SampleRender2::init(int argc, char **argv) {
    m_pTexMap = new RGB888Pixel[m_nTexMapX * m_nTexMapY];
    return initOpenGL(argc, argv);
}

void SampleRender2::setDataCallback(NeedImageCb needImage, void *pData) {
    m_NeedImage = needImage;
    m_pUserCookie = pData;
}

bool SampleRender2::run() {
    if (m_NeedImage) {
        glutIdleFunc(glutIdle);
    }

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();

    return true;
}

void SampleRender2::update() {
    // Swap the OpenGL display buffers
    glutSwapBuffers();
}

void SampleRender2::display() {
    if (NULL != m_NeedImage) {
        m_NeedImage(m_pUserCookie);
    }
}

// ��꽻��
void myMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mousetate = 1;
        Oldx = (float) x;
        Oldy = (float) y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
        mousetate = 0;
    //�����¼�
    if (state == GLUT_UP && button == 3) {
        scale += (float) 0.1;
    }
    if (state == GLUT_UP && button == 4) {
        scale -= (float) 0.1;
    }
    glutPostRedisplay();
}

// ����˶�ʱ
void onMouseMove(int x, int y) {
    if (mousetate) {
        //x��Ӧy����Ϊ��Ӧ���Ƿ�����
        yRotate += (float) x - Oldx;
        Oldx = (float) x;
        xRotate += (float) y - Oldy;
        Oldy = (float) y;
        glutPostRedisplay();
        //printf("xRotate = %f, yRotate = %f\n", xRotate, yRotate);
    }
}

bool SampleRender2::initOpenGL(int32_t argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLUT_Double ��ʾʹ��˫������ǵ�����
    glutInitWindowPosition(5, 5);
    glutInitWindowSize(m_nTexMapX, m_nTexMapY);
    m_glWin = glutCreateWindow(m_strRenderName.c_str());

    glViewport(0, 0, m_nTexMapX, m_nTexMapY);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(
            GL_DEPTH_TEST); //����������Ȼ������Ĺ��ܣ�������OPengl�Ϳ��Ը���Z���ϵ����أ���ô��ֻ����ǰ��û�ж���������²Ż����������أ��ڻ���3dʱ��������ã��Ӿ�Ч����Ƚ���ʵ
    // ------------------- Lighting  
    glEnable(GL_LIGHTING); // ���enbale��ô��ʹ�õ�ǰ�Ĺ��ղ���ȥ�Ƶ��������ɫ
    glEnable(GL_LIGHT0); //��һ����Դ����GL_LIGHT1��ʾ�ڶ�����Դ

    glutMouseFunc(myMouse);
    glutMotionFunc(onMouseMove); // ����ƶ���ʱ��ĺ���
    glutDisplayFunc(glutDisplay);
    glutReshapeFunc(glutWindowReshape);
    glutKeyboardFunc(glutKeyboard);

    //showFaceList = glGenLists(1);
    //showWireList = glGenLists(1);
    //showPointList = glGenLists(1);

    return true;
}


RenderWindow SampleRender2::createSubWin(WinHint2 &winhint) {
    if (m_glWin < 0) {
        return -1;
    }

    RenderWindow win = glutCreateSubWindow(m_glWin, winhint.x, winhint.y, winhint.w, winhint.h);
    glutSetCursor(GLUT_CURSOR_NONE);
    //glDisable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);

    return win;
}

void SampleRender2::glutIdle() {
    SampleRender2::g_pSampleRender->display();
}

void SampleRender2::glutDisplay() {
    //SampleRender2::g_pSampleRender->display();
}

void SampleRender2::glutMouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) {
        return;
    }

    //left button down mark the Cursor position
    if (GLUT_LEFT_BUTTON == button) {
        m_CursorPos.x = x * g_pSampleRender->m_nTexMapX / g_pSampleRender->m_nWindowWidth;
        m_CursorPos.y = y * g_pSampleRender->m_nTexMapY / g_pSampleRender->m_nWindowHeight;
    }

    //right button clear the Cusor position
    if (GLUT_RIGHT_BUTTON == button) {
        m_CursorPos.x = 0;
        m_CursorPos.y = 0;
    }
}

void SampleRender2::onKey(unsigned char key, int32_t x, int32_t y) {
    switch (key) {
        case 27 :
        case 'Q':
        case 'q':
            glutLeaveMainLoop();
            break;
        case 'r':
            break;
        case '2':
            break;
        case '3':
            break;
        case 'm':
            break;
    }

    if (m_keyboard) {
        m_keyboard(key, x, y);
    }

}

void SampleRender2::glutWindowReshape(int width, int height) {
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);//set viewpoint
    glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix
    glLoadIdentity();//replace the current matrix with the identity matrix
    gluPerspective(fieldAngle, (GLfloat) width / (GLfloat) height, 0.5, 30.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void
SampleRender2::drawMesh2(ImiPoint3D *p3ddata, uint8_t *pColor, uint32_t pointCount, uint32_t width, uint32_t height) {

    //calminmax(p3ddata, pointCount);
    //Ҫ���֮ǰ����Ȼ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //����ʾ��صĺ���
    glRotatef(xRotate, 1.0f, 0.0f, 0.0f); // ��������ת�ĺ��� ��һ�������ǽǶȴ�С������Ĳ�������ת�ķ�����
    glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale); // ����
    //printf("scale = %f\n",scale);

    glDisable(GL_LIGHTING);
    glPointSize(/*0.5*/1.5f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POINTS);

    float translationStep = 1.9f;
    if (pointCount == 640 * 480) {
        int width = 640;
        int height = 480;
        int index = 0;
        for (int i = 0; i < height; i += 2) {
            for (int j = 0; j < width; j += 2) {
                index = i * width + j;
                if (p3ddata[index].x != 0 || p3ddata[index].y != 0 || p3ddata[index].z != 0) {
                    //glBegin(GL_POINTS);
                    if (0 != pColor) {
                        glColor3f(pColor[index * 3], pColor[index * 3 + 1], pColor[index * 3 + 2]);
                    } else
                        glColor3f(1.5 - p3ddata[i].z * 1.2, 1.0 - p3ddata[i].z, p3ddata[index].z * 1.5);
                    glVertex3f(p3ddata[index].x, -p3ddata[index].y, -p3ddata[index].z + translationStep);

                    //glEnd();
                }
            }
        }
    } else {
        for (uint32_t i = 0; i < pointCount; ++i) {
            if (p3ddata[i].x != 0 || p3ddata[i].y != 0 || p3ddata[i].z != 0) {
                //glBegin(GL_POINTS);
                glColor3f(0.3f, 0.8f, p3ddata[i].z * 0.5);
                glVertex3f(p3ddata[i].x, -p3ddata[i].y, -p3ddata[i].z + translationStep);
                //glEnd();
            }
        }
    }

    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0, 0, 0);
    float aspectRatio = (float) 4.0 / (float) 3.0;
    float nearPlane = 0.5;
    float farPlane = 2.5;
    drawFrustum(fieldAngle, aspectRatio, nearPlane, 10);

    update();
}

void SampleRender2::drawMesh(ImiPoint3D *p3ddata, uint32_t pointCount, uint32_t width, uint32_t height) {
    //calminmax(p3ddata, pointCount);
    //Ҫ���֮ǰ����Ȼ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //����ʾ��صĺ���
    glRotatef(xRotate, 1.0f, 0.0f, 0.0f); // ��������ת�ĺ��� ��һ�������ǽǶȴ�С������Ĳ�������ת�ķ�����
    glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale); // ����
    //printf("scale = %f\n",scale);

    glDisable(GL_LIGHTING);
    glPointSize(/*0.5*/0.8f);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_POINTS);

    float translationStep = 1.9f;
    if (pointCount == 640 * 480) {
        int width = 640;
        int height = 480;
        int index = 0;
        for (int i = 0; i < height; i += 2) {
            for (int j = 0; j < width; j += 2) {
                index = i * width + j;
                if (p3ddata[index].x != 0 || p3ddata[index].y != 0 || p3ddata[index].z != 0) {
                    //glBegin(GL_POINTS);
                    glColor3f(1.5 - p3ddata[i].z * 1.2, 1.0 - p3ddata[i].z, p3ddata[index].z * 1.5);
                    glVertex3f(p3ddata[index].x, -p3ddata[index].y, -p3ddata[index].z + translationStep);

                    //glEnd();
                }
            }
        }
    } else {
        for (uint32_t i = 0; i < pointCount; ++i) {
            if (p3ddata[i].x != 0 || p3ddata[i].y != 0 || p3ddata[i].z != 0) {
                //glBegin(GL_POINTS);
                glColor3f(0.3f, 0.8f, p3ddata[i].z * 0.5);
                glVertex3f(p3ddata[i].x, -p3ddata[i].y, -p3ddata[i].z + translationStep);
                //glEnd();
            }
        }
    }

    glEnd();
    glEnable(GL_LIGHTING);

    glTranslatef(0, 0, 0);
    float aspectRatio = (float) 4.0 / (float) 3.0;
    float nearPlane = 0.5;
    float farPlane = 2.5;
    drawFrustum(fieldAngle, aspectRatio, nearPlane, 10);

    update();
}

const float DEG2RAD = 3.141593f / 180;

// draw frustum
///////////////////////////////////////////////////////////////////////////////
void SampleRender2::drawFrustum(float fovY, float aspectRatio, float nearPlane, float farPlane) {
    float centrumPoint = 1.9f;
    //include in cmath
    float tangent = tanf(fovY / 2 * DEG2RAD);
    float nearHeight = nearPlane * tangent;
    float nearWidth = nearHeight * aspectRatio;
    float farHeight = farPlane * tangent;
    float farWidth = farHeight * aspectRatio;

    // compute 8 vertices of the frustum
    float vertices[8][3];
    // near top right
    vertices[0][0] = nearWidth;
    vertices[0][1] = nearHeight;
    vertices[0][2] = (centrumPoint - nearPlane);
    // near top left
    vertices[1][0] = -nearWidth;
    vertices[1][1] = nearHeight;
    vertices[1][2] = (centrumPoint - nearPlane);
    // near bottom left
    vertices[2][0] = -nearWidth;
    vertices[2][1] = -nearHeight;
    vertices[2][2] = (centrumPoint - nearPlane);
    // near bottom right
    vertices[3][0] = nearWidth;
    vertices[3][1] = -nearHeight;
    vertices[3][2] = (centrumPoint - nearPlane);
    // far top right
    vertices[4][0] = farWidth;
    vertices[4][1] = farHeight;
    vertices[4][2] = (centrumPoint - farPlane);
    // far top left
    vertices[5][0] = -farWidth;
    vertices[5][1] = farHeight;
    vertices[5][2] = (centrumPoint - farPlane);
    // far bottom left
    vertices[6][0] = -farWidth;
    vertices[6][1] = -farHeight;
    vertices[6][2] = (centrumPoint - farPlane);
    // far bottom right
    vertices[7][0] = farWidth;
    vertices[7][1] = -farHeight;
    vertices[7][2] = (centrumPoint - farPlane);

    float colorLine1[4] = {0.8f, 0.0f, 0.0f, 0.8f};
    float colorLine2[4] = {0.4f, 0.f, 0.f, 0.6f};
    float colorPlane[4] = {0.5f, 0.5f, 0.5f, 0.0f};

    glDisable(GL_LIGHTING);
    //glDisable(GL_CULL_FACE);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw the edges around frustum
    glBegin(GL_LINES);
    glColor4fv(colorLine2);
    glVertex3f(0, 0, centrumPoint);
    glColor4fv(colorLine1);
    glVertex3fv(vertices[4]);

    glColor4fv(colorLine2);
    glVertex3f(0, 0, centrumPoint);
    glColor4fv(colorLine1);
    glVertex3fv(vertices[5]);

    glColor4fv(colorLine2);
    glVertex3f(0, 0, centrumPoint);
    glColor4fv(colorLine1);
    glVertex3fv(vertices[6]);

    glColor4fv(colorLine2);
    glVertex3f(0, 0, centrumPoint);
    glColor4fv(colorLine1);
    glVertex3fv(vertices[7]);
    glEnd();

    glColor4fv(colorLine1);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertices[4]);
    glVertex3fv(vertices[5]);
    glVertex3fv(vertices[6]);
    glVertex3fv(vertices[7]);
    glEnd();

    glColor4fv(colorLine1);
    glBegin(GL_LINE_LOOP);
    glVertex3fv(vertices[0]);
    glVertex3fv(vertices[1]);
    glVertex3fv(vertices[2]);
    glVertex3fv(vertices[3]);
    glEnd();

    // draw near and far plane
    //glColor4fv(colorPlane);
    //glBegin(GL_QUADS);
    //glVertex3fv(vertices[0]);
    //glVertex3fv(vertices[1]);
    //glVertex3fv(vertices[2]);
    //glVertex3fv(vertices[3]);
    //glVertex3fv(vertices[4]);
    //glVertex3fv(vertices[5]);
    //glVertex3fv(vertices[6]);
    //glVertex3fv(vertices[7]);
    //glEnd();

    //glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
}

void SampleRender2::calminmax(ImiPoint3D *p3ddata, uint32_t pointCount) {
    MinMaxXYZ[0] = p3ddata[0].x;
    MinMaxXYZ[1] = p3ddata[0].x;
    MinMaxXYZ[2] = p3ddata[0].y;
    MinMaxXYZ[3] = p3ddata[0].y;
    MinMaxXYZ[4] = p3ddata[0].z;
    MinMaxXYZ[5] = p3ddata[0].z;
    for (uint32_t i = 1; i < pointCount; ++i) {
        if (MinMaxXYZ[0] > p3ddata[i].x) {
            MinMaxXYZ[0] = p3ddata[i].x;
        }
        if (MinMaxXYZ[1] < p3ddata[i].x) {
            MinMaxXYZ[1] = p3ddata[i].x;
        }
        if (MinMaxXYZ[2] > p3ddata[i].y) {
            MinMaxXYZ[2] = p3ddata[i].y;
        }
        if (MinMaxXYZ[3] < p3ddata[i].y) {
            MinMaxXYZ[3] = p3ddata[i].y;
        }
        if (MinMaxXYZ[4] > p3ddata[i].z) {
            MinMaxXYZ[4] = p3ddata[i].z;
        }
        if (MinMaxXYZ[5] < p3ddata[i].z) {
            MinMaxXYZ[5] = p3ddata[i].z;
        }
    }
    centerPoint[0] = (MinMaxXYZ[0] + MinMaxXYZ[1]) / 2;
    centerPoint[1] = (MinMaxXYZ[2] + MinMaxXYZ[3]) / 2;
    centerPoint[2] = (MinMaxXYZ[4] + MinMaxXYZ[5]) / 2;
}
