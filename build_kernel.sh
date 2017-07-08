#!/bin/bash

export ARCH=arm
export PATH=$(pwd)/../PLATFORM/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.9/bin:$PATH

mkdir output

make -C $(pwd) O=output CROSS_COMPILE=arm-linux-androideabi- msm8974_sec_defconfig VARIANT_DEFCONFIG=msm8974_sec_klimtdcm_defconfig SELINUX_DEFCONFIG=selinux_defconfig
make -j64 -C $(pwd) O=output CROSS_COMPILE=arm-linux-androideabi-

cp output/arch/arm/boot/zImage $(pwd)/arch/arm/boot/zImage
