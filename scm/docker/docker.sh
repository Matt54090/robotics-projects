#!/bin/bash
# SPDX-License-Identifier: MIT
#
# Copyright (c) 2025 Junior Coder Rescue Team
# (junior.coder.rescue.team@gmail.com)
#
# See the LICENSE file in the project root for more details.

if [[ "$1" == "" ]]
then
	echo "Need to input the parameter"
	echo "You can input the parameters as below."
	echo "clean, distclean, build, run"
	echo "ex) ./docker.sh run"
	exit
fi

DOCKER_REPO="jcrt-basic"
DOCKER_TAG="ci"
DOCKER_FILE="Dockerfile.jcrt"

ROOT_DIR=$(git rev-parse --show-toplevel)
PROJECT_NAME="$(basename "${ROOT_DIR}")"

docker_clean()
{
	echo "Try to the ${FUNCNAME[0]}"

	# get the container id
	docker_ps=$(docker ps -a | \
		grep "${DOCKER_REPO}:${DOCKER_TAG}" | \
		awk '{printf $1}')

	# if exist the running container
	while [[ ${docker_ps} != "" ]]
	do
		docker kill "${docker_ps}"
		sleep 1

		docker_ps=$(docker ps -a | \
			grep "${DOCKER_REPO}:${DOCKER_TAG}" | \
			awk '{printf $1}')
	done
}

docker_distclean()
{
	echo "Try to the ${FUNCNAME[0]}"

	docker_clean

	# get the docker images information
	docker_image=$(docker images | grep ${DOCKER_REPO} | grep ${DOCKER_TAG})
	if [[ "${docker_image}" != "" ]]
	then
		docker rmi ${DOCKER_REPO}:${DOCKER_TAG}
	fi
}

docker_build()
{
	docker_image=$(docker images | grep ${DOCKER_REPO} | grep ${DOCKER_TAG})
	if [[ ${docker_image} != "" ]]
	then
		echo "Docker image(${DOCKER_REPO}:${DOCKER_TAG}) is exist already."
		exit
	fi

	if [[ ! -e "${DOCKER_FILE}" ]]
	then
		echo "Not exist the ${DOCKER_FILE}!"
		exit
	fi

	# docker build
	docker buildx build -t ${DOCKER_REPO}:${DOCKER_TAG} -f ${DOCKER_FILE} .
}

docker_run()
{
	docker_image=$(docker images | grep ${DOCKER_REPO} | grep ${DOCKER_TAG})
	if [[ ${docker_image} == "" ]]
	then
		echo "Docker image(${DOCKER_REPO}:${DOCKER_TAG}) is not exist."
		exit
	fi

	# docker run
	docker run \
		--rm \
		-it \
        -v "${ROOT_DIR}":/"${PROJECT_NAME}" \
		${DOCKER_REPO}:${DOCKER_TAG} \
		/bin/bash
}

case "$1" in
	"clean")
		docker_clean
		;;
	"distclean")
		docker_distclean
		;;
	"build")
		docker_build
		;;
	"run")
		docker_run
		;;
	*)
		echo "Invalid parameter!"
		exit
		;;
esac

echo "Done"
