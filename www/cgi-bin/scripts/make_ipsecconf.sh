#!/bin/sh

echo "conn net-net" > /tmp/ipsec.conf
echo "	right = $1" >> /tmp/ipsec.conf
echo "	left = $2" >> /tmp/ipsec.conf
echo "	keyexchange = $3" >> /tmp/ipsec.conf
echo "	ike = $4" >> /tmp/ipsec.conf
echo "	ikelifetime = $5" >> /tmp/ipsec.conf
echo "	margintime = $6" >> /tmp/ipsec.conf
echo "	auto = $7" >> /tmp/ipsec.conf
echo "	keyingtries = $8" >> /tmp/ipsec.conf
echo "	aggressive = $9" >> /tmp/ipsec.conf
echo "	authby = $10" >> /tmp/ipsec.conf
echo "	rightid = $11" >> /tmp/ipsec.conf
echo "	forceencaps = $12" >> /tmp/ipsec.conf
echo "	type = $13" >> /tmp/ipsec.conf
echo "	lifetime = $14" >> /tmp/ipsec.conf
echo "	replay_window = $15" >> /tmp/ipsec.conf
echo "	esp = $16" >> /tmp/ipsec.conf
echo "	leftsubnet = $17" >> /tmp/ipsec.conf
echo "	rightsubnet = $18" >> /tmp/ipsec.conf
echo "	dpdaction = $19" >> /tmp/ipsec.conf
echo "	dpddelay = $20" >> /tmp/ipsec.conf
echo "	dpdtimeout = $21" >> /tmp/ipsec.conf
echo "	closeaction = $22" >> /tmp/ipsec.conf

sync

cp -r /tmp/ipsec.conf /mnt/ramdisk/do/conf/ipsec.conf
sync

