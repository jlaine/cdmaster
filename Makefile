# definitions

VERSION = 1.0
PKG_DIST = CDMAster-$(VERSION)

PKG_FILES = AUTHORS CDMAster.dsw COPYING Makefile
PKG_DIRS = CDMAClient CDMAServer common

VCS_FILTER = ! -name .arch-ids ! -name CVS

# global targets

build: pkg-build

dist: clean pkg-dist

clean:
	for ext in h cpp; \
	do \
	  find -type f -name *.$$ext~ -exec rm -f {} \; ; \
	done

%: %.in Makefile
	sed -e 's,@VERSION@,$(VERSION),g' $< > $@


# diogenes package targets

pkg-build: 

pkg-dist: pkg-build
	rm -rf $(PKG_DIST) $(PKG_DIST).tar.gz
	mkdir $(PKG_DIST)
	cp -a $(PKG_FILES) $(PKG_DIST)
	for dir in `find $(PKG_DIRS) -type d $(VCS_FILTER)`; \
	do \
          mkdir -p $(PKG_DIST)/$$dir; \
	  find $$dir -maxdepth 1 -type f -exec cp {} $(PKG_DIST)/$$dir \; ; \
	done
	tar czf $(PKG_DIST).tar.gz $(PKG_DIST)
	rm -rf $(PKG_DIST)


.PHONY: build dist clean pkg-build pkg-dist

