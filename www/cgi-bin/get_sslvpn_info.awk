BEGIN {
}
{
	if ($2 == "id")
	{
       		id = $3;
	}

	if ($2 == "passwd")
	{
       		passwd = $3;
	}

	if ($2 == "remote")
	{
       		remote = $3;
	}

	if ($2 == "port")
	{
		remote_port = $3;
	}
	
	if ($2 == "auth-retry")
	{
		auth_retry = $3;
	}

	if ($2 == "connect-retry")
	{
        	connect_retry = $3;
	}
	
	if ($2 == "connect-retry-max")
	{
		connect_retry_max = $3;
	}
}
END {
	print id, passwd, remote, remote_port, auth_retry, connect_retry, connect_retry_max
}
