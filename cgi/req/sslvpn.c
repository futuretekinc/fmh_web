#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "qdecoder.h"

#define TEMP_SSLVPN_CONF        "/tmp/_client.ovpn"
#define SSLVPN_CONF             "/mnt/ramdisk/do/sslvpn_client/conf/client.ovpn"
#define TEMP_SSLVPN_USR        "/tmp/_usr_crt"
#define SSLVPN_USR             "/mnt/ramdisk/do/sslvpn_client/conf/usr_crt"

int FTMC_SSLVPN(qentry_t *pReq)
{
	int		nRet = 0;
	char	pCmdBuff[1024];
	char *pCmd = pReq->getstr(pReq, "cmd", false);
	
	qcgires_setcontenttype(pReq, "application/json");

	if (strcasecmp(pCmd, "get") == 0)
	{
		//qcgires_setcontenttype(pReq, "application/json");

		char	szBuf[1024];

		memset(szBuf, 0, sizeof(szBuf));

		FILE *pPF = popen("/mnt/ramdisk/img/etc/www/cgi-bin/scripts/sslvpn.sh", "r");
		if (pPF == NULL)
		{
				nRet = -1;
				goto error;
		}

		while(fgets(szBuf, sizeof(szBuf) - 1, pPF) != 0)
		{
				printf("%s", szBuf);
		}
		printf(",");

		pclose(pPF);
	}
	else if(strcasecmp(pCmd, "set") == 0)
	{
			char *pRemote	= pReq->getstr(pReq, "remote", false);
			char *pPort		= pReq->getstr(pReq, "port", false);
			char *pAuth		= pReq->getstr(pReq, "auth_retry", false);
			char *pRetry    = pReq->getstr(pReq, "connect_retry", false);
			char *pRetryMax = pReq->getstr(pReq, "connect_retry_max", false);
			char *pID		= pReq->getstr(pReq, "id", false);
			char *pPassword = pReq->getstr(pReq, "password", false);

			if ((pRemote == NULL) || 
				(pPort == NULL) || 
				(pAuth == NULL) || 
				(pRetry == NULL) || 
				(pRetryMax == NULL) || 
				(pID == NULL) ||
				(pPassword == NULL))
			{
					nRet = -1;
					goto error;
			}

			FILE *pFP  = fopen(TEMP_SSLVPN_CONF, "w");
			if (pFP == NULL)
			{
					nRet = -1;
					goto error;
			}

			fprintf(pFP, "client\n");
			fprintf(pFP, "dev tun\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "auth-user-pass conf/usr_crt\n");
			fprintf(pFP, ";auth none\n");
			fprintf(pFP, "\n");
			fprintf(pFP, ";proto tcp\n");
			fprintf(pFP, "remote %s %s\n", pRemote, pPort);
			fprintf(pFP, "\n");
			fprintf(pFP, "script-security 3 system\n");
			fprintf(pFP, "\n");
			fprintf(pFP, ";tls-cipher TLS-DHE-RSA-WITH-AES-256-GCM-SHA384\n");
			fprintf(pFP, ";tls-version-min 1.2\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "no-iv\n");
			fprintf(pFP, "no-replay\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "persist-key\n");
			fprintf(pFP, "persist-tun\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "ca cert/ca.crt\n");
			fprintf(pFP, "cert cert/client.crt\n");
			fprintf(pFP, "key cert/client.key\n");
			fprintf(pFP, "comp-lzo\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "verb 3\n");
			fprintf(pFP, "reneg-sec 0\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "cipher AES-128-CBC\n");
			fprintf(pFP, ";auth-nocache\n");
			fprintf(pFP, "auth-retry %s\n", pAuth);
			fprintf(pFP, "\n");
			fprintf(pFP, "log-append log/xenics\n");
			fprintf(pFP, "\n");
			fprintf(pFP, "connect-retry %s\n", pRetry);
			fprintf(pFP, "connect-retry-max %s\n", pRetryMax);
			fclose(pFP);

			pFP = fopen(TEMP_SSLVPN_USR, "w");
			if (pFP == NULL)
			{
					nRet = -1;
					goto error;
			}

			fprintf(pFP, "%s\n", pID);
			fprintf(pFP, "%s", pPassword);
			fclose(pFP);

			sprintf(pCmdBuff, "/bin/cp -f %s %s;/bin/cp -f %s %s;sync;sync;/mnt/ramdisk/do/ssslvpn_client/xenics restart", TEMP_SSLVPN_CONF, SSLVPN_CONF, TEMP_SSLVPN_USR, SSLVPN_USR);
			pFP = popen(pCmdBuff, "r");

			printf("{");

			pclose(pFP);
	}
	else
	{
		nRet = -1;	
	}

error:
	
	printf("\"result\":\"%s\"}", (nRet == 0)?"success":"failed");

	return	nRet;
}
