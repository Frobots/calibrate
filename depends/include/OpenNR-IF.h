/*	@file		OpenNR-IF.h
 *	@brief		OpenNR Interface
 *	@version	V1.4
 */
typedef void* NACHI_HANDLE;

#pragma once

#include <stddef.h>
#include <string>

#define NR_EXTENDED_DLL_API

//================================================
// Define
//================================================

//------------------------------------------------
// CONNECT SPEC
//------------------------------------------------
#define		NR_OBJECT_INTERNAL		(0)				// Internal
#define		NR_OBJECT_EXTERNAL_TCP	(1)				// External(TCP)
#define		NR_OBJECT_EXTERNAL_UDP	(2)				// External(UDP)

#define		NR_MODE_COMM_SERVER		(0)				// Server For Communication
#define		NR_MODE_COMM_CLIENT		(1)				// Client For Communication

#define		NR_DATA_REAL			(0)				// Server For Communication
#define		NR_DATA_XML				(1)				// Client For Communication

//------------------------------------------------
// DATA ACCESS MODE
//------------------------------------------------

#define		NR_ACCESS_WAIT			0				// Wait
#define		NR_ACCESS_NO_WAIT		1				// No Wait?j

//------------------------------------------------
// Run/Stop
//------------------------------------------------

// For CtrlMotor
#define		NR_STANBY_OFF_REQ		0				// Stanby OFF
#define		NR_STANBY_ON_REQ		1				// Stanby ON

// For CtrlRun
#define		NR_STOP_REQ				0				// Stop
#define		NR_RUN_REQ				1				// Run

// For CtrlEventLog / CtrlMakeDirectory
#define		NR_INTERNAL_REQ			0				// Internal Memory
#define		NR_RC_EXTERNAL_REQ		1				// RC External Memory

// For CtrlEventLog
#define		NR_EVENT_LOG_SYSTEM			0			// System
#define		NR_EVENT_LOG_APPLICATION	1			// Application
#define		NR_EVENT_LOG_SECURITY		2			// Security

// For NR_AcsFTP
// FTP service start/stop
#define		NR_FTP_SERVICE_START		1
#define		NR_FTP_SERVICE_STOP			0

// FTP service ANONYMOUS
#define		NR_FTP_ANONYMOUS_FORBID			0
#define		NR_FTP_ANONYMOUS_ALLOW			1
#define		NR_FTP_ANONYMOUS_ONLY_ALLOW		2

// FTP service Connect Num
#define		NR_FTP_CONNECT_NUM_MIN			0
#define		NR_FTP_CONNECT_NUM_MAX			10

// FTP service Timeout
#define		NR_FTP_TIMEOUT_MIN				0
#define		NR_FTP_TIMEOUT_MAX				900

// FTP service Directory State
#define		NR_FTP_DIRECTORY_ONLY_READ		0
#define		NR_FTP_DIRECTORY_ONLY_WRITE		1
#define		NR_FTP_DIRECTORY_READ_WRITE		2

//------------------------------------------------
// Real Data ID
//------------------------------------------------

// For Get()------EXT
typedef	enum NR_GetRealDataExtId
{
        eNR_GET_STATUS_EXT_ID = 0,
        eNR_GET_TIME_EXT_ID,
        eNR_GET_CUR_TCP_POS_EXT_ID,
        eNR_GET_COM_TCP_POS_EXT_ID,
        eNR_GET_WORK_COORD_EXT_ID,
        eNR_GET_TOOL_COORD_EXT_ID,
        eNR_GET_CUR_ANGLE_EXT_ID,
        eNR_GET_COM_ANGLE_EXT_ID,
        eNR_GET_TORQUE_EXT_ID,
        eNR_GET_MORTOR_AMP_EXT_ID,
        eNR_GET_DIG_OUT_EXT_ID,
        eNR_GET_DIG_IN_EXT_ID,
        eNR_GET_ANA_OUT_EXT_ID,
        eNR_GET_ANA_IN_EXT_ID,
        eNR_GET_REAL_MAX_EXT_ID
} NR_GET_REAL_DATA_EXT_EXT_ID;

