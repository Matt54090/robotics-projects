# Reference Documentation

Basic Packages for Ubuntu 24.04 as below,

```
$ sudo apt install -y build-essential \
    software-properties-common \
    neovim \
    htop \
    gcc \
    make \
    cmake \
    git \
    terminator \
    net-tools \
    openssh-server \
    python3-dev \
    python3-pip \
    python3-setuptools \
    python3-venv
```


For install the VSCode in Ubuntu 24.04,

```
$ sudo apt update
$ sudo apt install wget gpg apt-transport-https -y
$ wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
$ sudo install -o root -g root -m 644 packages.microsoft.gpg /usr/share/keyrings/
$ sudo sh -c 'echo "deb [arch=amd64 signed-by=/usr/share/keyrings/packages.microsoft.gpg] \
https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list’
$ rm -f packages.microsoft.gpg
```


For configuration in VSCode,

```
{
    // 저장 시 자동 정렬
    "editor.formatOnSave": true,
    "[c]": {
        "editor.defaultFormatter": "ms-vscode.cpptools"
    },
    "[cpp]": {
        "editor.defaultFormatter": "ms-vscode.cpptools"
    },
    "[python]": {
        "editor.defaultFormatter": "ms-python.black-formatter"
    },
    // black 포맷팅 설정
    "black-formatter.args": [
        "--line-length=79"
    ],
    // import 정렬 자동화
    "isort.args": [
        "--profile",
        "black"
    ],
    // 저장 시 isort + format 실행
    "editor.codeActionsOnSave": {
        "source.organizeImports": "explicit"
    },
    // 린터/정적분석기 설정
    "python.linting.enabled": true,
    "python.linting.mypyEnabled": true,
    "python.linting.flake8Enabled": true,
    "python.linting.pylintEnabled": false, // 둘 중 하나만 활성화 추천
    "python.analysis.typeCheckingMode": "strict"
}
```
