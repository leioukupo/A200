/********************************************************************************
Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
All rights reserved.

@File Name		: main.cpp
@Author			: Wendell
@Date			: 2018-06-18
@Description	: read color frame and view
@Version		: 1.0.0
@History		:
1.2018-06-18 Wendell Created file
********************************************************************************/
#include <cstdio>

// Imi Head File
#include "ImiNect.h"

// UI
#include "../Common/Render.h"

// window handle
SampleRender *g_pRender = nullptr;

ImiDeviceAttribute *g_DeviceAttr = nullptr;

// device handle
ImiDeviceHandle g_ImiDevice = nullptr;

// stream handles
ImiStreamHandle g_streams[10];
uint32_t g_streamNum = 5;

// window callback, called by SampleRender::display()
static bool needImage(void *pData)
{
	static RGB888Pixel s_rgbImage[1280 * 1024];

	int32_t avStreamIndex = 0;
	ImiImageFrame *imiFrame = nullptr;

	// frame read.
	if (0 != imiReadNextFrame(g_streams[avStreamIndex], &imiFrame, 100))
	{
		return false;
	}

	if (nullptr == imiFrame)
	{
		return false;
	}

	// show to the window
	switch (imiFrame->pixelFormat)
	{
	case IMI_PIXEL_FORMAT_IMAGE_RGB24:
	{
		g_pRender->draw(-1, (uint8_t *)imiFrame->pData, imiFrame->size, imiFrame->width, imiFrame->height);
		break;
	}
	case IMI_PIXEL_FORMAT_IMAGE_YUV420SP:
	{
		YUV420SPToRGB((uint8_t *)s_rgbImage, (uint8_t *)imiFrame->pData, imiFrame->width, imiFrame->height);
		g_pRender->draw(-1, (uint8_t *)s_rgbImage, imiFrame->width * imiFrame->height * 3, imiFrame->width, imiFrame->height);
		break;
	}
	case IMI_PIXEL_FORMAT_IMAGE_YUV422:
	{
		YUV422ToRGB((uint8_t *)s_rgbImage, (uint8_t *)imiFrame->pData, imiFrame->width, imiFrame->height);
		g_pRender->draw(-1, (uint8_t *)s_rgbImage, imiFrame->width * imiFrame->height * 3, imiFrame->width, imiFrame->height);
		break;
	}
	}

	// call this to free frame
	imiReleaseFrame(&imiFrame);

	return true;
}

int Exit()
{
	// 7.imiCloseStream()
	for (uint32_t num = 0; num < g_streamNum; ++num)
	{
		if (nullptr != g_streams[num])
		{
			imiCloseStream(g_streams[num]);
			g_streams[num] = nullptr;
		}
	}

	// 8.imiCloseDevice()
	if (nullptr != g_ImiDevice)
	{
		imiCloseDevice(g_ImiDevice);
		g_ImiDevice = nullptr;
	}

	// 9.imiReleaseDeviceList
	if (nullptr != g_DeviceAttr)
	{
		imiReleaseDeviceList(&g_DeviceAttr);
		g_DeviceAttr = nullptr;
	}

	// 10.imiDestroy()
	imiDestroy();

	if (nullptr != g_pRender)
	{
		delete g_pRender;
		g_pRender = nullptr;
	}

	printf("------ exit ------\n");

	getchar();

	return 0;
}

int main(int argc, char **argv)
{
	// 1.imiInitialize()
	  ImiDriverInfo *A;
	  A->driverType= 0x00;
	  printf("%x",A->driverType);
//	  int32_t retur = imiInitialize2(A);
	int retur = imiInitialize();
	if (0 != retur)
	{
		printf("ImiNect Init Failed! ret = %d\n", retur);
		return Exit();
	}
	printf("ImiNect Init Success.\n");

	// 2.imiGetDeviceList()
	uint32_t deviceCount = 0;
	imiGetDeviceList(&g_DeviceAttr, &deviceCount);
	if ((deviceCount <= 0) || (nullptr == g_DeviceAttr))
	{
		printf("Get No Connected ImiDevice!\n");
		return Exit();
	}
	printf("Get %d Connected ImiDevice.\n", deviceCount);

	// 3.imiOpenDevice()
	retur = imiOpenDevice(g_DeviceAttr[0].uri, &g_ImiDevice, 0);
	if (0 != retur)
	{
		printf("Open ImiDevice Failed! ret = %d\n", retur);
		return Exit();
	}
	printf("ImiDevice Opened.\n");

	// 4.imiSetFrameMode()
	const ImiFrameMode *pFrameMode;
	pFrameMode = imiGetCurrentFrameMode(g_ImiDevice, IMI_DEPTH_FRAME);
	printf("%d\n", pFrameMode->resolutionX);
	int32_t error_code = 0;
	error_code = imiGetLastError();
	printf("error\n");
	printf("%x\n", error_code);
	if (nullptr == pFrameMode)
	{
		printf("Get current frame mode failed!\n");
		return Exit();
	}
	printf("Get current frame mode:%d-%d-%d-%d-%d\n", pFrameMode->bitsPerPixel, pFrameMode->framerate,
		   pFrameMode->pixelFormat, pFrameMode->resolutionX, pFrameMode->resolutionY);
	imiSetFrameMode(g_ImiDevice, IMI_DEPTH_FRAME, (ImiFrameMode *)pFrameMode);

	// 5.imiOpenStream()
	retur = imiOpenStream(g_ImiDevice, IMI_DEPTH_FRAME, nullptr, nullptr, &g_streams[g_streamNum++]);
	if (0 != retur)
	{
		printf("Open Color Stream Failed! ret = %d\n", retur);
		int32_t error_code = 0;
		error_code = imiGetLastError();
		printf("error\n");
		printf("%x", error_code);
		return Exit();
	}
	printf("Open Color Stream Success.\n");

	// 6.create window and set read Stream frame data callback
	g_pRender = new SampleRender("DEPTH Color View", pFrameMode->resolutionX, pFrameMode->resolutionY); // window title & size
	g_pRender->init(argc, argv);
	g_pRender->setDataCallback(needImage, nullptr);
	g_pRender->run();

	return Exit();
}
