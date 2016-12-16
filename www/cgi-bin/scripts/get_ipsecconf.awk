BEGIN {
}
{
	if ($1 == "right") {
		right = $2
	}
	if ($1 == "left") {
		left = $2
	}
	if ($1 == "keyexchange") {
        	keyexchange = $2
        }
	if ($1 == "ike") {
         	ike = $2
        }
	if ($1 == "ikelifetime") {    
		ikelifetime = $2
        }
	if ($1 == "margintime") {    
               	margintime = $2
        }
	if ($1 == "auto") {    
         	auto = $2           
        }
	if ($1 == "keyingtries") {    
                keyingtries = $2    
        }
	if ($1 == "aggressive") {    
         	aggressive = $2           
        }
	if ($1 == "authby") {    
         	authby = $2           
        }           
        if ($1 == "rightid") {
		rightid = $2                    
        }           
        if ($1 == "forceencaps") {
                forceencaps = $2    
        }           
        if ($1 == "type") {
		type = $2			                    
        }           
        if ($1 == "lifetime") {
		lifetime = $2                    
        }           
        if ($1 == "replay_window") {
		replay_window = $2                    
        }
	if ($1 == "esp") {    
         	esp = $2           
        }           
        if ($1 == "leftsubnet") {
		leftsubnet = $2                    
        }           
        if ($1 == "rightsubnet") {
        	rightsubnet = $2            
        }           
        if ($1 == "dpdaction") {
		dpdaction = $2                    
        }           
        if ($1 == "dpddelay") {
		dpddelay = $2                    
        }           
        if ($1 == "dpdtimeout") {
		dpdtimeout = $2                    
        }
	if ($1 == "closeaction") {         
                closeaction = $2
        }
}
END {
	print right, left, keyexchange, ike, ikelifetime, margintime, auto, keyingtries, aggressive, authby, rightid, forceencaps, type, lifetime, replay_window, esp, leftsubnet, rightsubnet, dpdaction, dpddelay, dpdtimeout, closeaction
}
