#!/bin/bash
pid=$(ps | grep "[c]amera_mock" | awk '{print $1}')
if [ -n "$pid" ]; then
        kill $pid && echo "camera_mock stopped"
else
        echo "camera_mock was not running"
        exit 1
fi