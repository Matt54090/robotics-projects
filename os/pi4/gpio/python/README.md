# Prerequisites

Install the packages below,

```
$ sudo apt install python3-dev \
                    python3-setuptools \
                    python3-venv \
                    python3-pip
```

Setup the virtual environment.

```
$ python3 -m venv .env
$ source .env/bin/activate
(.env) $ pip install -U pip
(.env) $ pip install RPi.GPIO
```


# Execute the python code

```
(.env) $ python gpio.py
```
