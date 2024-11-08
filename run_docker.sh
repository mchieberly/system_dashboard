#!/bin/bash

CONTAINER_NAME="system_dashboard"
IMAGE_NAME="mchieberly/system_dashboard"
TAG="latest"

# Remove the old docker container if it exists
if [ "$(docker ps -a -q -f name=$CONTAINER_NAME)" ]; then
    echo "Stopping and removing existing container: $CONTAINER_NAME"
    docker stop $CONTAINER_NAME
    docker rm $CONTAINER_NAME
else
    echo "No existing container found with name: $CONTAINER_NAME"
fi

# Run a new container with the specified name
echo "Starting a new container: $CONTAINER_NAME"
docker run -d --name $CONTAINER_NAME ${IMAGE_NAME}:${TAG}

# Follow the container logs
docker logs -f $CONTAINER_NAME
