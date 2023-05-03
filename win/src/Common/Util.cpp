#include <stdint.h>
#include <string.h>

//#include <ImiNect.h>
#include "ImiNect.h"

#include "Util.h"

#ifdef _WIN32
#ifdef __INTEL_COMPILER
#include <ia32intrin.h>
#else

#include <emmintrin.h>

#endif
#endif
#define YUV420_U   0
#define YUV420_Y1  1
#define YUV420_Y2  2
#define YUV420_V   3
#define YUV420_Y3  4
#define YUV420_Y4  5
#define YUV420_BPP 6
#define YUV422_U  0
#define YUV422_Y1 1
#define YUV422_V  2
#define YUV422_Y2 3
#define YUV422_BPP 4
#define YUV_RED   0
#define YUV_GREEN 1
#define YUV_BLUE  2
#define YUV_ALPHA  3
#define YUV_RGBA_BPP 4
#define YUYV_Y1 0
#define YUYV_U  1
#define YUYV_Y2 2
#define YUYV_V  3
#define YUYV_BPP 4
#define YUV_RED   0
#define YUV_GREEN 1
#define YUV_BLUE  2
#define YUV_RGB_BPP 3

#define MIN(a, b)            (((a) < (b)) ? (a) : (b))
#define MAX(a, b)            (((a) > (b)) ? (a) : (b))

typedef uint16_t DepthPixel;

void YUV444ToRGB888(uint8_t cY, uint8_t cU, uint8_t cV,
                    uint8_t &cR, uint8_t &cG, uint8_t &cB) {
    int32_t nC = cY - 16;
    int16_t nD = cU - 128;
    int16_t nE = cV - 128;

    nC = nC * 298 + 128;

    cR = (uint8_t) MIN(MAX((nC + 409 * nE) >> 8, 0), 255);
    cG = (uint8_t) MIN(MAX((nC - 100 * nD - 208 * nE) >> 8, 0), 255);
    cB = (uint8_t) MIN(MAX((nC + 516 * nD) >> 8, 0), 255);
};

void YUV420SPToRGB(uint8_t *rgb, uint8_t *yuv420sp, int width, int heigh) {
    int frameSize = width * heigh;
    int tmp;
    int pos = 0;
    int i, j;
    int uvp;
    int y, u, v, yp;
    int y1192;
    int r, g, b;

    for (j = 0, yp = 0; j < heigh; j++) {
        uvp = frameSize + (j >> 1) * width;
        u = 0;
        v = 0;
        for (i = 0; i < width; i++, yp++) {
            y = (0xff & ((int) yuv420sp[yp])) - 16;
            if (y < 0) y = 0;
            if ((i & 1) == 0) {
                v = (0xff & yuv420sp[uvp++]) - 128;
                u = (0xff & yuv420sp[uvp++]) - 128;
            }

            y1192 = 1192 * y;
            r = (y1192 + 1634 * v);
            g = (y1192 - 833 * v - 400 * u);
            b = (y1192 + 2066 * u);

            if (r < 0) r = 0; else if (r > 262143) r = 262143;
            if (g < 0) g = 0; else if (g > 262143) g = 262143;
            if (b < 0) b = 0; else if (b > 262143) b = 262143;

            tmp = 0xff000000 | ((r << 6) & 0xff0000) | ((g >> 2) & 0xff00) | ((b >> 10) & 0xff);
            *(rgb + pos) = (tmp >> 16) & 0xff;
            pos++;
            *(rgb + pos) = (tmp >> 8) & 0xff;
            pos++;
            *(rgb + pos) = (tmp) & 0xff;
            pos++;
        }
    }
}

int convert_yuv_to_rgb_pixel(int y, int u, int v) {
    unsigned int pixel32 = 0;
    unsigned char *pixel = (unsigned char *) &pixel32;
    int r, g, b;
    r = y + (1.370705 * (v - 128));
    g = y - (0.698001 * (v - 128)) - (0.337633 * (u - 128));
    b = y + (1.732446 * (u - 128));
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    pixel[0] = r;
    pixel[1] = g;
    pixel[2] = b;
    return pixel32;
}

