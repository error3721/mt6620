/*******************************************************************************
* Copyright (c) 2013, MediaTek Inc.
*
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU General Public License version 2 as published by the Free
* Software Foundation.
*
* Alternatively, this software may be distributed under the terms of BSD
* license.
********************************************************************************
*/

/*******************************************************************************
* THIS SOFTWARE IS PROVIDED BY MEDIATEK "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT OR FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL MEDIATEK BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************
*/

#ifndef _CMD_BUF_H
#define _CMD_BUF_H

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/

/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/

typedef enum _COMMAND_TYPE {
	COMMAND_TYPE_GENERAL_IOCTL,
	COMMAND_TYPE_NETWORK_IOCTL,
	COMMAND_TYPE_SECURITY_FRAME,
	COMMAND_TYPE_MANAGEMENT_FRAME,
	COMMAND_TYPE_NUM
} COMMAND_TYPE, *P_COMMAND_TYPE;

typedef VOID(*PFN_CMD_DONE_HANDLER) (IN P_ADAPTER_T prAdapter,
				     IN P_CMD_INFO_T prCmdInfo,
				     IN PUINT_8 pucEventBuf);

typedef VOID(*PFN_CMD_TIMEOUT_HANDLER) (IN P_ADAPTER_T prAdapter,
					IN P_CMD_INFO_T prCmdInfo);

struct _CMD_INFO_T {
	QUE_ENTRY_T rQueEntry;

	COMMAND_TYPE eCmdType;

	UINT_16 u2InfoBufLen;	/* This is actual CMD buffer length */
	PUINT_8 pucInfoBuffer;	/* May pointer to structure in prAdapter */
	P_NATIVE_PACKET prPacket;	/* only valid when it's a security frame */

	ENUM_NETWORK_TYPE_INDEX_T eNetworkType;
	UINT_8 ucStaRecIndex;	/* only valid when it's a security frame */

	PFN_CMD_DONE_HANDLER pfCmdDoneHandler;
	PFN_CMD_TIMEOUT_HANDLER pfCmdTimeoutHandler;

	BOOLEAN fgIsOid;	/* Used to check if we need indicate */

	UINT_8 ucCID;
	BOOLEAN fgSetQuery;
	BOOLEAN fgNeedResp;
	BOOLEAN fgDriverDomainMCR;	/* Access Driver Domain MCR, for CMD_ID_ACCESS_REG only */
	UINT_8 ucCmdSeqNum;
	UINT_32 u4SetInfoLen;	/* Indicate how many byte we read for Set OID */

/* information indicating by OID/ioctl */
	PVOID pvInformationBuffer;
	UINT_32 u4InformationBufferLength;

/* private data */
	UINT_32 u4PrivateData;
};

/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/

/*******************************************************************************
*                   F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/
VOID cmdBufInitialize(IN P_ADAPTER_T prAdapter);

P_CMD_INFO_T
cmdBufAllocateCmdInfo(IN P_ADAPTER_T prAdapter, IN UINT_32 u4Length);

VOID cmdBufFreeCmdInfo(IN P_ADAPTER_T prAdapter, IN P_CMD_INFO_T prCmdInfo);

/*----------------------------------------------------------------------------*/
/* Routines for CMDs                                                          */
/*----------------------------------------------------------------------------*/
WLAN_STATUS
wlanSendSetQueryCmd(IN P_ADAPTER_T prAdapter,
		    UINT_8 ucCID,
		    BOOLEAN fgSetQuery,
		    BOOLEAN fgNeedResp,
		    BOOLEAN fgIsOid,
		    PFN_CMD_DONE_HANDLER pfCmdDoneHandler,
		    PFN_CMD_TIMEOUT_HANDLER pfCmdTimeoutHandler,
		    UINT_32 u4SetQueryInfoLen,
		    PUINT_8 pucInfoBuffer,
		    OUT PVOID pvSetQueryBuffer, IN UINT_32 u4SetQueryBufferLen);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/
#endif /* _CMD_BUF_H */
