//
// Created by leioukupo on 2024/6/10.
//
//
// Created by leioukupo on 2024/6/10.
//

#include <cstdio>
#include <vector>

#ifndef _WIN32
#include <unistd.h>
#endif

// Imi Head File
#include "ImiNect.h"
// cam head file
#include "ImiCamera.h"
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
ImiCameraHandle g_ImiCamera = nullptr;
// 流句柄
ImiStreamHandle g_streams[10];
// 流数量
uint32_t g_streamNum = 0;
// 帧模式
ImiCameraFrameMode *pMode;
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

// 2rgb888      去拜耳阵列处理
void rawToRgb888(const uint8_t *rawData, uint8_t *rgbData, int width, int height) {
//    rgbData.resize(width * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;

            uint8_t r, g, b;
            if ((y % 2 == 0) && (x % 2 == 0)) {
                // Blue pixel
                b = rawData[index];
                g = ((y > 0 ? rawData[index - width] : 0) + (y < height - 1 ? rawData[index + width] : 0) +
                     (x > 0 ? rawData[index - 1] : 0) + (x < width - 1 ? rawData[index + 1] : 0)) / 4;
                r = ((y > 0 && x > 0 ? rawData[index - width - 1] : 0) +
                     (y > 0 && x < width - 1 ? rawData[index - width + 1] : 0) +
                     (y < height - 1 && x > 0 ? rawData[index + width - 1] : 0) +
                     (y < height - 1 && x < width - 1 ? rawData[index + width + 1] : 0)) / 4;
            } else if ((y % 2 == 0) && (x % 2 == 1)) {
                // Green pixel (on blue row)
                g = rawData[index];
                b = ((x > 0 ? rawData[index - 1] : 0) + (x < width - 1 ? rawData[index + 1] : 0)) / 2;
                r = ((y > 0 && x > 0 ? rawData[index - width - 1] : 0) +
                     (y > 0 && x < width - 1 ? rawData[index - width + 1] : 0) +
                     (y < height - 1 && x > 0 ? rawData[index + width - 1] : 0) +
                     (y < height - 1 && x < width - 1 ? rawData[index + width + 1] : 0)) / 4;
            } else if ((y % 2 == 1) && (x % 2 == 0)) {
                // Green pixel (on red row)
                g = rawData[index];
                r = ((y > 0 ? rawData[index - width] : 0) + (y < height - 1 ? rawData[index + width] : 0)) / 2;
                b = ((y > 0 && x > 0 ? rawData[index - width - 1] : 0) +
                     (y > 0 && x < width - 1 ? rawData[index - width + 1] : 0) +
                     (y < height - 1 && x > 0 ? rawData[index + width - 1] : 0) +
                     (y < height - 1 && x < width - 1 ? rawData[index + width + 1] : 0)) / 4;
            } else {
                // Red pixel
                r = rawData[index];
                g = ((y > 0 ? rawData[index - width] : 0) + (y < height - 1 ? rawData[index + width] : 0) +
                     (x > 0 ? rawData[index - 1] : 0) + (x < width - 1 ? rawData[index + 1] : 0)) / 4;
                b = ((y > 0 && x > 0 ? rawData[index - width - 1] : 0) +
                     (y > 0 && x < width - 1 ? rawData[index - width + 1] : 0) +
                     (y < height - 1 && x > 0 ? rawData[index + width - 1] : 0) +
                     (y < height - 1 && x < width - 1 ? rawData[index + width + 1] : 0)) / 4;
            }

            rgbData[index * 3 + 0] = r;
            rgbData[index * 3 + 1] = g;
            rgbData[index * 3 + 2] = b;
        }
    }
}

static bool needImage(void *pData) {
    ImiCameraFrame *pFrame = nullptr;
    static RGB888Pixel s_rgbImage[640 * 480];
    uint8_t *pRgbImage = nullptr;
    // 5. 读一帧
    if (0 != imiCamReadNextFrame(g_ImiCamera, &pFrame, 100)) {
        printf("error_code: %s\n", imiGetErrorString(imiGetLastError()));
        return -1;
    }
    //打印pFrame的各项值
    printf("pixelFormat: %d\n", pFrame->pixelFormat);
    printf("frameIndex: %d\n", pFrame->frameNum);
    printf("timestamp: %llu\n", pFrame->timeStamp);
    printf("Fps: %d\n", pFrame->fps);
    printf("width: %d\n", pFrame->width);
    printf("height: %d\n", pFrame->height);
    printf("size: %d\n", pFrame->size);
    printf("rotationAngle: %u\n", pFrame->rotationAngle);
    printf("bitPerPixel: %d\n", pFrame->bitPerPixel);
//    处理图像
    uint32_t rgbSize = pFrame->size / 2;
    pRgbImage = (uint8_t *) pFrame->pData;
//    for (rgbSize = 0; rgbSize < pFrame->size / 2; ++rgbSize) {
//        s_rgbImage[rgbSize].r = pRgbImage[rgbSize].r;
//        s_rgbImage[rgbSize].g = pRgbImage[rgbSize].g;
//        s_rgbImage[rgbSize].b = pRgbImage[rgbSize].b;
//    }
//    memcpy(s_rgbImage, pFrame->pData, rgbSize);
//    winhint
    rawToRgb888(pRgbImage, (uint8_t *) s_rgbImage, pFrame->width, pFrame->height);
    WinHint rect;
    rect.x = 100; // 设置窗口的 x 位置
    rect.y = 200; // 设置窗口的 y 位置
    rect.w = 480; // 设置窗口的宽度
    rect.h = 640; // 设置窗口的高度
    g_pRender->draw((uint8_t *) s_rgbImage, rgbSize, rect);
    imiCamReleaseFrame(&pFrame);
    return true;
}
int Exit() {
    //6.关闭流
    imiCamStopStream(g_ImiCamera);
    //7.关闭设备
    if (nullptr != g_ImiCamera) {
        imiCamClose(g_ImiCamera);
        g_ImiCamera = nullptr;
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
    uint32_t ret;
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
    ret = imiCamOpen(&g_ImiCamera);
    if (ret != 0) {
        printf("imiCamOpen failed: %d\n", ret);
        printf("error_code: %s\n", imiGetErrorString(imiGetLastError()));
        return -1;
    } else
        printf("imiCamOpen success\n");
    // 4.打开流
    //设置帧模式
    pMode = new ImiCameraFrameMode();
    pMode->fps = 30;
    pMode->resolutionX = 480;
    pMode->resolutionY = 640;
    pMode->pixelFormat=CAMERA_PIXEL_FORMAT_RGB888;
    imiCamSetFrameMode(g_ImiCamera, pMode);
    int32_t a = 5;
    do {
        a = imiCamStartStream2(g_ImiCamera);
        volatile int count = 0;
        for (int i = 0; i < 500 * 10000; ++i) {
            ++count; // 空操作
        }
        printf("%d\n", a);
    } while (a != 0);
    printf("Open UVC Stream Success.\n");
//    if (imiCamStartStream(g_ImiCamera, pMode)==0){
//        printf("Open UVC Stream Success.\n");
//    }
//    else{
//        printf("Open UVC Stream Failed.\n");
//        int32_t error_code;
//        printf("error_code: %s\n", imiGetErrorString(imiGetLastError()));
//        return -1;
//    }
//    6. 渲染
    g_pRender = new SampleRender("UVC View", pMode->resolutionX, pMode->resolutionY);  // window title & size
    g_pRender->init(0, nullptr);
    g_pRender->setKeyCallback(keyboardFun);
    g_pRender->setDataCallback(needImage, nullptr);
    g_pRender->run();

    return Exit();
}