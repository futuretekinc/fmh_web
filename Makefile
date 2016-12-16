PREFIX=/www

export PREFIX

SUBDIR=cgi

all: build

build: 
	for dir in $(SUBDIR); do\
		make -C $$dir;\
	done

configure:

install:
	[ -d ${DESTDIR}${PREFIX} ] || mkdir -p ${DESTDIR}${PREFIX}
	cp -r www/* ${DESTDIR}${PREFIX}
	for dir in $(SUBDIR); do\
		make -C $$dir install;\
	done

clean:
	for dir in $(SUBDIR); do\
		make -C $$dir clean;\
	done
