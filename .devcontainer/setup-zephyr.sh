#!/bin/bash
set -e

ARG ZEPHYR_SDK_VERSION=0.16.8

echo "=== Installing System Dependencies ==="
sudo apt-get update && sudo DEBIAN_FRONTEND=noninteractive apt-get -y install --no-install-recommends \
   git cmake ninja-build gperf ccache dfu-util wget ca-certificates \
   python3-pip python3-setuptools python3-tk python3-wheel \
   xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev

echo "=== Deploying West Workspace Utility ==="
pip3 install --user west
export PATH=$PATH:$HOME/.local/bin

echo "=== Fetching Minimal Zephyr ARM SDK ==="
cd /tmp
wget -q https://github.com{ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
tar -xf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz
mkdir -p $HOME/zephyr-sdk
mv zephyr-sdk-${ZEPHYR_SDK_VERSION}/* $HOME/zephyr-sdk/

echo "=== Cloning Zephyr Project Manifest v3.7 ==="
cd /workspaces/zephyr-codespace
west init -m https://github.com --mr v3.7.0 zephyrproject
cd zephyrproject
west update
west zephyr-export
pip3 install --user -r zephyr/scripts/requirements.txt

# Bind environment variables persistently into shell profiles
echo "export ZEPHYR_SDK_INSTALL_DIR=$HOME/zephyr-sdk" >> $HOME/.bashrc
echo "export PATH=$PATH:$HOME/.local/bin" >> $HOME/.bashrc
echo "=== Zephyr Engine Provisioned Successfully ==="
