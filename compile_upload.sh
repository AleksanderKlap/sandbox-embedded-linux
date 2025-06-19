#!/bin/sh

echo "Download toolchain"
mkdir -p toolchain
gdown https://drive.google.com/uc?id=1YFKVe8KBIDbx3eXMCm9P2pn3qBHjo9Pm -O toolchain/toolchain.tar.xz

echo "Extract toolchain"
tar -xJf toolchain/toolchain.tar.xz -C toolchain

echo "Compile code"
cd apps
make all
cd ..

echo "Copy binaries to the container"
for bin in camera_mock frame_analysis; do
    docker cp apps/bin/$bin build-test:/usr/bin/$bin
done

echo "Copy cukinia config"
docker cp cukinia.conf build-test:/etc/cukinia/cukinia.conf


