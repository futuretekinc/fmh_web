#!/bin/sh /etc/rc.common

adminID=
adminPW=

config_webadmin()
{
	config_get adminID "${1}" userid "admin"
	config_get adminPW "${1}" passwd "admin"
}

start()
{
	[ -n "${ID}" ] && [ -n "${PW}" ] || return

	config_load webadmin

	config_foreach config_webadmin webadmin

	[ "${ID}" = "${adminID}" ]  && [ "${PW}" = "${amdinPW}" ] && echo "OK"
}