// For Set()------EXT
typedef	enum NR_SetRealDataExtId
{
        eNR_SET_STATUS_EXT_ID = 0,
        eNR_SET_TIME_EXT_ID,
        eNR_SET_COM_TCP_POS_EXT_ID,
        eNR_SET_WORK_COORD_EXT_ID,
        eNR_SET_TOOL_COORD_EXT_ID,
        eNR_SET_COM_ANGLE_EXT_ID,
        eNR_SET_DIG_OUT_EXT_ID,
        eNR_SET_ANA_OUT_EXT_ID,
        eNR_SET_REAL_MAX_EXT_ID
} NR_SET_REAL_DATA_EXT_EXT_ID;

// For Get()------STD
typedef	enum NR_GetRealDataStdId
{
        eNR_GET_STATUS_STD_ID = 0,
        eNR_GET_TIME_STD_ID,
        eNR_GET_CUR_TCP_POS_STD_ID,
        eNR_GET_CUR_ANGLE_STD_ID,
        eNR_GET_MORTOR_AMP_STD_ID,
        eNR_GET_DIG_OUT_STD_ID,
        eNR_GET_DIG_IN_STD_ID,
        eNR_GET_REAL_MAX_STD_ID
} NR_GET_REAL_DATA_STD_STD_ID;

// For Set()------STD
typedef	enum NR_SetRealDataStdId
{
        eNR_SET_STATUS_STD_ID = 0,
        eNR_SET_TIME_STD_ID,
        eNR_SET_COM_TCP_POS_STD_ID,
        eNR_SET_WORK_COORD_STD_ID,
        eNR_SET_TOOL_COORD_STD_ID,
        eNR_SET_COM_ANGLE_STD_ID,
        eNR_SET_DIG_OUT_STD_ID,
        eNR_SET_REAL_MAX_STD_ID
} NR_SET_REAL_DATA_STD_STD_ID;


//------------------------------------------------
// SubId MAX?i For Set()/Get()?j
//------------------------------------------------
#define		NR_MAX_AXIS_STD			(8)
#define		NR_MAX_AXIS				(7)
#define		NR_MAX_XYZRPY			(6)
#define		NR_MAX_DIGITAL_SIG		(64)
#define		NR_MAX_ANALOG_CH		(16)

//------------------------------------------------
// Priority
//------------------------------------------------
#define		NR_PULL_MODE			(-1)
#define		NR_PUSH_MODE_5			(0)
#define		NR_PUSH_MODE_10			(1)
#define		NR_PUSH_MODE_50			(2)
#define		NR_PUSH_MODE_100		(3)
#define		NR_PUSH_MODE_200		(4)
#define		NR_PUSH_MODE_500		(5)
#define		NR_PUSH_MODE_1000		(6)

//================================================
// I/F RET CODE
//================================================

#define		NR_E_NORMAL				0					// Normal

#define		NR_E_ALREADY			1001				// Alrady
#define		NR_E_NONE_SEND			1002				// None Send (Alrady Send)
#define		NR_E_EXIT				1003				// Process Exit
//------------------------------------------------
// I/F ERROR
//------------------------------------------------
#define		NR_E_PARAM				-1001				// I/F Parameter Error
#define		NR_E_INVALID			-1002				// I/F Invalid Error
#define		NR_E_NONE_SUPPORT		-1003				// I/F None Support
#define		NR_E_EXEC_FAIL			-1004				// Exec Error
#define		NR_E_SEQ				-1005				// Sequence Error
#define		NR_E_LICENSE			-1006				// LICENSE Error
#define		NR_E_XML_SCHEMA			-1007				// XML schema Error
#define		NR_E_VERSION_NONE_SUPPORT -1010				// VERSION NONE SUPPORT

