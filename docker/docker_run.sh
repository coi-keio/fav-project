#!/bin/sh

IMAGE_NAME=$1
shift

if [ "${IMAGE_NAME}" = "" ]; then
  exit 1
fi

docker run --rm -it \
    -v $(pwd)/..:/usr/local/fav \
    -w /usr/local/fav \
    ${IMAGE_NAME} bash
