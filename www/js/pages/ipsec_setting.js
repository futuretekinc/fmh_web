/**
 * Created by kindmong on 2015-11-05.
 */
function init() {
    $.li18n.currentLocale = 'kr';
    document.getElementById("menu_network").innerHTML = _t('network');
}

$(document).ready(function(){
    menu();
    init();
    initIPSEC();
});

//json으로  수정해야함.
function initIPSEC() {
	var url = "";
    if (isTest) {
        url = "/json/ipsec.json";
    } else {
        url = "/cgi-bin/ipsec?cmd=get";
    }

    $.ajax({
        type:"get",
        url:url,
        dataType:"json",
        success : function(json) {
            if (json.enable == "true")
            {
                var right = document.getElementById("right");
                var left = document.getElementById("left");
                var keyexchange = document.getElementById("keyexchange");
                var ike = document.getElementById("ike");
                var ikelifetime = document.getElementById("ikelifetime");
                var margintime = document.getElementById("margintime");
                var auto = document.getElementById("auto");
                var keyingtries = document.getElementById("keyingtries");
                var aggressive = document.getElementById("aggressive");
                var authby = document.getElementById("authby");
                var rightid = document.getElementById("rightid");
                var forceencaps  = document.getElementById("forceencaps");
                var type  = document.getElementById("type");
                var lifetime = document.getElementById("lifetime");
                var replay_window = document.getElementById("replay_window");
                var esp = document.getElementById("esp");
                var leftsubnet = document.getElementById("leftsubnet");
                var rightsubnet = document.getElementById("rightsubnet");
                var dpdaction  = document.getElementById("dpdaction");
                var dpddelay  = document.getElementById("dpddelay");
                var dpdtimeout = document.getElementById("dpdtimeout");
                var closeaction = document.getElementById("closeaction");

                right.value = json.config.right;
                left.value = json.config.left;
                keyexchange.value = json.config.keyexchange;
                ike.value = json.config.ike;
                ikelifetime.value = json.config.ikelifetime;
                margintime.value = json.config.margintime;
                auto.value = json.config.auto;
                keyingtries.value = json.config.keyingtries;
                aggressive.value = json.config.aggressive;
                authby.value = json.config.authby;
                rightid.value = json.config.rightid;
                forceencaps.value = json.config.forceencaps;
                type.value = json.config.type;
                lifetime.value = json.config.lifetime;
                replay_window.value = json.config.replay_window;
                esp.value = json.config.esp;
                leftsubnet.value = json.config.leftsubnet;
                rightsubnet.value = json.config.rightsubnet;
                dpdaction.value = json.config.dpdaction;
                dpddelay.value = json.config.dpddelay;
                dpdtimeout.value = json.config.dpdtimeout;
                closeaction.value = json.config.closeaction;
            } else {
                alert("Not IPSec version.");                             
                window.location.href = "../../pages/network/sslvpn_setting.html";
            }
        },
        error : function(xhr, status, error) {
			console.log("에러발생");
        }
    });
}

function set()
{
	var data = "" // "/cgi-bin/ipsec?cmd=set"

	var right = document.getElementById("right");
	var left = document.getElementById("left");
	var keyexchange = document.getElementById("keyexchange");
	var ike = document.getElementById("ike");
	var ikelifetime = document.getElementById("ikelifetime");
	var margintime = document.getElementById("margintime");
	var auto = document.getElementById("auto");
	var keyingtries = document.getElementById("keyingtries");
	var aggressive = document.getElementById("aggressive");
	var authby = document.getElementById("authby");
	var rightid = document.getElementById("rightid");
	var forceencaps  = document.getElementById("forceencaps");
	var type  = document.getElementById("type");
	var lifetime = document.getElementById("lifetime");
	var replay_window = document.getElementById("replay_window");
	var esp = document.getElementById("esp");
	var leftsubnet = document.getElementById("leftsubnet");
	var rightsubnet = document.getElementById("rightsubnet");
	var dpdaction  = document.getElementById("dpdaction");
	var dpddelay  = document.getElementById("dpddelay");
	var dpdtimeout = document.getElementById("dpdtimeout");
	var closeaction = document.getElementById("closeaction");

	data += "&right=" + right.value;
	data += "&left=" + encodeURIComponent(left.value);
	data += "&keyexchange=" + keyexchange.value;
	data += "&ike=" + ike.value;
	data += "&ikelifetime=" + ikelifetime.value;
	data += "&margintime=" + margintime.value;
	data += "&auto=" + auto.value;
	data += "&keyingtries=" + encodeURIComponent(keyingtries.value);
	data += "&aggressive=" + aggressive.value;
	data += "&authby=" + authby.value;
	data += "&rightid=" + encodeURIComponent(rightid.value);
	data += "&forceencaps=" + forceencaps.value;
	data += "&type=" + type.value;
	data += "&lifetime=" + lifetime.value;
	data += "&replay_window=" + replay_window.value;
	data += "&esp=" + esp.value;
	data += "&leftsubnet=" + leftsubnet.value;
	data += "&rightsubnet=" + rightsubnet.value;
	data += "&dpdaction=" + dpdaction.value;
	data += "&dpddelay=" + dpddelay.value;
	data += "&dpdtimeout=" + dpdtimeout.value;
	data += "&closeaction=" + closeaction.value;
	
	//alert(data);
	
	$.ajax({
        type:"get",
        url:"/cgi-bin/ipsec?cmd=set" + data,
        dataType:"json",
        success : function(json) {
            console.log(json);
            if (json.result == "success") {
            	alert("설정이 변경 되었습니다.\n장비의 전원을 내렸다 올려 주세요.");
            }
        },
        error : function(xhr, status, error) {
			console.log("에러발생");
        }
    });
}
