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
//#include <GL/glew.h>
#include "glew.h"

#endif

//#include <GL/freeglut.h>
#include "freeglut.h"
#include <stdio.h>
#include <string.h>
#include <cmath>

#include "Render.h"


#if defined(_WIN32)
#define IMISnprintf _snprintf_s
#else
#define IMISnprintf snprintf
#endif


POSITION SampleRender::m_CursorPos;
POSITION m_BeginPos;
POSITION m_EndPos;

WinHint marrChildWnd[8];
WinHint marrChildWndIR[8];

double mAvgValueOfDepth[8] = {0};

double mDFValue[8] = {0.0};

bool gbDoubleWin = false;

SampleRender *SampleRender::g_pSampleRender = NULL;

void SampleRender::glutKeyboard(unsigned char key, int x, int y) {
    g_pSampleRender->onKey(key, x, y);
}

SampleRender::SampleRender(const char *pRenderName, const uint32_t winSizeX, const uint32_t winSizeY) :
        m_strRenderName(pRenderName),
        m_nTexMapX(winSizeX),
        m_nTexMapY(winSizeY),
        m_pTexMap(NULL),
        m_NeedImage(NULL),
        m_pUserCookie(NULL),
        m_keyboard(NULL),
        m_mouseboard(NULL),
        m_mouseMove(NULL),
        m_glWin(0),
        m_nWindowWidth(winSizeX),
        m_nWindowHeight(winSizeY) {
    g_pSampleRender = this;
    memset(&m_hint, 0, sizeof(m_hint));
}

SampleRender::~SampleRender() {
    if (NULL != m_pTexMap) {
        delete[] m_pTexMap;
        m_pTexMap = NULL;
    }

    g_pSampleRender = NULL;
}

bool SampleRender::init(int argc, char **argv) {
    m_pTexMap = new RGB888Pixel[m_nTexMapX * m_nTexMapY];
    return initOpenGL(argc, argv);
}

void SampleRender::setDataCallback(NeedImageCb needImage, void *pData) {
    m_NeedImage = needImage;
    m_pUserCookie = pData;
}

bool SampleRender::run() {
    if (m_NeedImage) {
        glutIdleFunc(glutIdle);
    }

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
    glutMainLoop();

    return true;
}

void SampleRender::initViewPort() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, m_nTexMapX, m_nTexMapY, 0, -1.0, 1.0);
}

void SampleRender::update() {
    // Swap the OpenGL display buffers
    glutSwapBuffers();
}

void SampleRender::display() {
    if (NULL != m_NeedImage) {
        m_NeedImage(m_pUserCookie);
    }
}

bool SampleRender::initOpenGL(int32_t argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(m_nTexMapX, m_nTexMapY);
    m_glWin = glutCreateWindow(m_strRenderName.c_str());
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glutKeyboardFunc(glutKeyboard);
    glutDisplayFunc(glutDisplay);
    glutMouseFunc(glutMouse);
    glutMotionFunc(moveMouse);
    glutReshapeFunc(glutWindowReshape);

    return true;
}

void SampleRender::moveMouse(int xMouse, int yMouse) {
    g_pSampleRender->onMouseMove(xMouse, yMouse);
}

