BEGIN {
	count=1
}
{
	if (count == 1)
	{
		id = $1
	} else {
		password = $1
	}
	count=2
}
END {
	print id, password
}
