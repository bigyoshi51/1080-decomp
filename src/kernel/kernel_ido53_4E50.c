/* IDO 5.3 -O1 -mips2 donor for func_80004E50 = libultra osLeoDiskInit
 * (io/leodiskinit.c verbatim; cfe -E expansion of the 2.0I header
 * chain, comment-swallowed macros re-spelled by sed). PROVEN
 * 2026-08-22: 64/64 words -- every non-reloc word identical; all 38
 * diffs are reloc fields (LeoDiskHandle field hi/lo pairs, __osPiTable,
 * __osDiskHandle, 3 jals). RETRACTS the long-documented "D6/D7
 * shared-$at store pair matches no compiler output family / plausibly
 * hand-touched asm" cap: the verbatim OSPiHandle STRUCT definition
 * (fields pageSize/relDuration at +6/+7 of the one LeoDiskHandle
 * symbol, in-place reloc addends) makes 5.3 -O1 emit the single shared
 * lui $at natively -- the cap was an artifact of the separate-extern-
 * u8-symbol spelling (and the earlier struct probe's context).
 * Sign-extended lo16 pins (undefined_syms_auto.txt):
 *   LeoDiskHandle = 0x800195D0 (lui 0x8002/lo 0x95Dx wrap)
 *   __osPiTable   = 0x8000A46C (lui 0x8001/lo 0xA46C wrap)
 *   __osDiskHandle= 0x80019644 (lui 0x8002/lo 0x9644 wrap)
 * POST_COMPILE renames osLeoDiskInit -> func_80004E50 and the jal
 * callees bzero=func_800030D0, __osDisableInt=func_800066B0,
 * __osRestoreInt=func_800066D0. Spliced into kernel_003_b.c.o via
 * REPLACE_FUNC_BODY (same-size splice, no boundary fix needed). */