RenderWindow SampleRender::createSubWin(WinHint &winhint) {
    if (m_glWin < 0) {
        return -1;
    }

    RenderWindow win = glutCreateSubWindow(m_glWin, winhint.x, winhint.y, winhint.w, winhint.h);
    glutSetCursor(GLUT_CURSOR_NONE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    return win;
}

void SampleRender::drawPoint(int32_t x, int32_t y) {
    glDisable(GL_TEXTURE_2D);

    //Draw Cursor Point
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(4.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    glEnable(GL_TEXTURE_2D);
}

void SampleRender::drawCursorXYZValue(ImiImageFrame **pFrame, bool bSaveResult/*=false*/) {
    if (NULL == pFrame) {
        return;
    }

    //Draw Cursor X,Y,Z Value

    uint32_t curIndex = (*pFrame)->width * (m_CursorPos.y * ((*pFrame)->height) / m_nTexMapY) +
                        (m_CursorPos.x * ((*pFrame)->width) / m_nTexMapX);

    if (curIndex >= (*pFrame)->size) {
        return;
    }
    unsigned short *pData = (unsigned short *) ((*pFrame)->pData);
    unsigned int depth = pData[curIndex];
    if (m_EndPos.x > 0 && m_EndPos.y > 0) {
        for (int nIndex = 0; nIndex < 8; nIndex++) {
            mAvgValueOfDepth[nIndex] = 0;
            mDFValue[nIndex] = 0;
            uint32_t uSum = 0;
            int nSumPoints = 0;
            double dCurAvg = 0;
            int nMaxValue = 0;
            double nDf = 0;
            uint16_t uPointNum = marrChildWnd[nIndex].w * marrChildWnd[nIndex].h;
            uint16_t pDataChild[640 * 480] = {0};

            for (int h = 0; h < marrChildWnd[nIndex].h; h++) {
                for (int w = 0; w < marrChildWnd[nIndex].w; w++) {
                    curIndex = (*pFrame)->width * ((marrChildWnd[nIndex].y + h) * ((*pFrame)->height) / m_nTexMapY) +
                               ((marrChildWnd[nIndex].x + w) * ((*pFrame)->width) / (m_nTexMapX / 2));

                    if (curIndex >= (*pFrame)->size) {
                        uSum += 0;
                    } else if (pData[curIndex] > 0 && pData[curIndex] < 10000) {
                        uSum += pData[curIndex];
                        pDataChild[nSumPoints++] = pData[curIndex];
                        //;
                        //dCurAvg=uSum/nSumPoints;
                        if (nMaxValue < pData[curIndex]) {
                            nMaxValue = pData[curIndex];
                        }
                    }
                }
            }
            if (nSumPoints > 0) {
                dCurAvg = 0.0;
                mAvgValueOfDepth[nIndex] = (double) uSum / (double) nSumPoints;
                for (int j = 0; j < nSumPoints; j++) {
                    dCurAvg += abs((double) pDataChild[j] - mAvgValueOfDepth[nIndex]) *
                               abs((double) pDataChild[j] - mAvgValueOfDepth[nIndex]);
                    //dCurAvg +=;

                }
                mDFValue[nIndex] = sqrt(dCurAvg / (double) nSumPoints);
                //printf("Index=%d Max=%d Num of Points=%d\r\n",nIndex,nMaxValue,nSumPoints);
            } else {
                mAvgValueOfDepth[nIndex] = 0;
                mDFValue[nIndex] = 0;
            }

        }
        if (bSaveResult) {
            static int snFileIndex = 1;
            char strIr[128] = {0};
            sprintf(strIr, ".\\savefiles\\results_save-%d.txt", snFileIndex++);
            FILE *pFile = fopen(strIr, "wb");
            if (pFile) {
                char pSaveData[1024] = {0};
                for (int n = 0; n < 4; n++) {
                    //fseek(pFile,);
                    sprintf(pSaveData, "%d, %.3f, %.3f\r\n", n, mAvgValueOfDepth[4 - 1 - n], mDFValue[3 - n]);
                    fseek(pFile, 0, 2);
                    fwrite(pSaveData, strlen(pSaveData), 1, pFile);
                }
                for (int n = 4; n < 8; n++) {
                    sprintf(pSaveData, "%d, %.3f, %.3f\r\n", n, mAvgValueOfDepth[n], mDFValue[n]);
                    fseek(pFile, 0, 2);
                    fwrite(pSaveData, strlen(pSaveData), 1, pFile);
                }
                fclose(pFile);
                //printf("save one depth frame raw data to depth.raw Success !\n");
            } else {
                printf("save :%s Failed !\n", strIr);
            }
        }
    }


    glDisable(GL_TEXTURE_2D);

    //Draw Cursor Point
    glColor3f(1.0f, 0.0f, 0.0f);
    //glPointSize(4.0f);
//	glBegin(GL_POINTS);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//	glVertex2i(m_CursorPos.x, m_CursorPos.y);
    if (m_EndPos.x > 0 && m_EndPos.y > 0) {
        //glBegin(GL_LINE_LOOP);
        //glVertex2i(m_BeginPos.x, m_BeginPos.y);
        //glVertex2i(m_EndPos.x, m_BeginPos.y);
        //glVertex2i(m_EndPos.x, m_EndPos.y);
        //glVertex2i(m_BeginPos.x, m_EndPos.y);
        ////	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        ////	glRectd(m_CursorPos.x-20, m_CursorPos.y-20, m_CursorPos.x+20, m_CursorPos.y+20);
        ////	glFlush();
        //glEnd();

        for (int nIndex = 0; nIndex < 8; nIndex++) {
            glBegin(GL_LINE_LOOP);
            glVertex2i(marrChildWnd[nIndex].x, marrChildWnd[nIndex].y);
            glVertex2i(marrChildWnd[nIndex].x + marrChildWnd[nIndex].w, marrChildWnd[nIndex].y);
            glVertex2i(marrChildWnd[nIndex].x + marrChildWnd[nIndex].w,
                       marrChildWnd[nIndex].y + marrChildWnd[nIndex].h);
            glVertex2i(marrChildWnd[nIndex].x, marrChildWnd[nIndex].y + marrChildWnd[nIndex].h);
            glEnd();
            if (gbDoubleWin) {
                glBegin(GL_LINE_LOOP);
                glVertex2i(marrChildWndIR[nIndex].x, marrChildWndIR[nIndex].y);
                glVertex2i(marrChildWndIR[nIndex].x + marrChildWndIR[nIndex].w, marrChildWndIR[nIndex].y);
                glVertex2i(marrChildWndIR[nIndex].x + marrChildWndIR[nIndex].w,
                           marrChildWndIR[nIndex].y + marrChildWndIR[nIndex].h);
                glVertex2i(marrChildWndIR[nIndex].x, marrChildWndIR[nIndex].y + marrChildWndIR[nIndex].h);
                glEnd();
            }
        }
        char buffS[32];
        int yOffset = 0;
        for (int nIndex = 0; nIndex < 8; nIndex++) {
            memset(buffS, 0, sizeof(buffS));
            IMISnprintf(buffS, 16, "%.2f", mAvgValueOfDepth[nIndex]);
            yOffset =
                    marrChildWnd[nIndex].y + 10 * (nIndex < 4 ? -1 : 1) + marrChildWnd[nIndex].h * (nIndex < 4 ? 0 : 1);
            drawString(buffS, marrChildWnd[nIndex].x + 2, yOffset);

            IMISnprintf(buffS, 16, "%.2f\0", mDFValue[nIndex]);
            yOffset =
                    marrChildWnd[nIndex].y + 20 * (nIndex < 4 ? -1 : 1) + marrChildWnd[nIndex].h * (nIndex < 4 ? 0 : 1);
            drawString(buffS, marrChildWnd[nIndex].x + 2, yOffset);
            if (gbDoubleWin) {
                memset(buffS, 0, sizeof(buffS));
                IMISnprintf(buffS, 16, "%.2f", mAvgValueOfDepth[nIndex]);
                yOffset = marrChildWndIR[nIndex].y + 10 * (nIndex < 4 ? -1 : 1) +
                          marrChildWndIR[nIndex].h * (nIndex < 4 ? 0 : 1);
                drawString(buffS, marrChildWndIR[nIndex].x + 2, yOffset);
                IMISnprintf(buffS, 16, "%.2f\0", mDFValue[nIndex]);
                yOffset = marrChildWndIR[nIndex].y + 20 * (nIndex < 4 ? -1 : 1) +
                          marrChildWndIR[nIndex].h * (nIndex < 4 ? 0 : 1);
                drawString(buffS, marrChildWndIR[nIndex].x + 2, yOffset);
            }
        }
    }

    glEnable(GL_TEXTURE_2D);

    return;


    //����glClear���Ӵ�����������һ�������Ƶ�ͼ��
    //glClear(GL_COLOR_BUFFER_BIT);
    //���õ�ǰ��ͼ����ɫ
    //glColor3f(0.98f, 0.625f, 0.12f);
    //���ƾ��Σ���һ�������ʾ���Ͻǣ��ڶ��Ա�ʾ���½�

    //ˢ�¶���
    //���ڲ���openGL���������䳣���ȴ��ڶ�����
    //ֱ��openGL��������ͬʱ�������������
    //glFlush();

    char buff[32];

    int XposOffset = 5;
    int YposOffsetX = 20;
    int YposOffsetY = 40;
    int YposOffsetZ = 60;
    if (m_CursorPos.x + 85 > m_nWindowWidth) {
        XposOffset = -85;
    }
    if (m_CursorPos.y + 45 > m_nWindowHeight) {
        YposOffsetX = -45;
        YposOffsetY = -25;
        YposOffsetZ = -5;
    }

    memset(buff, 0, sizeof(buff));
    IMISnprintf(buff, 16, "X=%d", m_CursorPos.x);
    drawString(buff, m_CursorPos.x + XposOffset, m_CursorPos.y + YposOffsetX);

    memset(buff, 0, sizeof(buff));
    IMISnprintf(buff, 16, "Y=%d", m_CursorPos.y);
    drawString(buff, m_CursorPos.x + XposOffset, m_CursorPos.y + YposOffsetY);

    memset(buff, 0, sizeof(buff));
    IMISnprintf(buff, 16, "Z=%u", depth);
    drawString(buff, m_CursorPos.x + XposOffset, m_CursorPos.y + YposOffsetZ);
}

void SampleRender::drawString(const char *str, uint32_t x, uint32_t y, void *font/* = GLUT_BITMAP_9_BY_15*/) {
    glDisable(GL_TEXTURE_2D);

    glRasterPos2i(x, y);

    if (NULL == str) {
        return;
    }

    for (; *str != '\0'; ++str) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10/*GLUT_BITMAP_TIMES_ROMAN_24*/, *str);
    }

    glEnable(GL_TEXTURE_2D);
}


