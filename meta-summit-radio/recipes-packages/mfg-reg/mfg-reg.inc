SECTION = "Wireless"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

HFP = "${@bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'eabihf', 'eabi', d)}"

REG_ARCH:x86 = "-x86"
REG_ARCH:x86-64 = "-x86_64"
REG_ARCH:powerpc64 = "-powerpc-e5500"
REG_ARCH:arm = "-arm-${HFP}"
REG_ARCH:aarch64 = "-aarch64"

REG_FULL_NAME = "${REG_NAME}${REG_ARCH}-${PV}"

SUMMIT_URI ?= "${SUMMIT_URI_BASE}"
SUMMIT_URI:summit-internal = "${SUMMIT_URI_BASE}/${REG_NAME}/laird/${PV}"

SRC_URI = "${SUMMIT_URI}/${REG_FULL_NAME}.tar.bz2;subdir=src;name=${REG_NAME}${REG_ARCH}"

S = "${WORKDIR}/src"
B = "${WORKDIR}/build"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

FILES:${PN} += "${nonarch_base_libdir}/*"

INSANE_SKIP:${PN} = "ldflags already-stripped"

ALLOW_EMPTY:${PN}-dev = "0"
ALLOW_EMPTY:${PN}-dbg = "0"

RDEPENDS:${PN} += " \
	libedit libnl libnl-genl libnl-route \
	${@bb.utils.contains('DISTRO_FEATURES', 'bluetooth', 'bluez5', '', d)} \
	"

do_unpack:append() {
    import tarfile, os
    mfgname = d.expand(d.getVar("REG_FULL_NAME", True))
    s = d.expand(d.getVar("S", True))
    b = d.expand(d.getVar("B", True))
    os.chdir(s)
    os.system("./" + mfgname + ".sh tar")
    tf = tarfile.open(s + "/" + mfgname + ".tar.bz2")
    tf.extractall(b)
}