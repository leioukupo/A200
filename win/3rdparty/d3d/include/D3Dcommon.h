

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 7.00.0555 */
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H

#include "windows.h"
#include "ole2.h"

#endif /*COM_NO_WINDOWS_H*/

#ifndef __d3dcommon_h__
#define __d3dcommon_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */

#ifndef __ID3D10Blob_FWD_DEFINED__
#define __ID3D10Blob_FWD_DEFINED__
typedef interface ID3D10Blob ID3D10Blob;
#endif    /* __ID3D10Blob_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C" {
#endif


/* interface __MIDL_itf_d3dcommon_0000_0000 */
/* [local] */

typedef
enum D3D_DRIVER_TYPE {
    D3D_DRIVER_TYPE_UNKNOWN = 0,
    D3D_DRIVER_TYPE_HARDWARE = (D3D_DRIVER_TYPE_UNKNOWN + 1),
    D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1),
    D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),
    D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1),
    D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)
} D3D_DRIVER_TYPE;

typedef
enum D3D_FEATURE_LEVEL {
    D3D_FEATURE_LEVEL_9_1 = 0x9100,
    D3D_FEATURE_LEVEL_9_2 = 0x9200,
    D3D_FEATURE_LEVEL_9_3 = 0x9300,
    D3D_FEATURE_LEVEL_10_0 = 0xa000,
    D3D_FEATURE_LEVEL_10_1 = 0xa100,
    D3D_FEATURE_LEVEL_11_0 = 0xb000
} D3D_FEATURE_LEVEL;

typedef
enum D3D_PRIMITIVE_TOPOLOGY {
    D3D_PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
    D3D_PRIMITIVE_TOPOLOGY_POINTLIST = 1,
    D3D_PRIMITIVE_TOPOLOGY_LINELIST = 2,
    D3D_PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
    D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
    D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
    D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
    D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
    D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
    D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
    D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = 33,
    D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = 34,
    D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = 35,
    D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = 36,
    D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = 37,
    D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = 38,
    D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = 39,
    D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = 40,
    D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = 41,
    D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = 42,
    D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = 43,
    D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = 44,
    D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = 45,
    D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = 46,
    D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = 47,
    D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = 48,
    D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = 49,
    D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = 50,
    D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = 51,
    D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = 52,
    D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = 53,
    D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = 54,
    D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = 55,
    D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = 56,
    D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = 57,
    D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = 58,
    D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = 59,
    D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = 60,
    D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = 61,
    D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = 62,
    D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = 63,
    D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64,
    D3D10_PRIMITIVE_TOPOLOGY_UNDEFINED = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
    D3D10_PRIMITIVE_TOPOLOGY_POINTLIST = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
    D3D10_PRIMITIVE_TOPOLOGY_LINELIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
    D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
    D3D10_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
    D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
    D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
    D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
    D3D11_PRIMITIVE_TOPOLOGY_POINTLIST = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
    D3D11_PRIMITIVE_TOPOLOGY_LINELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
    D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
    D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
    D3D11_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
    D3D11_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST
} D3D_PRIMITIVE_TOPOLOGY;