void YUV422ToRGB(uint8_t *rgb, uint8_t *yuv422, uint32_t width, uint32_t height) {
    uint32_t in, out = 0;
    uint32_t pixel_16;
    uint8_t pixel_24[3];
    uint32_t pixel32;
    int y0, u, y1, v;

    for (in = 0; in < width * height * 2; in += 4) {
        pixel_16 =
                yuv422[in + 3] << 24 |
                yuv422[in + 2] << 16 |
                yuv422[in + 1] << 8 |
                yuv422[in + 0];
        y0 = (pixel_16 & 0x000000ff);
        u = (pixel_16 & 0x0000ff00) >> 8;
        y1 = (pixel_16 & 0x00ff0000) >> 16;
        v = (pixel_16 & 0xff000000) >> 24;
        pixel32 = convert_yuv_to_rgb_pixel(y0, u, v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
        pixel32 = convert_yuv_to_rgb_pixel(y1, u, v);
        pixel_24[0] = (pixel32 & 0x000000ff);
        pixel_24[1] = (pixel32 & 0x0000ff00) >> 8;
        pixel_24[2] = (pixel32 & 0x00ff0000) >> 16;
        rgb[out++] = pixel_24[0];
        rgb[out++] = pixel_24[1];
        rgb[out++] = pixel_24[2];
    }
}

#ifdef _WIN32

void YUV420ToRGB888(const uint8_t *pYUVImage, uint8_t *pRGBImage, uint32_t nYUVSize) {
    const uint8_t *pLastYUV = pYUVImage + nYUVSize - YUV420_BPP;

    while (pYUVImage < pLastYUV && pRGBImage < pYUVImage) {
        YUV444ToRGB888(pYUVImage[YUV420_Y1], pYUVImage[YUV420_U], pYUVImage[YUV420_V],
                       pRGBImage[YUV_RED], pRGBImage[YUV_GREEN], pRGBImage[YUV_BLUE]);
        pRGBImage += YUV_RGB_BPP;

        YUV444ToRGB888(pYUVImage[YUV420_Y2], pYUVImage[YUV420_U], pYUVImage[YUV420_V],
                       pRGBImage[YUV_RED], pRGBImage[YUV_GREEN], pRGBImage[YUV_BLUE]);
        pRGBImage += YUV_RGB_BPP;

        YUV444ToRGB888(pYUVImage[YUV420_Y3], pYUVImage[YUV420_U], pYUVImage[YUV420_V],
                       pRGBImage[YUV_RED], pRGBImage[YUV_GREEN], pRGBImage[YUV_BLUE]);
        pRGBImage += YUV_RGB_BPP;

        YUV444ToRGB888(pYUVImage[YUV420_Y4], pYUVImage[YUV420_U], pYUVImage[YUV420_V],
                       pRGBImage[YUV_RED], pRGBImage[YUV_GREEN], pRGBImage[YUV_BLUE]);
        pRGBImage += YUV_RGB_BPP;

        pYUVImage += YUV420_BPP;
    }
}

void YUV422ToRGB888(const uint8_t *pYUVImage, uint8_t *pRGBImage, uint32_t nYUVSize, uint32_t *pnActualRead,
                    uint32_t *pnRGBSize) {
    const uint8_t *pYUVLast = pYUVImage + nYUVSize - 8;
    const uint8_t *pYUVOrig = pYUVImage;
    const uint8_t *pRGBOrig = pRGBImage;
    const uint8_t *pRGBLast = pRGBImage + *pnRGBSize - 12;

    const __m128 minus128 = _mm_set_ps1(-128);
    const __m128 plus113983 = _mm_set_ps1(1.13983F);
    const __m128 minus039466 = _mm_set_ps1(-0.39466F);
    const __m128 minus058060 = _mm_set_ps1(-0.58060F);
    const __m128 plus203211 = _mm_set_ps1(2.03211F);
    const __m128 zero = _mm_set_ps1(0);
    const __m128 plus255 = _mm_set_ps1(255);

    // define YUV floats
    __m128 y;
    __m128 u;
    __m128 v;

    __m128 temp;

    // define RGB floats
    __m128 r;
    __m128 g;
    __m128 b;

    // define RGB integers
    __m128i iR;
    __m128i iG;
    __m128i iB;

    uint32_t *piR = (uint32_t *) &iR;
    uint32_t *piG = (uint32_t *) &iG;
    uint32_t *piB = (uint32_t *) &iB;

    while (pYUVImage <= pYUVLast && pRGBImage <= pRGBLast) {
        // process 4 pixels at once (values should be ordered backwards)
        y = _mm_set_ps(pYUVImage[YUV422_Y2 + YUV422_BPP], pYUVImage[YUV422_Y1 + YUV422_BPP], pYUVImage[YUV422_Y2],
                       pYUVImage[YUV422_Y1]);
        u = _mm_set_ps(pYUVImage[YUV422_U + YUV422_BPP], pYUVImage[YUV422_U + YUV422_BPP], pYUVImage[YUV422_U],
                       pYUVImage[YUV422_U]);
        v = _mm_set_ps(pYUVImage[YUV422_V + YUV422_BPP], pYUVImage[YUV422_V + YUV422_BPP], pYUVImage[YUV422_V],
                       pYUVImage[YUV422_V]);

        u = _mm_add_ps(u, minus128); // u -= 128
        v = _mm_add_ps(v, minus128); // v -= 128

        /*

        http://en.wikipedia.org/wiki/YUV

        From YUV to RGB:
        R =     Y + 1.13983 V
        G =     Y - 0.39466 U - 0.58060 V
        B =     Y + 2.03211 U

        */

        temp = _mm_mul_ps(plus113983, v);
        r = _mm_add_ps(y, temp);

        temp = _mm_mul_ps(minus039466, u);
        g = _mm_add_ps(y, temp);
        temp = _mm_mul_ps(minus058060, v);
        g = _mm_add_ps(g, temp);

        temp = _mm_mul_ps(plus203211, u);
        b = _mm_add_ps(y, temp);

        // make sure no value is smaller than 0
        r = _mm_max_ps(r, zero);
        g = _mm_max_ps(g, zero);
        b = _mm_max_ps(b, zero);

        // make sure no value is bigger than 255
        r = _mm_min_ps(r, plus255);
        g = _mm_min_ps(g, plus255);
        b = _mm_min_ps(b, plus255);

        // convert floats to int16 (there is no conversion to uint8, just to int8).
        iR = _mm_cvtps_epi32(r);
        iG = _mm_cvtps_epi32(g);
        iB = _mm_cvtps_epi32(b);

        // extract the 4 pixels RGB values.
        // because we made sure values are between 0 and 255, we can just take the lower byte
        // of each INT16
        pRGBImage[0] = (uint8_t) piR[0];
        pRGBImage[1] = (uint8_t) piG[0];
        pRGBImage[2] = (uint8_t) piB[0];

        pRGBImage[3] = (uint8_t) piR[1];
        pRGBImage[4] = (uint8_t) piG[1];
        pRGBImage[5] = (uint8_t) piB[1];

        pRGBImage[6] = (uint8_t) piR[2];
        pRGBImage[7] = (uint8_t) piG[2];
        pRGBImage[8] = (uint8_t) piB[2];

        pRGBImage[9] = (uint8_t) piR[3];
        pRGBImage[10] = (uint8_t) piG[3];
        pRGBImage[11] = (uint8_t) piB[3];

        // advance the streams
        pYUVImage += 8;
        pRGBImage += 12;
    }

    *pnActualRead = (uint32_t) (pYUVImage - pYUVOrig);
    *pnRGBSize = (uint32_t) (pRGBImage - pRGBOrig);
};

#else
void YUV422ToRGB888(const uint8_t* pYUVImage, uint8_t* pRGBImage, uint32_t nYUVSize, uint32_t* pnActualRead, uint32_t* pnRGBSize)
{
    const uint8_t* pOrigYUV = pYUVImage;
    const uint8_t* pCurrYUV = pYUVImage;
    const uint8_t* pOrigRGB = pRGBImage;
    uint8_t* pCurrRGB = pRGBImage;
    const uint8_t* pLastYUV = pYUVImage + nYUVSize - YUV422_BPP;
    const uint8_t* pLastRGB = pRGBImage + *pnRGBSize - YUV_RGB_BPP;

    while (pCurrYUV <= pLastYUV && pCurrRGB <= pLastRGB)
    {
        YUV444ToRGB888(pCurrYUV[YUV422_Y1], pCurrYUV[YUV422_U], pCurrYUV[YUV422_V],
                        pCurrRGB[YUV_RED], pCurrRGB[YUV_GREEN], pCurrRGB[YUV_BLUE]);
        pCurrRGB += YUV_RGB_BPP;
        YUV444ToRGB888(pCurrYUV[YUV422_Y2], pCurrYUV[YUV422_U], pCurrYUV[YUV422_V],
                        pCurrRGB[YUV_RED], pCurrRGB[YUV_GREEN], pCurrRGB[YUV_BLUE]);
        pCurrRGB += YUV_RGB_BPP;
        pCurrYUV += YUV422_BPP;
    }

    *pnActualRead = pCurrYUV - pOrigYUV;
    *pnRGBSize = pCurrRGB - pOrigRGB;
};

#endif


void calculateHistogram(float *pHistogram, int histogramSize, const ImiImageFrame &frame) {
    const DepthPixel *pDepth = (const DepthPixel *) frame.pData;
    // Calculate the accumulative histogram (the yellow display...)
    memset(pHistogram, 0, histogramSize * sizeof(float));
    //int restOfRow = frame.width;
    int height = frame.height;
    int width = frame.width;

    unsigned int nNumberOfPoints = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x, ++pDepth) {
            if (*pDepth != 0) {
                pHistogram[*pDepth]++;
                nNumberOfPoints++;
            }
        }
    }
    for (int nIndex = 1; nIndex < histogramSize; nIndex++) {
        pHistogram[nIndex] += pHistogram[nIndex - 1];
    }
    if (nNumberOfPoints) {
        for (int nIndex = 1; nIndex < histogramSize; nIndex++) {
            pHistogram[nIndex] = (256 * (1.0f - (pHistogram[nIndex] / nNumberOfPoints)));
        }
    }
}

