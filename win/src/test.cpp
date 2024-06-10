/********************************************************************************
Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
All rights reserved.

@File Name		: main.cpp
@Author			: Wendell
@Date			: 2018-06-18
@Description	: read IR frame and view
@Version		: 1.0.0
@History		:
1.2018-06-18 Wendell Created file
********************************************************************************/
#include <cstdio>
#include <cstring>

#ifndef _WIN32
#include <unistd.h>
#endif

// Imi Head File
#include "ImiNect.h"

// UI
#include "../Common/Render.h"

#define MAX_DEPTH 921600

#pragma pack(push, 1)

typedef struct {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
} BMPFILEHEADER_T;

typedef struct {
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} BMPINFOHEADER_T;

typedef struct tagRGBPixel {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGBPixel;

#pragma pack(pop)

//switch of save one frame
bool g_bSave = false;
uint8_t g_bmpColor[1920 * 1080 * 3] = {0};


// window handle
SampleRender *g_pRender = nullptr;

ImiDeviceAttribute *g_DeviceAttr = nullptr;

// device handle
ImiDeviceHandle g_ImiDevice = nullptr;

// stream handles
ImiStreamHandle g_streams[10];
uint32_t g_streamNum = 0;

int32_t saveToBMP(const char *bmpImagePath, const uint8_t *pframe, int width, int height) {
    BMPFILEHEADER_T bmfh; // bitmap file header
    BMPINFOHEADER_T bmih; // bitmap info header (windows)

    const int OffBits = 54;

    int32_t imagePixSize = width * height;

    memset(&bmfh, 0, sizeof(BMPFILEHEADER_T));
    bmfh.bfReserved1 = 0;
    bmfh.bfReserved2 = 0;
    bmfh.bfType = 0x4d42;
    bmfh.bfOffBits = OffBits; // ͷ����Ϣ54�ֽ�
    bmfh.bfSize = imagePixSize * 3 + OffBits;

    memset(&bmih, 0, sizeof(BMPINFOHEADER_T));
    bmih.biSize = 40; // �ṹ���СΪ40
    bmih.biPlanes = 1;
    bmih.biSizeImage = imagePixSize * 3;

    bmih.biBitCount = 24;
    bmih.biCompression = 0;
    bmih.biWidth = width;
    bmih.biHeight = height;

    // rgb -> bgr
    auto *pRgb = (RGBPixel *) g_bmpColor;
    auto *pSrc = (RGBPixel *) pframe;
    int tmpindex1(0), tmpindex2(0);

    for (int i = 0; i < height; ++i) {
        tmpindex1 = i * width;
        tmpindex2 = (height - i - 1) * width;
        for (int j = 0; j < width; ++j) {
            pRgb[tmpindex1 + j].r = pSrc[tmpindex2 + j].b;
            pRgb[tmpindex1 + j].g = pSrc[tmpindex2 + j].g;
            pRgb[tmpindex1 + j].b = pSrc[tmpindex2 + j].r;
        }
    }

    char buf[128] = {0};
    std::string fullPath = bmpImagePath;

    FILE *pSaveBmp = fopen(fullPath.c_str(), "wb");
    if (nullptr == pSaveBmp) {
        return -1;
    }

    fwrite(&bmfh, 8, 1, pSaveBmp);
    fwrite(&bmfh.bfReserved2, sizeof(bmfh.bfReserved2), 1, pSaveBmp);
    fwrite(&bmfh.bfOffBits, sizeof(bmfh.bfOffBits), 1, pSaveBmp);
    fwrite(&bmih, sizeof(BMPINFOHEADER_T), 1, pSaveBmp);
    fwrite(g_bmpColor, imagePixSize * 3, 1, pSaveBmp);

    fclose(pSaveBmp);

    return 0;
}


// Histogram view mode
//计算直方图
//float *pHistogram  指向一个float的数组
//int histogramSize  数组的元素个数
//把pHistogram每一个元素映射到1-256
void calculateHistogram(float *pHistogram, int histogramSize, const ImiImageFrame *frame) {
    const auto *pDepth = (const uint16_t *) frame->pData;

    memset(pHistogram, 0, histogramSize * sizeof(float));// 0复制到pHistogram

    int height = frame->height;
    int width = frame->width;

    float nNumberOfPoints = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++pDepth) {
            if (*pDepth != 0) {
                pHistogram[*pDepth]++;+
//                printf("pHistogram: %f\n",pHistogram[*pDepth]);
                nNumberOfPoints++;//TODO: 这里可能是统计点数
            }
        }
    }

    for (int nIndex = 1; nIndex < histogramSize; ++nIndex) {
        pHistogram[nIndex] = pHistogram[nIndex] + pHistogram[nIndex - 1];//TODO: 两点之和？
    }//得到pHistogram所有元素和
    if (nNumberOfPoints) {
        for (int nIndex = 1; nIndex < histogramSize; ++nIndex) {
            pHistogram[nIndex] = (256 * (1.0f - (pHistogram[nIndex] / nNumberOfPoints)));//TODO:这里应该是转换成颜色啥的？？
        }//                                     pHistogram[nIndex] / nNumberOfPoints是pHistogram的平均值
    }//                                         可能是把pHistogram每一个元素映射到0-255
}
//        todo:参考这段计算点云信息
//        for (int m = 0; m < depth.rows; m++)
//            for (int n = 0; n < depth.cols; n++)
//            {
//                // 获取深度图中(m,n)处的值
//                unsigned short d = depth.ptr<unsigned short>(m)[n];
//                // d 可能没有值，若如此，跳过此点
//                if (d == 0)
//                    continue;
//                // d 存在值，则向点云增加一个点
//                PointT p;
//
//                // 计算这个点的空间坐标
//                p.z = double(d) / camera_factor;
//                p.x = (n - camera_cx) * p.z / camera_fx;
//                p.y = (m - camera_cy) * p.z / camera_fy;
//
//                // 从rgb图像中获取它的颜色
//                // rgb是三通道的BGR格式图，所以按下面的顺序获取颜色
//                p.b = rgb.ptr<uchar>(m)[n * 3];
//                p.g = rgb.ptr<uchar>(m)[n * 3 + 1];
//                p.r = rgb.ptr<uchar>(m)[n * 3 + 2];
//
//                // 把p加入到点云中
//                cloud->points.push_back(p);
//            }

