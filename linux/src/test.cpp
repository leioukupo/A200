//
// Created by leioukupo on 2023/9/24.
//
/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : main.cpp
  @Author        : Zhang hongliang
  @Date          : 2015-06-18
  @Description   : read color frame and depth frame
  @Version       : 0.1.0
  @History       :
  1.2015-06-18 Zhang Hongliang Created file
  2.2016-10-25 Zhang Ya Modify
********************************************************************************/

// Imi Head File
#include "ImiNect.h"

// UI
#include "../Common/Render.h"

#include <cstdio>
#include <cstring>

#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480
#define DEFAULT_PERPIXEL_BITS 16
#define DEFAULT_FRAMERATE 30

// window handle
SampleRender *g_pRender = nullptr;

// stream handles
ImiStreamHandle g_streams[10] = {NULL};
uint32_t g_streamNum = 0;

// window callback, called by SampleRender::display()
static bool needImage(void *pData)
{
    static RGB888Pixel g_colorImage[IMAGE_WIDTH * IMAGE_HEIGHT];
    static RGB888Pixel g_depthImage[IMAGE_WIDTH * IMAGE_HEIGHT];
    static bool g_bColorFrameOK = false;
    static bool g_bDepthFrameOK = false;
    static uint32_t g_realDepthImageSize = 0;
    static uint32_t g_realColorImageSize = 0;
    static uint32_t g_realDepthWidth = 0;
    static uint32_t g_realDepthHeight = 0;

    // wait for stream, -1 means infinite;
    int32_t avStreamIndex;
    if (0 != imiWaitForStreams(g_streams, g_streamNum, &avStreamIndex, 100))
    {
        return false;
    }

    // frame coming, read.
    ImiImageFrame *imiFrame = nullptr;
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &imiFrame, 30))
    {
        return false;
    }

    if (NULL == imiFrame)
    {
        return true;
    }
    imiFrame->type = IMI_DEPTH_FRAME;
    // show to the window
    if (IMI_DEPTH_FRAME == imiFrame->type)
    {
        // uint32_t rgbSize;
        switch (imiFrame->pixelFormat)
        {
        case IMI_PIXEL_FORMAT_IMAGE_H264:
        case IMI_PIXEL_FORMAT_IMAGE_RGB24:
        {
            memcpy((void *)&g_colorImage, (const void *)imiFrame->pData, imiFrame->size);
            g_realColorImageSize = imiFrame->size;
            break;
        }
        case IMI_PIXEL_FORMAT_IMAGE_YUV420SP:
        {
            YUV420SPToRGB((uint8_t *)g_colorImage, (uint8_t *)imiFrame->pData, imiFrame->width, imiFrame->height);
            g_realColorImageSize = imiFrame->width * imiFrame->height * 3;
            break;
        }
        default:
        {
            break;
        }
        }
        g_bColorFrameOK = true;
    }
    else // IMI_DEPTH_FRAME == imiFrame->type
    {
        uint32_t i;
        uint16_t *pde = (uint16_t *)imiFrame->pData;
        for (i = 0; i < imiFrame->size / 2; ++i)
        {
            g_depthImage[i].r = pde[i] >> 3;
            g_depthImage[i].g = g_depthImage[i].b = g_depthImage[i].r;
        }
        g_realDepthImageSize = i;
        g_realDepthWidth = imiFrame->width;
        g_realDepthHeight = imiFrame->height;
        g_bDepthFrameOK = true;
    }

    if (g_bColorFrameOK && g_bDepthFrameOK)
    {
        g_pRender->initViewPort();

        WindowHint hint(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
        g_pRender->draw((uint8_t *)g_colorImage, g_realColorImageSize, hint);

        hint.x += IMAGE_WIDTH;
        hint.w = g_realDepthWidth;
        hint.h = g_realDepthHeight;
        g_pRender->draw((uint8_t *)g_depthImage, g_realDepthImageSize, hint);

        g_pRender->update();

        g_bColorFrameOK = false;
        g_bDepthFrameOK = false;
    }

    imiReleaseFrame(&imiFrame);
    return true;
}

int main(int argc, char **argv)
{
    // 1.imiInitialize()
    if (0 != imiInitialize())
    {
        printf("ImiNect Init Failed!\n");
        getchar();
        return -1;
    }
    printf("ImiNect Init Success.\n");

    // 2.imiGetDeviceList()
    ImiDeviceAttribute *pDeviceAttr = NULL;
    uint32_t deviceCount = 0;
    imiGetDeviceList(&pDeviceAttr, &deviceCount);
    if (deviceCount <= 0 || NULL == pDeviceAttr)
    {
        printf("Get No Connected Imidevice!");
        imiDestroy();
        getchar();
        return -1;
    }
    printf("Get %d Connected Imidevice.\n", deviceCount);

    // 3.imiOpenDevice()
    ImiDeviceHandle pImiDevice = NULL;
    if (0 != imiOpenDevice(pDeviceAttr[0].uri, &pImiDevice, IMI_DEVICE_CAMERA))
    {
        printf("Open Imidevice Failed!\n");
        goto exit;
    }
    printf("Imidevice Opened.\n");

    // 4.imiSetFrameMode()
    ImiFrameMode frameMode;
    frameMode.pixelFormat = IMI_PIXEL_FORMAT_IMAGE_YUV420SP;
    frameMode.resolutionX = IMAGE_WIDTH;
    frameMode.resolutionY = IMAGE_HEIGHT;
    frameMode.bitsPerPixel = DEFAULT_PERPIXEL_BITS;
    frameMode.framerate = DEFAULT_FRAMERATE;

    imiSetFrameMode(pImiDevice, IMI_DEPTH_FRAME, &frameMode);

    // 5.imiOpenStream()
    //    if (0 != imiOpenStream(pImiDevice, IMI_DEPTH_FRAME, NULL, NULL, &g_streams[g_streamNum++]))
    //    {
    //        printf("Open Color Stream Failed!\n");
    //        goto exit;
    //    }
    //    printf("Open Color Stream Success.\n");

    if (0 != imiOpenStream(pImiDevice, IMI_DEPTH_FRAME, NULL, NULL, &g_streams[g_streamNum++]))
    {
        printf("Open Depth Stream Failed!\n");
        goto exit;
    }
    printf("Open Depth Stream Success.\n");

    // 6.create window and set read Stream frame data callback
    g_pRender = new SampleRender("ColorDepthView", IMAGE_WIDTH * 2, IMAGE_HEIGHT); // window title & size
    g_pRender->init(argc, argv);
    g_pRender->setDataCallback(needImage, NULL);
    g_pRender->run();

exit:
    // 7.imiCloseStream()
    for (uint32_t num = 0; num < g_streamNum; ++num)
    {
        if (NULL != g_streams[num])
        {
            imiCloseStream(g_streams[num]);
        }
    }

    // 8.imiCloseDevice()
    if (NULL != pImiDevice)
    {
        imiCloseDevice(pImiDevice);
    }

    // 9.imiReleaseDeviceList()
    if (NULL != pDeviceAttr)
    {
        imiReleaseDeviceList(&pDeviceAttr);
    }

    // 10.imiDestroy()
    imiDestroy();

    if (NULL != g_pRender)
    {
        delete g_pRender;
        g_pRender = NULL;
    }

    getchar();

    return 0;
}
