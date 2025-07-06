.PHONY: all

all:: debian artix

.PHONY: debian
debian:
	cd debian &&  debuild -i -us -uc -b

.PHONY: artix
artix:
	cd artix && makepkg -f --check
