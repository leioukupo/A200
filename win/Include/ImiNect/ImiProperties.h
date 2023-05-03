/********************************************************************************
  Copyright (c) 2015 Huajie IMI Technology Co., Ltd.
  All rights reserved.

  @File Name     : ImiProperties.h
  @Author        : Chen Shangwei
  @Date          : 2015-05-14
  @Description   : Define ImiNect Propeties
  @Version       : 0.1.0

  @History       :
  1.2015-05-14 Chen Shangwei Created file

********************************************************************************/

#ifndef _IMI_C_PROPERTIES_H_
#define _IMI_C_PROPERTIES_H_

// Public Properties
typedef enum {
    //General,
    IMI_PROPERTY_GENERAL_VERSION = 0x00,//ImiVersions Read Only
    IMI_PROPERTY_GENERAL_SERIAL_NUMBER = 0x01,//String, Read Only
    IMI_PROPERTY_GENERAL_FRAME_SYNC = 0x02, //Not Support Yet
    IMI_PROPERTY_IMAGE_REGISTRATION = 0x03, //value type ImiBOOL, IMI_TRUE:open registration, IMI_FALSE: close registration
    IMI_PROPERTY_DEVICE_ATTRIBUTE = 0x04,   //ImiDeviceAttribute, Read Only
    IMI_PROPERTY_DEVICE_LIGHT_MODE = 0x05,   //0 all close  1 open point light 2 open flood light
    IMI_PROPERTY_RESET_DEVICE = 0x06,//value type uint8_t, 1 reset Device
    IMI_PROPERTY_IR_DIST = 0x07,//value type uint8_t, 0-255
    IMI_PROPERTY_CHIP_REGISTRATION = 0x08, //valuie type uint8_t, 1 :open chip registration  0: close chip registration  default: 0
    IMI_PROPERTY_DEVICE_SWITCH_POWER = 0x09, //valuie type uint8_t, 1 :power is 1.3A   0: power is 0.8A   default: 0
    // Color,
    IMI_PROPERTY_COLOR_MIRROR = 0x13, //value type uint8_t, 1:mirror, 0: not mirror
    IMI_PROPERTY_COLOR_SHARPNESS = 0x14, //Not Support Yet
    IMI_PROPERTY_COLOR_BRIGHTNESS = 0x15, //Not Support Yet
    IMI_PROPERTY_COLOR_CONTRAST = 0x16, //Not Support Yet
    IMI_PROPERTY_COLOR_SATURATION = 0x17, //Not Support Yet
    IMI_PROPERTY_COLOR_GAIN = 0X18, //Not Support Yet
    IMI_PROPERTY_COLOR_AUTO_WHITE_BALANCE_MODE = 0x19, //Not Support Yet
    IMI_PROPERTY_COLOR_AUTO_EXPOSURE_MODE = 0x1a, //Not Support Yet
    IMI_PROPERTY_COLOR_ANTIFLICKER = 0x1b, //Not Support Yet
    IMI_PROPERTY_COLOR_INTRINSIC_PARAMS = 0x1d, // camera intrinsic parameter, value type float params[9]: ImiCameraIntrinsic Struct

    //Depth,
    IMI_PROPERTY_DEPTH_HOLE_FILTER = 0x33,//value type uint8_t, 1: open(default), 0: close
    IMI_PROPERTY_DEPTH_MIRROR = 0x34, //value type uint8_t, 1:mirror, 0: not mirror
    IMI_PROPERTY_DEPTH_DECIMATION = 0x35,//Not Support Yet
    IMI_PROPERTY_DEPTH_DENOISE = 0x37,  // value type uint8_t, 1: denoising, 0: not denoising, default 1
    IMI_PROPERTY_DEPTH_INTRINSIC_PARAMS = 0x36, // depth intrinsic parameter, value type float params[9]: ImiCameraIntrinsic Struct

    //IR,
    IMI_PROPERTY_IR_MIRROR = 0x1045, // Bool
    IMI_PROPERTY_IR_INTRINSIC_PARAMS = 0x60, // ir intrinsic parameter, value type float params[9]: ImiCameraIntrinsic Struct

    //Skeleton,
    IMI_PROPERTY_SKELETON_SMOOTH = 0x40,
    IMI_PROPERTY_SKELETON_MIRROR = 0x41, //value type uint8_t, 1:mirror, 0: not mirror
    IMI_PROPERTY_SKELETON_USER_SELECTOR_MODE = 0x53,
    IMI_PROPERTY_SKELETON_SELECT_TRACK_USER = 0x54,
    IMI_PROPERTY_SKELETON_UNSELECT_TRACK_USER = 0x55,
    IMI_PROPERTY_SKELETON_CALIBRATION = 0x57,  // value type uint8_t, 1:use calibration, 0: don't use calibration, default 0

    IMI_PROPERTY_GROUND_EQUATION = 0x70,     // value type uint8_t, 1:calculate ground equation, 0: don't calculate the ground equation, default 0
    IMI_PROPERTY_GROUND_CLEANUP = 0x71,     // value type uint8_t, 1:clear the ground, 0: don't clear the ground, default 0

    IMI_PROPERTY_LD_OPERATE = 0x80,  // value type uint8_t, 1: close the projector, 0: open the projector, default 0

    IMI_PROPERTY_FLOODLIGHT = 0x90,  // value type uint8_t, 1: open the floodlight, 0: close the floodlight, default 0

    IMI_PROPERTY_LASER_SAFETY_MODE = 0x99,  // value type uint8_t, 1: open the laser safety mode, 0: close the laser safety mode, default 1
    IMI_PROPERTY_SAFETY_DIST = 0x100,  // value type int16_t,
    IMI_PROPERTY_LIGHT_THRESHOLD = 0x101,  // value type int32_t,
    IMI_PROPERTY_AMBIENT_LIGHT_MODE = 0x102, //value type uint8_t, 1:open, 0:close, default 0
    IMI_PROPERTY_REAL_SAFETY_DIST = 0x103,  // value type int16_t,
    IMI_PROPERTY_REAL_LIGHT_THRESHOLD = 0x104,  // value type int32_t,

    IMI_PROPERTY_DEPTH_IR_MIRROR = 0x105,//value type uint8_t, 1:mirror, 0: not mirror

    IMI_PROPERTY_ROTATE_TRANS_INTRINSIC_PARAMS = 0x106, // rt intrinsic parameter, value type float params[12]:float rotate[9] + float trans[3]  ImiCameraIntrinsic Struct
    IMI_PROPERTY_IR_RECT = 0x107,    //ImiRect
    IMI_PROPERTY_CAMERA_PARAMS_4_USER = 0x109,            //Inquiry
    IMI_PROPERTY_IR_ENABLE = 0x10A,

    IMI_PROPERTY_PARAMS_IR2DEPTH_RT = 0x10B,            //Inquiry RT Array IR Camera 2 DepthCamera
    IMI_PROPERTY_DEPTH_IR_COLOR_MIRROR = 0x10C,//value type uint8_t, 1:mirror, 0: not mirror

    IMI_PROPERTY_IR_AE_SWITCH = 0x05e9,//value type uint8_t, 0:sonix AE close 1:sonix AE on    AE:automatic exposure

} ImiPropertyEnum;

