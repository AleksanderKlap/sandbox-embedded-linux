#!/bin/sh
if ps | grep "[f]rame_analysis" > /dev/null; then
    echo "frame_analysis is already running"
    exit 1
fi
nohup /usr/bin/frame_analysis --run > /tmp/frame_analysis.log 2>&1 &
echo "frame_analysis started"