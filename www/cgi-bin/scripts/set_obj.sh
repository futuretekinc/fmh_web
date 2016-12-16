#!/bin/sh

rm /mnt/ramdisk/ferret/script/fw/ip_address_object.batch
obj -F
echo "-T IP -A 1 -p $1" > /etc/ferret/script/fw/ip_address_object.batch
echo "-T IP -A 2 -p $2" >> /etc/ferret/script/fw/ip_address_object.batch
obj -B /etc/ferret/script/fw/ip_address_object.batch
omnifilter --switch
sync

ip=`echo "$1" | awk '{ split($0,arr,"."); printf("%s.%s.%s.1", arr[1], arr[2], arr[3]);}'`
echo "#!/bin/sh" > /mnt/ramdisk/img/etc/usr_script
echo "ifconfig eth0 $ip netmask 255.255.255.0" >> /mnt/ramdisk/img/etc/usr_script
echo "start-stop-daemon -Sbx /mnt/ramdisk/img/etc/killwatch.sh" >> /mnt/ramdisk/img/etc/usr_script
echo "httpd -h /mnt/ramdisk/img/etc/www" >> /mnt/ramdisk/img/etc/usr_script

sync
