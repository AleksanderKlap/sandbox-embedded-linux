# Sandbox embedded linux

### BUGS:

- scripts in the docker image have same name as program binary - thus does not trigger it as it catches itself with ps | grep and thinks is running aready _(FIXED)_
- frame analysis does not stop when the frames in the buffer are finished? _('fixed' with feof for now)_

### 1. Embedded linux made with buildroot - based on config:

- [.config](./.config)

**Note:** The kernel and boot are not generated as intention is to run on Docker QEMU container symulating RaspberryPi 3.

- [Docker Image](https://hub.docker.com/r/olosrolo/rp3_linux)

Image includes openSSH and runs sshd on init _(And copies my public ssh key for everybody that downloads this image woopsie)_

### 2. For now: 2 simple programs:

#### camera_mock

- producing fake camera frame (10x10 matrix of integers where 1 means car and 2 means pedestrian) every second
- logging them with timestamp to log file
- saving them as to a binary buffer that is protected with named semaphore.

#### frame_analysis

- reading frames from the same binary buffer and counts how much cars and pedestrians are in the frame, logging outcome into log file.

Programs are run for now manualy via ssh using scripts embedded to docker image.

Code is compiled with buildroot toolchain gcc from build output.

### UPDATE:

- push to main activate GitHub Action - the environment runs docker container from mentioned earlier image, gets the buildroot toolchain for gcc, compiles and uplodes binaries to the container, and run sample unit & cukinia tests -> providing files with results.
