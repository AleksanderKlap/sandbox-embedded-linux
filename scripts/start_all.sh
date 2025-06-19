#!/bin/sh
/usr/bin/start_camera.sh || exit 1
/usr/bin/start_analysis.sh || exit 1
echo "Camera mock and Frame analysis processes started"