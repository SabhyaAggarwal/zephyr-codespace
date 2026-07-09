#!/bin/bash
set -e

ARG ZEPHYR_SDK_VERSION=0.16.8

echo "=== Installing Dependencies ==="
sudo apt-get update && sudo DEBIAN_FRONTEND=noninteractive apt-get -y install --no-install-recommends \
   git cmake ninja-build gperf ccache dfu-util \
   python3-pip python3-setuptools python3-tk python3-wheel \
   xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev

echo "=== Installing West ==="
pip3 install --user west
export PATH=$PATH:$HOME/.local/bin

echo "=== Downloading Zephyr SDK ==="
cd /tmp
wget -q https://github.com{ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
tar -xf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
mkdir -p $HOME/zephyr-sdk
mv zephyr-sdk-${ZEPHYR_SDK_VERSION}/* $HOME/zephyr-sdk/

echo "=== Initializing Zephyr Workspace ==="
cd $CONTAINER_WORKSPACE_FOLDER
west init -m https://github.com --mr v3.7.0 zephyrproject
cd zephyrproject
west update
west zephyr-export
pip3 install --user -r zephyr/scripts/requirements.txt

echo "export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk" >> $HOME/.bashrc
echo "export PATH=$PATH:$HOME/.local/bin" >> $HOME/.bashrc
echo "=== Setup Complete! ==="
