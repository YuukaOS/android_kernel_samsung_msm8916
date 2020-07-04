#!/bin/bash

export ARCH=arm
export SUBARCH="arm"
export CROSS_COMPILE="arm-linux-gnueabihf-"
export VARIANT_DEFCONFIG="msm8916_sec_fortunave3g_eur_defconfig"
export SELINUX_DEFCONFIG="selinux_defconfig"

[ ! -d output ] && mkdir output

make -j$(nproc) -C $(pwd) O=output msm8916_sec_defconfig
make -j$(nproc) -C $(pwd) O=output
