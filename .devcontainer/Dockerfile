FROM ubuntu:22.04

# Avoid prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update and install tools
RUN apt-get update && apt-get install -y \
    iputils-ping curl wget software-properties-common \
    git \
    cmake \
    clang-format \
    doxygen \
    gcovr \
    ccache \
    python3-pip \
    && pip3 install cmake-format \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Set ccache as default compiler if you need
# ENV CC=/usr/lib/ccache/gcc
# ENV CXX=/usr/lib/ccache/g++
