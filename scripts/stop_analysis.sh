#!/bin/sh
pid=$(ps | grep "[f]rame_analysis" | awk '{print $1}')
if [ -n "$pid" ]; then
    kill $pid && echo "frame_analysis stopped"
else
    echo "frame_analysis was not running"
    exit 1
fi