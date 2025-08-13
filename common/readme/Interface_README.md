# Prerequisites

Install the package below,

```
$ sudo apt install -y pigpio \
    python3-pigpio \
    libserialport-dev
```

Check the pigpio daemon is running. If daemon is live, need to stop the daemon service before running the application.

```
$ sudo systemctl status pigpiod
$ sudo systemctl stop pigpiod
```


# Build

You can use the Makefile to build as below.

```
$ make
```

The default BUILD_MODE value is set to **debug**.
If you want to not show any message from application, build as release mode.

```
$ make BUILD_MODE=release
```

Also, can use the CMake to build as below.

```
$ mkdir -p build && cd build
$ cmake ../
$ make
```

When using the CMake with release mode, refer to the below commands.

```
$ mkdir -p build && cd build
$ cmake -DCMAKE_BUILD_TYPE=release ../
$ make
```


# Execute the Binary

You can execute the binary as below when you use the Makefile.

```
$ sudo ./jcrt
```

If you use the CMake to build, you can find the binary in build directory.

```
$ cd build
$ sudo ./jcrt
```


# Check the Memory Leak

First, need to **vargrind** tool on the target.

```
$ sudo apt install -y vargrind
```

Execute the test app with valgrind as below.

```
$ sudo -E valgrind \
    --leak-check=full \
    --track-origins=yes \
    --show-leak-kinds=all \
    ./jcrt
```

After the test, you input the ***ctrl+c*** to stop the application and can check the memory leak information from valgrind.
