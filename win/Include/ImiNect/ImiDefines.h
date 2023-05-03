/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : ImiDefines.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-27
  @Description   : Defines data structs used in IMI API
  @Version       : 0.1.0

  @History       :
  1.2015-05-27 Chen Shangwei Created file

********************************************************************************/

#ifndef _IMI_DEFINES_H_
#define _IMI_DEFINES_H_

#include <stdint.h>
#include <ImiProperties.h>

#ifdef __cplusplus
extern "C" {
#endif


//types
struct ImiDevice;
struct ImiStream;
struct ImiRecord;
typedef struct ImiDevice *ImiDeviceHandle;
typedef struct ImiStream *ImiStreamHandle;
typedef struct ImiRecord *ImiRecordHandle;

//basic enums
#define    IMI_DEVICE_CAMERA  (1 << 0)
#define    IMI_DEVICE_AUDIO   (1 << 1)

typedef uint32_t ImiBOOL;
#define IMI_TRUE    1
#define IMI_FALSE   0

typedef enum {
    IMI_ROTATION_ANGLE_0 = 0x00,
    IMI_ROTATION_ANGLE_90 = 0x01,
    IMI_ROTATION_ANGLE_180 = 0x02,
    IMI_ROTATION_ANGLE_270 = 0x03,
} ImiRotationAngle;

typedef enum {
    IMI_DRIVER_NONE = 0x00,
    IMI_DRIVER_USB = 0x01,
    IMI_DRIVER_FILE = 0x02,
    IMI_DRIVER_NET = 0x03,
} ImiDriverType;


typedef enum {

    IMI_BITPERPIXEL_MODE_IR_8 = 0x10, //open ir stream, one pixel use 8 bit
    IMI_BITPERPIXEL_MODE_IR_16 = 0x11, //open ir stream, one pixel use 16 bit
    IMI_BITPERPIXEL_MODE_DEPTH_16 = 0x20, //open depth stream, one pixel use 16 bit
    IMI_BITPERPIXEL_MODE_DEPTH_16_IR_16 = 0x30, //open depthIr stream, one depth pixel use 16 bit, one ir pixel use 16 bit
    IMI_BITPERPIXEL_MODE_DEPTH_16_IR_8 = 0x31, //open depthIr stream, one depth pixel use 16 bit, one ir pixel use  8 bit
} ImiBitPerPixelMode;


typedef uint32_t ImiFrameType;
enum {
    IMI_DEPTH_FRAME = 0x00,
    IMI_DEPTH_SKELETON_FRAME = 0x01,
    IMI_USER_INDEX_SKELETON_FRAME = 0x02,
    IMI_SKELETON_FRAME = 0x03,
    IMI_COLOR_FRAME = 0x04,
    IMI_DEPTH_IR_FRAME = 0x05,
    IMI_IR_FRAME = 0x06,
    IMI_IR_FLOOD_FRAME = 0x09, IMI_DEPTH_IR_COLOR_FRAME = 0x0A  //USBLITE ֧����ͼͬ�� 20210301
};

typedef enum {
    IMI_COLOR_DATA = 0x00,
    IMI_DEPTH_DATA = 0x04,
    IMI_DEPTH_ORG_DATA = 0x05,
    IMI_DEPTH_SKELETON_DATA = 0x08,
    IMI_USER_INDEX_SKELETON_DATA = 0x0c,
    IMI_SKELETON_DATA = 0x10
} ImiDataType;

typedef enum {
    IMI_DEVICE_STATE_CONNECT = 0,
    IMI_DEVICE_STATE_DISCONNECT = 1
} ImiDeviceState;

typedef uint32_t ImiCoordinateConvertMode;
enum {
    IMI_COORDINATE_VGATOVGA = 0,
    IMI_COORDINATE_VGATO720P = 1,
    IMI_COORDINATE_VGATO1080P = 2,

    IMI_COORDINATE_QVGATOVGA = 3,
    IMI_COORDINATE_QVGATO720P = 4,
    IMI_COORDINATE_QVGATO1080P = 5
};

//basic struct
typedef struct tagImiDriverInfo {
    ImiDriverType driverType;
    int32_t netListenPort;        // required when driverType is IMI_DRIVER_NET
    char recordFilePath[255];  // required when driverType is IMI_DRIVER_FILE
} ImiDriverInfo;

#define MAX_SN_SIZE 64
typedef struct tagImiDeviceAttribute {
    uint16_t vendorId;
    uint16_t productId;
    uint32_t deviceAddress;
    char serialNumber[MAX_SN_SIZE];
    char uri[255];
} ImiDeviceAttribute;

typedef struct tagVector4I {
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t w;
} ImiVector4I;

typedef struct tagVector4 {
    float x;
    float y;
    float z;
    float w;
} ImiVector4;

typedef struct tagPoint3D {
    float x;
    float y;
    float z;
} ImiPoint3D;

typedef int16_t ImiDepthPixel;
typedef struct tagImiFrame {
    ImiPixelFormat pixelFormat;
    ImiFrameType type;
    uint32_t frameNum;
    uint64_t timeStamp;

    uint32_t fps;
    int32_t width;
    int32_t height;

    void *pData;//depth color pixel data, if not null
    void *pSkeletonData;//skeleton frame if not null
    uint32_t size;

    ImiRotationAngle rotationAngle;            //picture rotation angle

    ImiBitPerPixelMode bitPerPixel;  // per pixel use bit

} ImiImageFrame;

typedef struct tagImiFrameMode {
    ImiPixelFormat pixelFormat;
    int16_t resolutionX;
    int16_t resolutionY;
    int8_t bitsPerPixel;
    int8_t framerate;
} ImiFrameMode;

typedef uint32_t ImiDeviceAnalzinParamsStatus;
enum {
    IMI_PARAMS_ANALZIN_OK = 0x00,   // ���ļ���ȡ��������ȷ
    IMI_PARAMS_ANALZIN_FILE_INFO_CRC_NOT_CORRECT = 0x01,   //�ļ����ݺ��ļ����ݼ������crc��ƥ��
    IMI_PARAMS_ANALZIN_FILE_SN_NOT_CORRECT = 0x02,   //�����ļ�SN��ƥ��
    IMI_PARAMS_ANALZIN_FILE_FW_VERSION_NOT_CORRECT = 0x03,   //�����ļ��̼��汾�Ų�ƥ��
    IMI_PARAMS_ANALZIN_FILE_SDK_VERSION_NOT_CORRECT = 0x04,   //�����ļ�SDK�汾�Ų�ƥ��
    IMI_PARAMS_ANALZIN_FILE_DEPTHPARAMS_NOT_CORRECT = 0x05,   //�����ļ���Ȳ�����ƥ��
    IMI_PARAMS_ANALZIN_FILE_SIZE_NOT_CORRECT = 0x06,   //�ļ����Ȳ���ȷ
    IMI_PARAMS_ANALZIN_FILE_NOT_EXIST = 0x07,   //�ļ�������
    IMI_PARAMS_OPEN_FILE_FAILED = 0x08,   //���ļ�ʧ��
};

typedef uint32_t ImiDeviceReadParamsStatus;
enum {
    IMI_PARAMS_READ_OK = 0x00,   // ���豸��ȡ������ȷ
    IMI_PARAMS_NOT_READ_FROM_DEVICE = 0x01,   // ���ļ���ȡ���ļ�������ȷ��δ���豸��ȡ
    IMI_PARAMS_READ_CRC_NOT_CORRECT = 0x02,   //���豸��ȡ��Ȳ�������ȷ
    IMI_PARAMS_READ_SN_NOT_CORRECT = 0x03,   //���豸��ȡSN����ȷ
    IMI_PARAMS_READ_FW_VERSION_NOT_CORRECT = 0x04,   //���豸��ȡ�̼��汾�Ų���ȷ
    IMI_PARAMS_READ_DEPTHPARAMS_NOT_CORRECT = 0x05,   //���豸��ȡ��Ȳ�������ȷ
};

typedef struct tagImiDeviceParamsStatuse {
    ImiDeviceAnalzinParamsStatus deviceAnalzinParamsStatus;
    ImiDeviceReadParamsStatus deviceReadParamsStatus;
} ImiDeviceParamsStatus;

typedef struct tagImiRect {
    int32_t x;
    int32_t y;
    int32_t w;
    int32_t h;
} ImiIRRect;

#if defined(_WIN32)
typedef void (_stdcall *ImiNewFrameCallback)(ImiStreamHandle stream, void *pUserData);
typedef void (_stdcall *ImiDeviceStateCallback)(const char *deviceUri, ImiDeviceState deviceState, void *pUserData);
#else
typedef void (* ImiNewFrameCallback) (ImiStreamHandle stream, void* pUserData);
typedef void (* ImiDeviceStateCallback) (const char* deviceUri, ImiDeviceState deviceState, void* pUserData);
#endif

#ifdef __cplusplus
}
#endif
#endif // _IMI_DEFINES_H_