//------------------------------------------------
// I/F CONNECT ERROR
//------------------------------------------------
#define		NR_E_SEND				-2001				// Send Error
#define		NR_E_SEND_TIME_OUT		-2002				// Response Recv TimeOut After Send Error
#define		NR_E_RECV				-2003				// Recv Error
#define		NR_E_RETRY_OVER			-2004				// Retry Over
#define		NR_E_RECV_TIME_OUT		-2005				// Recv TimeOut

//------------------------------------------------
// I/F UPDATE ERROR
//------------------------------------------------
#define		NR_E_UDATE_FATAL		-3001				// fatal error
#define		NR_E_UDATE_READONLY		-3002				// read only
#define		NR_E_UDATE_MISMATCH		-3003				// mode	mismatch
#define		NR_E_UDATE_MISSING		-3004				// missing data
#define		NR_E_UDATE_UNITINVALID	-3005				// unit invalid

//------------------------------------------------
// I/F CTRL ERROR
//------------------------------------------------
#define		NR_E_CTRL_FATAL			-4001				// fatal error
#define		NR_E_CTRL_FORMAT		-4002				// format error
#define		NR_E_CTRL_LIMIT			-4003				// limit error
#define		NR_E_CTRL_EXECFAIL		-4004				// exec	error

//------------------------------------------------
// Pack data ID
//------------------------------------------------
typedef	enum NR_SetPackDataId
{
        eNR_SET_NONE = 0,
        eNR_SET_ENC_CUR_ID,					// Encoder   (Current)
        eNR_SET_ENC_COM_ID,					// Encoder   (Command)
        eNR_SET_POS_CUR_ID,					// Position  (Current)
        eNR_SET_POS_COM_ID,					// Position  (Command)
        eNR_SET_CURR_CUR_ID,				// Current   (Current)
        eNR_SET_CURR_COM_ID,				// Current   (Command)
        eNR_SET_SPD_CUR_ID,					// Speed     (Current)
        eNR_SET_SPD_COM_ID,					// Speed     (Command)
        eNR_SET_TCP_CUR_ID,					// TCP pos.  (Current)
        eNR_SET_TCP_COM_ID,					// TCP pos.  (Command)
        eNR_SET_TCPSPD_CUR_ID,				// TCP Speed (Current)
        eNR_SET_TCPSPD_COM_ID,				// TCP Speed (Command)
        eNR_SET_UBTRQ_ID,					// Unbalance torque
        eNR_SET_FIXIN_ID,					// Fixed input
        eNR_SET_FIXOUT_ID,					// Fixed output
        eNR_SET_ASNIN_ID,					// Assign input
        eNR_SET_ASNOUT_ID,					// Assign output
        eNR_SET_AIN_ID,						// Analog input
        eNR_SET_AOUT_ID,					// Analog output
        eNR_SET_DIN_ID,						// Digital input
        eNR_SET_DOUT_ID,					// Digital output
        eNR_SET_FSNS_ID,					// Force sensor
        eNR_SET_FCTRL_SFT_ID,				// Force control shift
        eNR_SET_PRG_ID,						// Program number
        eNR_SET_STP_ID,						// Step number
        eNR_SET_TRQ_ID,						// torque
        eNR_SET_OUTTRQ_ID,					// output torque
        eNR_SET_PLAYBACK_ID,				// Playback
} NR_SET_PACK_DATA_ID;

//------------------------------------------------
// Set OutputDebugLog Mode
//------------------------------------------------
typedef	enum NR_LogExportMode
{
        LOG_EXPORT_MODE_OFF = 0,
        LOG_EXPORT_MODE_ON,
} NR_LOGEXPORTMODE;


//================================================
// STRUCTURE
//================================================

//------------------------------------------------
// Open() I/F
//------------------------------------------------

typedef	struct nachi_CommIfInfo
{
        char	*pcAddrs;				//! Ip Address
        long	lPortNo;				//! Port No
        long	lRetry;					//! Send Retry
        long	lSendTimeOut;			//! Send TimeOut msec( Data Recv --> Correct Data Send TimeOut )
        long	lCommSide;				//! Communication Side( NR_OBJECT_INTERNAL/NR_OBJECT_EXTERNAL_TCP/NR_OBJECT_EXTERNAL_UDP)
        long	lMode;					//! Internal:0 only, External:Server(NR_MODE_COMM_SERVER)/Client(NR_MODE_COMM_CLIENT)
        long	lKind;					//! Internal:Real(0)/XML(1), External:0 only
}	NACHI_COMMIF_INFO;