void Depth2RGB888(RGB888Pixel *pRGBImage, uint32_t *pnRGBSize, float *pHistogram, int histogramSize,
                  const ImiImageFrame &depthframe) {
    calculateHistogram(pHistogram, histogramSize, depthframe);

    RGB888Pixel *pRgbRow = pRGBImage;
    const DepthPixel *pDepthRow = (const DepthPixel *) depthframe.pData;
    int rowSize = depthframe.width;

    for (int y = 0; y < depthframe.height; ++y) {

        const DepthPixel *pDepth = pDepthRow;
        RGB888Pixel *pRgb = pRgbRow;
        for (int x = 0; x < depthframe.width; ++x, ++pDepth, ++pRgb) {
            if (*pDepth != 0) {
                pRgb->r = (int8_t) pHistogram[*pDepth];
                pRgb->g = (int8_t) pHistogram[*pDepth];
                pRgb->b = 0;
            }
        }

        pDepthRow += rowSize;
        pRgbRow += rowSize;
    }

    *pnRGBSize = (depthframe.width * depthframe.height * sizeof(RGB888Pixel));
}

static const int64_t NUM_MILLISEC_PER_SEC = 1000;
static const int64_t NUM_MICROSECS_PER_SEC = 1000000;
static const int64_t NUM_NANNOSECS_PER_SEC = 1000000000;

