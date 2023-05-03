/********************************************************************************
Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
All rights reserved.

@File Name		: main.cpp
@Author			: Wendell
@Date			: 2018-06-18
@Description	: read Depth frame to convert to PointCloud and view
@Version		: 1.0.0
@History		:
1.2018-06-18 Wendell Created file
********************************************************************************/
#include <cstdio>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <fstream>
#include <ctime>

using namespace std;

// Imi Head File
#include "ImiNect.h"

// UI 3D
#include "../Common/Render2.h"

// window handle
SampleRender2 *g_pRender2 = nullptr;

ImiDeviceAttribute *g_DeviceAttr = nullptr;

// device handle
ImiDeviceHandle g_ImiDevice = nullptr;

// stream handles
ImiStreamHandle g_streams[10];
uint32_t g_streamNum = 0;

uint32_t g_Width = 640;
uint32_t g_Height = 480;

//switch of save one PointCloud
bool g_bSave = false;

ImiPoint3D g_Point3D[1920 * 1080] = {0};

// window callback, called by SampleRender::display()
static bool needImage(void *pData) {
    int32_t avStreamIndex = 0;
    ImiImageFrame *pFrame = nullptr;

    // frame read.
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 100)) {
        return false;
    }

    if (nullptr == pFrame) {
        return false;
    }

    //use default camera intrinsic parameter
    imiConvertDepthToPointCloud(pFrame, 0, 0, 0, 0, 0, &g_Point3D[0]);

    if (g_bSave) {
        char filename[128] = {0};
        sprintf(filename, "./imipcd_%d.obj", time(nullptr));
        ofstream fout(filename, ios::binary);

        int pcdCount = pFrame->width * pFrame->height;
        for (int i = 0; i < pcdCount; ++i) {
            //if(g_Point3D[i].z < 1.0 && g_Point3D[i].z > 0.1)
            //{
            fout << "v " << g_Point3D[i].x << " " << g_Point3D[i].y << " " << g_Point3D[i].z << "\r\n";
            //}
        }
        fout.close();

        printf("save one Depth frame PointCloud data to %s Success !\n", filename);

        g_bSave = false;
    }

    g_pRender2->drawMesh(&g_Point3D[0], pFrame->width * pFrame->height, pFrame->width, pFrame->height);

    // call this to free frame
    imiReleaseFrame(&pFrame);

    return true;
}

// keyboard event callback to save one PointCloud
void keyboardFun(unsigned char key, int32_t x, int32_t y) {
    switch (key) {
        case 'S':
        case 's':
            g_bSave = true;
            break;
        default:
            printf("Please input 's' or 'S'  to save image: \n");
            break;
    }
}

int Exit() {
    //7.imiCloseStream()
    for (uint32_t num = 0; num < g_streamNum; ++num) {
        if (nullptr != g_streams[num]) {
            imiCloseStream(g_streams[num]);
            g_streams[num] = nullptr;
        }
    }

    //8.imiCloseDevice()
    if (nullptr != g_ImiDevice) {
        imiCloseDevice(g_ImiDevice);
        g_ImiDevice = nullptr;
    }

    //9.imiReleaseDeviceList
    if (nullptr != g_DeviceAttr) {
        imiReleaseDeviceList(&g_DeviceAttr);
        g_DeviceAttr = nullptr;
    }

    //10.imiDestroy()
    imiDestroy();

    if (nullptr != g_pRender2) {
        delete g_pRender2;
        g_pRender2 = nullptr;
    }

    printf("------ exit ------\n");

    getchar();

    return 0;
}

int main(int argc, char **argv) {
    //1.imiInitialize()
    int ret = imiInitialize();
    if (0 != ret) {
        printf("ImiNect Init Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("ImiNect Init Success.\n");

    //2.imiGetDeviceList()
    uint32_t deviceCount = 0;
    imiGetDeviceList(&g_DeviceAttr, &deviceCount);
    if ((deviceCount <= 0) || (nullptr == g_DeviceAttr)) {
        printf("Get No Connected ImiDevice!\n");
        return Exit();
    }
    printf("Get %d Connected ImiDevice.\n", deviceCount);

    //3.imiOpenDevice()
    ret = imiOpenDevice(g_DeviceAttr[0].uri, &g_ImiDevice, 0);
    if (0 != ret) {
        printf("Open ImiDevice Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("ImiDevice Opened.\n");

    //4.imiGetCurrentFrameMode
    const ImiFrameMode *pFrameMode = imiGetCurrentFrameMode(g_ImiDevice, IMI_DEPTH_FRAME);
    if (nullptr == pFrameMode) {
        printf("Get current frame mode failed!\n");
        return Exit();
    }
    printf("Get current frame mode:%d-%d-%d-%d-%d\n", pFrameMode->bitsPerPixel, pFrameMode->framerate,
           pFrameMode->pixelFormat, pFrameMode->resolutionX, pFrameMode->resolutionY);
    imiSetFrameMode(g_ImiDevice, IMI_DEPTH_FRAME, (ImiFrameMode *) pFrameMode);
    g_Width = pFrameMode->resolutionX;
    g_Height = pFrameMode->resolutionY;

    //5.imiOpenStream()
    ret = imiOpenStream(g_ImiDevice, IMI_DEPTH_FRAME, nullptr, nullptr, &g_streams[g_streamNum++]);
    if (0 != ret) {
        printf("Open Depth Stream Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("Open Depth Stream Success.\n");

    //6.create window and set read Stream frame data callback
    g_pRender2 = new SampleRender2("Point Cloud View", g_Width * 2, g_Height * 2);  // window title & size
    g_pRender2->init(argc, argv);
    g_pRender2->setDataCallback(needImage, nullptr);
    g_pRender2->setKeyCallback(keyboardFun);
    g_pRender2->run();

    return Exit();
}
