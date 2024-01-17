SUMMARY = "Summit Backports for NX61x"

BACKPORTS_CONFIG = "${@bb.utils.contains('DISTRO_FEATURES','bluetooth','sona_nx611','sona_nx611_nbt',d)}"

RCONFLICTS:${PN} = " \
        kernel-module-60-backports \
        kernel-module-lwb-if-backports \
        kernel-module-msd45-backports \
        kernel-module-msd50-backports \
        kernel-module-qcacld-backports \
        "

require summit-backports.inc radio-stack-nx-version.inc