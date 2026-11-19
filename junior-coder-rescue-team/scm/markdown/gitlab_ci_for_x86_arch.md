# How to setup the gitlab CI


## How to setup the Host server

* I use the host server as the AWS(Amazon Web Services)

* To execute the Gitlab-Runner as the Docker needs to install the Docker in the host

  * [Install Docker Engine on Ubuntu](https://docs.docker.com/engine/install/ubuntu/)

```bash
$ sudo apt-get update
$ sudo apt-get install ca-certificates curl gnupg
$ sudo install -m 0755 -d /etc/apt/keyrings
$ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
$ sudo chmod a+r /etc/apt/keyrings/docker.gpg

$ echo \
  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
$ sudo apt-get update
$ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```


## How to build the docker image for the CI

```bash
$ cd $(git rev-parse --show-toplevel)
$ scm/docker/docker.sh build
```

* After that, you can check the new docker image for the CI

```bash
$ docker images
REPOSITORY   TAG       IMAGE ID       CREATED          SIZE
jcrt-basic   ci        25ef934f30ba   29 seconds ago   900MB
```

* If you want to connect the new docker image,

```bash
$ scm/docker/docker.sh run
root@<container id>:/#
```


## How to write the .gitlab-ci.yml file

* Please refer to the link below
	- <https://docs.gitlab.com/ee/ci/yaml/README.html>


## How to setup the gitlab runner on the host

* gitlab-runner install command,

```bash
$ curl -L https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh | sudo bash
$ sudo apt install gitlab-runner
```

* Start the *gitlab-runner* on the AWS

```bash
$ sudo gitlab-runner register --url https://gitlab.com  --token <Gitlab Repo Tocken>
Runtime platform                                    arch=amd64 os=linux pid=10725 revision=3046fee8 version=16.6.0
Running in system-mode.

Enter the GitLab instance URL (for example, https://gitlab.com/):
[https://gitlab.com]:
Verifying runner... is valid                        runner=KqsoGHd98
Enter a name for the runner. This is stored only in the local config.toml file:
[ip-172-31-5-21]: jcrt-basic
Enter an executor: kubernetes, docker, docker-windows, parallels, docker+machine, instance, custom, shell, ssh, virtualbox, docker-autoscaler:
docker
Enter the default Docker image (for example, ruby:2.7):
jcrt-basic:ci
Runner registered successfully. Feel free to start it, but if it's running already the config should be automatically reloaded!

Configuration (with the authentication token) was saved in "/etc/gitlab-runner/config.toml"
```

* Please refer to find the \<My-Token\> as below,

![gitlab_runner_1](https://user-images.githubusercontent.com/54479819/78148837-44f09c80-7470-11ea-871e-851b9e7886df.png)

* After register the *gitlab-runner*, you can see below image,

![gitlab_runner_4](https://user-images.githubusercontent.com/54479819/81576249-fde8b600-93e2-11ea-8166-3aab79d77823.png)

* In the AWS,
```bash
$ sudo gitlab-runner status
Runtime platform	arch=amd64 os=linux pid=xxx revision=xxx version=12.10.2
gitlab-runner: Service is running!
```

* Also, can check the gitlab-runner configuration file in the AWS,

```bash
$ cat /etc/gitlab-runner/config.toml
concurrent = 1
check_interval = 0

[session_server]
  session_timeout = 1800

[[runners]]
  name = "gitlab-runner for the jcrt"
  url = "https://gitlab.com/"
  token = "<token value>"
  executor = "docker"
  [runners.custom_build_dir]
  [runners.cache]
	[runners.cache.s3]
	[runners.cache.gcs]
  [runners.docker]
	tls_verify = false
	image = "jcrt-basic:ci"
	privileged = false
	disable_entrypoint_overwrite = false
	oom_kill_disable = false
	disable_cache = true
	pull_policy = "if-not-present"
	shm_size = 0
```

* Also, you can check the gitlab-runner list below command,

```bash
$ sudo gitlab-runner list
Runtime platform                                    arch=amd64 os=linux pid=1754051 revision=3046fee8 version=16.6.0
Listing configured runners                          ConfigFile=/etc/gitlab-runner/config.toml
jcrt-basic                                          Executor=docker Token=<token value> URL=https://gitlab.com
```
