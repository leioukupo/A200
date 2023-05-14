//
// Created by leioukupo on 2023/5/6.
//
#include <cstdio>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpragma-pack"
// Imi Head File
#include "ImiNect.h"
// UI
#define MAX_DEPTH 10000
ImiDeviceAttribute *g_DeviceAttr = nullptr;

// device handle
ImiDeviceHandle g_ImiDevice = nullptr;
// stream handles
ImiStreamHandle g_streams[10];
uint32_t g_streamNum = 0;

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
    printf("------ exit ------\n");

    getchar();

    return 0;
}

int main(int argc, char **argv) {
    //初始化
    int ret = imiInitialize();
    if (0 != ret) {
        printf("ImiNect Init Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("ImiNect Init Success.\n");
    //获取设备
    uint32_t deviceCount = 0;
    imiGetDeviceList(&g_DeviceAttr, &deviceCount);
    if ((deviceCount <= 0) || (nullptr == g_DeviceAttr)) {
        printf("Get No Connected ImiDevice!\n");
        return Exit();
    }
    printf("Get %d Connected ImiDevice.\n", deviceCount);
    //打开设备
    ret = imiOpenDevice(g_DeviceAttr[0].uri, &g_ImiDevice, 0);
    if (0 != ret) {
        printf("Open ImiDevice Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("ImiDevice Opened.\n");
    //当前相机模式
    const ImiFrameMode *pMode = imiGetCurrentFrameMode(g_ImiDevice, IMI_DEPTH_FRAME);
    if (nullptr == pMode) {
        printf("Get current frame mode failed!\n");
        return Exit();
    }
    printf("Get current frame mode:%d-%d-%d-%d-%d\n", pMode->bitsPerPixel,
           pMode->framerate, pMode->pixelFormat, pMode->resolutionX, pMode->resolutionY);
    imiSetFrameMode(g_ImiDevice, IMI_DEPTH_FRAME, (ImiFrameMode *) pMode);
    //5.imiOpenStream()
    ret = imiOpenStream(g_ImiDevice, IMI_DEPTH_FRAME, nullptr, nullptr, &g_streams[g_streamNum++]);
    if (0 != ret) {
        printf("Open Depth Stream Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("Open Depth Stream Success.\n");
    return Exit();
}





