#!/bin/sh

sslvpn_client=`cat /mnt/ramdisk/do/sslvpn_client/conf/client.ovpn | awk -f /mnt/ramdisk/img/etc/www/cgi-bin/scripts/get_sslvpn.awk`
sslvpn_usr=`cat /mnt/ramdisk/do/sslvpn_client/conf/usr_crt | awk -f /mnt/ramdisk/img/etc/www/cgi-bin/scripts/get_sslvpn_usr.awk`

remote=`echo $sslvpn_client | awk '{print $1}'`
port=`echo $sslvpn_client | awk '{ print $2 }'`
auth_retry=`echo $sslvpn_client | awk '{ print $3 }'`
connect_retry=`echo $sslvpn_client | awk '{ print $4 }'`
connect_retry_max=`echo $sslvpn_client | awk '{ print $5 }'`
id=`echo $sslvpn_usr | awk '{ print $1 }'`
password=`echo $sslvpn_usr | awk '{ print $2 }'`


echo "{"
echo "\"config\":{"
echo "	\"remote\":\"$remote\","
echo "	\"port\":\"$port\","
echo "	\"auth_retry\":\"$auth_retry\","
echo "	\"connect_retry\":\"$connect_retry\","
echo "	\"connect_retry_max\":\"$connect_retry_max\","
echo "	\"id\":\"$id\","
echo "	\"password\":\"$password\""
echo "	}"
