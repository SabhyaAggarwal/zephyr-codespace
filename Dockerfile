FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive

# 1. Install system utilities and core build pipelines
RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake ninja-build gperf ccache dfu-util wget curl ca-certificates \
    xz-utils file make gcc gcc-multilib g++-multilib \
    python3 python3-pip python3-venv python3-setuptools python3-wheel python3-tk \
    device-tree-compiler \
    && rm -rf /var/lib/apt/lists/*

# 2. Deploy West command line manager
RUN pip3 install --no-cache-dir west

# 3. Fetch and extract the official minimal Zephyr ARM SDK
WORKDIR /opt
RUN wget -q https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.16.8/zephyr-sdk-0.16.8_linux-x86_64_minimal.tar.xz
RUN tar -xf zephyr-sdk-0.16.8_linux-x86_64_minimal.tar.xz
RUN rm zephyr-sdk-0.16.8_linux-x86_64_minimal.tar.xz
RUN /opt/zephyr-sdk-0.16.8/setup.sh -t arm-zephyr-eabi -c

# 4. Set persistent path environment variables
ENV ZEPHYR_SDK_INSTALL_DIR=/opt/zephyr-sdk-0.16.8
ENV PATH=/root/.local/bin:${PATH}

# 5. Initialize the complete Zephyr workspace using the correct repository path
WORKDIR /workspace
RUN west init -m https://github.com/zephyrproject-rtos/zephyr --mr v3.7.0 zephyrproject
RUN cd zephyrproject && west update
RUN cd zephyrproject && west zephyr-export
RUN cd zephyrproject && pip3 install --no-cache-dir -r zephyr/scripts/requirements.txt

# Set default working directory inside the build workspace
WORKDIR /workspace/zephyrproject/zephyr
