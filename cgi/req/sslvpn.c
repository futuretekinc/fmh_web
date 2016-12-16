#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "qdecoder.h"

#define TEMP_SSLVPN_CONF        "/tmp/_sslvpn"
#define SSLVPN_CONF             "/etc/config/sslvpn"

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

		FILE *pPF = popen("/www/cgi-bin/scripts/sslvpn.sh", "r");
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

			fprintf(pFP, "config sslvpn\n");
			fprintf(pFP, "\toption\tid\t%s\n", pID);
			fprintf(pFP, "\toption\tpasswd\t%s\n", pPassword);
			fprintf(pFP, "\toption\tremote\t%s\n", pRemote);
			fprintf(pFP, "\toption\tport\t%s\n", pPort);
			fprintf(pFP, "\toption\tauth-retry\t%s\n", pAuth);
			fprintf(pFP, "\toption\tconnect-retry\t%s\n", pRetry);
			fprintf(pFP, "\toption\tconnect-retry-max\t%s\n", pRetryMax);
			fclose(pFP);

			sprintf(pCmdBuff, "/bin/cp -f %s %s;sync;sync;/etc/init.d/sslvpn restart", TEMP_SSLVPN_CONF, SSLVPN_CONF);
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