static const int64_t NUM_MICROSECS_PER_MILLESEC = NUM_MICROSECS_PER_SEC /
                                                  NUM_MILLISEC_PER_SEC;
static const int64_t NUM_NANOSECS_PER_MILLESEC = NUM_NANNOSECS_PER_SEC /
                                                 NUM_MILLISEC_PER_SEC;
static const int64_t NUM_NANOSECS_PER_MICROSEC = NUM_NANNOSECS_PER_SEC /
                                                 NUM_MICROSECS_PER_SEC;

// January 1970, in NTP milliseconds.
static const int64_t JAN1970_AS_NTP_MILLISECS = 2208988800000;

static const uint32_t UINT32_HALF = 0x80000000;
#ifndef UINT32_MAX
#define UINT32_MAX  ((uint32_t)-1)
#endif

uint64_t timeNanos2() {

    uint64_t ticks = 0;
#if 0
#if defined(_WIN32)
    static volatile LONG last_timegettime = 0;
    static volatile int64_t num_wrap_timegettime = 0;
    volatile LONG* last_timegettime_ptr = &last_timegettime;

    DWORD now = timeGetTime();

    // Atomically update the last gotten time
    DWORD old = InterlockedExchange(last_timegettime_ptr, now);

    if(now < old)
    {
        // If now is earlier than old, there may have been a race between
        // threads.
        // 0x0fffffff ~3.1 days, the code will not take that long to execute
        // so it must have been a wrap around.
        if(old > 0xf0000000 && now < 0x0fffffff)
        {
            num_wrap_timegettime++;
        }
    }

    ticks = now + (num_wrap_timegettime << 32);
    ticks = ticks * NUM_NANOSECS_PER_MILLESEC;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    ticks = NUM_NANNOSECS_PER_SEC * static_cast<uint64_t>(ts.tv_sec) +
        static_cast<uint64_t>(ts.tv_nsec);
#endif
#endif
    return ticks;
}

uint64_t time2() {
    return static_cast<uint64_t>(timeNanos2() / NUM_NANOSECS_PER_MILLESEC);
}