void SampleRender::draw(RenderWindow win2Draw, uint8_t *pRgbBuffer, uint32_t size, uint32_t width, uint32_t height,
                        ImiImageFrame **pFrame) {
    // so, use -1 means to  draw the window it self;
    if (win2Draw >= 0) {
        glutSetWindow(win2Draw);
    }

    initViewPort();

    memset(m_pTexMap, 0, m_nTexMapX * m_nTexMapY * sizeof(RGB888Pixel));

    {
        const RGB888Pixel *pImageRow = (const RGB888Pixel *) pRgbBuffer;
        RGB888Pixel *pTexRow = m_pTexMap;
        int32_t rowSize = width;

        for (uint32_t y = 0; y < height; ++y) {
            const RGB888Pixel *pImage = pImageRow;
            RGB888Pixel *pTex = pTexRow;

            for (uint32_t x = 0; x < width; ++x, ++pImage, ++pTex) {
                *pTex = *pImage;
            }

            pImageRow += rowSize;
            pTexRow += m_nTexMapX;
        }
    }

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nTexMapX, m_nTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pTexMap);

    // Display the OpenGL texture map
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);

    int32_t nXRes = width;
    int32_t nYRes = height;

    // upper left
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    // upper right
    glTexCoord2f((float) nXRes / (float) m_nTexMapX, 0);
    glVertex2f((GLfloat) m_nTexMapX, 0);
    // bottom right
    glTexCoord2f((float) nXRes / (float) m_nTexMapX, (float) nYRes / (float) m_nTexMapY);
    glVertex2f((GLfloat) m_nTexMapX, (GLfloat) m_nTexMapY);
    // bottom left
    glTexCoord2f(0, (float) nYRes / (float) m_nTexMapY);
    glVertex2f(0, (GLfloat) m_nTexMapY);

    glEnd();

    if (m_CursorPos.x > 0 && m_CursorPos.y > 0) {
        drawCursorXYZValue(pFrame);
    }

    update();
}

