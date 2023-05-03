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

#ifndef _IMI_SAMPLE_RENDER2_H_
#define _IMI_SAMPLE_RENDER2_H_

#include <string>
#include <stdint.h>
#include <string.h>

//Imi Head File
#include "ImiNect.h"
#include "ImiDefines.h"
#include "ImiSkeleton.h"

#include "Utill.h"

typedef struct WindowHint2
{
	uint32_t x;
	uint32_t y;
	uint32_t w;
	uint32_t h;

	WindowHint2()
	{
		memset(this, 0, sizeof(*this));
	}

	WindowHint2(uint32_t param_x, uint32_t param_y, uint32_t param_w, uint32_t param_h):
			  x(param_x),y(param_y),w(param_w),h(param_h)
	{
	}

}WinHint2;

typedef struct _POSITION2
{
	int32_t x;
	int32_t y;
	
	_POSITION2()
	{
		memset(this, 0, sizeof(*this));
	}
}POSITION2;

typedef bool (*NeedImageCb)(void* pData);

typedef int32_t RenderWindow;

typedef void (*keyCallback)(unsigned char key, int32_t x, int32_t y);

class SampleRender2
{
public:
	SampleRender2(const char* pRenderName, const uint32_t winSizeX, const uint32_t winSizeY);
	virtual ~SampleRender2();

	bool init(int32_t argc, char **argv);
	void setDataCallback(NeedImageCb needImage, void* pData);
	bool run();

	void update();

	RenderWindow createSubWin(WinHint2& winhint);
	void setSubWinPosition(WinHint2& winhint);

	virtual void setKeyCallback(keyCallback keyhandle) {m_keyboard = keyhandle;};

    virtual void drawMesh(ImiPoint3D *p3ddata, uint32_t pointCount, uint32_t width, uint32_t height);

    void setDisplayPoint() {
        m_bShowPoint = !m_bShowPoint;
    }

    void setDisplayMesh()
    {
        m_bShowMesh = !m_bShowMesh;
    }

	void drawFrustum(float fovY, float aspectRatio, float nearPlane, float farPlane);
	void calminmax(ImiPoint3D *p3ddata, uint32_t pointCount);

protected:
	virtual void display();
	virtual bool initOpenGL(int32_t argc, char **argv);
	virtual void onKey(unsigned char key, int32_t x, int32_t y);

private:
	SampleRender2(const SampleRender2&);
	SampleRender2& operator=(SampleRender2&);

	static void glutIdle();
	static void glutDisplay();
	static void glutMouse(int button, int state, int x, int y);
	static void glutKeyboard(unsigned char key, int x, int y);
	static void glutWindowReshape(int width, int height);

	static SampleRender2* g_pSampleRender;

	std::string	    m_strRenderName;

	uint32_t        m_nTexMapX;
    uint32_t        m_nTexMapY;

	RGB888Pixel*	m_pTexMap;

	NeedImageCb     m_NeedImage;
	void*			m_pUserCookie;
	
	WinHint2 		m_hint;

	keyCallback m_keyboard;
	uint32_t 		m_glWin;
	
	static POSITION2	m_CursorPos;

	int m_nWindowWidth;
	int m_nWindowHeight;

    bool  m_bShowPoint;
    bool  m_bShowMesh;

	float MinMaxXYZ[6];
	float centerPoint[3];
};


#endif 