// Pixel Format
typedef enum {
    IMI_PIXEL_FORMAT_DEP_16BIT = 0x00, //Depth

    IMI_PIXEL_FORMAT_IMAGE_YUV422 = 0x01, //Rgb
    IMI_PIXEL_FORMAT_IMAGE_H264 = 0x02, //H264 Compressed
    IMI_PIXEL_FORMAT_IMAGE_RGB24 = 0x03,
    IMI_PIXEL_FORMAT_IMAGE_YUV420SP = 0x04,  //NV21
    IMI_PIXEL_FORMAT_DEP_IR_16BIT = 0x05,

    IMI_PIXEL_FORMAT_IR_16BIT = 0x09,
} ImiPixelFormat;

// Image mirror's values
enum ImiMirror {
    PARAM_MIRROR_DISABLE = 0x00,
    PARAM_MIRROR_ENABLE = 0x01
};

// Color brightness's values
enum ImiColorBrightness {
    PARAM_COLOR_BRIGHTNESS_DEFAULT = 0x00,
    PARAM_COLOR_BRIGHTNESS_ADD_1 = 0x01,
    PARAM_COLOR_BRIGHTNESS_ADD_2 = 0x02,
    PARAM_COLOR_BRIGHTNESS_ADD_3 = 0x03,
    PARAM_COLOR_BRIGHTNESS_ADD_4 = 0x04,
    PARAM_COLOR_BRIGHTNESS_REDUCE_1 = 0x05,
    PARAM_COLOR_BRIGHTNESS_REDUCE_2 = 0x06,
    PARAM_COLOR_BRIGHTNESS_REDUCE_3 = 0x07,
    PARAM_COLOR_BRIGHTNESS_REDUCE_4 = 0x08
};

// Color contrast's values
enum ImiColorContrast {
    PARAM_COLOR_CONTRAST_DEFAULT = 0x00,
    PARAM_COLOR_CONTRAST_ADD_1 = 0x01,
    PARAM_COLOR_CONTRAST_ADD_2 = 0x02,
    PARAM_COLOR_CONTRAST_ADD_3 = 0x03,
    PARAM_COLOR_CONTRAST_ADD_4 = 0x04,
    PARAM_COLOR_CONTRAST_REDUCE_1 = 0x05,
    PARAM_COLOR_CONTRAST_REDUCE_2 = 0x06,
    PARAM_COLOR_CONTRAST_REDUCE_3 = 0x07,
    PARAM_COLOR_CONTRAST_REDUCE_4 = 0x08
};

