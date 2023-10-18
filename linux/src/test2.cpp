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

#include <stdio.h>
#include <string.h>

#include "ImiCameraDefines.h"
#include "ImiCamera.h"


#define IMAGE_WIDTH				    640
#define IMAGE_HEIGHT				480
#define DEFAULT_PERPIXEL_BITS		16
#define DEFAULT_FRAMERATE			30


// window handle
SampleRender*   g_pRender = NULL;

// stream handles
ImiStreamHandle	g_streams[10] = { NULL };
uint32_t		g_streamNum = 0;

ImiCameraHandle g_cameraDevice = NULL;

// window callback, called by SampleRender::display()
static bool needImage(void* pData)
{
    static RGB888Pixel	g_depthImage[IMAGE_WIDTH * IMAGE_HEIGHT];
    static RGB888Pixel	g_colorImage[IMAGE_WIDTH * IMAGE_HEIGHT];

    // wait for stream, -1 means infinite;
    int32_t avStreamIndex;
    if (0 != imiWaitForStreams(g_streams, g_streamNum, &avStreamIndex, 100))
    {
        return false;
    }

    // frame coming, read.
    ImiImageFrame* imiFrame = NULL;
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &imiFrame, 30))
    {
        return false;
    }

    if (NULL == imiFrame)
    {
        return true;
    }

    uint32_t i;
    uint16_t * pde = (uint16_t*)imiFrame->pData;
    for (i = 0; i < imiFrame->size/2; ++i)
    {
        g_depthImage[i].r = pde[i] >> 3;
        g_depthImage[i].g = g_depthImage[i].b = g_depthImage[i].r;
    }


    ImiCameraFrame* pCamFrame = NULL;
    if(0 != imiCamReadNextFrame(g_cameraDevice, &pCamFrame, 40)) {
        imiReleaseFrame(&imiFrame);
        return false;
    }

    if(NULL == pCamFrame) {
        imiReleaseFrame(&imiFrame);
        return true;
    }

    memcpy((void*)&g_colorImage, (const void*)pCamFrame->pData, pCamFrame->size);

    g_pRender->initViewPort();

    WindowHint hint(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    g_pRender->draw((uint8_t*)g_colorImage, pCamFrame->size, hint);

    hint.x += IMAGE_WIDTH;
    hint.w = imiFrame->width;
    hint.h = imiFrame->height;
    g_pRender->draw((uint8_t*)g_depthImage, imiFrame->size, hint);

    g_pRender->update();


    imiCamReleaseFrame(&pCamFrame);
    imiReleaseFrame(&imiFrame);

    return true;

}

int main(int argc, char** argv)
{
    //1.imiInitialize()
    if (0 != imiInitialize())
    {
        printf("ImiNect Init Failed!\n");
        getchar();
        return -1;
    }
    printf("ImiNect Init Success.\n");
//    获取相机支持的帧模式
//    const ImiCameraFrameMode** pModes;
//    uint32_t* pNumber= nullptr;
//    imiCamGetSupportFrameModes(g_cameraDevice, pModes, nullptr);
//    printf("mode number %n\n",pNumber);
    // open UVC camera

    if(0 != imiCamOpen(&g_cameraDevice)) {
        printf("Open UVC Camera Failed!\n");
        getchar();
        return -1;
    }

//    ImiCameraFrameMode frameMode = {CAMERA_PIXEL_FORMAT_RGB888, 640, 480, 30};
    if(0 != imiCamStartStream2(g_cameraDevice)) {
        printf("Start Camera stream Failed!\n");
        imiCamClose(g_cameraDevice);

        getchar();
        return -1;
    }

    //2.imiGetDeviceList()
    ImiDeviceAttribute* pDeviceAttr = NULL;
    uint32_t deviceCount = 0;
    imiGetDeviceList(&pDeviceAttr, &deviceCount);
    if( deviceCount <= 0 || NULL == pDeviceAttr )
    {
        printf("Get No Connected Imidevice!");
        imiDestroy();
        getchar();
        return -1;
    }
    printf("Get %d Connected Imidevice.\n", deviceCount);


    ImiDeviceHandle pImiDevice = NULL;

    //3.imiOpenDevice()
    if (0 != imiOpenDevice(pDeviceAttr[0].uri, &pImiDevice, IMI_DEVICE_CAMERA))
    {
        printf("Open Imidevice Failed!\n");
        goto exit;
    }
    printf("Imidevice Opened.\n");

    if (0 != imiOpenStream(pImiDevice, IMI_DEPTH_FRAME, NULL, NULL, &g_streams[g_streamNum++]))
    {
        printf("Open Depth Stream Failed!\n");
        goto exit;
    }
    printf("Open Depth Stream Success.\n");


    //6.create window and set read Stream frame data callback
    g_pRender = new SampleRender("UVCDepthViewer", IMAGE_WIDTH * 2, IMAGE_HEIGHT); // window title & size
    g_pRender->init(argc, argv);
    g_pRender->setDataCallback(needImage, NULL);

    g_pRender->run();

    exit:

    if(NULL != g_cameraDevice) {
        imiCamStopStream(g_cameraDevice);
        imiCamClose(g_cameraDevice);
        g_cameraDevice = NULL;
    }

    //7.imiCloseStream()
    for (uint32_t num = 0; num < g_streamNum; ++num)
    for (uint32_t num = 0; num < g_streamNum; ++num)
    {
        if (NULL != g_streams[num])
        {
            imiCloseStream(g_streams[num]);
        }
    }

    //8.imiCloseDevice()
    if (NULL != pImiDevice)
    {
        imiCloseDevice(pImiDevice);
    }

    //9.imiReleaseDeviceList()
    if(NULL != pDeviceAttr)
    {
        imiReleaseDeviceList(&pDeviceAttr);
    }

    //10.imiDestroy()
    imiDestroy();

    if (NULL != g_pRender)
    {
        delete g_pRender;
        g_pRender = NULL;
    }

    getchar();

    return 0;
}
