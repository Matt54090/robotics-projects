# Build

```
$ make
```


# Execute the Binary

```
$ sudo ./test
```


# Check the Memory Leak

First, need to **vargrind** tool on the target

```
$ sudo apt install -y vargrind
```

Execute the test app with valgrind as below

```
$ sudo -E valgrind \
    --leak-check=full \
    --track-origins=yes \
    --show-leak-kinds=all \
    ./test
```
