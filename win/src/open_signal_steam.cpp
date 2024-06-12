//
// Created by leioukupo on 2024/6/10.
//

#include <cstdio>

#ifndef _WIN32
#include <unistd.h>
#endif

// Imi Head File
#include "ImiNect.h"

// UI
#include "../Common/Render.h"

#define MAX_DEPTH 921600

#pragma pack(push, 1)

typedef struct tagRGBPixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

#pragma pack(pop)
//围绕结构定义的#pragma pack(push, 1)
// #pragma pack(pop)指令是编译器指令
// 用于控制结构的内存对齐。在这种情况下，
// #pragma pack(push, 1)将对齐设置为1字节，
// 这意味着编译器将尽可能紧密地打包结构成员，没有填充字节。当结构需要特定大小时，这是有用的，例如当它被用于表示文件或网络包中的数据。
// 在结构定义之后，使用#pragma pack(pop)来恢复之前的打包对齐


// 窗口句柄 用于渲染
SampleRender *g_pRender = nullptr;

// 设备属性指针
ImiDeviceAttribute *g_DeviceAttr = nullptr;

// 设备句柄
ImiDeviceHandle g_ImiDevice = nullptr;

// 流句柄
ImiStreamHandle g_streams[10];
// 流数量
uint32_t g_streamNum = 0;
ImiNewFrameCallback Open_streamCallback(const int* p)
{
    printf("open callback\n");
    printf("a: %d\n", *p);
    return nullptr;
}
void keyboardFun(unsigned char key, int32_t x, int32_t y) {
    switch (key) {
        case 'S':
        case 's':
            break;
        default:
            printf("Please input 's' or 'S'  to save image: \n");
            break;
    }
}
static bool needImage(void *pData) {
    int32_t avStreamIndex = 0;
    ImiImageFrame *pFrame = nullptr;
    // 5. 读一帧
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 100)) {
        int32_t error_code;
        printf("error_code: %s\n", imiGetErrorString(imiGetLastError()));
        return -1;
    }
    //打印pFrame的各项值
    printf("pixelFormat: %d\n", pFrame->pixelFormat);
    printf("frameType: %d\n", pFrame->type);
    printf("frameIndex: %d\n", pFrame->frameNum);
    printf("timestamp: %llu\n", pFrame->timeStamp);
    printf("dataSize: %d\n", pFrame->fps);
    printf("width: %d\n", pFrame->width);
    printf("height: %d\n", pFrame->height);
    printf("size: %d\n", pFrame->size);
    printf("rotationAngle: %u\n", pFrame->rotationAngle);
    printf("bitPerPixel: %d\n", pFrame->bitPerPixel);
//    TODO:处理接收数据,使得可以显示 解码
    imiReleaseFrame(&pFrame);
    return true;
}
int Exit() {
    //6.关闭流
    imiCloseStream(g_streams[g_streamNum]);
    //7.关闭设备
    if (nullptr != g_ImiDevice) {
        imiCloseDevice(g_ImiDevice);
        g_ImiDevice = nullptr;
    }
    //8.释放设备列表
    if (nullptr != g_DeviceAttr) {
        imiReleaseDeviceList(&g_DeviceAttr);
        g_DeviceAttr = nullptr;
    }
    //9.释放所以资源
    imiDestroy();
    printf("------ exit ------\n");
    getchar();
    return 0;
}

int main() {
    // 1.初始化
    int ret;
    ret = imiInitialize();
    if (ret != 0) {
        printf("imiInitialize failed: %d\n", ret);
        return -1;
    } else
        printf("imiInitialize success\n");
    // 2.获取设备列表
    uint32_t deviceCount = 0; //设备数量
    imiGetDeviceList(&g_DeviceAttr, &deviceCount);
    if ((deviceCount == 0) || (nullptr == g_DeviceAttr)) {
        printf("No device found\n");
        return -1;
    }
    // 打印g_DeviceAttr的各项值   g_DeviceAttr是指针数组
    // 打印ImiDeviceAttribute的各项值
    printf("vendorId: %d\n", g_DeviceAttr[0].vendorId);
    printf("productId: %d\n", g_DeviceAttr[0].productId);
    printf("deviceAddress: %u\n", g_DeviceAttr[0].deviceAddress);
    printf("serialNumber: %s\n", g_DeviceAttr[0].serialNumber);
    printf("uri: %s\n", g_DeviceAttr[0].uri);
    // 3.打开设备
    ret = imiOpenDevice(g_DeviceAttr[0].uri, &g_ImiDevice, 0);
    if (ret != 0) {
        printf("imiOpenDevice failed: %d\n", ret);
        return -1;
    } else
        printf("imiOpenDevice success\n");
    // 4.打开流
    //设置帧模式
    const ImiFrameMode *pMode = imiGetCurrentFrameMode(g_ImiDevice, IMI_DEPTH_FRAME);
    if (nullptr == pMode) {
        printf("Get current frame mode failed!\n");
        return -1;
    }
    printf("Get current frame mode:%d-%d-%d-%d-%d\n", pMode->bitsPerPixel,
           pMode->framerate, pMode->pixelFormat, pMode->resolutionX, pMode->resolutionY);
    imiSetFrameMode(g_ImiDevice, IMI_DEPTH_FRAME, (ImiFrameMode *) pMode);
    int a =0;
    int *p;
    p= &a;
    ret = imiOpenStream(g_ImiDevice, IMI_DEPTH_FRAME, Open_streamCallback(p), p, &g_streams[g_streamNum++]);
    if (0 != ret) {
        printf("Open Depth Stream Failed! ret = %d\n", ret);
        return -1;
    }
    printf("Open Depth Stream Success.\n");
//    6. 渲染
    g_pRender = new SampleRender("Depth View", pMode->resolutionX, pMode->resolutionY);  // window title & size
    g_pRender->init(0, nullptr);
    g_pRender->setKeyCallback(keyboardFun);
    g_pRender->setDataCallback(needImage, nullptr);
    g_pRender->run();

    return Exit();
}































