BEGIN {
}
{
    	if (NR == 1)
    	{
        	id = $1;
    	}
	
	if (NR == 2)
	{
		pw = $1;
	}
}
END {
	print id, pw
}
