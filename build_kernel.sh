#!/bin/bash

export ARCH=arm
export KBUILD_BUILD_USER=$(id -u -n)
export KBUILD_BUILD_HOST=$(uname -n)@$(uname -o)
export CROSS_COMPILE=$(pwd)/../arm-eabi-4.8/bin/arm-eabi-

mkdir output

make -j$(nproc) -C $(pwd) O=output VARIANT_DEFCONFIG=msm8916_sec_fortunave3g_eur_defconfig msm8916_sec_defconfig SELINUX_DEFCONFIG=selinux_defconfig
make -j$(nproc) -C $(pwd) O=output


