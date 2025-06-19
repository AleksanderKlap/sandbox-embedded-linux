!/bin/sh
[ -f /tmp/camera_mock.log ] && rm /tmp/camera.log && echo "Log file removed" || echo "No log file"
[ -f /tmp/camera_buffer ] && rm /tmp/camera_buffer && echo "Buffer file removed" || echo "No buffer file"
[ -f /tmp/analysis_output ] && rm /tmp/analysis_output && echo "Analysis output file removed" || echo "No analysis output file"