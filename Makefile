VERSION = 0.1.0
SONAME = libcringe.so
DESTDIR ?= /
PREFIX ?= usr
LIBDIR ?= lib
INCLUDEDIR ?= include
LIB_DEST ?= $(DESTDIR)/$(PREFIX)/$(LIBDIR)
INCLUDE_DEST ?= $(DESTDIR)/$(PREFIX)/$(INCLUDEDIR)

all: build

build: cringe.c cringe.h
	$(CC) -c -fpic $(CFLAGS) -o libcringe.o cringe.c
	$(CC) -Wl,-soname=$(SONAME) -shared -o $(SONAME).$(VERSION) libcringe.o
	[ -e "./$(SONAME)" ] || ln -s $(SONAME).$(VERSION) $(SONAME)

clean: libcringe.so.$(VERSION) libcringe.so libcringe.o
	rm $^

install: libcringe.so.$(VERSION) cringe.h
	install -Dm755 $(SONAME).$(VERSION) $(LIB_DEST)/$(SONAME).$(VERSION) 
	install -Dm644 cringe.h $(INCLUDE_DEST)/cringe.h
	install -Dm644 cringe-string.h $(INCLUDE_DEST)/cringe-string.h
	[ -e "$(LIB_DEST)/$(SONAME)" ] || ln -s $(LIB_DEST)/$(SONAME).$(VERSION) $(LIB_DEST)/$(SONAME)

uninstall: $(LIB_DEST)/$(SONAME) $(LIB_DEST)/$(SONAME).$(VERSION) $(INCLUDE_DEST)/cringe.h $(INCLUDE_DEST)/cringe-string.h
	rm $^
