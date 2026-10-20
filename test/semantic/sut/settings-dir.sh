#!/bin/bash
# Prints the Ghidra user settings directory for the current XDG_CONFIG_HOME, and refuses
# (exit 1) when that is the user's own (~/.config/ghidra) unless XS16_USER_SETTINGS=1,
# since the callers install extensions into it.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
fw=$GHIDRA_INSTALL_DIR/Ghidra/Framework
settings=$(java -cp "$fw/Utility/lib/Utility.jar:$fw/Generic/lib/Generic.jar" "$here/SettingsDir.java")
case $settings in
"$HOME"/.config/ghidra/*)
	if [ "${XS16_USER_SETTINGS:-}" != 1 ]; then
		echo "refusing to install test extensions into $settings (your own Ghidra settings);" \
			"unset XDG_CONFIG_HOME or set XS16_USER_SETTINGS=1" >&2
		exit 1
	fi ;;
esac
echo "$settings"
