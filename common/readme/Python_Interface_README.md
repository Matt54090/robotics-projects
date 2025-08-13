# Prerequisites

Install the packages below,

```
$ sudo apt install python3-dev \
                    python3-setuptools \
                    python3-venv \
                    python3-pip \
                    pigpio \
                    python3-pigpio \
```

Check the pigpio deamon is running.

```
$ sudo systemctl status pigpiod
$ sudo systemctl start pigpiod
```

Setup the virtual environment.

```
$ python3 -m venv .env
$ source .env/bin/activate
(.env) $ pip install -U pip
(.env) $ pip install -r <root_dir>/common/build_tools/requirements.txt
```


# Execute the python code

```
(.env) $ python <interface name>.py
```
