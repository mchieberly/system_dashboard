#!/bin/bash

CONTAINER_NAME="system_dashboard"

# Remove the old docker container if it exists
if [ "$(docker ps -a -q -f name=$CONTAINER_NAME)" ]; then
    echo "Stopping and removing existing container: $CONTAINER_NAME"
	# Send a Ctrl + C to initiate container cleanup
	docker exec -it $CONTAINER_NAME kill -SIGINT 1
    docker stop $CONTAINER_NAME
	docker rm $CONTAINER_NAME
else
    echo "No existing container found with name: $CONTAINER_NAME"
fi

