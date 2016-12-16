## Compiler options
OBJS	= main.o page.o profile.o md5.o debug.o xml.o util.o\
		  public.o login.o system.o ssid.o\
		  sslvpn.o ipsec.o 
TARGET	= req.cgi
CMDS	= login logout page public sslvpn ipsec system
SUBDIR  = scripts

$(TARGET) : $(OBJS)
	${CC} ${CFLAGS} ${CPPFLAGS} -o $@ $(OBJS) ${LIBS}

install : $(TARGET)
	install -m 0755 $(TARGET) ${DESTDIR}${PREFIX}
	for cmd in $(CMDS); do \
		ln -s ${TARGET} ${DESTDIR}${PREFIX}/$$cmd;\
	done
	for dir in $(SUBDIR); do\
		make -C $$dir install;\
	done

## Clear Module
clean:
	rm -f *.o ${TARGETS}
	rm -rf upload tmp

## Compile Module
.c.o:
	${CC} ${CFLAGS} ${CPPFLAGS} -c -o $@ $<
