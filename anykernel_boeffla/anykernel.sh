# AnyKernel2 Script
#
# Original and credits: osm0sis @ xda-developers
#
# Modified by Lord Boeffla, 05.12.2016

############### AnyKernel setup start ############### 

# EDIFY properties
do.devicecheck=1
do.initd=0
do.modules=1
do.cleanup=1
device.name1=hltexx
device.name2=hltelra
device.name3=hltetmo
device.name4=hltecan
device.name5=hlteatt
device.name6=hlteub
device.name7=hlteacg
device.name8=hlte
device.name9=hltekor
device.name10=hlteskt
device.name11=hltektt
device.name12=js01lte
device.name13=sltecan
device.name14=ks01lte
device.name15=klimtdcm

# shell variables
block=/dev/block/platform/msm_sdcc.1/by-name/boot;
add_seandroidenforce=1
supersu_exclusions=""
is_slot_device=0;

############### AnyKernel setup end ############### 

## AnyKernel methods (DO NOT CHANGE)
# import patching functions/variables - see for reference
. /tmp/anykernel/tools/ak2-core.sh;

# dump current kernel
dump_boot;

############### Ramdisk customization start ###############

# AnyKernel permissions
chmod 775 $ramdisk/sbin
chmod 755 $ramdisk/sbin/busybox

chmod 775 $ramdisk/res
chmod -R 755 $ramdisk/res/bc
chmod -R 755 $ramdisk/res/misc

# ramdisk changes
# ... none

############### Ramdisk customization end ###############

# write new kernel
write_boot;
