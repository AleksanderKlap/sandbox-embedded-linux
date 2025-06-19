#!/bin/sh
/usr/bin/start_camera_mock.sh || exit 1
/usr/bin/start_frame_analysis.sh || exit 1
echo "Camera mock and Frame analysis processes started"