#!/bin/bash

set -o errexit

[[ $# -eq 0 ]] || exit 1

export KBUILD_BUILD_VERSION=1
export KBUILD_BUILD_USER=yuukaos
export KBUILD_BUILD_HOST=yuukaos
export KBUILD_BUILD_TIMESTAMP="$(date -d "@$(git --no-pager show -s --format=%ct)")"

export PATH=$(pwd)/../gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabihf/bin:$PATH

export ARCH=arm
export SUBARCH=arm
export CROSS_COMPILE=arm-linux-gnueabihf-
export VARIANT_DEFCONFIG=msm8916_sec_fortunave3g_eur_defconfig
export SELINUX_DEFCONFIG=selinux_defconfig

[ ! -d out ] && mkdir out

chrt -bp 0 $$

make -j$(nproc) -C $(pwd) O=out msm8916_sec_defconfig
make -j$(nproc) -C $(pwd) O=out