void SampleRender::drawRectangle(int x, int y, int width, int height, WinHint &winhint) {
    glDisable(GL_TEXTURE_2D);

    float coordinates1[6] = {x + winhint.x, y, 0, x + width + winhint.x, y, 0};

    glLineWidth(3.0);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glVertexPointer(3, GL_FLOAT, 0, coordinates1);
    glDrawArrays(GL_LINES, 0, 2);

    float coordinates2[6] = {x + winhint.x, y + winhint.y, 0, x + winhint.x, y + winhint.y + height, 0};
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glVertexPointer(3, GL_FLOAT, 0, coordinates2);
    glDrawArrays(GL_LINES, 0, 2);

    float coordinates3[6] = {x + width + winhint.x, y + winhint.y, 0, x + width + winhint.x, y + winhint.y + height, 0};
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glVertexPointer(3, GL_FLOAT, 0, coordinates3);
    glDrawArrays(GL_LINES, 0, 2);

    float coordinates4[6] = {x + winhint.x, y + winhint.y + height, 0, x + width + winhint.x, y + winhint.y + height,
                             0};
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glVertexPointer(3, GL_FLOAT, 0, coordinates4);
    glDrawArrays(GL_LINES, 0, 2);

    glEnable(GL_TEXTURE_2D);
}

