# Reference Documentation


## Basic Packages for Ubuntu 24.04 as below,

```
sudo apt update

sudo apt install -y \
    gcc-arm-none-eabi \
    gdb-multiarch \
    openocd \
    make \
    cmake \
    git \
    build-essential
```


## For install the VSCode in Ubuntu 24.04,

```
$ sudo apt update
$ sudo apt install wget gpg apt-transport-https -y
$ wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
$ sudo install -o root -g root -m 644 packages.microsoft.gpg /usr/share/keyrings/
$ sudo sh -c 'echo "deb [arch=amd64 signed-by=/usr/share/keyrings/packages.microsoft.gpg] \
https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list’
$ rm -f packages.microsoft.gpg

$ sudo apt update
$ sudo apt install code -y
```


## For configuration in VSCode,

```
$ sudo apt install clangd clang-format bear -y

$ clangd --version
$ clang-format --version
$ bear --version
```


### Create the files as below under root directory of the project,


#### .vscode/settings.json

```
{
    "editor.formatOnSave": true,

    "files.associations": {
        "*.h": "c"
    },

    "C_Cpp.intelliSenseEngine": "disabled",

    "clangd.path": "clangd",
    "clangd.arguments": [
        "--background-index",
        "--header-insertion=never",
        "--clang-tidy"
    ],

    "[c]": {
        "editor.defaultFormatter": "llvm-vs-code-extensions.vscode-clangd"
    }
}
```


#### .vscode/tasks.json

```
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "flash",
            "type": "shell",
            "command": "make flash",
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": []
        }
    ]
}
```


#### .vscode/launch.json

```
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug STM32",
            "cwd": "${workspaceFolder}",
            "executable": "${workspaceFolder}/build/firmware.elf",
            "request": "launch",
            "type": "cortex-debug",
            "servertype": "openocd",
            "configFiles": [
                "/usr/share/openocd/scripts/interface/stlink.cfg",
                "/usr/share/openocd/scripts/target/stm32f4x.cfg"
            ],
            "runToEntryPoint": "main"
        }
    ]
}
```


#### .clang-format

```
BasedOnStyle: LLVM
IndentWidth: 4
TabWidth: 4
UseTab: Never
ColumnLimit: 100
BreakBeforeBraces: Allman
AllowShortIfStatementsOnASingleLine: false
SortIncludes: false
```


#### .clangd

```
CompileFlags:
  Add:
    - -Iapp
    - -Ibsp
    - -Idevices
    - -Icommon
    - -ICore/Inc
    - -IDrivers/STM32F4xx_HAL_Driver/Inc
    - -IDrivers/CMSIS/Device/ST/STM32F4xx/Include
    - -IDrivers/CMSIS/Include
    - -DSTM32F407xx
    - -DUSE_HAL_DRIVER
```


## Add the code as below in Makefile

```
OCD_PATH = "/usr/share/openocd/scripts"

flash:
	openocd \
		-f $(OCD_PATH)/interface/stlink.cfg \
		-f $(OCD_PATH)/target/stm32f4x.cfg \
		-c "program build/$(TARGET).elf verify reset exit"
```


### Compile

```
$ make -j
```


### Flash

```
$ make flash
```


### Create the Database for clangd

```
$ bear -- make -j
```


### for printf with floating point support,

```
LDFLAGS += -u _printf_float
```


## Add the icon for the operating the application


### ~/.local/share/applications/stm32f4cubemx.desktop

```
[Desktop Entry]
Name=STM32CubeMX
Comment=STM32 Configuration Tool
Exec=/usr/local/STMicroelectronics/STM32Cube/STM32CubeMX/STM32CubeMX
Icon=/usr/local/STMicroelectronics/STM32Cube/STM32CubeMX/help/STM32CubeMX.png
Terminal=false
Type=Application
Categories=Development;
```

```
$ update-desktop-database ~/.local/share/applications
```
