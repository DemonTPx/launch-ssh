VERSION=0.1
CODENAME=`lsb_release -c | cut -f2`

.PHONY: all clean build-deb

all: build-deb

clean: rm -rf build/*

build-deb:
	mkdir -p build/deb/DEBIAN build/deb/usr/bin build/deb/usr/share/applications
	cp debian/control build/deb/DEBIAN/
	cp debian/launch-ssh.desktop build/deb/usr/share/applications/
	cp cmake-build-release/launch_ssh build/deb/usr/bin/
	dpkg-deb --build build/deb build/launch-ssh_${VERSION}-${CODENAME}_amd64.deb
