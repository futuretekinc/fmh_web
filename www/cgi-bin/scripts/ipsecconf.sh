#!/bin/sh

if [ -d "/mnt/ramdisk/do/sslvpn_client" ]
then
    echo "{"
    echo "\"enable\":\"false\""
else
    ipsec=`cat /mnt/ramdisk/do/conf/ipsec.conf | tr -d ' ' | sed '1d' | awk '{ split($0,arr,"="); printf("%s %s\n", arr[1], arr[2]);}' | awk -f /mnt/ramdisk/img/etc/www/cgi-bin/scripts/get_ipsecconf.awk`
    right=`echo $ipsec | awk '{print $1}'`
    left=`echo $ipsec | awk '{ print $2 }'`
    keyexchange=`echo $ipsec | awk '{ print $3 }'`
    ike=`echo $ipsec | awk '{ print $4 }'`
    ikelifetime=`echo $ipsec | awk '{ print $5 }'`
    margintime=`echo $ipsec | awk '{ print $6 }'`
    auto=`echo $ipsec | awk '{ print $7 }'`
    keyingtries=`echo $ipsec | awk '{ print $8 }'`
    aggressive=`echo $ipsec | awk '{ print $9 }'`
    authby=`echo $ipsec | awk '{ print $10 }'`
    rightid=`echo $ipsec | awk '{ print $11 }'`
    forceencaps=`echo $ipsec | awk '{ print $12 }'`
    type=`echo $ipsec | awk '{ print $13 }'`
    lifetime=`echo $ipsec | awk '{ print $14 }'`
    replay_window=`echo $ipsec | awk '{ print $15 }'`
    esp=`echo $ipsec | awk '{ print $16 }'`
    leftsubnet=`echo $ipsec | awk '{ print $17 }'`
    rightsubnet=`echo $ipsec | awk '{ print $18 }'`
    dpdaction=`echo $ipsec | awk '{ print $19 }'`
    dpddelay=`echo $ipsec | awk '{ print $20 }'`
    dpdtimeout=`echo $ipsec | awk '{ print $21 }'`
    closeaction=`echo $ipsec | awk '{ print $22 }'`


    echo "{"
    echo "\"enable\":\"true\","
    echo "\"config\":{"
    echo "	\"right\":\"$right\","
    echo "	\"left\":\"$left\","
    echo "	\"keyexchange\":\"$keyexchange\","
    echo "	\"ike\":\"$ike\","
    echo "	\"ikelifetime\":\"$ikelifetime\","
    echo "	\"margintime\":\"$margintime\","
    echo "	\"auto\":\"$auto\","
    echo "	\"keyingtries\":\"$keyingtries\","
    echo "	\"aggressive\":\"$aggressive\","
    echo "	\"authby\":\"$authby\","
    echo "	\"rightid\":\"$rightid\","
    echo "	\"forceencaps\":\"$forceencaps\","
    echo "	\"type\":\"$type\","
    echo "	\"lifetime\":\"$lifetime\","
    echo "	\"replay_window\":\"$replay_window\","
    echo "	\"esp\":\"$esp\","
    echo "	\"leftsubnet\":\"$leftsubnet\","
    echo "	\"rightsubnet\":\"$rightsubnet\","
    echo "	\"dpdaction\":\"$dpdaction\","
    echo "	\"dpddelay\":\"$dpddelay\","
    echo "	\"dpdtimeout\":\"$dpdtimeout\","
    echo "	\"closeaction\":\"$closeaction\""
    echo "	}"
fi
