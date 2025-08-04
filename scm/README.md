# Software Configuration Management

  * Based on the Ubuntu 22.04 (6.2.0-36-generic)


## Directory Structure


### docker

  * On the AWS, set up the CI/CD environment using gitlab-runner with docker


### scripts

  * For the CI/CD, implement the scripts in this directory

  * Implemented general bash for the CI/CD in the ***common*** directory

  * In the ***ci*** directory, check the coding rule, build state and static analytics using ***shellcheck, clang-format, isort/flake8/pylint***

  * Refer the each tools version below

    * **shellcheck**
    ```bash
	$ shellcheck --version
	ShellCheck - shell script analysis tool
	version: 0.8.0
	license: GNU General Public License, version 3
	website: https://www.shellcheck.net
    ```

    * **clang-format**

	```bash
	$ clang-format --version
	Ubuntu clang-format version 14.0.0-1ubuntu1.1
	```

	* **isort**

	```bash
	$ isort --version
                 _                 _
                (_) ___  ___  _ __| |_
                | |/ _/ / _ \/ '__  _/
                | |\__ \/\_\/| |  | |_
                |_|\___/\___/\_/   \_/

      isort your imports, so you don't have to.

                    VERSION 5.12.0
	```

	* **flake8**

	```bash
	$ flake8 --version
	6.1.0 (mccabe: 0.7.0, pycodestyle: 2.11.1, pyflakes: 3.1.0) CPython 3.10.12 on Linux
	```

	* **pylint**

	```bash
	$ pylint --version
	pylint 3.0.2
	astroid 3.0.1
	Python 3.10.12 (main, Jun 11 2023, 05:26:28) [GCC 11.4.0]
	```
