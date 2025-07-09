.PHONY: all

all:: debian artix

.PHONY: debian
debian:
	cd deb && { rsync -vlr ../../ --exclude package --exclude .git . ; debuild -S -sa ; }

debian-put:
	dput ppa:tnmurphy/extramake extramake_0.1_amd64.changes # change version number!

.PHONY: artix
artix:
	cd artix && makepkg -f --check