typedef
enum D3D_PRIMITIVE {
    D3D_PRIMITIVE_UNDEFINED = 0,
    D3D_PRIMITIVE_POINT = 1,
    D3D_PRIMITIVE_LINE = 2,
    D3D_PRIMITIVE_TRIANGLE = 3,
    D3D_PRIMITIVE_LINE_ADJ = 6,
    D3D_PRIMITIVE_TRIANGLE_ADJ = 7,
    D3D_PRIMITIVE_1_CONTROL_POINT_PATCH = 8,
    D3D_PRIMITIVE_2_CONTROL_POINT_PATCH = 9,
    D3D_PRIMITIVE_3_CONTROL_POINT_PATCH = 10,
    D3D_PRIMITIVE_4_CONTROL_POINT_PATCH = 11,
    D3D_PRIMITIVE_5_CONTROL_POINT_PATCH = 12,
    D3D_PRIMITIVE_6_CONTROL_POINT_PATCH = 13,
    D3D_PRIMITIVE_7_CONTROL_POINT_PATCH = 14,
    D3D_PRIMITIVE_8_CONTROL_POINT_PATCH = 15,
    D3D_PRIMITIVE_9_CONTROL_POINT_PATCH = 16,
    D3D_PRIMITIVE_10_CONTROL_POINT_PATCH = 17,
    D3D_PRIMITIVE_11_CONTROL_POINT_PATCH = 18,
    D3D_PRIMITIVE_12_CONTROL_POINT_PATCH = 19,
    D3D_PRIMITIVE_13_CONTROL_POINT_PATCH = 20,
    D3D_PRIMITIVE_14_CONTROL_POINT_PATCH = 21,
    D3D_PRIMITIVE_15_CONTROL_POINT_PATCH = 22,
    D3D_PRIMITIVE_16_CONTROL_POINT_PATCH = 23,
    D3D_PRIMITIVE_17_CONTROL_POINT_PATCH = 24,
    D3D_PRIMITIVE_18_CONTROL_POINT_PATCH = 25,
    D3D_PRIMITIVE_19_CONTROL_POINT_PATCH = 26,
    D3D_PRIMITIVE_20_CONTROL_POINT_PATCH = 28,
    D3D_PRIMITIVE_21_CONTROL_POINT_PATCH = 29,
    D3D_PRIMITIVE_22_CONTROL_POINT_PATCH = 30,
    D3D_PRIMITIVE_23_CONTROL_POINT_PATCH = 31,
    D3D_PRIMITIVE_24_CONTROL_POINT_PATCH = 32,
    D3D_PRIMITIVE_25_CONTROL_POINT_PATCH = 33,
    D3D_PRIMITIVE_26_CONTROL_POINT_PATCH = 34,
    D3D_PRIMITIVE_27_CONTROL_POINT_PATCH = 35,
    D3D_PRIMITIVE_28_CONTROL_POINT_PATCH = 36,
    D3D_PRIMITIVE_29_CONTROL_POINT_PATCH = 37,
    D3D_PRIMITIVE_30_CONTROL_POINT_PATCH = 38,
    D3D_PRIMITIVE_31_CONTROL_POINT_PATCH = 39,
    D3D_PRIMITIVE_32_CONTROL_POINT_PATCH = 40,
    D3D10_PRIMITIVE_UNDEFINED = D3D_PRIMITIVE_UNDEFINED,
    D3D10_PRIMITIVE_POINT = D3D_PRIMITIVE_POINT,
    D3D10_PRIMITIVE_LINE = D3D_PRIMITIVE_LINE,
    D3D10_PRIMITIVE_TRIANGLE = D3D_PRIMITIVE_TRIANGLE,
    D3D10_PRIMITIVE_LINE_ADJ = D3D_PRIMITIVE_LINE_ADJ,
    D3D10_PRIMITIVE_TRIANGLE_ADJ = D3D_PRIMITIVE_TRIANGLE_ADJ,
    D3D11_PRIMITIVE_UNDEFINED = D3D_PRIMITIVE_UNDEFINED,
    D3D11_PRIMITIVE_POINT = D3D_PRIMITIVE_POINT,
    D3D11_PRIMITIVE_LINE = D3D_PRIMITIVE_LINE,
    D3D11_PRIMITIVE_TRIANGLE = D3D_PRIMITIVE_TRIANGLE,
    D3D11_PRIMITIVE_LINE_ADJ = D3D_PRIMITIVE_LINE_ADJ,
    D3D11_PRIMITIVE_TRIANGLE_ADJ = D3D_PRIMITIVE_TRIANGLE_ADJ,
    D3D11_PRIMITIVE_1_CONTROL_POINT_PATCH = D3D_PRIMITIVE_1_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_2_CONTROL_POINT_PATCH = D3D_PRIMITIVE_2_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_3_CONTROL_POINT_PATCH = D3D_PRIMITIVE_3_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_4_CONTROL_POINT_PATCH = D3D_PRIMITIVE_4_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_5_CONTROL_POINT_PATCH = D3D_PRIMITIVE_5_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_6_CONTROL_POINT_PATCH = D3D_PRIMITIVE_6_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_7_CONTROL_POINT_PATCH = D3D_PRIMITIVE_7_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_8_CONTROL_POINT_PATCH = D3D_PRIMITIVE_8_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_9_CONTROL_POINT_PATCH = D3D_PRIMITIVE_9_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_10_CONTROL_POINT_PATCH = D3D_PRIMITIVE_10_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_11_CONTROL_POINT_PATCH = D3D_PRIMITIVE_11_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_12_CONTROL_POINT_PATCH = D3D_PRIMITIVE_12_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_13_CONTROL_POINT_PATCH = D3D_PRIMITIVE_13_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_14_CONTROL_POINT_PATCH = D3D_PRIMITIVE_14_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_15_CONTROL_POINT_PATCH = D3D_PRIMITIVE_15_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_16_CONTROL_POINT_PATCH = D3D_PRIMITIVE_16_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_17_CONTROL_POINT_PATCH = D3D_PRIMITIVE_17_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_18_CONTROL_POINT_PATCH = D3D_PRIMITIVE_18_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_19_CONTROL_POINT_PATCH = D3D_PRIMITIVE_19_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_20_CONTROL_POINT_PATCH = D3D_PRIMITIVE_20_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_21_CONTROL_POINT_PATCH = D3D_PRIMITIVE_21_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_22_CONTROL_POINT_PATCH = D3D_PRIMITIVE_22_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_23_CONTROL_POINT_PATCH = D3D_PRIMITIVE_23_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_24_CONTROL_POINT_PATCH = D3D_PRIMITIVE_24_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_25_CONTROL_POINT_PATCH = D3D_PRIMITIVE_25_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_26_CONTROL_POINT_PATCH = D3D_PRIMITIVE_26_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_27_CONTROL_POINT_PATCH = D3D_PRIMITIVE_27_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_28_CONTROL_POINT_PATCH = D3D_PRIMITIVE_28_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_29_CONTROL_POINT_PATCH = D3D_PRIMITIVE_29_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_30_CONTROL_POINT_PATCH = D3D_PRIMITIVE_30_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_31_CONTROL_POINT_PATCH = D3D_PRIMITIVE_31_CONTROL_POINT_PATCH,
    D3D11_PRIMITIVE_32_CONTROL_POINT_PATCH = D3D_PRIMITIVE_32_CONTROL_POINT_PATCH
} D3D_PRIMITIVE;