void SampleRender::draw(uint8_t *pRgbBuffer, uint32_t size, const WinHint &rect) {
    memset(m_pTexMap, 0, m_nTexMapX * m_nTexMapY * sizeof(RGB888Pixel));

    {
        const RGB888Pixel *pImageRow = (const RGB888Pixel *) pRgbBuffer;
        RGB888Pixel *pTexRow = m_pTexMap;
        int32_t rowSize = rect.w;

        for (uint32_t y = 0; y < rect.h; ++y) {
            const RGB888Pixel *pImage = pImageRow;
            RGB888Pixel *pTex = pTexRow;

            for (uint32_t x = 0; x < rect.w; ++x, ++pImage, ++pTex) {
                *pTex = *pImage;
            }

            pImageRow += rowSize;
            pTexRow += m_nTexMapX;
        }
    }

    //glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nTexMapX, m_nTexMapY, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pTexMap);

    // Display the OpenGL texture map
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);

    int32_t nXRes = rect.w;
    int32_t nYRes = rect.h;

    // upper left
    glTexCoord2f(0, 0);
    glVertex2f((GLfloat) rect.x, (GLfloat) rect.y);
    // upper right
    glTexCoord2f((float) nXRes / (float) m_nTexMapX, 0);
    glVertex2f((GLfloat) (rect.x + rect.w), (GLfloat) rect.y);
    // bottom right
    glTexCoord2f((float) nXRes / (float) m_nTexMapX, (float) nYRes / (float) m_nTexMapY);
    glVertex2f((GLfloat) (rect.x + rect.w), (GLfloat) (rect.y + +rect.h));
    // bottom left
    glTexCoord2f(0, (float) nYRes / (float) m_nTexMapY);
    glVertex2f((GLfloat) rect.x, (GLfloat) (rect.y + rect.h));

    glEnd();
}

