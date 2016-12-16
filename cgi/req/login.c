#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "qdecoder.h"
#include "profile.h"
#include "ssid.h"
#include "md5.h"
#include "util.h"
#include <time.h>

int FTMC_Login(qentry_t *pReq)
{
	int		nRet = -1;
	FILE 	*pFP;
	char	pCMD[64];
	char	pBuf[64];
	char	pSSID[64];

	char	*pUserID = (char *)pReq->getstr(pReq, "id", false);
	char	*pPasswd = (char *)pReq->getstr(pReq, "pw", false);
	char    *pSeed	= (char *)pReq->getstr(pReq, "seed", false);

	qcgires_setcontenttype(pReq, "application/json");
	printf("{\n");

	sprintf(pCMD, "ID=%s PW=%s /www/cgi-bin/scripts/login.sh start\n", pUserID, pPasswd);
	pFP = popen(pCMD, "r");
	if (pFP == NULL)
	{
		goto error;	
	}

	if (fgets(pBuf, sizeof(pBuf) - 1, pFP) == 0)
	{
		goto error;	
	}

	if (strncasecmp(pBuf, "ok", 2) != 0)
	{
		printf("\t\"message\": \"Invalid id or passwd[%s]!\"\n", pBuf);
		goto error;
	}

	FTMC_MakeSSID(pSeed, pSSID, sizeof(pSSID));
	FTMC_SaveSSID(pSSID, time(0));

	printf("\t\"login\"\n");
	printf("\t{\n");
	printf("\t\t\"ssid\":\"%s\"\n", pSSID);
	printf("\t},\n");
	nRet = 0;

error:
	if (pFP != NULL)
	{
		fclose(pFP);	
	}

	if (nRet == 0)
	{
		printf("\t\"result\" : \"success\"\n");
	}
	else
	{
		printf("\t\"result\" : \"error\"\n");
	}
	printf("}\n");

	return	nRet;
}