#pragma pack( push, 1 )

//------------------------------------------------
// I/F GetAll
//------------------------------------------------

// DEVISE-->APP

typedef struct NR_GetCtrlInfo{
        unsigned short		ushEstopBit 	: 1; 		// Estop
        unsigned short		ushPlaybkBit 	: 1; 		// Playbk
        unsigned short		ushConnectBit 	: 1; 		// Connect
        unsigned short		ushErrorBit 	: 5; 		// Error
        unsigned short		ushMotorBit   	: 1;		// Motor
        unsigned short		ushRsv        	: 6;		// Rsv
        unsigned short		ushProtcolBit 	: 1;		// Protcol
} NR_GET_CTRL_INFO;

typedef struct NR_GetRealDataBodyExt{
        float fCurTcpPos[ NR_MAX_AXIS ]; 			// CurTcpPos
        float fComTcpPos[ NR_MAX_AXIS ]; 			// ComTcpPos
        float fWorkCoord[ NR_MAX_XYZRPY ]; 			// WorkCoord
        float fToolCoord[ NR_MAX_XYZRPY ]; 			// ToolCoord
        float fCurAngle[ NR_MAX_AXIS ]; 			// fCurAngle
        float fComAngle[ NR_MAX_AXIS ]; 			// ComAngle
        float fTorque[ NR_MAX_AXIS ]; 				// Torque
        float fCurrent[ NR_MAX_AXIS ]; 				// Current
        bool bDigOut[ NR_MAX_DIGITAL_SIG ]; 		// DigOut
        bool bDigIn[ NR_MAX_DIGITAL_SIG ]; 			// DigIn
        float fAnaOut[ NR_MAX_ANALOG_CH ]; 			// AnaOut
        float fAnaIn[ NR_MAX_ANALOG_CH ]; 			// AnaIn
} NR_GET_REAL_DATA_BODY_EXT;

typedef struct NR_GetRealDataBodyStd{
        float fCurTcpPos[ NR_MAX_AXIS_STD ]; 		// CurTcpPos
        float fCurAngle[ NR_MAX_AXIS_STD ]; 		// CurAngle
        float fCurrent[ NR_MAX_AXIS_STD ]; 			// Current
        bool bDigOut[ NR_MAX_DIGITAL_SIG ]; 		// DigOut
        bool bDigIn[ NR_MAX_DIGITAL_SIG ]; 			// DigIn
} NR_GET_REAL_DATA_BODY_STD;

typedef struct NR_GetRealDataAll{
        NR_GET_CTRL_INFO stCtrl;					// Ctrl
        int nTime; 									// Time
        union {
                NR_GET_REAL_DATA_BODY_EXT	stExt;		// EXT(ushProtcolBit=1)
                NR_GET_REAL_DATA_BODY_STD	stStd;		// STD(ushProtcolBit=0)
        } ustData;
} NR_GET_REAL_DATA_ALL;

//------------------------------------------------
// I/F SetAll
//------------------------------------------------
// APP-->DEVISE


typedef struct NR_SetCtrlInfo{
        unsigned short		ushEstopBit 	: 1; 		// Estop
        unsigned short		ushFinishBit 	: 1; 		// Finish
        unsigned short		ushOrderBit 	: 1; 		// Order
        unsigned short		ushRsv        	: 12;		// Rsv
        unsigned short		ushProtcolBit 	:  1;		// Protcol
} NR_SET_CTRL_INFO;

