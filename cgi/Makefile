PREFIX=/www/cgi-bin

CFLAGS	= -std=gnu99 -Wall -fPIC -g -I. -DDEBUG
CPPFLAGS= -I${CURDIR}/qdecoder-12.0.4/src/  -I./ -D_GNU_SOURCE
LIBS	= ${CURDIR}/qdecoder-12.0.4/src/libqdecoder.a 

export PREFIX CFLAGS CPPFLAGS LIBS 

LIBDIR=qdecoder-12.0.4
SUBDIR=req

all: build

build: 
	for lib in $(LIBDIR); do\
		make -C $$lib;\
	done
	for dir in $(SUBDIR); do\
		make -C $$dir;\
	done

configure:

install:
	for dir in $(SUBDIR); do\
		make -C $$dir install;\
	done

clean:
	for lib in $(LIBDIR); do\
		make -C $$lib clean;\
	done
	for dir in $(SUBDIR); do\
		make -C $$dir clean;\
	done
