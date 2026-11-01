USE_INSTALL_ROOT=1
# Install root for the nto (QNX Neutrino) build.  Defaults to a "stage"
# directory inside the repository; override with QNX_INSTALL_ROOT if needed.
INSTALL_ROOT_nto=${QNX_INSTALL_ROOT:-${PWD}/stage}
VERSION_REL=6.4.0
