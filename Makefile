# nihwm - nihilist window manager, fork of DWM
# See LICENSE file for copyright and license details.

include config.mk

CC = gcc 
SRC = drw.c layout.c nihwm.c util.c rulemodes.c
OBJ = ${SRC:.c=.o}

all: options nihwm

options:
	@echo nihwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"
	@echo "INSTALL  = ${INSTALL}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk nihwm.h

config.h:
	cp config.def.h $@

nihwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f nihwm ${OBJ} nihwm-${VERSION}.tar.gz

dist: clean
	mkdir -p nihwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		nihwm.1 drw.h util.h ${SRC} nihwm.png transient.c nihwm-${VERSION}
	tar -cf nihwm-${VERSION}.tar nihwm-${VERSION}
	gzip nihwm-${VERSION}.tar
	rm -rf nihwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f nihwm ${DESTDIR}${PREFIX}/bin
	cp -f nihwmctl ${DESTDIR}${PREFIX}/bin
	cp -f nih ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/nihwm
	chmod 755 ${DESTDIR}${PREFIX}/bin/nihwmctl
	chmod 755 ${DESTDIR}${PREFIX}/bin/nih
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < nihwm.1 > ${DESTDIR}${MANPREFIX}/man1/nihwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/nihwm.1
	
	mkdir -p ${INSTALL}/usr/share/xsessions
	cp -f nihwm.desktop ${INSTALL}/usr/share/xsessions
	chmod 644 ${INSTALL}/usr/share/xsessions/nihwm.desktop
	
	cp -f nih.desktop ${INSTALL}/usr/share/xsessions
	chmod 644 ${INSTALL}/usr/share/xsessions/nih.desktop
	
	mkdir -p ${CONFIG}/rofi
	cp -f nihwm-theme.rasi ${CONFIG}/rofi	

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/nihwm\
		${DESTDIR}${MANPREFIX}/man1/nihwm.1

.PHONY: all options clean dist install uninstall
