#!/bin/bash
# ---------------------------------------------------------------------------
# Build openQNX on a Linux host.
# ---------------------------------------------------------------------------
# Usage:
#   ./build-linux.sh [qnx|native]
#
#   qnx      - Build with the QNX Momentics cross-toolchain (Linux-hosted).
#              Requires QNX Momentics 6.4 installed; set QNX_BASE or edit
#              qnx_env.  Produces a bootable QNX Neutrino image.
#
#   native   - Attempt a host-gcc build.  NOT supported out of the box;
#              openQNX is a QNX RTOS source tree and porting it to host gcc
#              is a full OS port (the x86 kernel cannot run on Linux).
#              This mode exists to collect compile errors and drive the port.
# ---------------------------------------------------------------------------
set -u

cd "$(dirname "$0")"

mode="${1:-qnx}"

case "$mode" in
  qnx)
    echo "==> Building openQNX with the QNX Momentics toolchain (Linux host)"
    if [ ! -f qnx_env ]; then
        echo "ERROR: qnx_env not found" >&2; exit 1
    fi
    # shellcheck disable=SC1090
    . ./qnx_env || exit 1
    cd trunk
    echo "==> make CPULIST=x86 OSLIST=nto hinstall"
    make CPULIST=x86 OSLIST=nto hinstall || exit 1
    echo "==> make CPULIST=x86 OSLIST=nto install"
    make CPULIST=x86 OSLIST=nto install || exit 1
    echo "==> Done. Output is staged under INSTALL_ROOT (see qconf-override.mk)"
    ;;

  native)
    echo "==> Attempting host-gcc build (unsupported port-in-progress)"
    echo "    openQNX is a QNX Neutrino RTOS tree. The kernel, libc and most"
    echo "    services depend on QNX headers and the QNX mkfiles build system."
    echo "    A native Linux build is a full OS port and is not complete."
    cd trunk
    make -f Makefile 2>&1 | head -5 || true
    echo "    (see README.linux-port.md for the porting plan)"
    ;;

  *)
    echo "Usage: $0 {qnx|native}" >&2
    exit 2
    ;;
esac
