var isTest = false;

function menu() {
	$.li18n.currentLocale = 'kr';
    document.getElementById("menu_network").innerHTML = _t('network');
}

function logout() {
    alert("logout");
    window.location.href="/";
}
