/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : Render.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-28
  @Description   : Sample View
  @Version       : 0.1.0

  @History       :
  1.2015-05-28 Chen Shangwei Created file
  2.2016-10-25 Aaron Zhang Modify
********************************************************************************/

#ifndef _IMI_SAMPLE_RENDER_H_
#define _IMI_SAMPLE_RENDER_H_

#include <string>
#include <stdint.h>
#include <string.h>

//Imi Head File
#include "ImiNect.h"
#include "ImiDefines.h"
#include "ImiSkeleton.h"

#include "Util.h"

typedef struct WindowHint {
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;

    WindowHint() {
        memset(this, 0, sizeof(*this));
    }

    WindowHint(uint32_t param_x, uint32_t param_y, uint32_t param_w, uint32_t param_h) :
            x(param_x), y(param_y), w(param_w), h(param_h) {
    }

} WinHint;

typedef struct _POSITION {
    int32_t x;
    int32_t y;

    _POSITION() {
        memset(this, 0, sizeof(*this));
    }
} POSITION;

typedef bool (*NeedImageCb)(void *pData);

typedef int32_t RenderWindow;

typedef void (*keyCallback)(unsigned char key, int32_t x, int32_t y);

typedef void (*mouseCallback)(int32_t mouseKey, int32_t state, int32_t x, int32_t y);

typedef void (*mouseMoveCallback)(int32_t x, int32_t y);

class SampleRender {
public:
    SampleRender(const char *pRenderName, const uint32_t winSizeX, const uint32_t winSizeY);

    virtual ~SampleRender();

    bool init(int32_t argc, char **argv);

    void setDataCallback(NeedImageCb needImage, void *pData);

    bool run();

    void initViewPort();

    void update();

    RenderWindow createSubWin(WinHint &winhint);

    void setSubWinPosition(WinHint &winhint);

    virtual void draw(RenderWindow win, uint8_t *pRgbBuffer, uint32_t size, uint32_t width, uint32_t height,
                      ImiImageFrame **pFrame = NULL);

    virtual void setKeyCallback(keyCallback keyhandle) { m_keyboard = keyhandle; };

    virtual void setMouseCallback(mouseCallback mousehandle) { m_mouseboard = mousehandle; };

    virtual void setMouseMoveCallback(mouseMoveCallback mousehandle) { m_mouseMove = mousehandle; };

    virtual void draw(uint8_t *pRgbBuffer, uint32_t size, const WinHint &rect);

    virtual void drawSkeleton(const ImiImageFrame *pFrame, WinHint &winhint);

    virtual void
    drawBone(const ImiSkeletonData *pSkeletonData, ImiSkeletonPositionIndex first, ImiSkeletonPositionIndex second,
             int32_t width, int32_t height, WinHint &winhint);

    virtual void drawCursorXYZValue(ImiImageFrame **pFrame, bool bSaveResult = false);

    virtual void drawString(const char *str, uint32_t x, uint32_t y, void *font = (void *) 0x0002);

    virtual void drawRectangle(int x, int y, int width, int height, WinHint &winhint);

    virtual void drawPoint(int32_t x, int32_t y);

protected:
    virtual void display();

    virtual bool initOpenGL(int32_t argc, char **argv);

    virtual void onKey(unsigned char key, int32_t x, int32_t y);

    virtual void onMouse(int32_t button, int32_t state, int32_t x, int32_t y);

    virtual void onMouseMove(int32_t x, int32_t y);

private:
    SampleRender(const SampleRender &);

    SampleRender &operator=(SampleRender &);

    static void glutIdle();

    static void glutDisplay();

    static void glutMouse(int button, int state, int x, int y);

    static void glutKeyboard(unsigned char key, int x, int y);

    static void glutWindowReshape(int width, int height);

    static void moveMouse(int xMouse, int yMouse);

    static SampleRender *g_pSampleRender;

    std::string m_strRenderName;

    uint32_t m_nTexMapX;
    uint32_t m_nTexMapY;

    RGB888Pixel *m_pTexMap;

    NeedImageCb m_NeedImage;
    void *m_pUserCookie;

    WinHint m_hint;

    keyCallback m_keyboard;
    uint32_t m_glWin;

    mouseCallback m_mouseboard;

    mouseMoveCallback m_mouseMove;

    static POSITION m_CursorPos;

    int m_nWindowWidth;
    int m_nWindowHeight;
};


#endif 
