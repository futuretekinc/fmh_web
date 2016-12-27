#!/bin/sh

/bin/cp /tmp/_client.ovpn /mnt/ramdisk/do/sslvpn_client/conf/client.ovpn
/bin/cp /tmp/_usr_crt /mnt/ramdisk/do/sslvpn_client/conf/usr_crt
sync;sync
/mnt/ramdisk/do/sslvpn_client/xenics stop
/mnt/ramdisk/do/sslvpn_client/xenics start