typedef
enum D3D_SRV_DIMENSION {
    D3D_SRV_DIMENSION_UNKNOWN = 0,
    D3D_SRV_DIMENSION_BUFFER = 1,
    D3D_SRV_DIMENSION_TEXTURE1D = 2,
    D3D_SRV_DIMENSION_TEXTURE1DARRAY = 3,
    D3D_SRV_DIMENSION_TEXTURE2D = 4,
    D3D_SRV_DIMENSION_TEXTURE2DARRAY = 5,
    D3D_SRV_DIMENSION_TEXTURE2DMS = 6,
    D3D_SRV_DIMENSION_TEXTURE2DMSARRAY = 7,
    D3D_SRV_DIMENSION_TEXTURE3D = 8,
    D3D_SRV_DIMENSION_TEXTURECUBE = 9,
    D3D_SRV_DIMENSION_TEXTURECUBEARRAY = 10,
    D3D_SRV_DIMENSION_BUFFEREX = 11,
    D3D10_SRV_DIMENSION_UNKNOWN = D3D_SRV_DIMENSION_UNKNOWN,
    D3D10_SRV_DIMENSION_BUFFER = D3D_SRV_DIMENSION_BUFFER,
    D3D10_SRV_DIMENSION_TEXTURE1D = D3D_SRV_DIMENSION_TEXTURE1D,
    D3D10_SRV_DIMENSION_TEXTURE1DARRAY = D3D_SRV_DIMENSION_TEXTURE1DARRAY,
    D3D10_SRV_DIMENSION_TEXTURE2D = D3D_SRV_DIMENSION_TEXTURE2D,
    D3D10_SRV_DIMENSION_TEXTURE2DARRAY = D3D_SRV_DIMENSION_TEXTURE2DARRAY,
    D3D10_SRV_DIMENSION_TEXTURE2DMS = D3D_SRV_DIMENSION_TEXTURE2DMS,
    D3D10_SRV_DIMENSION_TEXTURE2DMSARRAY = D3D_SRV_DIMENSION_TEXTURE2DMSARRAY,
    D3D10_SRV_DIMENSION_TEXTURE3D = D3D_SRV_DIMENSION_TEXTURE3D,
    D3D10_SRV_DIMENSION_TEXTURECUBE = D3D_SRV_DIMENSION_TEXTURECUBE,
    D3D10_1_SRV_DIMENSION_UNKNOWN = D3D_SRV_DIMENSION_UNKNOWN,
    D3D10_1_SRV_DIMENSION_BUFFER = D3D_SRV_DIMENSION_BUFFER,
    D3D10_1_SRV_DIMENSION_TEXTURE1D = D3D_SRV_DIMENSION_TEXTURE1D,
    D3D10_1_SRV_DIMENSION_TEXTURE1DARRAY = D3D_SRV_DIMENSION_TEXTURE1DARRAY,
    D3D10_1_SRV_DIMENSION_TEXTURE2D = D3D_SRV_DIMENSION_TEXTURE2D,
    D3D10_1_SRV_DIMENSION_TEXTURE2DARRAY = D3D_SRV_DIMENSION_TEXTURE2DARRAY,
    D3D10_1_SRV_DIMENSION_TEXTURE2DMS = D3D_SRV_DIMENSION_TEXTURE2DMS,
    D3D10_1_SRV_DIMENSION_TEXTURE2DMSARRAY = D3D_SRV_DIMENSION_TEXTURE2DMSARRAY,
    D3D10_1_SRV_DIMENSION_TEXTURE3D = D3D_SRV_DIMENSION_TEXTURE3D,
    D3D10_1_SRV_DIMENSION_TEXTURECUBE = D3D_SRV_DIMENSION_TEXTURECUBE,
    D3D10_1_SRV_DIMENSION_TEXTURECUBEARRAY = D3D_SRV_DIMENSION_TEXTURECUBEARRAY,
    D3D11_SRV_DIMENSION_UNKNOWN = D3D_SRV_DIMENSION_UNKNOWN,
    D3D11_SRV_DIMENSION_BUFFER = D3D_SRV_DIMENSION_BUFFER,
    D3D11_SRV_DIMENSION_TEXTURE1D = D3D_SRV_DIMENSION_TEXTURE1D,
    D3D11_SRV_DIMENSION_TEXTURE1DARRAY = D3D_SRV_DIMENSION_TEXTURE1DARRAY,
    D3D11_SRV_DIMENSION_TEXTURE2D = D3D_SRV_DIMENSION_TEXTURE2D,
    D3D11_SRV_DIMENSION_TEXTURE2DARRAY = D3D_SRV_DIMENSION_TEXTURE2DARRAY,
    D3D11_SRV_DIMENSION_TEXTURE2DMS = D3D_SRV_DIMENSION_TEXTURE2DMS,
    D3D11_SRV_DIMENSION_TEXTURE2DMSARRAY = D3D_SRV_DIMENSION_TEXTURE2DMSARRAY,
    D3D11_SRV_DIMENSION_TEXTURE3D = D3D_SRV_DIMENSION_TEXTURE3D,
    D3D11_SRV_DIMENSION_TEXTURECUBE = D3D_SRV_DIMENSION_TEXTURECUBE,
    D3D11_SRV_DIMENSION_TEXTURECUBEARRAY = D3D_SRV_DIMENSION_TEXTURECUBEARRAY,
    D3D11_SRV_DIMENSION_BUFFEREX = D3D_SRV_DIMENSION_BUFFEREX
} D3D_SRV_DIMENSION;

typedef struct _D3D_SHADER_MACRO {
    LPCSTR Name;
    LPCSTR Definition;
} D3D_SHADER_MACRO;

typedef struct _D3D_SHADER_MACRO *LPD3D_SHADER_MACRO;

DEFINE_GUID(IID_ID3D10Blob, 0x8ba5fb08, 0x5195, 0x40e2, 0xac, 0x58, 0xd, 0x98, 0x9c, 0x3a, 0x1, 0x2);


extern RPC_IF_HANDLE __MIDL_itf_d3dcommon_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3dcommon_0000_0000_v0_0_s_ifspec;

#ifndef __ID3D10Blob_INTERFACE_DEFINED__
#define __ID3D10Blob_INTERFACE_DEFINED__

/* interface ID3D10Blob */
/* [unique][local][object][uuid] */


EXTERN_C const IID IID_ID3D10Blob;

#if defined(__cplusplus) && !defined(CINTERFACE)

MIDL_INTERFACE("8BA5FB08-5195-40e2-AC58-0D989C3A0102")
ID3D10Blob : public IUnknown {
public:
    virtual LPVOID STDMETHODCALLTYPE GetBufferPointer(void) = 0;

    virtual SIZE_T STDMETHODCALLTYPE GetBufferSize(void) = 0;

};

#else 	/* C style interface */

