#ifndef _IMI_SAMPLE_UTILL_H_
#define _IMI_SAMPLE_UTILL_H_

#include <stdint.h>

#pragma pack (push, 1)

typedef struct
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
}RGB888Pixel;

typedef struct
{
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
   
}ARGB8888Pixel;

typedef uint16_t DepthPixel;

typedef struct
{
	uint8_t u;
	uint8_t y1;
	uint8_t v;
	uint8_t y2;
}YUV422DoublePixel;

#pragma pack (pop)

extern void YUV420SPToRGB(uint8_t* rgb, uint8_t* yuv420sp, int width, int heigh);
extern void YUV422ToRGB(uint8_t *rgb, uint8_t *yuv422, uint32_t width, uint32_t height);
extern void YUV420ToRGB888(const uint8_t* pYUVImage, uint8_t* pRGBImage, uint32_t nYUVSize);
extern void YUV422ToRGB888(const uint8_t* pYUVImage, uint8_t* pRGBImage, uint32_t nYUVSize, uint32_t* pnActualRead, uint32_t* pnRGBSize);
extern void Depth2RGB888(RGB888Pixel* pRGBImage, uint32_t* pnRGBSize, float* pHistogram, int histogramSize, const ImiImageFrame& depthframe);
extern uint64_t time2();
#endif