void SampleRender::drawSkeleton(const ImiImageFrame *pFrame, WinHint &winhint) {
    if (NULL == pFrame) {
        return;
    }

    glDisable(GL_TEXTURE_2D);

    char strUserLabel[512] = "";
    char strPositionLabel[512] = "";
    ImiSkeletonFrame *pSkeleton = (ImiSkeletonFrame *) pFrame->pSkeletonData;

    for (int i = 0; i < MAX_TRACKED_PEOPLE_NUM; ++i) {
        const ImiSkeletonData *pSkeletonData = &pSkeleton->skeletonData[i];
        memset(strUserLabel, 0, sizeof(strUserLabel));
        memset(strPositionLabel, 0, sizeof(strPositionLabel));

        if (IMI_SKELETON_TRACKED == pSkeletonData->trackingState) {

            int width = pFrame->width;
            int height = pFrame->height;

            IMISnprintf(strUserLabel, sizeof(strUserLabel), "%d tracked,trackid: %d, track state:%d", i + 1,
                        pSkeletonData->trackingID, pSkeletonData->trackingState);
            IMISnprintf(strPositionLabel, sizeof(strPositionLabel), "position:x=%f y=%f z=%f w=%f",
                        pSkeletonData->position.x, pSkeletonData->position.y, pSkeletonData->position.z,
                        pSkeletonData->position.w);

            // for test
            //printf("### tracked ### %d tracked,trackid: %d, track state:%d\n",i+1, pSkeletonData->trackingState);

            // Render Torso
            drawBone(pSkeletonData, IMI_SKELETON_POSITION_HEAD,
                     IMI_SKELETON_POSITION_SHOULDER_CENTER, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SHOULDER_CENTER,
                     IMI_SKELETON_POSITION_SHOULDER_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SHOULDER_CENTER,
                     IMI_SKELETON_POSITION_SHOULDER_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SHOULDER_CENTER,
                     IMI_SKELETON_POSITION_SPINE, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SPINE,
                     IMI_SKELETON_POSITION_HIP_CENTER, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_HIP_CENTER,
                     IMI_SKELETON_POSITION_HIP_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_HIP_CENTER,
                     IMI_SKELETON_POSITION_HIP_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SHOULDER_LEFT,
                     IMI_SKELETON_POSITION_ELBOW_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_ELBOW_LEFT,
                     IMI_SKELETON_POSITION_WRIST_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_WRIST_LEFT,
                     IMI_SKELETON_POSITION_HAND_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_SHOULDER_RIGHT,
                     IMI_SKELETON_POSITION_ELBOW_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_ELBOW_RIGHT,
                     IMI_SKELETON_POSITION_WRIST_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_WRIST_RIGHT,
                     IMI_SKELETON_POSITION_HAND_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_HIP_LEFT,
                     IMI_SKELETON_POSITION_KNEE_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_KNEE_LEFT,
                     IMI_SKELETON_POSITION_ANKLE_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_ANKLE_LEFT,
                     IMI_SKELETON_POSITION_FOOT_LEFT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_HIP_RIGHT,
                     IMI_SKELETON_POSITION_KNEE_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_KNEE_RIGHT,
                     IMI_SKELETON_POSITION_ANKLE_RIGHT, width, height, winhint);

            drawBone(pSkeletonData, IMI_SKELETON_POSITION_ANKLE_RIGHT,
                     IMI_SKELETON_POSITION_FOOT_RIGHT, width, height, winhint);
        } else if (IMI_SKELETON_POSITION_ONLY == pSkeletonData->trackingState) {
            IMISnprintf(strUserLabel, sizeof(strUserLabel), "postion only--trackid: %d, track state:%d",
                        pSkeletonData->trackingID, pSkeletonData->trackingState);
            IMISnprintf(strPositionLabel, sizeof(strPositionLabel), "position:x=%f y=%f z=%f w=%f",
                        pSkeletonData->position.x, pSkeletonData->position.y, pSkeletonData->position.z,
                        pSkeletonData->position.w);

            // for test
            //printf("### position ### postion only--trackid: %d, track state:%d\n", pSkeletonData->trackingID, pSkeletonData->trackingState);
        } else if (IMI_SKELETON_NOT_TRACKED == pSkeletonData->trackingState) {
            IMISnprintf(strUserLabel, sizeof(strUserLabel), "trackid: %d, track state: %d", pSkeletonData->trackingID,
                        pSkeletonData->trackingState);
            IMISnprintf(strPositionLabel, sizeof(strPositionLabel), "position:x=%f y=%f z=%f w=%f \n",
                        pSkeletonData->position.x, pSkeletonData->position.y, pSkeletonData->position.z,
                        pSkeletonData->position.w);

            // for test
            //printf("### not tracked ### trackid: %d, track state: %d\n", pSkeletonData->trackingID, pSkeletonData->trackingState);
        } else if (0 != pSkeletonData->trackingID) {
            IMISnprintf(strUserLabel, sizeof(strUserLabel), "%d - userid, status:%d", pSkeletonData->trackingID,
                        pSkeletonData->trackingState);
            IMISnprintf(strPositionLabel, sizeof(strPositionLabel), "position:x=%f y=%f z=%f w=%f",
                        pSkeletonData->position.x, pSkeletonData->position.y, pSkeletonData->position.z,
                        pSkeletonData->position.w);

            // for test
            //printf("### not zero ### %d - userid, status:%d\n", pSkeletonData->trackingID, pSkeletonData->trackingState);
        } else {
            continue;
        }

        ImiVector4I postion;
        imiConvertCoordinateWorldToDepth(&postion, &pSkeletonData->position, pFrame->height, pFrame->width);
        drawString(strUserLabel, postion.x, postion.y);
        if (postion.x != 0 || postion.y != 0) {
            drawString(strPositionLabel, postion.x, postion.y + 26);
        }
    }

    glEnable(GL_TEXTURE_2D);
}