typedef struct ID3D10BlobVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
        ID3D10Blob * This,
        /* [in] */ REFIID riid,
        /* [annotation][iid_is][out] */
        __RPC__deref_out  void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(
        ID3D10Blob * This);

    ULONG ( STDMETHODCALLTYPE *Release )(
        ID3D10Blob * This);

    LPVOID ( STDMETHODCALLTYPE *GetBufferPointer )(
        ID3D10Blob * This);

    SIZE_T ( STDMETHODCALLTYPE *GetBufferSize )(
        ID3D10Blob * This);

    END_INTERFACE
} ID3D10BlobVtbl;

interface ID3D10Blob
{
    CONST_VTBL struct ID3D10BlobVtbl *lpVtbl;
};



#ifdef COBJMACROS


#define ID3D10Blob_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ID3D10Blob_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ID3D10Blob_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ID3D10Blob_GetBufferPointer(This)	\
    ( (This)->lpVtbl -> GetBufferPointer(This) ) 

#define ID3D10Blob_GetBufferSize(This)	\
    ( (This)->lpVtbl -> GetBufferSize(This) ) 

#endif /* COBJMACROS */


#endif    /* C style interface */


#endif    /* __ID3D10Blob_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_d3dcommon_0000_0001 */
/* [local] */

typedef interface ID3D10Blob *LPD3D10BLOB;
typedef ID3D10Blob ID3DBlob;
typedef ID3DBlob *LPD3DBLOB;
#define IID_ID3DBlob IID_ID3D10Blob
typedef
enum _D3D_INCLUDE_TYPE {
    D3D_INCLUDE_LOCAL = 0,
    D3D_INCLUDE_SYSTEM = (D3D_INCLUDE_LOCAL + 1),
    D3D10_INCLUDE_LOCAL = D3D_INCLUDE_LOCAL,
    D3D10_INCLUDE_SYSTEM = D3D_INCLUDE_SYSTEM,
    D3D_INCLUDE_FORCE_DWORD = 0x7fffffff
} D3D_INCLUDE_TYPE;

typedef interface ID3DInclude ID3DInclude;
#undef INTERFACE
#define INTERFACE ID3DInclude
DECLARE_INTERFACE(ID3DInclude) {
    STDMETHOD(Open)(THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData,
                    UINT *pBytes) PURE;

    STDMETHOD(Close)(THIS_ LPCVOID pData) PURE;
};
typedef ID3DInclude *LPD3DINCLUDE;
typedef
enum _D3D_SHADER_VARIABLE_CLASS {
    D3D_SVC_SCALAR = 0,
    D3D_SVC_VECTOR = (D3D_SVC_SCALAR + 1),
    D3D_SVC_MATRIX_ROWS = (D3D_SVC_VECTOR + 1),
    D3D_SVC_MATRIX_COLUMNS = (D3D_SVC_MATRIX_ROWS + 1),
    D3D_SVC_OBJECT = (D3D_SVC_MATRIX_COLUMNS + 1),
    D3D_SVC_STRUCT = (D3D_SVC_OBJECT + 1),
    D3D_SVC_INTERFACE_CLASS = (D3D_SVC_STRUCT + 1),
    D3D_SVC_INTERFACE_POINTER = (D3D_SVC_INTERFACE_CLASS + 1),
    D3D10_SVC_SCALAR = D3D_SVC_SCALAR,
    D3D10_SVC_VECTOR = D3D_SVC_VECTOR,
    D3D10_SVC_MATRIX_ROWS = D3D_SVC_MATRIX_ROWS,
    D3D10_SVC_MATRIX_COLUMNS = D3D_SVC_MATRIX_COLUMNS,
    D3D10_SVC_OBJECT = D3D_SVC_OBJECT,
    D3D10_SVC_STRUCT = D3D_SVC_STRUCT,
    D3D11_SVC_INTERFACE_CLASS = D3D_SVC_INTERFACE_CLASS,
    D3D11_SVC_INTERFACE_POINTER = D3D_SVC_INTERFACE_POINTER,
    D3D_SVC_FORCE_DWORD = 0x7fffffff
} D3D_SHADER_VARIABLE_CLASS;

typedef
enum _D3D_SHADER_VARIABLE_FLAGS {
    D3D_SVF_USERPACKED = 1,
    D3D_SVF_USED = 2,
    D3D_SVF_INTERFACE_POINTER = 4,
    D3D_SVF_INTERFACE_PARAMETER = 8,
    D3D10_SVF_USERPACKED = D3D_SVF_USERPACKED,
    D3D10_SVF_USED = D3D_SVF_USED,
    D3D11_SVF_INTERFACE_POINTER = D3D_SVF_INTERFACE_POINTER,
    D3D11_SVF_INTERFACE_PARAMETER = D3D_SVF_INTERFACE_PARAMETER,
    D3D_SVF_FORCE_DWORD = 0x7fffffff
} D3D_SHADER_VARIABLE_FLAGS;