// Color saturation's values
enum ImiColorSaturation {
    PARAM_COLOR_SATURATION_DEFAULT = 0x00,
    PARAM_COLOR_SATURATION_ADD_1 = 0x01,
    PARAM_COLOR_SATURATION_ADD_2 = 0x02,
    PARAM_COLOR_SATURATION_ADD_3 = 0x03,
    PARAM_COLOR_SATURATION_ADD_4 = 0x04,
    PARAM_COLOR_SATURATION_REDUCE_1 = 0x05,
    PARAM_COLOR_SATURATION_REDUCE_2 = 0x06,
    PARAM_COLOR_SATURATION_REDUCE_3 = 0x07,
    PARAM_COLOR_SATURATION_REDUCE_4 = 0x08
};

// Color auto white balance's values
enum ImiColorWhiteBalance {
    PARAM_COLOR_WHITE_BALANCE_AUTO = 0x00,
    PARAM_COLOR_WHITE_BALANCE_MANUAL_SUNNY = 0x01,
    PARAM_COLOR_WHITE_BALANCE_MANUAL_CLOUDY = 0x02,
    PARAM_COLOR_WHITE_BALANCE_MANUAL_OFFICE = 0x03,
    PARAM_COLOR_WHITE_BALANCE_MANUAL_HOME = 0x04,
    PARAM_COLOR_WHITE_BALANCE_MANUAL_NIGHT = 0x05
};

// Color auto exposure's values
enum ImiColorAutoExposure {
    PARAM_COLOR_AUTO_EXPOSURE_MODE_DISABLE = 0x00,
    PARAM_COLOR_AUTO_EXPOSURE_MODE_ENABLE = 0x01
};

// Light mode
enum ImiLightMode {
    IMI_LIGHT_MODE_SUNNY = 0x00,
    IMI_LIGHT_MODE_CLOUDY = 0x01,
    IMI_LIGHT_MODE_OFFICE = 0x02,
    IMI_LIGHT_MODE_HOME = 0x03,
    IMI_LIGHT_MODE_NIGHT = 0x04
};

#pragma pack (push, 1)

typedef struct tag_imi_fov_arear {
    int topLeftX;
    int topLeftY;
    int width;
    int height;

} imi_fov_arear;

typedef struct tag_imi_support_capacity {
    imi_fov_arear fov_arear_28cm;
    imi_fov_arear fov_arear_60cm;
    imi_fov_arear fov_arear_100cm;
    uint8_t bSupportColorDepthIr;
    uint8_t bSupportOutdoorMode;
    uint8_t bSupportScanCodeMode;
    uint8_t bSupportReset;
    uint8_t bSupportFloodIr;
} ImiSupportCapacity;

typedef struct tag_imi_sdk_version {
    uint8_t major;
    uint8_t minor;
    uint16_t revision;
} imi_sdk_version;

typedef struct tag_imi_fw_version {
    uint8_t major;
    uint8_t minor;
    uint16_t revision;
    uint8_t ap_major;
    uint8_t ap_minor;
    uint16_t ap_version;
} imi_fw_version;

typedef struct {
    imi_sdk_version sdk_version;
    imi_fw_version fw_version;
    char hw_version[64];
    char uvc_color_version[64];
    char bridge_fw_version[64];
} ImiVersions;


typedef struct {
    float fxParam;  //����
    float fyParam;  //����
    float cxParam;  //�������
    float cyParam;  //�������
    float k1Param;  //�������
    float k2Param;  //�������
    float k3Param;  //�������
    float p1Param;  //�������
    float p2Param;  //�������
} ImiCameraIntrinsic;

typedef struct {
    // ��ת����
    float rotateParam1;
    float rotateParam2;
    float rotateParam3;
    float rotateParam4;
    float rotateParam5;
    float rotateParam6;
    float rotateParam7;
    float rotateParam8;
    float rotateParam9;

    // ƽ������
    float transParam1;
    float transParam2;
    float transParam3;
} ImiRtIntrinsic;

typedef struct {
    float fFx;        //����		fx
    float fFy;        //����		fy
    float fCx;        //��������  cx
    float fCy;        //��������  cy
    float fTx;       // BaseLine ���߳���
    float fMinDis;    //��С��������
    float fMaxDis;  //������
    float fEf0;    //��������ͷ����
} ImiCameraParaDataInq;


typedef struct {
    uint16_t projectorTemp;
    uint16_t projectorCurrent;
    uint16_t chipTemp;
    uint16_t boxTemp;
} ImiCameraTemperatue;

#pragma pack(pop)

#endif // _IMI_C_PROPERTIES_H_
