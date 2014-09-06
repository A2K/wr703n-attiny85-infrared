
TOOLCHAIN=${HOME}/openwrt
export STAGING_DIR=${TOOLCHAIN}/staging_dir

CROSSGCC_BIN_PATH=${TOOLCHAIN}/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/mips-openwrt-linux-uclibc/bin
CROSSGCC_LIBEXEC_PATH=${TOOLCHAIN}/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/libexec/gcc/mips-openwrt-linux-uclibc/4.6.3

echo "${PATH}" | grep "${CROSSGCC_BIN_PATH}:" >/dev/null 2>&1 || export PATH="${CROSSGCC_BIN_PATH}:${PATH}" 
echo "${PATH}" | grep "${CROSSGCC_LIBEXEC_PATH}:" >/dev/null 2>&1 || export PATH="${CROSSGCC_LIBEXEC_PATH}:${PATH}" 

