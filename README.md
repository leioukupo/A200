# A200
A200+mini摄像头开发       
使用A200+mini开发一个三维扫描仪
# 文件说明
+ include 
> 头文件
+ libs
> 库文件
> 把库添加到系统库路径, 免得每次运行需要指定库搜索路径
+ 55-iminect-usb.rules

> 设备挂载规则
> ```bash
> chmod 777 55-iminect-usb.rules
> sudo -S cp 55-iminect-usb.rules /etc/udev/rules.d
> sudo -S udevadm control --reload-rules
> ```


+ 运行时需要复制3rparty中的run_libs所有文件到运行目录
+ 如果缺少dll, 解压3rparty中的zip, 并复制dll到c盘的windows/system32中

# 进度

pcl库有小问题，延迟到六月底解决，届时使用linux
尝试用opencv处理点云     

