#!/bin/sh
status=0
/usr/bin/stop_camera.sh || status=1
/usr/bin/stop_analysis.sh || status=1
if [ $status -eq 0 ]; then
    echo "Camera mock and Frame analyisis processes stopped"
fi
exit $status