typedef struct NR_SetRealDataBodyExt{
        float fComTcpPos[ NR_MAX_AXIS ]; 			// ComTcpPos
        float fWorkCoord[ NR_MAX_XYZRPY ]; 			// WorkCoord
        float fToolCoord[ NR_MAX_XYZRPY ]; 			// ToolCoord
        float fComAngle[ NR_MAX_AXIS ];		 		// ComAngle
        bool bDigOut[ NR_MAX_DIGITAL_SIG ]; 		// DigOut
        float fAnaOut[ NR_MAX_ANALOG_CH ]; 			// AnaOut
} NR_SET_REAL_DATA_BODY_EXT;

typedef struct NR_SetRealDataBodyStd{
        float fComTcpPos[ NR_MAX_AXIS_STD ]; 		// ComTcpPos
        float fWorkCoord[ NR_MAX_XYZRPY ]; 			// WorkCoord
        float fToolCoord[ NR_MAX_XYZRPY ]; 			// ToolCoord
        float fComAngle[ NR_MAX_AXIS_STD ];			// ComAngle
        bool bDigOut[ NR_MAX_DIGITAL_SIG ]; 		// DigOut
} NR_SET_REAL_DATA_BODY_STD;

typedef struct NR_SetRealDataAll{
        NR_SET_CTRL_INFO stCtrl;					// tCtrl
        int nTime;									// Time
        union {
                NR_SET_REAL_DATA_BODY_EXT	stExt;		// EXT(ushProtcolBit=1)
                NR_SET_REAL_DATA_BODY_STD	stStd;		// STD(ushProtcolBit=0)
        } ustData;
} NR_SET_REAL_DATA_ALL;

typedef struct NR_Notification {
        int		nErrCode;
        int		nUnitNo;
        int		nMechNo;
        int		nAxisNo;
        char*	csProg;
        int		nStepNo;
} NR_NOTIFICATION;

typedef struct _SYSTEMTIME {
        unsigned short		wYear;
        unsigned short		wMonth;
        unsigned short		wDayOfWeek;
        unsigned short		wDay;
        unsigned short		wHour;
        unsigned short		wMinute;
        unsigned short		wSecond;
        unsigned short		wMilliseconds;
} SYSTEMTIME;

typedef struct NR_Shift {
        float				fX;
        float				fY;
        float				fZ;
        float				fRoll;
        float				fPitch;
        float				fYaw;
} NR_SHIFT;

typedef struct NR_Pose	{
        float				fX;
        float				fY;
        float				fZ;
        float				fRoll;
        float				fPitch;
        float				fYaw;
} NR_POSE;

typedef struct NR_PoseConf {
        float				fX;
        float				fY;
        float				fZ;
        float				fRoll;
        float				fPitch;
        float				fYaw;
        unsigned int		unConfig;
} NR_POSE_CONF;

typedef struct NR_PalletReg {
        int					RegID;
        int					Execute;
        int					Kind;
        int					Layer;
        int					Work;
} NR_PALLETREG;

typedef struct NR_PalletWork {
        float				PalletID;
        float				Length;
        float				Width;
        float				Height;
        float				dL;
        float				dW;
        float				Xa;
        float				Ya;
} NR_PALLETWORK;

typedef struct NR_PalletLayer {
        float				LayerNum;
        float				TotalHeight;
        float				LayerType;
        struct {
                float			PleneID;
                float			Height;
        } Layer[50];
} NR_PALLETLAYER;

typedef struct NR_PalletPlene {
        float				Type;
        float				WorkNum[2];
        float				Shift[2];
        struct {
                float			PosX;			// X
                float			PosY;			// Y
                float			PosZ;			// Z
                float			ThetaZ;			// ??z
                float			Approach;
        } Work[99];
} NR_PALLETPLENE;

typedef struct NR_Pack {
        unsigned long	dwDtNum;
        struct {
                unsigned long	dwCounter;
                struct {
                        union {
                                float	fDt;
                                unsigned long	dwDt;
                                int				nDt;
                        };
                } Data[64];
        } Que[40];
} NR_PACK;

typedef struct NR_Scope {
        struct {
                float			fTime;
                float			fData[6];
        } Buffer[40];
} NR_SCOPE;

