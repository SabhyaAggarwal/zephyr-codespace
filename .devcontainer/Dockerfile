# Explicitly use the canonical global domain format to prevent parsing errors
FROM docker.io/visualstudio/devcontainers/base:ubuntu-22.04

ARG ZEPHYR_SDK_VERSION=0.16.8

# Install base build dependencies
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
       git cmake ninja-build gperf ccache dfu-util \
       python3-pip python3-setuptools python3-tk python3-wheel \
       xz-utils file make gcc gcc-multilib g++-multilib libsdl2-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install West tool
RUN pip3 install west

# Download and install Zephyr SDK targeting ARM architectures
WORKDIR /opt
RUN wget -q https://github.com{ZEPHYR_SDK_VERSION}/zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && tar -xf zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && rm zephyr-sdk-${ZEPHYR_SDK_VERSION}_linux-x86_64_minimal.tar.xz \
    && cd zephyr-sdk-${ZEPHYR_SDK_VERSION} \
    && ./setup.sh -t arm-zephyr-eabi

# Configure environment variables
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-${ZEPHYR_SDK_VERSION}
