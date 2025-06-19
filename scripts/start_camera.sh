#!/bin/sh
if ps | grep "[c]amera_mock" > /dev/null; then
        echo "camera_mock is already running"
        exit 1
fi
nohup /usr/bin/camera_mock > /tmp/camera_mock.log 2>&1 &
echo "camera_mock started"