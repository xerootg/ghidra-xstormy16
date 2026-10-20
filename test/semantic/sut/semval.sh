#!/bin/bash
# Runs the SUT runner inside Ghidra's launcher, so the class loader and the installed
# extensions (the Xstormy16 language under test) are set up as for any Ghidra tool.
# The runner jar is itself installed as a small user extension ("xs16-semval") next to
# the module under test, which is how GhidraLauncher finds launchable classes.
# With XDG_CONFIG_HOME/XDG_CACHE_HOME unset they default to sut/build/xdg{,cache}, so
# your own Ghidra settings are left alone.
#   semval.sh run|bench <options>   (see XsSemRunner.java)
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
: "${GHIDRA_INSTALL_DIR:?GHIDRA_INSTALL_DIR is not set}"
jar=${SEMVAL_JAR:-$here/build/semval.jar}
fw=$GHIDRA_INSTALL_DIR/Ghidra/Framework
version=$(sed -n 's/^application.version=//p' "$GHIDRA_INSTALL_DIR/Ghidra/application.properties")
export XDG_CONFIG_HOME=${XDG_CONFIG_HOME:-$here/build/xdg} XDG_CACHE_HOME=${XDG_CACHE_HOME:-$here/build/xdgcache}
settings=$("$here/settings-dir.sh")
ext=$settings/Extensions/xs16-semval
mkdir -p "$ext/lib"
cp "$jar" "$ext/lib/semval.jar"
: > "$ext/Module.manifest"
printf 'name=xs16-semval\ndescription=xstormy16 semantic test runner\nauthor=test\ncreatedOn=\nversion=%s\n' \
	"$version" > "$ext/extension.properties"
exec java -Xmx${SEMVAL_XMX:-3g} -Djava.system.class.loader=ghidra.GhidraClassLoader \
	-Djava.awt.headless=true -Dfile.encoding=UTF8 -Xshare:off \
	-cp "$fw/Utility/lib/Utility.jar" \
	ghidra.Ghidra xs16.semval.XsSemRunner "$@"
