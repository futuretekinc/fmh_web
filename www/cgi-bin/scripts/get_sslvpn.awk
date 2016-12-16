BEGIN {
}
{
	if ($1 == "remote") {
		remote = $2
		port = $3
	}
	if ($1 == "auth-retry") {
        	auth_retry = $2
        }
	if ($1 == "connect-retry") {
         	connect_retry = $2
        }
	if ($1 == "connect-retry-max") {    
		connect_retry_max = $2
        }
	if ($1 == "id") {    
               	id = $2
        }
	if ($1 == "password") {    
         	password = $2           
        }
}
END {
	print remote, port, auth_retry, connect_retry, connect_retry_max, id, password
}