void SampleRender::drawBone(const ImiSkeletonData *pSkeletonData, ImiSkeletonPositionIndex first,
                            ImiSkeletonPositionIndex second, int32_t width, int32_t height, WinHint &winhint) {
    ImiSkeletonPositionTrackingState state0 = pSkeletonData->skeletonPositionTrackingState[first];
    ImiSkeletonPositionTrackingState state1 = pSkeletonData->skeletonPositionTrackingState[second];
    // Any is not tracked
    if ((IMI_SKELETON_POSITION_NOT_TRACKED == state0) || (IMI_SKELETON_POSITION_NOT_TRACKED == state1)) {
        return;
    }

    // Both are inferred
    if ((IMI_SKELETON_POSITION_INFERRED == state0) && (IMI_SKELETON_POSITION_INFERRED == state1)) {
        return;
    }

    ImiVector4I joint1;
    imiConvertCoordinateWorldToDepth(&joint1, &pSkeletonData->skeletonPositions[first], height, width);

    ImiVector4I joint2;
    imiConvertCoordinateWorldToDepth(&joint2, &pSkeletonData->skeletonPositions[second], height, width);

    float coordinates[6] = {(float) joint1.x + winhint.x, (float) joint1.y, 0.0, (float) joint2.x + winhint.x,
                            (float) joint2.y, 0.0};

    glLineWidth(3.0);

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(2);
    glVertexPointer(3, GL_FLOAT, 0, coordinates);
    glDrawArrays(GL_LINES, 0, 2);


    glPointSize(10);

    glColor3f(0.0, 1.0, 0.0);
    glVertexPointer(3, GL_FLOAT, 0, coordinates);
    glDrawArrays(GL_POINTS, 0, 1);

    glColor3f(0.0, 1.0, 0.0);
    glVertexPointer(3, GL_FLOAT, 0, coordinates + 3);
    glDrawArrays(GL_POINTS, 0, 1);

}

void SampleRender::glutIdle() {
    SampleRender::g_pSampleRender->display();
}

void SampleRender::glutDisplay() {
    //SampleRender::ms_self->display();
}