// window callback, called by SampleRender::display()
static bool needImage(void *pData) {
    static float s_depthHist[MAX_DEPTH];
    static RGB888Pixel s_rgbImage[1280 * 1024];

    int32_t avStreamIndex = 0;
    ImiImageFrame *pFrame = nullptr;

    // frame read.
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 100)) {
        return false;
    }

    if (nullptr == pFrame) {
        return false;
    }

    // Calculate histogram
    calculateHistogram(s_depthHist, MAX_DEPTH, pFrame);

    uint32_t rgbSize;
    auto *pde = (uint16_t *) pFrame->pData;
    for (rgbSize = 0; rgbSize < pFrame->size / 2; ++rgbSize) { //填充rgb值
        s_rgbImage[rgbSize].r = s_depthHist[pde[rgbSize]]; // s_rgbImage是一个二维数组, 第一维是像素点,第二维是rgb
        s_rgbImage[rgbSize].g = s_rgbImage[rgbSize].r;
        s_rgbImage[rgbSize].b = 0;

    }

    if (g_bSave) { //保存图像
        static int index = 0;
        index++;
        {
            char bufName[64] = {0};
            sprintf(bufName, "Depth_%d.raw", index);
            FILE *pFile = fopen(bufName, "wb");
            if (pFile) {
                fwrite(pFrame->pData, pFrame->size, 1, pFile);
                fclose(pFile);
                printf("save one depth frame %s Success !\n", bufName);
            } else {
                printf("save one depth frame raw  Failed !\n");
            }
        }

        {
            char bufName[64] = {0};
            sprintf(bufName, "Depth_%d.bmp", index);

            if (0 == saveToBMP(bufName, (const uint8_t *) s_rgbImage, pFrame->width, pFrame->height)) {
                printf("save one depth frame %s Success !\n", bufName);
            } else {
                printf("save one depth frame bmp Failed !\n");
            }
        }

        g_bSave = false;
    }
// TODO:这里开始测试各种转换函数

    // Draw
    g_pRender->draw(-1, (uint8_t *) s_rgbImage, rgbSize, pFrame->width, pFrame->height, &pFrame);

    // call this to free frame
    imiReleaseFrame(&pFrame);

    return true;
}
static bool colorImage(void *pData){
    int32_t avStreamIndex = 0;
    uint32_t rgbSize;
    ImiImageFrame *pFrame = nullptr;
    static RGB888Pixel s_rgbImage[1280 * 1024];
    // frame read.
    if (0 != imiReadNextFrame(g_streams[avStreamIndex], &pFrame, 100)) {
        return false;
    }

    if (nullptr == pFrame) {
        return false;
    }

// Draw
    g_pRender->draw(-1, (uint8_t *) s_rgbImage, rgbSize, pFrame->width, pFrame->height, &pFrame);

    // call this to free frame
    imiReleaseFrame(&pFrame);
    return true;
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

    if (nullptr != g_pRender) {
        delete g_pRender;
        g_pRender = nullptr;
    }

    printf("------ exit ------\n");

    getchar();

    return 0;
}

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
ImiNewFrameCallback Open_streamCallback()
{
//    printf("打开流，回调启动");
    printf("open callback\n");
    return nullptr;
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
    const ImiFrameMode *pMode = imiGetCurrentFrameMode(g_ImiDevice, IMI_DEPTH_FRAME);
    if (nullptr == pMode) {
        printf("Get current frame mode failed!\n");
        return Exit();
    }
    printf("Get current frame mode:%d-%d-%d-%d-%d\n", pMode->bitsPerPixel,
           pMode->framerate, pMode->pixelFormat, pMode->resolutionX, pMode->resolutionY);
    imiSetFrameMode(g_ImiDevice, IMI_DEPTH_FRAME, (ImiFrameMode *) pMode);

    //5.imiOpenStream()
    ret = imiOpenStream(g_ImiDevice, IMI_COLOR_FRAME, Open_streamCallback(), nullptr, &g_streams[g_streamNum++]);
    if (0 != ret) {
        printf("Open Depth Stream Failed! ret = %d\n", ret);
        return Exit();
    }
    printf("Open Depth Stream Success.\n");

    //6.create window and set read Stream frame data callback
    g_pRender = new SampleRender("Depth View", pMode->resolutionX, pMode->resolutionY);  // window title & size
    g_pRender->init(argc, argv);
    g_pRender->setKeyCallback(keyboardFun);
    g_pRender->setDataCallback(colorImage, nullptr);
    g_pRender->run();

    return Exit();
}