typedef struct NR_FtpEnable {
        int				nEnable;
        const char*		csPassword;
} NR_FTP_ENABLE;

typedef struct NR_FtpStatus {
        int				nAnonymous;
        int				nConnectNum;
        int				nTimeout;
        const char*		csHomeDir;
        int				nDirectoryState;
        const char*		csLoginMessage;
        const char*		csPassword;
} NR_FTP_STATUS;

#pragma pack( pop )

// Notify Method Callback Method Pointer
typedef void(*Notify)(NR_Notification*);

/*!	@brief		open communication
 *	@param[in]	NACHI_COMMIF_INFO *pInfo
 *	@param[out]	none
 *	@retval		SUCCESS		connect object id
 *				FAIL		Error Code
 */
NR_EXTENDED_DLL_API int NR_Open( NACHI_COMMIF_INFO *pInfo );

/*!	@brief		close communication
 *	@param[in]	nOpenId			connect object id
 *								0(All Close)
 *	@retval		SUCCESS			NR_E_NORMAL
 *				FAIL			Error Code
 */
NR_EXTENDED_DLL_API int NR_Close(int nOpenId );

/*!	@brief		Ctrl Moter ON/OFF
 *	@param[in]	nOpenId			connect object id
 *	@param[in]	lCtrlSW			ON(1)/OFF(0)
 *	@retval		over Zero		Normal
 *				under Zero		Error
 */
NR_EXTENDED_DLL_API int NR_CtrlMotor(int nOpenId, long lCtrlSW);