typedef
enum _D3D_SHADER_VARIABLE_TYPE {
    D3D_SVT_VOID = 0,
    D3D_SVT_BOOL = 1,
    D3D_SVT_INT = 2,
    D3D_SVT_FLOAT = 3,
    D3D_SVT_STRING = 4,
    D3D_SVT_TEXTURE = 5,
    D3D_SVT_TEXTURE1D = 6,
    D3D_SVT_TEXTURE2D = 7,
    D3D_SVT_TEXTURE3D = 8,
    D3D_SVT_TEXTURECUBE = 9,
    D3D_SVT_SAMPLER = 10,
    D3D_SVT_SAMPLER1D = 11,
    D3D_SVT_SAMPLER2D = 12,
    D3D_SVT_SAMPLER3D = 13,
    D3D_SVT_SAMPLERCUBE = 14,
    D3D_SVT_PIXELSHADER = 15,
    D3D_SVT_VERTEXSHADER = 16,
    D3D_SVT_PIXELFRAGMENT = 17,
    D3D_SVT_VERTEXFRAGMENT = 18,
    D3D_SVT_UINT = 19,
    D3D_SVT_UINT8 = 20,
    D3D_SVT_GEOMETRYSHADER = 21,
    D3D_SVT_RASTERIZER = 22,
    D3D_SVT_DEPTHSTENCIL = 23,
    D3D_SVT_BLEND = 24,
    D3D_SVT_BUFFER = 25,
    D3D_SVT_CBUFFER = 26,
    D3D_SVT_TBUFFER = 27,
    D3D_SVT_TEXTURE1DARRAY = 28,
    D3D_SVT_TEXTURE2DARRAY = 29,
    D3D_SVT_RENDERTARGETVIEW = 30,
    D3D_SVT_DEPTHSTENCILVIEW = 31,
    D3D_SVT_TEXTURE2DMS = 32,
    D3D_SVT_TEXTURE2DMSARRAY = 33,
    D3D_SVT_TEXTURECUBEARRAY = 34,
    D3D_SVT_HULLSHADER = 35,
    D3D_SVT_DOMAINSHADER = 36,
    D3D_SVT_INTERFACE_POINTER = 37,
    D3D_SVT_COMPUTESHADER = 38,
    D3D_SVT_DOUBLE = 39,
    D3D_SVT_RWTEXTURE1D = 40,
    D3D_SVT_RWTEXTURE1DARRAY = 41,
    D3D_SVT_RWTEXTURE2D = 42,
    D3D_SVT_RWTEXTURE2DARRAY = 43,
    D3D_SVT_RWTEXTURE3D = 44,
    D3D_SVT_RWBUFFER = 45,
    D3D_SVT_BYTEADDRESS_BUFFER = 46,
    D3D_SVT_RWBYTEADDRESS_BUFFER = 47,
    D3D_SVT_STRUCTURED_BUFFER = 48,
    D3D_SVT_RWSTRUCTURED_BUFFER = 49,
    D3D_SVT_APPEND_STRUCTURED_BUFFER = 50,
    D3D_SVT_CONSUME_STRUCTURED_BUFFER = 51,
    D3D10_SVT_VOID = D3D_SVT_VOID,
    D3D10_SVT_BOOL = D3D_SVT_BOOL,
    D3D10_SVT_INT = D3D_SVT_INT,
    D3D10_SVT_FLOAT = D3D_SVT_FLOAT,
    D3D10_SVT_STRING = D3D_SVT_STRING,
    D3D10_SVT_TEXTURE = D3D_SVT_TEXTURE,
    D3D10_SVT_TEXTURE1D = D3D_SVT_TEXTURE1D,
    D3D10_SVT_TEXTURE2D = D3D_SVT_TEXTURE2D,
    D3D10_SVT_TEXTURE3D = D3D_SVT_TEXTURE3D,
    D3D10_SVT_TEXTURECUBE = D3D_SVT_TEXTURECUBE,
    D3D10_SVT_SAMPLER = D3D_SVT_SAMPLER,
    D3D10_SVT_SAMPLER1D = D3D_SVT_SAMPLER1D,
    D3D10_SVT_SAMPLER2D = D3D_SVT_SAMPLER2D,
    D3D10_SVT_SAMPLER3D = D3D_SVT_SAMPLER3D,
    D3D10_SVT_SAMPLERCUBE = D3D_SVT_SAMPLERCUBE,
    D3D10_SVT_PIXELSHADER = D3D_SVT_PIXELSHADER,
    D3D10_SVT_VERTEXSHADER = D3D_SVT_VERTEXSHADER,
    D3D10_SVT_PIXELFRAGMENT = D3D_SVT_PIXELFRAGMENT,
    D3D10_SVT_VERTEXFRAGMENT = D3D_SVT_VERTEXFRAGMENT,
    D3D10_SVT_UINT = D3D_SVT_UINT,
    D3D10_SVT_UINT8 = D3D_SVT_UINT8,
    D3D10_SVT_GEOMETRYSHADER = D3D_SVT_GEOMETRYSHADER,
    D3D10_SVT_RASTERIZER = D3D_SVT_RASTERIZER,
    D3D10_SVT_DEPTHSTENCIL = D3D_SVT_DEPTHSTENCIL,
    D3D10_SVT_BLEND = D3D_SVT_BLEND,
    D3D10_SVT_BUFFER = D3D_SVT_BUFFER,
    D3D10_SVT_CBUFFER = D3D_SVT_CBUFFER,
    D3D10_SVT_TBUFFER = D3D_SVT_TBUFFER,
    D3D10_SVT_TEXTURE1DARRAY = D3D_SVT_TEXTURE1DARRAY,
    D3D10_SVT_TEXTURE2DARRAY = D3D_SVT_TEXTURE2DARRAY,
    D3D10_SVT_RENDERTARGETVIEW = D3D_SVT_RENDERTARGETVIEW,
    D3D10_SVT_DEPTHSTENCILVIEW = D3D_SVT_DEPTHSTENCILVIEW,
    D3D10_SVT_TEXTURE2DMS = D3D_SVT_TEXTURE2DMS,
    D3D10_SVT_TEXTURE2DMSARRAY = D3D_SVT_TEXTURE2DMSARRAY,
    D3D10_SVT_TEXTURECUBEARRAY = D3D_SVT_TEXTURECUBEARRAY,
    D3D11_SVT_HULLSHADER = D3D_SVT_HULLSHADER,
    D3D11_SVT_DOMAINSHADER = D3D_SVT_DOMAINSHADER,
    D3D11_SVT_INTERFACE_POINTER = D3D_SVT_INTERFACE_POINTER,
    D3D11_SVT_COMPUTESHADER = D3D_SVT_COMPUTESHADER,
    D3D11_SVT_DOUBLE = D3D_SVT_DOUBLE,
    D3D11_SVT_RWTEXTURE1D = D3D_SVT_RWTEXTURE1D,
    D3D11_SVT_RWTEXTURE1DARRAY = D3D_SVT_RWTEXTURE1DARRAY,
    D3D11_SVT_RWTEXTURE2D = D3D_SVT_RWTEXTURE2D,
    D3D11_SVT_RWTEXTURE2DARRAY = D3D_SVT_RWTEXTURE2DARRAY,
    D3D11_SVT_RWTEXTURE3D = D3D_SVT_RWTEXTURE3D,
    D3D11_SVT_RWBUFFER = D3D_SVT_RWBUFFER,
    D3D11_SVT_BYTEADDRESS_BUFFER = D3D_SVT_BYTEADDRESS_BUFFER,
    D3D11_SVT_RWBYTEADDRESS_BUFFER = D3D_SVT_RWBYTEADDRESS_BUFFER,
    D3D11_SVT_STRUCTURED_BUFFER = D3D_SVT_STRUCTURED_BUFFER,
    D3D11_SVT_RWSTRUCTURED_BUFFER = D3D_SVT_RWSTRUCTURED_BUFFER,
    D3D11_SVT_APPEND_STRUCTURED_BUFFER = D3D_SVT_APPEND_STRUCTURED_BUFFER,
    D3D11_SVT_CONSUME_STRUCTURED_BUFFER = D3D_SVT_CONSUME_STRUCTURED_BUFFER,
    D3D_SVT_FORCE_DWORD = 0x7fffffff
} D3D_SHADER_VARIABLE_TYPE;

