!/bin/sh
[ -f /tmp/camera_mock.log ] && rm /tmp/camera_mock.log && echo "Log file removed" || echo "No log file"
[ -f /tmp/camera_buffer ] && rm /tmp/camera_buffer && echo "Buffer file removed" || echo "No buffer file"