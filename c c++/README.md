# Linux环境搭建 

\## 下载 pico-sdk 和 pico-examples

cd ~
mkdir pico
cd pico
git clone -b master https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
cd ~/pico
git clone -b master https://github.com/raspberrypi/pico-examples.git

\## 下载 pico-project-generator

cd ~/pico
git clone https://github.com/raspberrypi/pico-project-generator.git

\## 添加环境变量

echo "export PICO_SDK_PATH=/home/$USER/pico/pico-sdk" >> .bashrc

\## 安装 VSCode 插件

code --install-extension marus25.cortex-debug
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools

\## 参考资料

https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf
https://datasheets.raspberrypi.com/pico/raspberry-pi-pico-c-sdk.pdf



# Windows 环境

- 搭建环境

https://www.bilibili.com/video/BV1Y3411Y7Zh/?vd_source=2fb67f6a093969074e9d8af4dea29e4f

https://blog.csdn.net/tianizimark/article/details/123060724

- 安装工具链接 Arm Embedded Toolchain


https://developer.arm.com/downloads/-/gnu-rm

安装到D:\Program Files (x86)\GNU Arm Embedded Toolchain，定位到bin执行命令查看安装情况

> arm-none-eabi-gcc -v

*添加环境变量PICO_TOOLCHAIN_PATH=D:\Program Files (x86)\GNU Arm Embedded Toolchain\10 2021.10\bin*

*添加到Path*



- 安装CMake


https://cmake.org/download/

安装到D:\Program Files\CMake\，安装时勾选添加到环境变量

- 安装Python（略）


- 安装Visual Studio


https://visualstudio.microsoft.com/zh-hans/downloads/

社区版，使用C++桌面开发



- vs命令行下编译

cd 到pico-examples目录，然后mk dir build，再cd build，执行

cmake -G "NMake Makefiles" ..



- vs命令行下编译闪灯uf2

  在上面的build目录下

  cd blink

  nmake
  
  此时，在blink的目录下会有blink.uf2文件，按住pico bootset，然后把uf2拖进去重启就能看到闪灯效果
  
  

- 使用VS Code

  需安装CMakeTools插件、C++ 插件、Cortex-Debug插件

  打开配置Setting，定位到Extendsions，选中CMakeTools插件

  CMakeTools配置：

  <u>Cmake: Configure Environment</u>

  AddItem添加PICO_SDK_PATH    D:\pico\pico-sdk

  <u>Cmake: Generator</u>

  输入NMake Makefiles

然后使用**VS2017开发人员命令**（一定要使用这个打开，不然会编译错误）打开vscode，配置kit 选安装的gcc套件，build all将进行类似上面的编译