void SampleRender::glutMouse(int button, int state, int x, int y) {
    if (state != GLUT_DOWN) {
        return;
    }

    //left button down mark the Cursor position
    if (GLUT_LEFT_BUTTON == button) {
        m_CursorPos.x = x * g_pSampleRender->m_nTexMapX / g_pSampleRender->m_nWindowWidth;
        m_CursorPos.y = y * g_pSampleRender->m_nTexMapY / g_pSampleRender->m_nWindowHeight;


        if (m_CursorPos.x >= g_pSampleRender->m_nWindowWidth / 2 &&
            (g_pSampleRender->m_nWindowWidth == 480 * 2 || g_pSampleRender->m_nWindowWidth == 640 * 2)) {
            //m_BeginPos.x = 0;
            //m_BeginPos.y = 0;
            gbDoubleWin = true;
        }


        if (m_BeginPos.x == 0 && m_BeginPos.y == 0) {
            m_BeginPos.x = m_CursorPos.x;
            m_BeginPos.y = m_CursorPos.y;
            if (gbDoubleWin && m_BeginPos.x >= g_pSampleRender->m_nWindowWidth / 2) {
                m_BeginPos.x -= g_pSampleRender->m_nWindowWidth / 2;
            }
        } else {
            m_EndPos.x = m_CursorPos.x;
            m_EndPos.y = m_CursorPos.y;

            if (gbDoubleWin && m_EndPos.x > g_pSampleRender->m_nWindowWidth / 2) {
                m_EndPos.x -= g_pSampleRender->m_nWindowWidth / 2;
            }


            int nWidthChild = abs(m_EndPos.x - m_BeginPos.x) / 4;
            int nHeightChild = abs(m_EndPos.y - m_BeginPos.y) / 2;
            if (nWidthChild < 6 || nHeightChild < 6) {
                return;
            }
            uint32_t nBeginx = m_BeginPos.x;
            uint32_t nBeginy = m_BeginPos.y;
            if (m_EndPos.x - m_BeginPos.x < 0) {
                nBeginx = m_EndPos.x;
            }

            if (m_EndPos.y - m_BeginPos.y < 0) {
                nBeginy = m_EndPos.y;
            }

            for (int nIndex = 0; nIndex < 2; nIndex++) {
                for (int j = 0; j < 4; j++) {
                    marrChildWnd[nIndex * 4 + j].x = nBeginx + j * nWidthChild + 2;
                    marrChildWnd[nIndex * 4 + j].y = nBeginy + nIndex * nHeightChild + 2;
                    marrChildWnd[nIndex * 4 + j].w = nWidthChild - 2 * 2;
                    marrChildWnd[nIndex * 4 + j].h = nHeightChild - 2 * 2;
                    if (gbDoubleWin) {
                        marrChildWndIR[nIndex * 4 + j].x =
                                nBeginx + j * nWidthChild + 2 + g_pSampleRender->m_nWindowWidth / 2;
                        marrChildWndIR[nIndex * 4 + j].y = nBeginy + nIndex * nHeightChild + 2;
                        marrChildWndIR[nIndex * 4 + j].w = nWidthChild - 2 * 2;
                        marrChildWndIR[nIndex * 4 + j].h = nHeightChild - 2 * 2;
                    }
                }
            }
        }
    }

    //right button clear the Cusor position
    if (GLUT_RIGHT_BUTTON == button) {
        m_CursorPos.x = 0;
        m_CursorPos.y = 0;
        m_BeginPos.x = 0;
        m_BeginPos.y = 0;
        m_EndPos.x = 0;
        m_EndPos.y = 0;
    }

    m_CursorPos.x = x * g_pSampleRender->m_nTexMapX / g_pSampleRender->m_nWindowWidth;
    m_CursorPos.y = y * g_pSampleRender->m_nTexMapY / g_pSampleRender->m_nWindowHeight;

    g_pSampleRender->onMouse(button, state, m_CursorPos.x, m_CursorPos.y);
}

void SampleRender::onMouse(int32_t button, int32_t state, int32_t x, int32_t y) {
    if (m_mouseboard) {
        m_mouseboard(button, state, x, y);
    }
}

void SampleRender::onMouseMove(int32_t x, int32_t y) {
    if (m_mouseMove) {
        m_mouseMove(x, y);
    }
}

void SampleRender::onKey(unsigned char key, int32_t x, int32_t y) {
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

void SampleRender::glutWindowReshape(int width, int height) {
    g_pSampleRender->m_nWindowWidth = width;
    g_pSampleRender->m_nWindowHeight = height;
    glViewport(0, 0, width, height);
}