typedef
enum _D3D_SHADER_INPUT_FLAGS {
    D3D_SIF_USERPACKED = 1,
    D3D_SIF_COMPARISON_SAMPLER = 2,
    D3D_SIF_TEXTURE_COMPONENT_0 = 4,
    D3D_SIF_TEXTURE_COMPONENT_1 = 8,
    D3D_SIF_TEXTURE_COMPONENTS = 12,
    D3D10_SIF_USERPACKED = D3D_SIF_USERPACKED,
    D3D10_SIF_COMPARISON_SAMPLER = D3D_SIF_COMPARISON_SAMPLER,
    D3D10_SIF_TEXTURE_COMPONENT_0 = D3D_SIF_TEXTURE_COMPONENT_0,
    D3D10_SIF_TEXTURE_COMPONENT_1 = D3D_SIF_TEXTURE_COMPONENT_1,
    D3D10_SIF_TEXTURE_COMPONENTS = D3D_SIF_TEXTURE_COMPONENTS,
    D3D_SIF_FORCE_DWORD = 0x7fffffff
} D3D_SHADER_INPUT_FLAGS;

typedef
enum _D3D_SHADER_INPUT_TYPE {
    D3D_SIT_CBUFFER = 0,
    D3D_SIT_TBUFFER = (D3D_SIT_CBUFFER + 1),
    D3D_SIT_TEXTURE = (D3D_SIT_TBUFFER + 1),
    D3D_SIT_SAMPLER = (D3D_SIT_TEXTURE + 1),
    D3D_SIT_UAV_RWTYPED = (D3D_SIT_SAMPLER + 1),
    D3D_SIT_STRUCTURED = (D3D_SIT_UAV_RWTYPED + 1),
    D3D_SIT_UAV_RWSTRUCTURED = (D3D_SIT_STRUCTURED + 1),
    D3D_SIT_BYTEADDRESS = (D3D_SIT_UAV_RWSTRUCTURED + 1),
    D3D_SIT_UAV_RWBYTEADDRESS = (D3D_SIT_BYTEADDRESS + 1),
    D3D_SIT_UAV_APPEND_STRUCTURED = (D3D_SIT_UAV_RWBYTEADDRESS + 1),
    D3D_SIT_UAV_CONSUME_STRUCTURED = (D3D_SIT_UAV_APPEND_STRUCTURED + 1),
    D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = (D3D_SIT_UAV_CONSUME_STRUCTURED + 1),
    D3D10_SIT_CBUFFER = D3D_SIT_CBUFFER,
    D3D10_SIT_TBUFFER = D3D_SIT_TBUFFER,
    D3D10_SIT_TEXTURE = D3D_SIT_TEXTURE,
    D3D10_SIT_SAMPLER = D3D_SIT_SAMPLER,
    D3D11_SIT_UAV_RWTYPED = D3D_SIT_UAV_RWTYPED,
    D3D11_SIT_STRUCTURED = D3D_SIT_STRUCTURED,
    D3D11_SIT_UAV_RWSTRUCTURED = D3D_SIT_UAV_RWSTRUCTURED,
    D3D11_SIT_BYTEADDRESS = D3D_SIT_BYTEADDRESS,
    D3D11_SIT_UAV_RWBYTEADDRESS = D3D_SIT_UAV_RWBYTEADDRESS,
    D3D11_SIT_UAV_APPEND_STRUCTURED = D3D_SIT_UAV_APPEND_STRUCTURED,
    D3D11_SIT_UAV_CONSUME_STRUCTURED = D3D_SIT_UAV_CONSUME_STRUCTURED,
    D3D11_SIT_UAV_RWSTRUCTURED_WITH_COUNTER = D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER
} D3D_SHADER_INPUT_TYPE;

typedef
enum _D3D_SHADER_CBUFFER_FLAGS {
    D3D_CBF_USERPACKED = 1,
    D3D10_CBF_USERPACKED = D3D_CBF_USERPACKED,
    D3D_CBF_FORCE_DWORD = 0x7fffffff
} D3D_SHADER_CBUFFER_FLAGS;

