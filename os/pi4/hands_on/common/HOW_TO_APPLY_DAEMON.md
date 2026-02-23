# How to Apply Daemon

First, copy this file to the systemd system directory as below,

```
$ sudo cp <root_dir>/os/pi4/hands_on/jcrt_mini_project.service /etc/systemd/system/
```

After that, register the daemon service and enable it to start at boot time.

```
sudo systemctl daemon-reload
sudo systemctl enable --now jcrt_mini_project.service
```


# Check the Daemon Status

```
$ sudo systemctl status jcrt_mini_project.service
```


# Stop the Daemon Service

```
$ sudo systemctl stop jcrt_mini_project.service
```


# Check the Daemon Log

```
$ ps -elf | grep main
$ sudo journalctl -f | grep <PID> --color
```