/*!	@brief		Ctrl Run START/STOP
 *	@param[in]	nOpenId			connect object id
 *	@param[in]  lCtrlSW			START(1)/STOP(0)
 *	@param[in]	nUnitId			unit id
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlRun(int nOpenId, long lCtrlSW, int nUnitId = 1);

/*!	@brief		Data Send(embedded mode)
 *	@param[in]	nOpenId			connect object id
 *	@param[in]	char*			sendBuf
 *	@param[in]	int				nBufSize
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_Send(int nOpenId, char* sendBuf, int nBufSize);

/*!	@brief		Data Receive(embedded mode)
 *	@param[in]	nOpenId			connect object id
 *	@param[in]	char*			recvBuf
 *	@param[in]	int				nBufSize
 *	@param[in]	int				nTimeOut
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_Recv(int nOpenId, char* recvBuf, int nBufSize, int nTimeOut);

/*!	@brief		Program / Pose File upload
 *	@param[in]	pszIpaddress	IP address
 *	@param[in]	pstrRemoteFile	Remote file
 *	@param[in]	pstrLocalFile	Local File
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_UpLoad(const char* pszIpaddress, const char* pstrRemoteFile, const char* pstrLocalFile);


/*!	@brief		Program / Pose File download
 *	@param[in]	pszIpaddress	IP address
 *	@param[in]	pstrRemoteFile	Remote file
 *	@param[in]	pstrLocalFile	Local File
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_DownLoad(const char* pszIpaddress, const char* pstrRemoteFile, const char* pstrLocalFile);

/*!	@brief		Set Program No
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	nProgNo			program no
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlProgram(int nOpenId, int nProgNo);

/*!	@brief		Set Step No
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	nStepNo			step no
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlStep(int nOpenId, int nStepNo);

/*!	@brief	 		Get signal of Stop.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			true:on, false:off
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsFixedIOStop(int nOpenId, bool* value,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get signal of Servo On.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			true:on, false:off
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsFixedIOServoOn(int nOpenId, bool* value,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get signal of Motors On Lamp.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			true:on, false:off
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsFixedIOMotorsOnLAMP(int nOpenId, bool* value,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get signal of Start Display1.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			true:on, false:off
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsFixedIOStartDisplay1(int nOpenId, bool* value,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set General Output Signal.
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			true:on, false:off
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsGeneralOutputSignal(int nOpenId, bool value[], bool bUpdate, int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Global Integer Variable.
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			global integer variable
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsGlobalInt(int nOpenId, int value[], bool bUpdate, int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Global Real Variable.
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			global real variable
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsGlobalFloat(int nOpenId, float value[], bool bUpdate, int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Global String Variable.
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			global string variable
 *	@param[in]		szBufSize		buffer size of each string value
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
#ifdef _UNICODE
#define NR_AcsGlobalString NR_AcsGlobalStringW
#else
#define NR_AcsGlobalString NR_AcsGlobalStringA
#endif
NR_EXTENDED_DLL_API int NR_AcsGlobalStringW(int nOpenId, wchar_t* value[], size_t szBufSize, bool bUpdate, int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);
NR_EXTENDED_DLL_API int NR_AcsGlobalStringA(int nOpenId, char* value[], size_t szBufSize, bool bUpdate, int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get Version.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			version string
 *	@param[in]		szBufSize		buffer size of string value
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
#ifdef _UNICODE
        #define NR_AcsVersion NR_AcsVersionW
#else
        #define NR_AcsVersion NR_AcsVersionA
#endif
NR_EXTENDED_DLL_API int NR_AcsVersionW(int nOpenId, wchar_t* value, size_t szBufSize);
NR_EXTENDED_DLL_API int NR_AcsVersionA(int nOpenId, char* value, size_t szBufSize);

/*!	@brief	 		Get Program No.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			program no
 *	@param[in]		nCount			number of data
 *	@param[in]		nUnitId			unit id
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsPrgNo(int  nOpenId, int* value, int nCount, int nUnitId = 1,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get Err Info.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			error info
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsErrInfo(int nOpenId, int value[], int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get Axis Theta.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			axis theta
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsAxisTheta(int nOpenId, float value[], int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get Axis Tool Tip Position.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			axis tool tip position
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsToolTipPos(int nOpenId, float value[], int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get CPU load
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			CPU load
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsCPULoad(int nOpenId, float* value,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Record Tool No
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			record tool no
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nUnitId			unit id
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsRecordToolNo(int nOpenId, int* value, bool bUpdate, int nUnitId = 1,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Posture Value
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			posture value
 *	@param[in]		bUpdate			TRUE:set, FALSE:get
 *	@param[in]		nId				value id
 *  @param[in]		nSubId			value subid
 *	@param[in]		nUnitId			unit id
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsPoseValue(int nOpenId, NR_POSE_CONF* value, bool bUpdate, int nId, int nSubId, int nUnitId = 1,
        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		Get/Set Over Ride Speed
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			waitting status signal
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nUnitId			unit id
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsSpeedOverride(int nOpenId, float* value, bool bUpdate, int nUnitId = 1,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief		Delete file
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	lpFileName
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlDeleteFile(int nOpenId, const char* lpFileName);

/*!	@brief		Shot down
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	bReboot
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlShutDown(int nOpenId, bool bReboot);

/*!	@brief	 		Get/Set Encoder offset
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			current unit no
 *	@param[in]		bUpdate			true:set, false:get
 *	@param[in]		nSubId			mechanism no
 *	@param[in]		nCount			number of data
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsEncOffsetValue(int nOpenId, int* value, bool bUpdate, int nSubId, int nCount);

/*!	@brief	 		FTP service start / stop
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			NR_FTP_ENABLE( nEnable / csPassword )
 *	@param[in]		bUpdate			TRUE:set, FALSE:get
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */

/*!	@brief		Move by Absolute TCP Position
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	pose			posture
 *  @param[in]	nConf			config
 *	@param[in]	fExtPos			extra position
 *	@param[in]	nExtPosSize		extra position num
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlMoveX(int nOpenId, NR_POSE* pose, int nType = 0, int nUnitId = 1, int nConf = 0, float fExtPos[] = NULL, int nExtPosSize = 0);

/*!	@brief		Move by Relative Robot Position
 *	@param[in]	nOpenId			connect object id
 *  @param[in]	pose			posture
 *  @param[in]	nType			0:Path / 1:Pause / 2:End
 *	@param[in]	nUnitId			unit id
 *  @param[in]	nConf			config
 *	@param[in]	fExtPos			extra position
 *	@param[in]	nExtPosSize		extra position num
 *	@retval		NR_E_NORMAL/NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_CtrlMoveXR(int nOpenId, NR_POSE* pose, int nType = 0, int nUnitId = 1, int nConf = 0, float fExtPos[] = NULL, int nExtPosSize = 0);

/*!	@brief	 		Get Order Tcp Speed.
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			order tcp speed
 *	@param[in]		nSubId			first index of data
 *	@param[in]		nCount			number of data
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsOrderTcpSpeed(int nOpenId, float value[], int nSubId, int nCount,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);


/*!	@brief	 		Get/Set Manual Speed
 *	@param[in]		nOpenId			connect object id
 *	@param[in/out]	value			manual speed
 *	@param[in]		bUpdate			TRUE:set, FALSE:get
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
NR_EXTENDED_DLL_API int NR_AcsManualSpeed(int nOpenId, int* value, bool bUpdate,
                                                                                                        int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_AcsAxisAmpValue(int nOpenId, float value[], int nSubId, int nCount,int nPriority = NR_PULL_MODE,float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_AcsAxisSpeed(int nOpenId, float value[], int nSubId, int nCount,int nPriority = NR_PULL_MODE,float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_AcsShift(int nOpenId,NR_SHIFT value[],bool bUpdate,int nSubId,int nCount,int nPriority=NR_PULL_MODE,float fThreshold=0.01f);

NR_EXTENDED_DLL_API int NR_AcsFixedIOConfirmMotorsOn(int nOpenId,bool* value,int nPriority = NR_PULL_MODE,float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_CtrlMoveJ(int nOpenId,float[],int nAngleSize,int nType = 0,int nUnitId = 1);

NR_EXTENDED_DLL_API int NR_AcsFixedIOTPEStop(int nOpenId,bool* value,int nPriority = NR_PULL_MODE,float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_AcsInterpolationKind(int nOpenId,int value[],bool bUpdate,int nUnitId = 1,int nPriority = NR_PULL_MODE,float fThreshold = 0.01f);

NR_EXTENDED_DLL_API int NR_AcsRecordSpeed(int nOpenId,int value[],bool bUpdate,int nUintId = 1,int nPriority=NR_PULL_MODE,float fThreshold=0.01f);


#ifdef _UNICODE
#define NR_AcsFtpEnable NR_AcsFtpEnableW
#else
#define NR_AcsFtpEnable NR_AcsFtpEnableA
#endif

NR_EXTENDED_DLL_API int NR_AcsFtpEnableW(int nOpenId, NR_FTP_ENABLE* value, bool bUpdate, int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);
NR_EXTENDED_DLL_API int NR_AcsFtpEnableA(int nOpenId, NR_FTP_ENABLE* value, bool bUpdate, int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*!	@brief	 		FTP service setting
 *	@param[in]		nOpenId			connect object id
 *	@param[out]		value			NR_FTP_STATUS(setting)
 *	@param[in]		bUpdate			TRUE:set, FALSE:get
 *	@param[in]		nPriority		a data update frequency when push transfer mode is used
 *	@param[in]		fThreshold		a tolerance area where the variable can change without sending a data update
 *	@retval			SUCCESS:NR_E_NORMAL
 *					FAIL:NR_E_XXXXX
 */
#ifdef _UNICODE
#define NR_AcsFtpStatus NR_AcsFtpStatusW
#else
#define NR_AcsFtpStatus NR_AcsFtpStatusA
#endif
NR_EXTENDED_DLL_API int NR_AcsFtpStatusW(int nOpenId, NR_FTP_STATUS* value, bool bUpdate, int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);
NR_EXTENDED_DLL_API int NR_AcsFtpStatusA(int nOpenId, NR_FTP_STATUS* value, bool bUpdate, int nPriority = NR_PULL_MODE, float fThreshold = 0.01f);

/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
/*************************************************************************************************************************/
