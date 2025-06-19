#!/bin/sh


echo "Run unit tests"
docker exec build-test sh -c "/usr/bin/camera_mock --test > /tmp/test_camera.log 2>&1"
docker exec build-test sh -c "/usr/bin/frame_analysis --test > /tmp/test_analysis.log 2>&1"

echo "Run cukinia tests on target container"
docker exec build-test cukinia -f junitxml -o /tmp/cukinia-results.xml 

echo "Copy cukinia test results back"
mkdir -p test_logs
docker cp build-test:/tmp/test_camera.log ./test_logs/test_camera.log
docker cp build-test:/tmp/test_analysis.log ./test_logs/test_analysis.log
docker cp build-test:/tmp/cukinia-results.xml ./test_logs/cukinia-results.xml


