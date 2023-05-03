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
# linux运行段错误, 转向win
+ 运行时需要将3rparty里的run_libs里的所有文件复制到运行目录
+ 如果缺少dll文件,解压3rparty里的zip文件, 将dll文件放置于c盘的windows/system32