typedef
enum _D3D_CBUFFER_TYPE {
    D3D_CT_CBUFFER = 0,
    D3D_CT_TBUFFER = (D3D_CT_CBUFFER + 1),
    D3D_CT_INTERFACE_POINTERS = (D3D_CT_TBUFFER + 1),
    D3D_CT_RESOURCE_BIND_INFO = (D3D_CT_INTERFACE_POINTERS + 1),
    D3D10_CT_CBUFFER = D3D_CT_CBUFFER,
    D3D10_CT_TBUFFER = D3D_CT_TBUFFER,
    D3D11_CT_CBUFFER = D3D_CT_CBUFFER,
    D3D11_CT_TBUFFER = D3D_CT_TBUFFER,
    D3D11_CT_INTERFACE_POINTERS = D3D_CT_INTERFACE_POINTERS,
    D3D11_CT_RESOURCE_BIND_INFO = D3D_CT_RESOURCE_BIND_INFO
} D3D_CBUFFER_TYPE;

typedef
enum D3D_NAME {
    D3D_NAME_UNDEFINED = 0,
    D3D_NAME_POSITION = 1,
    D3D_NAME_CLIP_DISTANCE = 2,
    D3D_NAME_CULL_DISTANCE = 3,
    D3D_NAME_RENDER_TARGET_ARRAY_INDEX = 4,
    D3D_NAME_VIEWPORT_ARRAY_INDEX = 5,
    D3D_NAME_VERTEX_ID = 6,
    D3D_NAME_PRIMITIVE_ID = 7,
    D3D_NAME_INSTANCE_ID = 8,
    D3D_NAME_IS_FRONT_FACE = 9,
    D3D_NAME_SAMPLE_INDEX = 10,
    D3D_NAME_FINAL_QUAD_EDGE_TESSFACTOR = 11,
    D3D_NAME_FINAL_QUAD_INSIDE_TESSFACTOR = 12,
    D3D_NAME_FINAL_TRI_EDGE_TESSFACTOR = 13,
    D3D_NAME_FINAL_TRI_INSIDE_TESSFACTOR = 14,
    D3D_NAME_FINAL_LINE_DETAIL_TESSFACTOR = 15,
    D3D_NAME_FINAL_LINE_DENSITY_TESSFACTOR = 16,
    D3D_NAME_TARGET = 64,
    D3D_NAME_DEPTH = 65,
    D3D_NAME_COVERAGE = 66,
    D3D_NAME_DEPTH_GREATER_EQUAL = 67,
    D3D_NAME_DEPTH_LESS_EQUAL = 68,
    D3D10_NAME_UNDEFINED = D3D_NAME_UNDEFINED,
    D3D10_NAME_POSITION = D3D_NAME_POSITION,
    D3D10_NAME_CLIP_DISTANCE = D3D_NAME_CLIP_DISTANCE,
    D3D10_NAME_CULL_DISTANCE = D3D_NAME_CULL_DISTANCE,
    D3D10_NAME_RENDER_TARGET_ARRAY_INDEX = D3D_NAME_RENDER_TARGET_ARRAY_INDEX,
    D3D10_NAME_VIEWPORT_ARRAY_INDEX = D3D_NAME_VIEWPORT_ARRAY_INDEX,
    D3D10_NAME_VERTEX_ID = D3D_NAME_VERTEX_ID,
    D3D10_NAME_PRIMITIVE_ID = D3D_NAME_PRIMITIVE_ID,
    D3D10_NAME_INSTANCE_ID = D3D_NAME_INSTANCE_ID,
    D3D10_NAME_IS_FRONT_FACE = D3D_NAME_IS_FRONT_FACE,
    D3D10_NAME_SAMPLE_INDEX = D3D_NAME_SAMPLE_INDEX,
    D3D10_NAME_TARGET = D3D_NAME_TARGET,
    D3D10_NAME_DEPTH = D3D_NAME_DEPTH,
    D3D10_NAME_COVERAGE = D3D_NAME_COVERAGE,
    D3D11_NAME_FINAL_QUAD_EDGE_TESSFACTOR = D3D_NAME_FINAL_QUAD_EDGE_TESSFACTOR,
    D3D11_NAME_FINAL_QUAD_INSIDE_TESSFACTOR = D3D_NAME_FINAL_QUAD_INSIDE_TESSFACTOR,
    D3D11_NAME_FINAL_TRI_EDGE_TESSFACTOR = D3D_NAME_FINAL_TRI_EDGE_TESSFACTOR,
    D3D11_NAME_FINAL_TRI_INSIDE_TESSFACTOR = D3D_NAME_FINAL_TRI_INSIDE_TESSFACTOR,
    D3D11_NAME_FINAL_LINE_DETAIL_TESSFACTOR = D3D_NAME_FINAL_LINE_DETAIL_TESSFACTOR,
    D3D11_NAME_FINAL_LINE_DENSITY_TESSFACTOR = D3D_NAME_FINAL_LINE_DENSITY_TESSFACTOR,
    D3D11_NAME_DEPTH_GREATER_EQUAL = D3D_NAME_DEPTH_GREATER_EQUAL,
    D3D11_NAME_DEPTH_LESS_EQUAL = D3D_NAME_DEPTH_LESS_EQUAL
} D3D_NAME;