typedef unsigned char			u8;	 
typedef unsigned short			u16;	 
typedef unsigned long			u32;	 
typedef unsigned long long		u64;	 
typedef signed char			s8;	 
typedef short				s16;	 
typedef long				s32;	 
typedef long long			s64;	 
typedef volatile unsigned char		vu8;	 
typedef volatile unsigned short		vu16;	 
typedef volatile unsigned long		vu32;	 
typedef volatile unsigned long long	vu64;	 
typedef volatile signed char		vs8;	 
typedef volatile short			vs16;	 
typedef volatile long			vs32;	 
typedef volatile long long		vs64;	 
typedef float				f32;	 
typedef double				f64;	 
typedef unsigned int    size_t;
typedef s32	OSPri;
typedef s32	OSId;
typedef union	{ struct { f32 f_odd; f32 f_even; } f; f64 d; }	__OSfp;
typedef struct {
	u64	at, v0, v1, a0, a1, a2, a3;
	u64	t0, t1, t2, t3, t4, t5, t6, t7;
	u64	s0, s1, s2, s3, s4, s5, s6, s7;
	u64	t8, t9,         gp, sp, s8, ra;
	u64	lo, hi;
	u32	sr, pc, cause, badvaddr, rcp;
	u32	fpcsr;
	__OSfp	 fp0,  fp2,  fp4,  fp6,  fp8, fp10, fp12, fp14;
	__OSfp	fp16, fp18, fp20, fp22, fp24, fp26, fp28, fp30;
} __OSThreadContext;
typedef struct OSThread_s {
	struct OSThread_s	*next;		 
	OSPri			priority;	 
	struct OSThread_s	**queue;	 
	struct OSThread_s	*tlnext;	 
	u16			state;		 
	u16			flags;		 
	OSId			id;		 
	int			fp;		 
	__OSThreadContext	context;	 
} OSThread;
typedef u32 OSEvent;
typedef u32 OSIntMask;
typedef u32 OSPageMask;
typedef u32 OSHWIntr;
typedef void *	OSMesg;
typedef struct OSMesgQueue_s {
	OSThread	*mtqueue;	 
	OSThread	*fullqueue;	 
	s32		validCount;	 
	s32		first;		 
	s32		msgCount;	 
	OSMesg		*msg;		 
} OSMesgQueue;
typedef struct {
	u32		errStatus;	 
        void     	*dramAddr;       
	void		*C2Addr;	 
	u32		sectorSize;	 
	u32		C1ErrNum;	 
	u32		C1ErrSector[4];	 
} __OSBlockInfo;
typedef struct {
	u32     	cmdType;       	 
	u16     	transferMode;    
	u16		blockNum;	 
	s32     	sectorNum;       
	u32     	devAddr;         
	u32		bmCtlShadow;	 
	u32		seqCtlShadow;	 
	__OSBlockInfo	block[2];	 
} __OSTranxInfo;
typedef struct OSPiHandle_s {
        struct OSPiHandle_s     *next;   
        u8                      type;    
        u8                      latency;         
        u8                      pageSize;        
        u8                      relDuration;     
        u8                      pulse;           
	u8			domain;		 
        u32                     baseAddress;     
        u32                     speed;           
        __OSTranxInfo           transferInfo;	 
} OSPiHandle;
typedef struct {
        u8      type;
        u32     address;
} OSPiInfo;
typedef struct {
        u16 		type;		 
        u8 		pri;		 
        u8		status;		 
	OSMesgQueue	*retQueue;	 
} OSIoMesgHdr;
typedef struct {
	OSIoMesgHdr	hdr;		 
	void *		dramAddr;	 
	u32		devAddr;	 
	u32 		size;		 
	OSPiHandle	*piHandle;	 
} OSIoMesg;
typedef struct {
        s32             active;		 
	OSThread	*thread;	 
        OSMesgQueue  	*cmdQueue;	 
        OSMesgQueue  	*evtQueue;	 
        OSMesgQueue  	*acsQueue;	 
        s32             (*dma)(s32, u32, void *, u32);
        s32             (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr;
typedef struct {
    u32	ctrl;
    u32	width;
    u32	burst;
    u32	vSync;
    u32	hSync;
    u32	leap;
    u32	hStart;
    u32	xScale;
    u32	vCurrent;
} OSViCommonRegs;
typedef struct {
    u32	origin;
    u32	yScale;
    u32	vStart;	
    u32	vBurst;
    u32	vIntr;
} OSViFieldRegs;
typedef struct {
    u8			type;		 
    OSViCommonRegs	comRegs;	 
    OSViFieldRegs	fldRegs[2];	 
} OSViMode;
typedef u64	OSTime;
typedef struct OSTimer_s {
	struct OSTimer_s	*next;	 
	struct OSTimer_s	*prev;	 
	OSTime			interval;	 
	OSTime			value;		 
	OSMesgQueue		*mq;		 
	OSMesg			msg;		 
} OSTimer;
typedef struct {
	u16     type;                    
	u8      status;                  
	u8	errno;
}OSContStatus;
typedef struct {
	u16     button;
	s8      stick_x;		 
	s8      stick_y;		 
	u8	errno;
} OSContPad;
typedef struct {
	void    *address;                
	u8      databuffer[32];          
        u8      addressCrc;              
	u8      dataCrc;                 
	u8	errno;
} OSContRamIo;
typedef struct {
	int		status;
	OSMesgQueue 	*queue;
	int		channel;
	u8		id[32];
	u8		label[32];
	int		version;
	int		dir_size;
	int		inode_table;		 
	int		minode_table;		 
	int		dir_table;		 
	int		inode_start_page;	 
	u8		banks;
	u8		activebank;
} OSPfs;
typedef struct {
	u32	file_size;	 
  	u32 	game_code;
  	u16 	company_code;
  	char  	ext_name[4];
  	char 	game_name[16];
} OSPfsState;
typedef struct {
	u16	*histo_base;		 
	u32	histo_size;		 
	u32	*text_start;		 
	u32	*text_end;		 
} OSProf;
extern u64 osClockRate;
extern OSViMode	osViModeTable[];	 
extern OSViMode	osViModeNtscLpn1;	 
extern OSViMode	osViModeNtscLpf1;
extern OSViMode	osViModeNtscLan1;
extern OSViMode	osViModeNtscLaf1;
extern OSViMode	osViModeNtscLpn2;
extern OSViMode	osViModeNtscLpf2;
extern OSViMode	osViModeNtscLan2;
extern OSViMode	osViModeNtscLaf2;
extern OSViMode	osViModeNtscHpn1;
extern OSViMode	osViModeNtscHpf1;
extern OSViMode	osViModeNtscHan1;
extern OSViMode	osViModeNtscHaf1;
extern OSViMode	osViModeNtscHpn2;
extern OSViMode	osViModeNtscHpf2;
extern OSViMode	osViModePalLpn1;	 
extern OSViMode	osViModePalLpf1;
extern OSViMode	osViModePalLan1;
extern OSViMode	osViModePalLaf1;
extern OSViMode	osViModePalLpn2;
extern OSViMode	osViModePalLpf2;
extern OSViMode	osViModePalLan2;
extern OSViMode	osViModePalLaf2;
extern OSViMode	osViModePalHpn1;
extern OSViMode	osViModePalHpf1;
extern OSViMode	osViModePalHan1;
extern OSViMode	osViModePalHaf1;
extern OSViMode	osViModePalHpn2;
extern OSViMode	osViModePalHpf2;
extern OSViMode	osViModeMpalLpn1;	 
extern OSViMode	osViModeMpalLpf1;
extern OSViMode	osViModeMpalLan1;
extern OSViMode	osViModeMpalLaf1;
extern OSViMode	osViModeMpalLpn2;
extern OSViMode	osViModeMpalLpf2;
extern OSViMode	osViModeMpalLan2;
extern OSViMode	osViModeMpalLaf2;
extern OSViMode	osViModeMpalHpn1;
extern OSViMode	osViModeMpalHpf1;
extern OSViMode	osViModeMpalHan1;
extern OSViMode	osViModeMpalHaf1;
extern OSViMode	osViModeMpalHpn2;
extern OSViMode	osViModeMpalHpf2;
extern s32 	osRomType;	 
extern void 	*osRomBase;	 
extern s32 	osTvType;	 
extern s32 	osResetType;	 
extern s32 	osCicId;
extern s32 	osVersion;
extern u32	osMemSize;	 
extern s32	osAppNMIBuffer[];
extern OSIntMask __OSGlobalIntMask;	 
extern OSPiHandle      *__osPiTable;     
extern OSPiHandle      *__osDiskHandle;  
extern void		osCreateThread(OSThread *, OSId, void (*)(void *),
				       void *, void *, OSPri);
extern void		osDestroyThread(OSThread *);
extern void		osYieldThread(void);
extern void		osStartThread(OSThread *);
extern void		osStopThread(OSThread *);
extern OSId		osGetThreadId(OSThread *);
extern void		osSetThreadPri(OSThread *, OSPri);
extern OSPri		osGetThreadPri(OSThread *);
extern void		osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32		osSendMesg(OSMesgQueue *, OSMesg, s32);
extern s32		osJamMesg(OSMesgQueue *, OSMesg, s32);
extern s32		osRecvMesg(OSMesgQueue *, OSMesg *, s32);
extern void		osSetEventMesg(OSEvent, OSMesgQueue *, OSMesg);
extern OSIntMask	osGetIntMask(void);
extern OSIntMask	osSetIntMask(OSIntMask);
extern void             osInitRdb(u8 *sendBuf, u32 sendSize);
extern void		osInvalDCache(void *, s32);
extern void		osInvalICache(void *, s32);
extern void		osWritebackDCache(void *, s32);
extern void		osWritebackDCacheAll(void);
extern void		osMapTLB(s32, OSPageMask, void *, u32, u32, s32);
extern void		osMapTLBRdb(void);
extern void		osUnmapTLB(s32);
extern void		osUnmapTLBAll(void);
extern void		osSetTLBASID(s32);
extern u32		 osVirtualToPhysical(void *);
extern void *		 osPhysicalToVirtual(u32);
extern u32 		osAiGetStatus(void);
extern u32 		osAiGetLength(void);
extern s32		osAiSetFrequency(u32);
extern s32		osAiSetNextBuffer(void *, u32);
extern u32 		osDpGetStatus(void);
extern void		osDpSetStatus(u32);
extern void 		osDpGetCounters(u32 *);
extern s32		osDpSetNextBuffer(void *, u64);
extern u32 		osPiGetStatus(void);
extern s32		osPiGetDeviceType(void);
extern s32		osPiRawWriteIo(u32, u32);
extern s32		osPiRawReadIo(u32, u32 *);
extern s32		osPiRawStartDma(s32, u32, void *, u32);
extern s32		osPiWriteIo(u32, u32);
extern s32		osPiReadIo(u32, u32 *);
extern s32		osPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32,
				     OSMesgQueue *);
extern void		osCreatePiManager(OSPri, OSMesgQueue *, OSMesg *, s32);
extern u32		osViGetStatus(void);
extern u32		osViGetCurrentMode(void);
extern u32		osViGetCurrentLine(void);
extern u32		osViGetCurrentField(void);
extern void		*osViGetCurrentFramebuffer(void);
extern void		*osViGetNextFramebuffer(void);
extern void		osViSetXScale(f32);
extern void		osViSetYScale(f32);
extern void		osViSetSpecialFeatures(u32);
extern void		osViSetMode(OSViMode *);
extern void		osViSetEvent(OSMesgQueue *, OSMesg, u32);
extern void		osViSwapBuffer(void *);
extern void		osViBlack(u8);
extern void		osViFade(u8, u16);
extern void		osViRepeatLine(u8);
extern void		osCreateViManager(OSPri);
extern OSTime		osGetTime(void);
extern void		osSetTime(OSTime);
extern int		osSetTimer(OSTimer *, OSTime, OSTime,
				   OSMesgQueue *, OSMesg);
extern int		osStopTimer(OSTimer *);
extern s32		osContInit(OSMesgQueue *, u8 *, OSContStatus *);
extern s32		osContReset(OSMesgQueue *, OSContStatus *);
extern s32		osContStartQuery(OSMesgQueue *);
extern s32		osContStartReadData(OSMesgQueue *);
extern s32		osContSetCh(u8);
extern void		osContGetQuery(OSContStatus *);
extern void		osContGetReadData(OSContPad *);
extern s32 osPfsInitPak(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsRepairId(OSPfs *);
extern s32 osPfsInit(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsReFormat(OSPfs *, OSMesgQueue *, int);
extern s32 osPfsChecker(OSPfs *);
extern s32 osPfsAllocateFile(OSPfs *, u16, u32, u8 *, u8 *, int, s32 *);
extern s32 osPfsFindFile(OSPfs *, u16, u32, u8 *, u8 *, s32 *);
extern s32 osPfsDeleteFile(OSPfs *, u16, u32, u8 *, u8 *);
extern s32 osPfsReadWriteFile(OSPfs *, s32, u8, int, int, u8 *);
extern s32 osPfsFileState(OSPfs *, s32, OSPfsState *);
extern s32 osPfsGetLabel(OSPfs *, u8 *, int *);
extern s32 osPfsSetLabel(OSPfs *, u8 *);
extern s32 osPfsIsPlug(OSMesgQueue *, u8 *);
extern s32 osPfsFreeBlocks(OSPfs *, s32 *);
extern s32 osPfsNumFiles(OSPfs *, s32 *, s32 *);
extern s32 osEepromProbe(OSMesgQueue *);
extern s32 osEepromRead(OSMesgQueue *, u8, u8 *);
extern s32 osEepromWrite(OSMesgQueue *, u8, u8 *);
extern s32 osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
extern s32 osEepromLongWrite(OSMesgQueue *, u8, u8 *, int);
extern s32 osMotorInit(OSMesgQueue *, OSPfs *, int);
extern s32 osMotorStop(OSPfs *);
extern s32 osMotorStart(OSPfs *);
extern OSPiHandle *osCartRomInit(void);
extern OSPiHandle *osLeoDiskInit(void);
extern OSPiHandle *osDriveRomInit(void);
extern s32 osEPiDeviceType(OSPiHandle *, OSPiInfo *);
extern s32 osEPiRawWriteIo(OSPiHandle *, u32 , u32);
extern s32 osEPiRawReadIo(OSPiHandle *, u32 , u32 *);
extern s32 osEPiRawStartDma(OSPiHandle *, s32 , u32 , void *, u32 );
extern s32 osEPiWriteIo(OSPiHandle *, u32 , u32 );
extern s32 osEPiReadIo(OSPiHandle *, u32 , u32 *);
extern s32 osEPiStartDma(OSPiHandle *, OSIoMesg *, s32);
extern s32 osEPiLinkHandle(OSPiHandle *);
extern void		osProfileInit(OSProf *, u32 profcnt);
extern void		osProfileStart(u32);
extern void		osProfileFlush(void);
extern void		osProfileStop(void);
extern s32		osTestHost(void);
extern void		osReadHost(void *, u32);
extern void		osWriteHost(void *, u32);
extern void		osAckRamromRead(void);
extern void		osAckRamromWrite(void);
extern void     bcopy(const void *, void *, int);
extern int      bcmp(const void *, const void *, int);
extern void     bzero(void *, int);
extern void		osInitialize(void);
extern u32		osGetCount(void);
extern void		osExit(void);
extern u32 		osGetMemSize(void);
extern int		sprintf(char *s, const char *fmt, ...);
extern void		osSyncPrintf(const char *fmt, ...);
extern void		osAsyncPrintf(const char *fmt, ...);
extern int		osSyncGetChars(char *buf);
extern int		osAsyncGetChars(char *buf);
extern u32		__osGetCause(void);
extern void		__osSetCause(u32);
extern u32		__osGetCompare(void);
extern void		__osSetCompare(u32);
extern u32		__osGetConfig(void);
extern void		__osSetConfig(u32);
extern void		__osSetCount(u32);
extern u32		__osGetSR(void);
extern void		__osSetSR(u32);
extern u32		__osDisableInt(void);
extern void		__osRestoreInt(u32);
extern u32              __osSetFpcCsr(u32);
extern u32              __osGetFpcCsr(void);
extern void		__osSetHWIntrRoutine(OSHWIntr, s32 (*handler)(void));
extern void		__osSetGlobalIntMask(OSHWIntr);
extern void		__osResetGlobalIntMask(OSHWIntr);
extern s32		__osLeoInterrupt(void);
extern u32		__osGetTLBASID(void);
extern u32		__osGetTLBPageMask(s32);
extern u32		__osGetTLBHi(s32);
extern u32		__osGetTLBLo0(s32);
extern u32		__osGetTLBLo1(s32);
extern u32 		__osSiGetStatus(void);
extern s32		__osSiRawWriteIo(u32, u32);
extern s32		__osSiRawReadIo(u32, u32 *);
extern s32		__osSiRawStartDma(s32, void *);
extern u32 		__osSpGetStatus(void);
extern void		__osSpSetStatus(u32);
extern s32		__osSpSetPc(u32);
extern s32		__osSpRawWriteIo(u32, u32);
extern s32		__osSpRawReadIo(u32, u32 *);
extern s32		__osSpRawStartDma(s32, u32, void *, u32);
extern void		__osError(s16, s16, ...);
extern OSThread *	__osGetCurrFaultedThread(void);
extern OSThread *	__osGetNextFaultedThread(OSThread *);
extern void		__osGIOInit(s32);
extern void		__osGIOInterrupt(s32);
extern void		__osGIORawInterrupt(s32);
extern OSThread *	__osGetActiveQueue(void);
extern void		__osSyncPutChars(int, int, const char *);
extern int		__osSyncGetChars(char *);
extern void		__osAsyncPutChars(int, int, const char *);
extern int		__osAsyncGetChars(char *);
extern int		__osAtomicInc(unsigned int *p);
extern int		__osAtomicDec(unsigned int *p);
extern u32             __osRdbSend(u8 *buf, u32 size, u32 type);
extern void	bcopy(const void *, void *, int);
extern int	bcmp(const void *, const void *, int);
extern void	bzero(void *, int);
extern void	blkclr(void *, int);
OSPiHandle LeoDiskHandle;
OSPiHandle *__osDiskHandle;
OSPiHandle *osLeoDiskInit()
{
	u32 saveMask;
	LeoDiskHandle.type = 2 ;
	LeoDiskHandle.baseAddress = ((u32)(0x05000000)|0xA0000000) ;
	LeoDiskHandle.latency = 3;
	LeoDiskHandle.pulse = 6;
	LeoDiskHandle.pageSize = 6;
	LeoDiskHandle.relDuration = 2;
	LeoDiskHandle.domain = 1 ;
	(*(vu32 *)((u32)((0x04600000+0x24))|0xA0000000) =(u32)( LeoDiskHandle.latency)) ;
	(*(vu32 *)((u32)((0x04600000+0x28))|0xA0000000) =(u32)( LeoDiskHandle.pulse)) ;
	(*(vu32 *)((u32)((0x04600000+0x2C))|0xA0000000) =(u32)( LeoDiskHandle.pageSize)) ;
	(*(vu32 *)((u32)((0x04600000+0x30))|0xA0000000) =(u32)( LeoDiskHandle.relDuration)) ;
	LeoDiskHandle.speed = 0;
	bzero(&LeoDiskHandle.transferInfo, sizeof(__OSTranxInfo));
	saveMask = __osDisableInt();
	LeoDiskHandle.next = __osPiTable;
	__osPiTable = &LeoDiskHandle;
	__osDiskHandle = &LeoDiskHandle;
	__osRestoreInt(saveMask);
	return &LeoDiskHandle;
}
