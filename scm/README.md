# Software Configuration Management

  * Based on the Ubuntu 20.04 (5.15.0-69-generic)


## Directory Structure


### docker

  * On the AWS, set up the CI/CD environment using gitlab-runner with docker


### markdown

  * For your information, share the setting guidance


### scripts

  * For the CI/CD, implement the scripts in this directory

  * Implemented general bash for the CI/CD in the ***common*** directory

  * In the ***ci*** directory, check the coding rule, build state and static analytics using ***shellcheck, clang-format, cpplint, isort/flake8/pylint, cppcheck***

  * Refer the each tools version below

    * **shellcheck**
    ```bash
	$ shellcheck --version
	ShellCheck - shell script analysis tool
	version: 0.7.0
	license: GNU General Public License, version 3
	website: https://www.shellcheck.net
    ```

    * **clang-format**

	```bash
	$ clang-format --version
	clang-format version 6.0.1 (tags/RELEASE_601/final)
	```

	* **cpplint**

	```bash
	$ cpplint --version
	Cpplint fork (https://github.com/cpplint/cpplint)
	cpplint 1.6.1
	Python 3.8.10 (default, Mar 13 2023, 10:26:41)
	[GCC 9.4.0]
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
	6.0.0 (mccabe: 0.7.0, pycodestyle: 2.10.0, pyflakes: 3.0.1) CPython 3.8.10 on Linux
	```

	* **pylint3**

	```bash
	$ pylint3 --version
	pylint 2.17.2
	astroid 2.15.2
	Python 3.8.10 (default, Mar 13 2023, 10:26:41)
	[GCC 9.4.0]
	```

	* **cppcheck**

	```bash
	$ cppcheck --version
	Cppcheck 2.7.4
	```
