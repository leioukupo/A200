# ImiNect 接⼝定义

## 初始化

### ImiSDK 初始化函数

+ ```cpp
  int32_t imiInitialize()

ImiSDK初始化函数

|  值   |              说明               |
|:----:|:-----------------------------:|
|  0   |             操作成功              |
| 小于 0 | 操作失败，imiGetLastError()获取详细错误码 |

    - 0x8030010d 不支持的驱动类型
    - 0x80300301 USB初始化失败

+ ```cpp 
  int32_t imiInitialize2(ImiDriverInfo* mDriverInfo)

ImiSDK初始化函数 2；支持 USB、FILE、NET三种驱动类型设定

|     Type      |    Name     |       Description        | IN/OUT |
|:-------------:|:-----------:|:------------------------:|:------:|
| ImiDriverInfo | mDriverInfo | 数据驱动类型信息，见 ImiDriverInfo |   IN   |

|  值   |              说明               |
|:----:|:-----------------------------:|
|  0   |             操作成功              |
| 小于 0 | 操作失败，imiGetLastError()获取详细错误码 |

    - 0x8030010d 不支持的驱动类型
    - 0x80300301 USB初始化失败

## 设备操作

### 获取系统中 Iminect 设备列表和个数

+ ```c++ 
  int32_t imiGetDeviceList(ImiDeviceAttribute** pDeviceList, int32_t* pDeviceCount)

|         Type         |     Name     | Description | IN/OUT |
|:--------------------:|:------------:|:-----------:|:------:|
| ImiDeviceAttribute** | pDeviceList  |  指向设备列表的指针  |   IN   |
|       int32_t*       | pDeviceCount |  指向设备数量的指针  |   IN   |

|  值   |              说明               |
|:----:|:-----------------------------:|
|  0   |             操作成功              |
| 小于 0 | 操作失败，imiGetLastError()获取详细错误码 |

    - 0x80300101 设备未初始化

### 打开设备

+ ```c++ 
  int32_t imiOpenDevice (const char* pDeviceUri, ImiDeviceHandle* pDevice, int32_t reserve)

|       Type       |    Name    |            Description            | IN/OUT |
|:----------------:|:----------:|:---------------------------------:|:------:|
|   const char*    | pDeviceUri | 设备 URI，当此值为 NULL时，默认打开设备列表中的第一个设备 |   IN   | 
| ImiDeviceHandle* |  pDevice   |      指向 ImiDeviceHandle 的指针       |  OUT   |
|     int32_t      |  reserve   |              保留，填 0               |   IN   |

|  值   |              说明               |
|:----:|:-----------------------------:|
|  0   |             操作成功              |
| 小于 0 | 操作失败，imiGetLastError()获取详细错误码 |

    - 0x80300101 设备未初始化
    - 0x80300102 设备未打开
    - 0x80300103 打开的设备数量超过上限
    - 0x80300202 第二个参数为空指针
    - 0x80300206 参数取值非法
    - 0x80300302 USB打开设备失败

### 关闭设备

+ ```c++ 
  int32_t imiCloseDevice(ImiDeviceHandle device)

|      Type       |  Name  |           Description            | IN/OUT |
|:---------------:|:------:|:--------------------------------:|:------:|
| ImiDeviceHandle | device | Devicehandle 由 imiOpenDevice()获得 |   IN   |

|  值   |              说明               |
|:----:|:-----------------------------:|
|  0   |             操作成功              |
| 小于 0 | 操作失败，imiGetLastError()获取详细错误码 |

> 关闭设备前先关闭和释放打开的数据流，见 imiStopStream(),imiDestroyChanelInstance()
- 0x80300101 设备未初始化
- 0x80300102 设备未打开