typedef
enum D3D_RESOURCE_RETURN_TYPE {
    D3D_RETURN_TYPE_UNORM = 1,
    D3D_RETURN_TYPE_SNORM = 2,
    D3D_RETURN_TYPE_SINT = 3,
    D3D_RETURN_TYPE_UINT = 4,
    D3D_RETURN_TYPE_FLOAT = 5,
    D3D_RETURN_TYPE_MIXED = 6,
    D3D_RETURN_TYPE_DOUBLE = 7,
    D3D_RETURN_TYPE_CONTINUED = 8,
    D3D10_RETURN_TYPE_UNORM = D3D_RETURN_TYPE_UNORM,
    D3D10_RETURN_TYPE_SNORM = D3D_RETURN_TYPE_SNORM,
    D3D10_RETURN_TYPE_SINT = D3D_RETURN_TYPE_SINT,
    D3D10_RETURN_TYPE_UINT = D3D_RETURN_TYPE_UINT,
    D3D10_RETURN_TYPE_FLOAT = D3D_RETURN_TYPE_FLOAT,
    D3D10_RETURN_TYPE_MIXED = D3D_RETURN_TYPE_MIXED,
    D3D11_RETURN_TYPE_UNORM = D3D_RETURN_TYPE_UNORM,
    D3D11_RETURN_TYPE_SNORM = D3D_RETURN_TYPE_SNORM,
    D3D11_RETURN_TYPE_SINT = D3D_RETURN_TYPE_SINT,
    D3D11_RETURN_TYPE_UINT = D3D_RETURN_TYPE_UINT,
    D3D11_RETURN_TYPE_FLOAT = D3D_RETURN_TYPE_FLOAT,
    D3D11_RETURN_TYPE_MIXED = D3D_RETURN_TYPE_MIXED,
    D3D11_RETURN_TYPE_DOUBLE = D3D_RETURN_TYPE_DOUBLE,
    D3D11_RETURN_TYPE_CONTINUED = D3D_RETURN_TYPE_CONTINUED
} D3D_RESOURCE_RETURN_TYPE;

typedef
enum D3D_REGISTER_COMPONENT_TYPE {
    D3D_REGISTER_COMPONENT_UNKNOWN = 0,
    D3D_REGISTER_COMPONENT_UINT32 = 1,
    D3D_REGISTER_COMPONENT_SINT32 = 2,
    D3D_REGISTER_COMPONENT_FLOAT32 = 3,
    D3D10_REGISTER_COMPONENT_UNKNOWN = D3D_REGISTER_COMPONENT_UNKNOWN,
    D3D10_REGISTER_COMPONENT_UINT32 = D3D_REGISTER_COMPONENT_UINT32,
    D3D10_REGISTER_COMPONENT_SINT32 = D3D_REGISTER_COMPONENT_SINT32,
    D3D10_REGISTER_COMPONENT_FLOAT32 = D3D_REGISTER_COMPONENT_FLOAT32
} D3D_REGISTER_COMPONENT_TYPE;

typedef
enum D3D_TESSELLATOR_DOMAIN {
    D3D_TESSELLATOR_DOMAIN_UNDEFINED = 0,
    D3D_TESSELLATOR_DOMAIN_ISOLINE = 1,
    D3D_TESSELLATOR_DOMAIN_TRI = 2,
    D3D_TESSELLATOR_DOMAIN_QUAD = 3,
    D3D11_TESSELLATOR_DOMAIN_UNDEFINED = D3D_TESSELLATOR_DOMAIN_UNDEFINED,
    D3D11_TESSELLATOR_DOMAIN_ISOLINE = D3D_TESSELLATOR_DOMAIN_ISOLINE,
    D3D11_TESSELLATOR_DOMAIN_TRI = D3D_TESSELLATOR_DOMAIN_TRI,
    D3D11_TESSELLATOR_DOMAIN_QUAD = D3D_TESSELLATOR_DOMAIN_QUAD
} D3D_TESSELLATOR_DOMAIN;

typedef
enum D3D_TESSELLATOR_PARTITIONING {
    D3D_TESSELLATOR_PARTITIONING_UNDEFINED = 0,
    D3D_TESSELLATOR_PARTITIONING_INTEGER = 1,
    D3D_TESSELLATOR_PARTITIONING_POW2 = 2,
    D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD = 3,
    D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN = 4,
    D3D11_TESSELLATOR_PARTITIONING_UNDEFINED = D3D_TESSELLATOR_PARTITIONING_UNDEFINED,
    D3D11_TESSELLATOR_PARTITIONING_INTEGER = D3D_TESSELLATOR_PARTITIONING_INTEGER,
    D3D11_TESSELLATOR_PARTITIONING_POW2 = D3D_TESSELLATOR_PARTITIONING_POW2,
    D3D11_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD = D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_ODD,
    D3D11_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN = D3D_TESSELLATOR_PARTITIONING_FRACTIONAL_EVEN
} D3D_TESSELLATOR_PARTITIONING;

typedef
enum D3D_TESSELLATOR_OUTPUT_PRIMITIVE {
    D3D_TESSELLATOR_OUTPUT_UNDEFINED = 0,
    D3D_TESSELLATOR_OUTPUT_POINT = 1,
    D3D_TESSELLATOR_OUTPUT_LINE = 2,
    D3D_TESSELLATOR_OUTPUT_TRIANGLE_CW = 3,
    D3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW = 4,
    D3D11_TESSELLATOR_OUTPUT_UNDEFINED = D3D_TESSELLATOR_OUTPUT_UNDEFINED,
    D3D11_TESSELLATOR_OUTPUT_POINT = D3D_TESSELLATOR_OUTPUT_POINT,
    D3D11_TESSELLATOR_OUTPUT_LINE = D3D_TESSELLATOR_OUTPUT_LINE,
    D3D11_TESSELLATOR_OUTPUT_TRIANGLE_CW = D3D_TESSELLATOR_OUTPUT_TRIANGLE_CW,
    D3D11_TESSELLATOR_OUTPUT_TRIANGLE_CCW = D3D_TESSELLATOR_OUTPUT_TRIANGLE_CCW
} D3D_TESSELLATOR_OUTPUT_PRIMITIVE;

DEFINE_GUID(WKPDID_D3DDebugObjectName, 0x429b8c22, 0x9188, 0x4b0c, 0x87, 0x42, 0xac, 0xb0, 0xbf, 0x85, 0xc2, 0x00);


extern RPC_IF_HANDLE __MIDL_itf_d3dcommon_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_d3dcommon_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif

