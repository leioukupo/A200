#ifndef _IMI_CAMERA_DEFINES_H_
#define _IMI_CAMERA_DEFINES_H_

#include <stdint.h>

//Api Export
#if !defined(IMICAMERA_API_EXPORT)
#if defined(_WIN32)
#define IMICAMERA_API_EXPORT __declspec(dllexport)
#elif defined (ANDROID) || defined (__linux__)
#define IMICAMERA_API_EXPORT __attribute__ ((visibility("default")))
#else
#	Unsupported Platform!
#endif
#endif

#ifdef __cplusplus
#	define IMICAMERA_EXP extern "C" IMICAMERA_API_EXPORT
#else // __cplusplus
#	define IMICAMERA_EXP IMICAMERA_API_EXPORT
#endif  // __cplusplus


typedef uint32_t ImiCAMBOOL;
#define IMI_CAM_TRUE    1
#define IMI_CAM_FALSE   0

struct ImiCamera;
typedef struct ImiCamera *ImiCameraHandle;


typedef enum {
    CAMERA_PIXEL_FORMAT_RGB888 = 0x00,
    CAMERA_PIXEL_FORMAT_MJPEG = 0x01,
    CAMERA_PIXEL_FORMAT_YUYV = 0x02,
    CAMERA_PIXEL_FORMAT_YUV420SP = 0x03

} ImiCameraPixelFormat;


typedef enum {
    CAMERA_ROTATION_ANGLE_0 = 0x00,
    CAMERA_ROTATION_ANGLE_90 = 0x01,
    CAMERA_ROTATION_ANGLE_180 = 0x02,
    CAMERA_ROTATION_ANGLE_270 = 0x03,
} ImiCameraRotationAngle;


typedef enum {
    CAMERA_BITPERPIXEL_MODE_COLOR_UNKNOW = 0x00, //unknow
    CAMERA_BITPERPIXEL_MODE_COLOR_24 = 0x01, //open color stream , one pixel use 24 bit

} ImiCameraBitPerPixelMode;

typedef enum {
    CAMERA_PICTURE_MODE_COLOR = 0x01, //picture mode is color
    CAMERA_PICTURE_MODE_GRAY = 0x02, //picture mode is gray

} ImiCameraPictureMode;


typedef struct tagImiCameraFrame {
    ImiCameraPixelFormat pixelFormat;
    uint32_t frameNum;
    uint64_t timeStamp;

    uint32_t fps;
    int32_t width;
    int32_t height;

    void *pData;
    uint32_t size;

    ImiCameraRotationAngle rotationAngle;  //picture rotation angle
    ImiCameraBitPerPixelMode bitPerPixel;    //per pixel use bit data
    ImiCameraPictureMode pictureMode;    //picture mode

} ImiCameraFrame;

typedef struct tagCameraFrameMode {
    ImiCameraPixelFormat pixelFormat;
    int32_t resolutionX;
    int32_t resolutionY;
    int32_t fps;
} ImiCameraFrameMode;

/*
IMI_CAM_PROPERTY_COLOR_EXPOSURE_ABSOLUTE_TIME set:
linux&android : 0x1388,  0x9c4,  0x4e2, 0x271, 0x138, 0x9c, 0x4e, 0x27, 0x14, 0x0a, 0x05, 0x02, 0x01
window        : -1        -2      -3     -4     -5     -6    -7    -8    -9    -10   -11   -12  -13
*/
typedef enum {
    IMI_CAM_PROPERTY_COLOR_AE_MODE = 0x00,                   // value type: uint8_t, 1:manual exposure time，0:auto exposure time
    IMI_CAM_PROPERTY_COLOR_EXPOSURE_ABSOLUTE_TIME = 0x01,    // value type: int32_t
    IMI_CAM_PROPERTY_COLOR_BACKLIGHT_COMPENSATION = 0x02,    // value type: int32_t, 1:face mode，2:scan mode
    IMI_CAM_PROPERTY_COLOR_EXPOSURE_ABSOLUTE_TIME_MAX = 0x03,
    IMI_CAM_PROPERTY_COLOR_EXPOSURE_ABSOLUTE_TIME_MIN = 0x04,

    IMI_CAM_PROPERTY_COLOR_FOCUS_ABS_MAX = 0x2FE,     //[get/set][int32_t] value type: int32_t ,    Max Focus Value
    IMI_CAM_PROPERTY_COLOR_FOCUS_ABS_MIN = 0x2FF,     //[get/set][int32_t] value type: int32_t ,    Min Focus Value
    IMI_CAM_PROPERTY_COLOR_FOCUS_AUTO = 0x300,             //value type: int8_t ,     auto focus
    IMI_CAM_PROPERTY_COLOR_FOCUS_ABS = 0x301,             //value type: int32_t ,    focal target distance in millimeters
    IMI_CAM_PROPERTY_COLOR_IRIS_ABS = 0x302,             //value type: int32_t,     set/get the IRIS_ABSOLUTE control.
    IMI_CAM_PROPERTY_COLOR_ZOOM_ABS = 0x303,             //value type: int32_t,     set/get the ZOOM_ABSOLUTE control;
    IMI_CAM_PROPERTY_COLOR_PAN_ABS = 0x304,             //value type: int32_t,     set/get the Pan control;
    IMI_CAM_PROPERTY_COLOR_TILT_ABS = 0x305,             //value type: int32_t,     set/get the Tilt control;
    IMI_CAM_PROPERTY_COLOR_ROLL_ABS = 0x306,             //value type: int32_t,	    set/get the ROLL_ABSOLUTE control.


    IMI_CAM_PROPERTY_COLOR_BRIGHTNESS = 0x307,                     //value type: int32_t  ,set/get the BRIGHTNESS control.   (-64, 64) default: 0
    IMI_CAM_PROPERTY_COLOR_CONTRAST = 0x308,                         //value type: int32_t  ,set/get the CONTRAST control	  （0，64） default : 32
    IMI_CAM_PROPERTY_COLOR_GAIN = 0x309,                         //value type: int32_t  ,set/get the GAIN control.              (0,100)   default :0
    IMI_CAM_PROPERTY_COLOR_HUE = 0x30A,                             //value type: int32_t  set/get the HUE control.					(-40 , 40) default 0
    IMI_CAM_PROPERTY_COLOR_SATURATION = 0x30B,                     //value type: int32_t    ,set/get the SATURATION   control.	(0,128)  default: 64
    IMI_CAM_PROPERTY_COLOR_SHARPNESS = 0x30C,                     //value type: int32_t  , set/get the SHARPNESS control.   (0, 6)  default :3
    IMI_CAM_PROPERTY_COLOR_GAMMA = 0x30D,                         //value type: int32_t  , set/get the GAMMA control. (72,500)   default :100 yes pass
    IMI_CAM_PROPERTY_COLOR_WHITE_BALANCE_TEMPERATURE = 0x30E,    //value type: int32_t  ,set/get the WHITE_BALANCE_TEMPERATURE control. (2800,6500) default : 4600

    IMI_PROPERTY_IMI_DATA_OUTPUT_TIMEOUT = 0x30F,    //value type int32_t,   setDataOutputTimeOut(ms)

    IMI_PROPERTY_IMI_SONIX_BRIDGE = 0x1073,    //value type Write 0 to  reset  sonix color

} ImiCamPropertyEnum;

typedef struct tagImiCamAttribute {
    uint16_t vendorId;
    uint16_t productId;
    char uri[255];
    char serialnumber[32];
} ImiCamAttribute;

#endif
