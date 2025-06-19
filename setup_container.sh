#!/bin/sh

echo "Pull docker image"
docker pull olosrolo/rp3_linux

echo "Set docker buildx"
docker run --rm --privileged tonistiigi/binfmt --install all
docker buildx create --use
docker buildx inspect --bootstrap

echo "Run ARM raspbery pi3 docker container and sleep for 10"
docker run -d --platform linux/arm/v7 --name build-test olosrolo/rp3_linux
sleep 10

echo "Checking if container is running"
docker ps -a
docker logs build-test || echo "No logs"