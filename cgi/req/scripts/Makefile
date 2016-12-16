PREFIX=/www/cgi-bin/scripts
## Compiler options
SCRIPTS= network.sh netfilter.sh dhcp.sh lte.sh sslvpn.sh

install :
	for script in $(SCRIPTS); do \
		install -m 0755 $$script ${DESTDIR}${PREFIX};\
	done

## Clear Module
clean:

## Compile Module
