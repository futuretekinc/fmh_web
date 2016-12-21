#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "qdecoder.h"

#define TEMP_IPSEC_CONF        "/tmp/_ipsec.conf"
#define IPSEC_CONF             "/mnt/ramdisk/do/conf/ipsec.conf"

int FTMC_IPSEC(qentry_t *pReq)
{
	int		nRet = 0;
	char	pCmdBuff[1024];
	char *pCmd = pReq->getstr(pReq, "cmd", false);
	
	qcgires_setcontenttype(pReq, "application/json");

	if (strcasecmp(pCmd, "get") == 0)
	{
		char	szBuf[1024];

		memset(szBuf, 0, sizeof(szBuf));

		FILE *pPF = popen("/mnt/ramdisk/img/etc/www/cgi-bin/scripts/ipsecconf.sh", "r");
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
			char *pRight	        = pReq->getstr(pReq, "right", false);
			char *pLeft		        = pReq->getstr(pReq, "left", false);
			char *pKeyexchange		= pReq->getstr(pReq, "keyexchange", false);
			char *pIke              = pReq->getstr(pReq, "ike", false);
			char *pIkelifetime      = pReq->getstr(pReq, "ikelifetime", false);
			char *pMargintime		= pReq->getstr(pReq, "margintime", false);
			char *pAuto             = pReq->getstr(pReq, "auto", false);
            char *pKeyingtries      = pReq->getstr(pReq, "keyingtries", false);
            char *pAggressive       = pReq->getstr(pReq, "aggressive", false);
            char *pAuthby           = pReq->getstr(pReq, "authby", false);
            char *pRightid          = pReq->getstr(pReq, "rightid", false);
            char *pForceencaps      = pReq->getstr(pReq, "forceencaps", false);
            char *pType             = pReq->getstr(pReq, "type", false);
            char *pLifetime         = pReq->getstr(pReq, "lifetime", false);
            char *pReplay_window    = pReq->getstr(pReq, "replay_window", false);
            char *pEsp              = pReq->getstr(pReq, "esp", false);
            char *pLeftsubnet       = pReq->getstr(pReq, "leftsubnet", false);
            char *pRightsubnet      = pReq->getstr(pReq, "rightsubnet", false);
            char *pDpdaction        = pReq->getstr(pReq, "dpdaction", false);
            char *pDpddelay         = pReq->getstr(pReq, "dpddelay", false);
            char *pDpdtimeout       = pReq->getstr(pReq, "dpdtimeout", false);
            char *pCloseaction      = pReq->getstr(pReq, "closeaction", false);

			if ((pRight == NULL) || 
				(pLeft == NULL) || 
				(pKeyexchange == NULL) || 
				(pIke == NULL) || 
				(pIkelifetime == NULL) || 
				(pMargintime == NULL) ||
				(pAuto == NULL) ||
				(pKeyingtries == NULL) ||
				(pAggressive == NULL) ||
				(pAuthby == NULL) ||
				(pRightid == NULL) ||
				(pForceencaps == NULL) ||
				(pType == NULL) ||
				(pLifetime == NULL) ||
				(pReplay_window == NULL) ||
				(pEsp == NULL) ||
				(pLeftsubnet == NULL) ||
				(pRightsubnet == NULL) ||
				(pDpdaction == NULL) ||
				(pDpddelay == NULL) ||
				(pDpdtimeout == NULL) ||
				(pCloseaction == NULL))
			{
					nRet = -1;
					goto error;
			}

			FILE *pFP  = fopen(TEMP_IPSEC_CONF, "w");
			if (pFP == NULL)
			{
					nRet = -1;
					goto error;
			}

			fprintf(pFP, "conn net-net\n");
			fprintf(pFP, "  right = %s\n", pRight);
			fprintf(pFP, "  left = %s\n", pLeft);
			fprintf(pFP, "  keyexchange = %s\n", pKeyexchange);
			fprintf(pFP, "  ike = %s\n", pIke);
			fprintf(pFP, "  ikelifetime = %s\n", pIkelifetime);
			fprintf(pFP, "  margintime = %s\n", pMargintime);
			fprintf(pFP, "  auto = %s\n", pAuto);
			fprintf(pFP, "  keyingtries = %s\n", pKeyingtries);
			fprintf(pFP, "  aggressive = %s\n", pAggressive);
			fprintf(pFP, "  authby = %s\n", pAuthby);
			fprintf(pFP, "  rightid = %s\n", pRightid);
			fprintf(pFP, "  forceencaps = %s\n", pForceencaps);
			fprintf(pFP, "  type = %s\n", pType);
			fprintf(pFP, "  lifetime = %s\n", pLifetime);
			fprintf(pFP, "  replay_window = %s\n", pReplay_window);
			fprintf(pFP, "  esp = %s\n", pEsp);
			fprintf(pFP, "  leftsubnet = %s\n", pLeftsubnet);
			fprintf(pFP, "  rightsubnet = %s\n", pRightsubnet);
			fprintf(pFP, "  dpdaction = %s\n", pDpdaction);
			fprintf(pFP, "  dpddelay = %s\n", pDpddelay);
			fprintf(pFP, "  dpdtimeout = %s\n", pDpdtimeout);
			fprintf(pFP, "  closeaction = %s\n", pCloseaction);
			fclose(pFP);

//			sprintf(pCmdBuff, "/bin/cp -f %s %s;sync;sync;/etc/rc.d/init.d/225lte-config restart", TEMP_IPSEC_CONF, IPSEC_CONF);
            sprintf(pCmdBuff, "/bin/cp -f %s %s;sync;sync;/mnt/ramdisk/img/etc/www/cgi-bin/scripts/set_obj.sh %s %s;sync;sync", TEMP_IPSEC_CONF, IPSEC_CONF, pLeftsubnet, pRightsubnet);
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
