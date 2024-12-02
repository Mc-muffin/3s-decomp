#ifndef	_ADXT_H_INCLUDED
#define	_ADXT_H_INCLUDED
/****************************************************************************/
/*																			*/
/*			$title$ �`�c�w�f�[�^�Đ� ���C�u����								*/
/*					ADXT (ADX TALK) Library									*/
/*																			*/
/*				1997.2.25		written M.Oshimi							*/
/*																			*/
/****************************************************************************/

/*	Version number of ADXT library 		*/
#define	ADXT_VER	"8.34"

#include "cri/ee/cri_xpt.h"
#include "sj.h"

/*	�X�g���[���R���g���[��				*/
/*	Stream Controller					*/
#ifndef ADXSTM_DEFINED
#define ADXSTM_DEFINED
typedef	void	*ADXSTM;
#endif

/*	�X�g���[���W���C���g�f�R�[�_		*/
/*	Stream Joint decoder				*/
#ifndef ADXSJD_DEFINED
#define ADXSJD_DEFINED
typedef void	*ADXSJD;
#endif

/*	�I�[�f�B�I�����_��					*/
/*	Audio Renderer						*/
#ifndef ADXRNA_DEFINED
#define ADXRNA_DEFINED
typedef void	*ADXRNA;
#endif

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif

/****************************************************************************/
/*		�萔�}�N��															*/
/*		MACRO CONSTANT														*/
/****************************************************************************/

/*	�ő哯��������						*/
/*	Maximum number of ADXT handle		*/
//	2001.09.14	S.Hosaka
//	�o���h������8->16
//#define	ADXT_MAX_OBJ		(8)
#define	ADXT_MAX_OBJ		(16)

/*	�ő�f�[�^�T�C�Y					*/
/*	Maximum data size					*/
#define	ADXT_MAX_DATASIZE	(0x40000000)

/*	���̓o�b�t�@�̃G�L�X�g���̈�̑傫��	*/
/*	Size of Extra area in input buffer		*/
#define ADXT_IBUF_XLEN (36)

/*	ADX Talk �̏o�̓o�b�t�@�̑傫���@�i�T���v���P�ʁj	*/
/*	Output buffer size of ADX Talk (unit:sample)		*/
#define	ADXT_OBUF_SIZE	(0x2000)
#define DECODE_AHX
#ifdef DECODE_AHX
#define	ADXT_OBUF_DIST	(0x2060)
#else
#define	ADXT_OBUF_DIST	(0x2020)
#endif

/*	�ő�T���v�����O���g��				*/
/*	Maximum sampling frequency			*/
#define	ADXT_MAX_SFREQ	(48000)

/*	ADX Talk�̍Đ�����	(ADXT_CALC_WORK�}�N���Ŏg�p)		*/
/*	Play method of ADX Talk (used 'ADXT_CALC_WORK' macro)	*/
#define ADXT_PLY_MEM	(0)			/*	����������̍Đ�					*/
									/*	Play memory data					*/
#define ADXT_PLY_STM	(1)			/*	CD����̃X�g���[���Đ�				*/
									/*	Stream play from CD-ROM				*/

#define ADXT_CALC_IBUFSIZE0(nch, sfreq)	(25000*(nch)*((sfreq)/1000)/44)

#define ADXT_CALC_IBUFSIZE(nch, nstm, sfreq)	\
	((ADXT_CALC_IBUFSIZE0(nch, sfreq)*((nstm)+1)+2048)/2048*2048+ADXT_IBUF_XLEN)

#ifdef XPT_TGT_GC
#define	ADXT_RNABUF_SIZE	(0x1000)
#define ADXT_CALC_OBUFSIZE(nch)	\
	( (ADXT_OBUF_DIST+ADXT_RNABUF_SIZE)*(nch)*sizeof(Sint16))
#else
#define ADXT_CALC_OBUFSIZE(nch)	\
	( ADXT_OBUF_DIST*(nch)*sizeof(Sint16))
#endif

#define ADXT_CALC_WORK(nch, stmflg, nstm, sfreq)	\
	(ADXT_CALC_IBUFSIZE(nch, nstm, sfreq)*(stmflg) + ADXT_CALC_OBUFSIZE(nch) + 64)

/*	�f�[�^�e�ʂ̌v�Z		*/
/*	Calc ADX Data size		*/
#define	ADXT_CalcDataLen(sec, nch, sfreq)	((sec)*(nch)*(sfreq)*18/32 + 256)

/* AHX���[�N�̈�T�C�Y		*/
/* Work size of AHX 		*/
#define ADXT_WORKSIZE_AHX	(12288)		/* 12KB */

/*	���̓o�b�t�@�ւ̓ǂݍ��ݗ�						*/
/*	Number of sectors to read into the input buffer	*/
#define ADXT_MAX_CDBSCT		(75)
#define ADXT_MIN_CDBSCT		(65)
#define ADXT_PREP_RDSCT		(25)

/*	$define$ ADX Talk�̓�����(ADXT_STAT_�`)	*/
/*	Status of ADX Talk							*/
#define	ADXT_STAT_STOP		(0)		/*	��~�� 								*/
									/*	During standstill					*/
#define ADXT_STAT_DECINFO	(1)		/*	�`�c�w �̃w�b�_���擾��			*/
									/*	Getting header information			*/
#define ADXT_STAT_PREP		(2)		/*	�Đ������� 							*/
									/*	During play preparation				*/
#define ADXT_STAT_PLAYING	(3)		/*	�f�R�[�h���Đ��� 					*/
									/*	During decode and play				*/
#define ADXT_STAT_DECEND	(4)		/*	�f�R�[�h�I�� 						*/
									/*	Decode end							*/
#define ADXT_STAT_PLAYEND	(5)		/*	�Đ��I�� 							*/
									/*	Play end							*/
#define ADXT_STAT_ERROR		(6)		/*	�ǂݍ��݃G���[����					*/
									/*	Read-in error outbreak state		*/

/*	$define$ ADX Talk�̃G���[�R�[�h�@(ADXT_ERR_�`)	*/
/*	Error code of ADX Talk							*/
#define	ADXT_ERR_OK			(0)		/*	���� 								*/
									/*	Normality							*/
#define ADXT_ERR_SHRTBUF	(-1)	/*	���̓o�b�t�@�G���v�e�B				*/
									/*	The input buffer is empty			*/
#define ADXT_ERR_SNDBLK		(-2)	/*	�T�E���h�u���b�N�G���[				*/
									/*	Error of sound block				*/

/*	$define$ �t�B���^���[�h	(ADXT_FLTMODE_�`)		*/
/*	Filter mode										*/
#define	ADXT_FLTMODE_CPU	(0)		/*	�b�o�t�ɂ��W�J���[�h				*/
									/*	by CPU								*/
#define	ADXT_FLTMODE_SCSP	(1)		/*	AICA-DSP�ɂ��W�J���[�h			*/
									/*	by AICA-DSP							*/

/*	$define$ �Đ����[�h	(ADXT_PMODE_�`)				*/
/*	Play mode										*/
#define	ADXT_PMODE_FNAME	(0)		/*	�t�@�C�����܂��� FID �ɂ��w��		*/
									/*	Play specified file name or file ID	*/
#define	ADXT_PMODE_AFS		(1)		/*	AFS �ɂ��w��						*/
									/*	Play specified AFS file				*/
#define	ADXT_PMODE_MEM		(2)		/*	�������Đ�							*/
									/*	Play data from memory				*/
#define	ADXT_PMODE_SJ		(3)		/*	�X�g���[���W���C���g�Đ�			*/
									/*	Play data from StreamJoint			*/
#define	ADXT_PMODE_SLFILE	(4)		/*	�V�[�����X�A���Đ��i�t�@�C���j		*/
									/*	Seamless continuous play from file	*/

/*	$define$ �G���[���J�o�[���[�h	(ADXT_RMODE_�`)	*/
/*	Mode of error recovery							*/
#define	ADXT_RMODE_NOACT	(0)		/*	���J�o�[�������Ȃ�					*/
									/*	Do not recover						*/
#define	ADXT_RMODE_STOP		(1)		/*	������~							*/
									/*	Automatic stop						*/
#define	ADXT_RMODE_REPLAY	(2)		/*	�����ăv���C						*/
									/*	Automatic replay					*/

/*	�p���|�b�g�̐ݒ�l		*/
/*	Panpot parameter		*/
#define	ADXT_PAN_LEFT		(-15)
#define	ADXT_PAN_CENTER		(0)
#define	ADXT_PAN_RIGHT		(15)
#define	ADXT_PAN_AUTO		(-128)	/*	MONO/STE �ɂ���Ď����I�ɐ؂�ւ���	*/
									/*	Changes automatically by data		*/

/*	�X�e���I�Đ����̃`�����l���ԍ�		*/
/*	Channel number playing stereo data	*/
/*	ADXT_CH_L:left, ADXT_CH_R:right		*/
#define	ADXT_CH_L			(0)
#define	ADXT_CH_R			(1)

/*	�ő�Đ��`�����l����				*/
/*	Maximum number of play channel		*/
#define	ADXT_MAX_NCH		(2)

/*	�T�[�o�֐��̌Ăяo�����p�x�̋K��l�@60�i��/�b�j				*/
/*	Default value of frequency called server function(times/sec)	*/
#define ADXT_DEF_SVRFREQ	(60)

/*	Default value of output volume(dB)	*/
#define	ADXT_DEF_OUTVOL		(0)

/*	���̓o�b�t�@�̉����l (�G���[�����p�A�P�ʃo�C�g�j				*/
/*	Minimum data in the input buffer(byte) (for coping with error)	*/
#define	ADXT_MIN_BUFDATA	(64)

/*	�G���[���ʎ��ԁ@�i�P��:�b)			*/
/*	Error distinction time(sec)			*/
#define	ADXT_EWAIT_PLY		(5)
#define	ADXT_EWAIT_NOTPLY	(20)

/*	�C���f�b�N�X�̍ő吔				*/
/*	Maximum number of index				*/
#define	ADXT_MAX_IDX		(0xFFFF)

/*	ADX�t�H�[�}�b�g�^�C�v				*/
/*	Format type of ADX					*/
#define ADXT_FMT_ADX		(1)
#define ADXT_FMT_AHX		(2)

/****************************************************************************/
/*		�f�[�^�^															*/
/*      Data type declaration												*/
/****************************************************************************/

/*	ADX Talk �I�u�W�F�N�g�\����		*/
/*	Structure of ADX Talk object	*/
typedef struct _adx_talk {
	Sint8	used;						/*	�g�p�����ۂ�					*/
	Sint8	stat;						/*	������						*/
	Sint8	pmode;						/*	�Đ����[�h						*/
	Sint8	maxnch;						/*	�ő�Đ��`�����l����			*/
	ADXSJD	sjd;						/*	ADX�X�g���[���W���C���g�f�R�[�_	*/
	ADXSTM	stm;						/*	���̓X�g���[���R���g���[��		*/
	ADXRNA	rna;						/*	�I�[�f�B�I�����_��				*/
	SJ		sjf;						/*	�t�@�C�����̓X�g���[���W���C���g*/
	SJ		sji;						/*	���̓X�g���[���W���C���g		*/
	SJ		sjo[ADXT_MAX_NCH];			/*	�o�̓X�g���[���W���C���g		*/
	Sint8	*ibuf;						/*	���̓o�b�t�@					*/
	Sint32	ibuflen;					/*	���̓o�b�t�@�T�C�Y�i�o�C�g�P��)	*/
	Sint32	ibufxlen;					/*	���̓o�b�t�@�G�N�X�g���T�C�Y	*/
	Sint16	*obuf;						/*	�o�̓o�b�t�@					*/
	Sint32	obufsize;					/*	�o�̓o�b�t�@�T�C�Y�i�T���v���j	*/
	Sint32	obufdist;					/*	�o�̓o�b�t�@�Ԋu�i�T���v���j	*/
	Sint32	svrfreq;					/*	�T�[�o�֐��Ăяo���p�x			*/
	Sint16	maxsct;						/*	���̓o�b�t�@���̍ō��Z�N�^��	*/
	Sint16	minsct;						/*	���̓o�b�t�@���̍Œ�Z�N�^��	*/
	Sint16	outvol;						/*	�o�̓{�����[��					*/
	Sint16	outpan[ADXT_MAX_NCH];		/*	�o�̓p���|�b�g�̐ݒ�l			*/
	Sint32	maxdecsmpl;					/*	�ő�f�R�[�h�T���v����			*/
	Sint32	lpcnt;						/*	���[�v�J�E���^					*/
	Sint32	lp_skiplen;					/*	���[�v�X�L�b�v�o�C�g��			*/
	Sint32	trp;						/*	�g�����X�|�[�Y�� (�Z���g)		*/
	Sint32	wpos;						/*	���f�B�A��̏������݈ʒu		*/
	Sint32	mofst;						/*	���f�B�A��̃I�t�Z�b�g			*/
	Sint16	ercode;						/*	�G���[�R�[�h					*/
	Sint32	edecpos;					/*	�G���[���o�p�f�R�[�h�ʒu		*/
	Sint16	edeccnt;					/*	�f�R�[�h�ʒu�J�E���^			*/
	Sint16	eshrtcnt;					/*	�����ޯ̧����è�����			*/
	Sint8	lpflg;						/*	���[�v���邩�ۂ�				*/
	Sint8	autorcvr;					/*	�����I�ɃG���[���A���邩�ۂ�	*/
	Sint8	fltmode;					/*	�t�B���^���[�h					*/
	Sint8	execflag;					/*	�T�[�o�����s���邩�ۂ�			*/
	Sint8	pstwait_flag;				/*	�����o�͊J�n�҂��t���O			*/
	Sint8	pstready_flag;				/*	�����o�͏��������t���O			*/
	Sint8	pause_flag;					/*	�ꎞ��~�t���O					*/
	void	*amp;						/*	�U�����o��						*/
	SJ		ampsji[ADXT_MAX_NCH];		/*	�U�����o�p����SJ				*/
	SJ		ampsjo[ADXT_MAX_NCH];		/*	�U�����o�p�o��SJ				*/
	Sint32	time_ofst;					/*	�����̃I�t�Z�b�g				*/
	Sint32	lesct;						/*	���[�v�Đ����̍ŏI�Z�N�^�ԍ�	*/
	Sint32	trpnsmpl;					/*			�g���b�v�T���v���ԍ�	*/
	void	*lsc;						/*	�A���X�g���[���R���g���[��		*/
	Sint8	lnkflg;						/*	�A���Đ��t���O					*/
	Sint8	rsv;						/*	�\��							*/
	Sint16	rsv2;						/*	�\��Q							*/
	Uint32 tvofst;						/*	�X�^�[�g���ԃI�t�Z�b�g			*/
	Uint32 svcnt;						/*	�X�^�[�gV-Sync�J�E���g			*/
	// 2001.11.14 oshimi
	Uint32 decofst;						/*	�g�[�^���f�R�[�h�I�t�Z�b�g		*/
	#ifdef __EE__
	Sint32	flush_nsmpl;				/*	�t���b�V�����ɑ}�������T���v����	*/
	#endif
} ADX_TALK;
typedef	ADX_TALK	*ADXT;

/*	�C���f�b�N�X�f�[�^	*/
/*	Index data			*/
typedef struct _adxt_idx {
	Uint16 nidx;
	Uint16 top;
} ADXT_IDX;

/*	�X���b�h�p�����[�^�\����		*/
/*	Parameter structure of Thread Param	*/
typedef struct {
	int	prio_lock;		// Lock Thread priority
	int	prio_safe;		// Safe Thread priority
	int	prio_vsync;		// Vsync Thread priority
	int	prio_main;		// Main Thread Normary priority
	int	prio_mwidle;	// Middleware Idle Thread priority
} ADXM_TPRM;

/*	�X���b�h�p�����[�^�\����(�g����)				*/
/*	Parameter structure of Extended Thread Param	*/
typedef struct {
	int	prio_lock;		// Lock Thread priority
	int	prio_safe;		// Safe Thread priority
	int	prio_usrvsync;	// User Vsync Thread priority
	int	prio_vsync;		// Vsync Thread priority
	int	prio_main;		// Main Thread Normary priority
	int	prio_mwidle;	// Middleware Idle Thread priority
	int	prio_usridle;	// User Idle Thread priority
} ADXM_TPRM_EX;

/*	ADX�w�b�_���\����					*/
/*	Parameter structure of ADX header	*/
typedef struct {
	Sint32 fmt;			// Format type (ADX/AHX)
	Sint32 sfreq;		// Sampling rate
	Sint32 nch;			// Number of channel
	Sint32 bps;			// Number of bit per sample
	Sint32 nsmpl;		// Total number of sample
	Sint32 lptype;		// Loop type
	Sint32 lpstart;		// Loop start position
	Sint32 lpend;		// Loop end position
} ADXHINFO;

/****************************************************************************/
/*		�֐��̐錾															*/
/*      Function Declaration												*/
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* $func$ ADX Talk �̏�����
 * [���@��] void ADXT_Init(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ADX Talk ������������B
 *			�ϐ��̈�̏��������s���B
 *  Initialization of ADX Talk
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Initializes ADX Talk. Initializes variable.
 */
void ADXT_Init(void);

/* $func$ ADX Talk�̏I��
 * [���@��] void ADXT_Finish(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ADX Talk �̏I������������B
 *  Termination of ADX Talk
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Finalizes ADX Talk.
 */
void ADXT_Finish(void);

/*	$func$ ���ׂĂ�ADXT�n���h���̏���
 * [���@��] void ADXT_DestroyAll(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���ׂĂ�ADXT�n���h������������B
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] You can destroy all ADXT handles.
 */
void ADXT_DestroyAll(void);

/*	$func$ ���ׂĂ�ADXT��ADXF�n���h���̏���
 * [���@��] void ADXT_CloseAllHandles(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���ׂĂ�ADXT�n���h����ADXF�n���h������������B
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] You can destroy all ADXT handles and close all ADXF handles.
 */
void ADXT_CloseAllHandles(void);

/*	$func$ ADXT�n���h�� �̐���
 * [���@��] ADXT ADXT_Create(Sint32 maxnch, void *work, Sint32 worksize);
 * [���@��] maxnch	: �ő�Đ��`�����l�����i���m�����݂̂P�F�X�e���I�Q�j
 *			work	: ���[�N�̈�
 *			worksize: ���[�N�̈�̃T�C�Y
 * [�o�@��] �Ȃ�
 * [�֐��l] ADXT�n���h��
 * [�@�@�\] ADXT�n���h���𐶐�����B
 *			work�̈�̃T�C�Y�́AADXT_CALC_WORK�}�N���ɂ���ċ��߂�B
 *  Creation of ADXT handle
 * [Inputs  ] maxnch  : Number of maximum channels(monoral:1, stereo:2)
 *			  work    : Working area
 *			  worksize: Size of working area(byte)
 * [Outputs ] None
 * [Return  ] ADXT handle
 * [Function] Creates ADXT handle.
 * [Remarks ] You calculate size of working area used 'ADXT_CALC_WORK' macro. 
 */
ADXT ADXT_Create(Sint32 maxnch, void *work, Sint32 worksize);

/* $func$ ADXT�n���h�� �̏���
 * [���@��] void ADXT_Destroy(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �w�肳�ꂽ ADXT�n���h������������B
 *  Destroy of ADXT handle
 * [Inputs  ] adxt   : ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Destroys specified ADXT handle.
 */
void ADXT_Destroy(ADXT adxt);

/* $func$ FID �w��ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartAfs(ADXT adxt, Sint32 patid, Sint32 fid);
 * [���@��] adxt	: ADXT�n���h��
 *			patid	: �p�[�e�B�V�������ʎq
 *			fid		: �t�@�C�����ʎq
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �p�[�e�B�V�������ʎq�ƃt�@�C�����ʎq�Ŏw�肳�ꂽ�`�c�w�t�@�C����
 *			�Đ����J�n����B
 *  Play start of ADX data by specified file ID
 * [Inputs  ] adxt	: ADXT handl
 *			  patid	: Partition ID
 *			  fid	: File ID
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play ADX file when you specify partition ID and file ID.
 */
void ADXT_StartAfs(ADXT adxt, Sint32 patid, Sint32 fid);

/* $func$ �t�@�C�����w��ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartFname(ADXT adxt, Sint8 *fname);
 * [���@��] adxt	: ADXT�n���h��
 *			fname	: �t�@�C����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] fname �Ŏw�肳�ꂽ�`�c�w�t�@�C���̍Đ����J�n����B
 *  Play start of ADX data specified file name
 * [Inputs  ] adxt	: ADXT handle
 *			  fname	: File name
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play ADX file when you specify file name.
 */
void ADXT_StartFname(ADXT adxt, Char8 *fname);

/* $func$ �X�g���[���W���C���g�ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartSj(ADXT adxt, SJ sj);
 * [���@��] adxt	: ADXT�n���h��
 *			sj		: �X�g���[���W���C���g
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �X�g���[���W���C���g���瓾����f�[�^���Đ�����B
 *  Play start of ADX data from Stream Joint
 * [Inputs  ] adxt	: ADXT handle
 *			  sj	: Stream Joint
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play ADX file when you specify Stream Joint.
 */
void ADXT_StartSj(ADXT adxt, SJ sj);

/* $func$ �������w��ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartMem(ADXT adxt, void *adxdat);
 * [���@��] adxt	: ADXT�n���h��
 *			adxdat	: �`�c�w�f�[�^�̃A�h���X
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] adxdat�Ŏw�肳�ꂽ�`�c�w�f�[�^���Đ�����B
 *  Play start of ADX data on memory
 * [Inputs  ] adxt	: ADXT handle
 *			  adxdat: Address of ADX data
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play ADX data on memory when you specify address.
 */
void ADXT_StartMem(ADXT adxt, void *adxdat);

/* $func$ �������w��ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartMem2(ADXT adxt, void *adxdat, Sint32 datlen);
 * [���@��] adxt	: ADXT�n���h��
 *			adxdat	: �`�c�w�f�[�^�̃A�h���X
 *			datlen	: �`�c�w�f�[�^�̑傫��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] adxdata �Ŏw�肳�ꂽ�`�c�w�f�[�^���Đ�����B
 *  Play start of ADX data on memory (TYPE 2)
 * [Inputs  ] adxt	: ADXT handle
 *			  adxdat: Address of ADX data
 *			  datlen: Length of playing ADX data
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play ADX data on memory. Plays to specified length.
 */
void ADXT_StartMem2(ADXT adxt, void *adxdat, Sint32 datlen);

/* $func$ �������w��ɂ��Đ��̊J�n
 * [���@��] void ADXT_StartMemIdx(ADXT adxt, void *acx, Sint32 no);
 * [���@��] adxt	: ADXT�n���h��
 *			acx		: �`�b�w�f�[�^�̃A�h���X
 *			no		: �C���f�b�N�X�ԍ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] acx �Ŏw�肳�ꂽ�`�b�w�f�[�^��no�Ԗڂ̃f�[�^���Đ�����B
 *  Play start of ACX data
 * [Inputs  ] adxt	: ADXT handle
 *			  acx	: Address of ACX data
 *			  no	: Index number
 * [Outputs ] None
 * [Return  ] None
 * [Function] Starts to play a part of ACX data when you specify index number.
 */
void ADXT_StartMemIdx(ADXT adxt, void *acx, Sint32 no);

/* $func$ �Đ��̒�~
 * [���@��] void ADXT_Stop(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �`�c�w�̍Đ����~����B
 *  Play stop
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Stops to play ADX data.
 */
void ADXT_Stop(ADXT adxt);

/* $func$ ��Ԃ̎擾
 * [���@��] Sint32 ADXT_GetStat( ADXT adxt );
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] ���݂� ADXT�n���h���̏�Ԃ�\���萔
 * 				ADXT_STAT_STOP	 :	��~��
 *				ADXT_STAT_DECINFO:	�`�c�w �̃w�b�_���擾��
 *				ADXT_STAT_PREP	 :	�Đ�������
 *				ADXT_STAT_PLAYING:	�f�R�[�h���Đ���
 *				ADXT_STAT_DECEND :	�f�R�[�h�I��
 *				ADXT_STAT_PLAYEND:	�Đ��I��
 * [�@�@�\] ���݂�ADXT�n���h���̏�Ԃ��擾����B
 *  Get status
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Status of ADXT handle
 * [Function] Obtains status of ADXT handle.
 */
Sint32 ADXT_GetStat(ADXT adxt);

/* $func$ �T���v���P�ʂł̍Đ������̎擾
 * [���@��] void ADXT_GetTime( ADXT adxt, Sint32 *ncount, Sint32 *tscale );
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] ncount	: �Đ��T���v����
 *			tscale	: �T���v�����O���g�� [ Hz ]
 * [�֐��l] �Ȃ�
 * [�@�@�\] �T���v���P�ʂōĐ��������擾����B
 *  Get play time by sample unit
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] ncount: Number of play sample
 *			  tscale: Sampling frequency(Hz)
 * [Return  ] None
 * [Function] Obtains play time by sample unit.
 */
void ADXT_GetTime(ADXT adxt, Sint32 *ncount, Sint32 *tscale);

/* $func$ �����Ԃł̍Đ������̎擾
 * [���@��] Sint32 ADXT_GetTimeReal(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Đ����� [ 1/100sec ]
 * [�@�@�\] �����ԂōĐ��������擾����B
 *  Get play time in real time
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Play time(1/100sec)
 * [Function] Obtains play time in real time.
 */
Sint32 ADXT_GetTimeReal(ADXT adxt);

/* $func$ �����f�[�^�̑��T���v�����̎擾
 * [���@��] Sint32 ADXT_GetNumSmpl( ADXT adxt );
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �����f�[�^�̑��T���v����
 * [�@�@�\] �Đ����� �`�c�w �f�[�^�̑��T���v�������擾����B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 *  Get a general sample number of sound data
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] General sample number of sound data
 * [Function] Obtains a general sample number of sound data.
 * [Remarks ] You can obtain a time between status of preparation
 *			  (ADXT_STAT_PREP) and status of play end(ADXT_STAT_PLAYEND).
 */
Sint32 ADXT_GetNumSmpl(ADXT adxt);

/* $func$ �����f�[�^�̃T���v�����O���g���̎擾
 * [���@��] Sint32 ADXT_GetSfreq(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �����f�[�^�̃T���v�����O���g��
 * [�@�@�\] �Đ����� �T���v�����O���g�������߂�B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 *  Get sampling frequecy
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Sampling frequency
 * [Function] Obtains sampling frequency.
 * [Remarks ] You can obtain a sampling frequency between status of preparation
 *			 (ADXT_STAT_PREP) and status of play end(ADXT_STAT_PLAYEND).
 */
Sint32 ADXT_GetSfreq(ADXT adxt);

/* $func$ �����f�[�^�̃`�����l�����̎擾
 * [���@��] Sint32 ADXT_GetNumChan(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �����f�[�^�̃`�����l�����̎擾
 * [�@�@�\] �Đ����̉����̃`�����l���������߂�B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 */
Sint32 ADXT_GetNumChan(ADXT adxt);

/* $func$ �w�b�_���̎擾
 * [���@��] Sint32 Sint32 ADXT_GetHdrLen(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �����f�[�^�̃w�b�_��
 * [�@�@�\] �Đ����̉����̃w�b�_�������߂�B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 */
Sint32 ADXT_GetHdrLen(ADXT adxt);

/* $func$ �����f�[�^�̗ʎq���̎擾
 * [���@��] Sint32 ADXT_GetFmtBps(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �����f�[�^�̗ʎq���r�b�g��
 * [�@�@�\] �Đ����̉����̗ʎq���r�b�g�������߂�B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 */
Sint32 ADXT_GetFmtBps(ADXT adxt);

/*	$func$ �p���|�b�g�̐ݒ�
 * [���@��] void ADXT_SetOutPan(ADXT adxt, Sint32 ch, Sint32 pan);
 * [���@��] adxt	: ADXT�n���h��
 *			ch		: �`���l���ԍ� (0, 1)
 *						ADXT_CH_L=0, ADXT_CH_R=1
 *			pan		: �p���ݒ�l (-15�`+15, -128)
 *						ADXT_PAN_LEFT=-15, ADXT_PAN_CENTER=0
 *						ADXT_PAN_RIGHT=15, ADXT_PAN_AUTO=-128
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �o�̓p���|�b�g��ݒ肷��B
 *			AUTO �̏ꍇ�́AADX �f�[�^�����m�������X�e���I���ɂ���Ď����I��
 *			�p�����ݒ肳���B
 *  Set panpot
 * [Inputs  ] adxt	: ADXT handle
 *			  ch	: Channel number(ADXT_CH_L:0, ADXT_CH_R:1)
 *			  pan	: Panpot(from -15 to +15, -128)
 *						ADXT_PAN_LEFT=-15, ADXT_PAN_CENTER=0
 *						ADXT_PAN_RIGHT=15, ADXT_PAN_AUTO=-128
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets panpot of specified channel number.
 *			 Sets automatically panpot by data, monoral or stereo, when you 
 *			 specified 'ADXT_PAN_AUTO'.
 */
void ADXT_SetOutPan(ADXT adxt, Sint32 ch, Sint32 pan);

/*	$func$ �p���|�b�g�̎擾
 * [���@��] Sint32 ADXT_GetOutPan(ADXT adxt, Sint32 ch);
 * [���@��] adxt	: ADXT�n���h��
 *			ch		: �`���l���ԍ� (0, 1)
 *						ADXT_CH_L=0, ADXT_CH_R=1
 * [�o�@��] �Ȃ�
 * [�֐��l] �p���|�b�g�̐ݒ�l
 * [�@�@�\] �o�̓p���|�b�g���擾����B
 *  Get panpot
 * [Inputs  ] adxt	: ADXT handle
 *			  ch	: Channel number(ADXT_CH_L:0, ADXT_CH_R:1)
 * [Outputs ] None
 * [Return  ] Panpot
 * [Function] Obtains panpot of specified channel number.
 */
Sint32 ADXT_GetOutPan(ADXT adxt, Sint32 ch);

/*	$func$ �o�̓{�����[���̐ݒ�
 * [���@��] void ADXT_SetOutVol(ADXT adxt, Sint32 vol);
 * [���@��] adxt	: ADXT�n���h��
 *			vol		: �������x���@(0:-0dB, -960:-96dB)
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �o�̓{�����[����ݒ肷��B
 *			vol�̐ݒ�l	0    :  -0dB  �����Ȃ�
 *						-30  :  -3dB  ��70%
 *						-60  :  -6dB  ��50%
 *						-960 : -96dB  �ő�̌�����
 *  Set volume
 * [Inputs  ] adxt	: ADXT handle
 *			  vol	: Volume (0:-dB, -960:-96dB)
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets the volume of a ADXT handle.
 *			 'vol'value	0    :  -0dB  No attenuation
 *						-30  :  -3dB  about 70%
 *						-60  :  -6dB  about 50%
 *						-960 : -96dB  Maximum attenuation
 */
void ADXT_SetOutVol(ADXT adxt, Sint32 vol);

/*	$func$ �o�̓{�����[���̎擾
 * [���@��] Sint32 ADXT_GetOutVol(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �o�̓{�����[���̐ݒ�l�@(0:-0dB �` -960:-96dB)
 * [�@�@�\] �o�̓{�����[�����擾����B
 *  Get volume
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Volume (0:-0dB, -960:-96dB)
 * [Function] Obtains the volume for a ADXT handle.
 */
Sint32 ADXT_GetOutVol(ADXT adxt);

/*	$func$ �T�[�o�֐��̌Ăяo���p�x�̐ݒ�	(�P�b������̌Ăяo����)
 * [���@��] void ADXT_SetSvrFreq(ADXT adxt, Sint32 freq);
 * [���@��] adxt	: ADXT�n���h��
 *			freq	: �T�[�o�֐��̌Ăяo���p�x (�P�b������̌Ăяo����)
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �T�[�o�֐�(ADXT_ExecServer�֐�)�̌Ăяo���p�x�̐ݒ肷��B
 *			�f�t�H���g�ł́A60���ݒ肳��Ă���B
 *			�ʏ�A�ݒ肷��K�v�͂Ȃ��B
 *  Set the frequency called server function(times/sec)
 * [Inputs  ] adxt	: ADXT handle
 *			  freq	: Frequency called server function(times/sec)
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets the frequency called server function(ADXT_ExecServer).
 *			 You do not need to set it usually. Default value is 60.
 */
void ADXT_SetSvrFreq(ADXT adxt, Sint32 freq);

/*	$func$ �ēǂݍ��݊J�n���Ԃ̐ݒ�
 * [���@��] void ADXT_SetReloadTime(ADXT adxt,float time,Sint32 nch,Sint32 sfreq);
 * [���@��] adxt	: ADXT�n���h��
 *			time	: �ēǂݍ��݊J�n����
 *			nch		: �`�����l����
 *			sfreq	: �T���v�����O���g��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���̓o�b�t�@�ւ̍ēǂݍ��݊J�n���Ԃ�ݒ肷��B
 *			���̓o�b�t�@���̃f�[�^�ʂ� time �b��菭�Ȃ��Ȃ�ƃf�B�X�N����
 *			�f�[�^��ǂݍ��ށB
 *  Set the time of start sector to reload
 * [Inputs  ] adxt	: ADXT handle
 *			  time  : start remain time
 *			  nch   : number of channel
 *			  sfreq : sampling frequency
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets of the time of start sector to reload into input buffer.
 *			 Reads data from disc when a quantity of data in the input 
 *			 buffer becomes less than 'time' [second].
 */
void ADXT_SetReloadTime(ADXT adxt, float time, Sint32 nch, Sint32 sfreq);

/*	$func$ �ēǂݍ��݊J�n�Z�N�^���̐ݒ�
 * [���@��] void ADXT_SetReloadSct(ADXT adxt, Sint32 minsct);
 * [���@��] adxt	: ADXT�n���h��
 *			minsct	: �ēǂݍ��݊J�n�Z�N�^��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���̓o�b�t�@�ւ̍ēǂݍ��݊J�n�Z�N�^����ݒ肷��B
 *			���̓o�b�t�@���̃f�[�^�ʂ� minsct �Z�N�^��菭�Ȃ��Ȃ�ƃf�B�X�N
 *			����f�[�^��ǂݍ��ށB
 *  Set the number of start sector to reload
 * [Inputs  ] adxt	: ADXT handle
 *			  minsct: start sector number
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets of the number of start sector to reload into input buffer.
 *			 Reads data from disc when a quantity of data in the input 
 *			 buffer becomes less than 'minsct' [sector].
 */
void ADXT_SetReloadSct(ADXT adxt, Sint32 minsct);

/*	$func$ ���̓o�b�t�@���̃Z�N�^���̎擾
 * [���@��] Sint32 ADXT_GetNumSctIbuf(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Z�N�^��
 * [�@�@�\] ���̓o�b�t�@�ɓǂݍ��܂�Ă���Z�N�^�����擾����B
 *  Get the amount of data stored in input buffer(sector)
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Number of sector
 * [Function] Obtains the amount of data that is stored in input buffer.
 */
Sint32 ADXT_GetNumSctIbuf(ADXT adxt);

/*	$func$ �o�̓o�b�t�@���̃T���v�����̎擾
 * [���@��] Sint32 ADXT_GetNumSmplObuf(ADXT adxt, Sint32 chno);
 * [���@��] adxt	: ADXT�n���h��
 *			chno	: �`�����l���ԍ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �T���v����
 * [�@�@�\] �o�̓o�b�t�@���̃T���v�������擾����B
 */
Sint32 ADXT_GetNumSmplObuf(ADXT adxt, Sint32 chno);

/*	$func$ ���̓o�b�t�@���Đ�����
 * [���@��] float ADXT_GetIbufRemainTime(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Đ��\���ԁ@(�P�ʁF�b)
 * [�@�@�\] ���̓o�b�t�@�ɂ���f�[�^�ōĐ��\�Ȏ��Ԃ��擾����B
 *			ADX�f�[�^�̂ݑΉ��B
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Playable time (sec)
 * [Function] Obtains playable time using only data in input buffer.
 *			  You can use this function only playing ADX data.
 */
float ADXT_GetIbufRemainTime(ADXT adxt);

/*	$func$ ���̓o�b�t�@�ɏ\���ȃf�[�^�����邩�ۂ��̌���
 * [���@��] Sint32 ADXT_IsIbufSafety(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] TRUE(1):�\���ȃf�[�^������AFALSE(0):�f�[�^�s��
 * [�@�@�\] ���̓o�b�t�@�ɏ\���ȃf�[�^�����邩�ۂ�����������B
 *			ADXT_SetReloadSct�֐��ɂ���Ďw�肳�ꂽ�ēǂݍ��݊J�n�Z�N�^���ȏ��
 *			�f�[�^�����̓o�b�t�@���ɑ��݂���ꍇ�ATRUE���Ԃ����B
 *  Check whether the input buffer is having enough data or not
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] TRUE(1):Has enough data, FALSE(0):Data are insufficient
 * [Function] Checks whether the input buffer is having enough data or not.
 *			  Returns 'TRUE' when data more than the number of sector appointed
 *			  exist in the input buffer.
 */
Sint32 ADXT_IsIbufSafety(ADXT adxt);

/*	$func$ �G���[���J�o���[���[�h�̎w��
 * [���@��] void ADXT_SetAutoRcvr(ADXT adxt, Sint32 rmode);
 * [���@��] adxt	: ADXT�n���h��
 *			rmode	: �G���[���J�o���[�̕��@
 *					  ADXT_RMODE_NOACT, ADXT_RMODE_STOP, ADXT_RMODE_REPLAY
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G���[���J�o���[�̕��@��ݒ肷��B
 *			ADXT_RMODE_NOACT : �G���[���J�o���[���Ȃ�
 *			ADXT_RMODE_STOP  : �����I�ɒ�~���A�����Ԃ�ADXT_STAT_STOP�ɂȂ�B
 *			ADXT_RMODE_REPLAY: CD����̃f�[�^�̋������r�؂ꂽ�Ƃ��ɁA�����I��
 *							   �t�@�C���̐擪����Đ�����B
 *							   ���̑��̏ꍇ�́A�����I�ɒ�~������B
 *  Set a mode of error recovery
 * [Inputs  ] adxt	: ADXT handle
 *			  rmode	: Method of error recovery
 *					  ADXT_RMODE_NOACT, ADXT_RMODE_STOP, ADXT_RMODE_REPLAY
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets the method that recover from error.
 *			 ADXT_RMODE_NOACT : Does not recover
 *			 ADXT_RMODE_STOP  : Stops automatically
 *			 ADXT_RMODE_REPLAY: Replay from the top of a file automatically 
 *							    when data supply from CD-ROM broke off.
 *							    Other cases stop automatically.
 */
void ADXT_SetAutoRcvr(ADXT adxt, Sint32 rmode);

/*	$func$ �Đ����I���������ۂ��̌���
 * [���@��] Sint32 ADXT_IsCompleted(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] TRUE(1):�Đ��I���AFALSE(0):�Đ���
 * [�@�@�\] �Đ����I���������ۂ��𒲂ׂ�B
 *  Check whether the play finished or not
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] TRUE(1):Finished, FALSE(0):Playing
 * [Function] Checks whether the play finished or not.
 */
Sint32 ADXT_IsCompleted(ADXT adxt);

/*	$func$ �e�n���h���̃T�[�o�֐��@�i������Ԃ̍X�V)
 * [���@��] void ADXT_ExecHndl(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �e�n���h���̓�����Ԃ��X�V����B
 *			ADXT_ExecServer������Ăяo�����B
 *  Server function of each handle
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Update the inside status.
 *			  This function is called from 'ADXT_ExecServer' function.
 */
void ADXT_ExecHndl(ADXT adxt);

/*	$func$ �T�[�o�֐��@�i������Ԃ̍X�V)
 * [���@��] void ADXT_ExecServer(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���C�u�����̓�����Ԃ��X�V����B
 *			V-Sync ���ɌĂяo���Ȃ���΂Ȃ�Ȃ��B
 *  Server function
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Update the inside status of library.
 */
void ADXT_ExecServer(void);

/*	$func$ �t�@�C���V�X�e���T�[�o�֐��@�i������Ԃ̍X�V)
 * [���@��] void ADXT_ExecFsSvr(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���C�u�����̓�����Ԃ��X�V����B
 *			V-Sync ���ɌĂяo���Ȃ���΂Ȃ�Ȃ��B
 *			�D��x��ADXT_ExecServer�����Ⴍ����B
 *  File System Server function
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Update the inside status of library.
 */
void ADXT_ExecFsSvr(void);

/*	$func$ �t�@�C���V�X�e���T�[�o�����������ۂ�
 * [���@��] Sint32 ADXT_IsActiveFsSvr(void);
 * [���@��] �Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] TRUE:�������^FALSE:�������Ă��Ȃ�
 * [�@�@�\] �t�@�C���V�X�e���T�[�o�����������ۂ����`�F�b�N����B
 *  Check active File System Server function
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] TRUE:active/FALSE:no active
 * [Function] Checks that File System server function is active.
 */
Sint32 ADXT_IsActiveFsSvr(void);

/*	$func$ �G���[�R�[�h�̎擾
 * [���@��] Sint32 ADXT_GetErrCode(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G���[�R�[�h���擾����B
 *  Get error code
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Obtains the error code.
 */
Sint32 ADXT_GetErrCode(ADXT adxt);

/*	$func$ �G���[�R�[�h�̃N���A
 * [���@��] void ADXT_ClearErrCode(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G���[�R�[�h���N���A����B
 *  Clear error code
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Clears the error code.
 */
void ADXT_ClearErrCode(ADXT adxt);

/*	$func$ ���[�v�����񐔂̎擾
 * [���@��] Sint32 ADXT_GetLpCnt(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] ���[�v������
 * [�@�@�\] ���[�v�����񐔂��擾����B
 *  Get the number of times played a loop
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Number of times played a loop
 * [Function] Obtains the number of times that played a loop.
 */
Sint32 ADXT_GetLpCnt(ADXT adxt);

/*	$func$ ���[�v�t���O�̐ݒ�
 * [���@��] void ADXT_SetLpFlg(ADXT adxt, Sint32 flg);
 * [���@��] adxt	: ADXT�n���h��
 *			flg		: 1=���[�v����A0=���[�v���Ȃ�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���[�v���邩�ۂ���ݒ肷��B
 *			�Đ����́A���[�v���������邱�Ƃ̂݉\�B
 *			�ēx�A���[�v��ݒ肷�鎞�́A�Đ��J�n���O�ɐݒ肷�邱�ƁB
 *  Set the loop flag
 * [Inputs  ] adxt	: ADXT handle
 *			  flg	: 1=loop, 0=not loop
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets whether play a loop or not.
 *			  You can only release looping play while playing.
 *			  If you set this flag again,
 *			  you have to set just before start playing.
 */
void ADXT_SetLpFlg(ADXT adxt, Sint32 flg);

/*	$func$ ���̓X�g���[���W���C���g�̎擾
 * [���@��] SJ ADXT_GetInputSj(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �X�g���[���W���C���g�n���h��
 * [�@�@�\] ���͗p�X�g���[���W���C���g���擾����B
 *  Get input Stream Joint
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Stream Joint
 * [Function] Obtains Stream Joint for the input.
 */
SJ ADXT_GetInputSj(ADXT adxt);

/*	$func$ �����o�͊J�n�҂��̐ݒ�
 * [���@��] void ADXT_SetWaitPlayStart(ADXT adxt, Sint32 flg);
 * [���@��] adxt	: ADXT�n���h��
 *			flg		: 1=�E�F�C�g����A0=�����o�͂𑦍��ɊJ�n����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �����̏o�͂̊J�n�҂���ݒ肷��B
 *  Set waiting for starting to output the sound
 * [Inputs  ] adxt	: ADXT handle
 *			  flg	: 1=waits, 0=starts to output sound
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets waiting for starting to output the sound.
 */
void ADXT_SetWaitPlayStart(ADXT adxt, Sint32 flg);

/*	$func$ �����o�͊J�n�����������ۂ��̔���
 * [���@��] Sint32 ADXT_IsReadyPlayStart(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] 1:���������^0:������
 * [�@�@�\] �����o�͊J�n�̏������������ۂ��𔻒肷��B
 *  Check whether preparations completion
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Checks whether ADXT handle was preparations completion.
 */
Sint32 ADXT_IsReadyPlayStart(ADXT adxt);

/*	$func$ �ꎞ��~�̐ݒ�
 * [���@��] void ADXT_Pause(ADXT adxt, Sint32 sw);
 * [���@��] adxt	: ADXT�n���h��
 *			sw		: 1=�ꎞ��~�A0=�ĊJ
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �ꎞ��~���邩�ۂ���ݒ肷��B
 *  Pause/Continue
 * [Inputs  ] adxt	: ADXT handle
 *			  sw	: 1=pause, 0=continue
 * [Outputs ] None
 * [Return  ] None
 * [Function] Stops temporarily by a specified switch and release temporary 
 *			  standstill.
 */
void ADXT_Pause(ADXT adxt, Sint32 sw);

/*	$func$ �ꎞ��~��Ԃ̎擾
 * [���@��] Sint32 ADXT_GetStatPause(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �ꎞ��~��� 1=�ꎞ��~�A0=��ꎞ��~
 * [�֐��l] �Ȃ�
 * [�@�@�\] �ꎞ��~��Ԃ��擾����B
 *  Pause/Continue
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] 1=pause, 0=not pause
 * [Return  ] None
 * [Function] Obtains the status of pause.
 */
Sint32 ADXT_GetStatPause(ADXT adxt);

/*	$func$ �_�C���N�g�Z���h���x���̐ݒ�
 * [���@��] void ADXT_SetDrctLvl(ADXT adxt, Sint32 drctlvl)
 * [���@��] adxt	: ADXT�n���h��
 *			drctlvl	: �_�C���N�g�Z���h���x���@(0dB �` -45dB)
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �_�C���N�g�Z���h���x����ݒ肷��B
 */
void ADXT_SetDrctLvl(ADXT adxt, Sint32 drctlvl);

/*	$func$ �_�C���N�g�Z���h���x���̎擾
 * [���@��] Sint32 ADXT_GetDrctLvl(ADXT adxt)
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �_�C���N�g�Z���h���x���@(0dB �` -45dB)
 * [�@�@�\] �_�C���N�g�Z���h���x�����擾����B
 */
Sint32 ADXT_GetDrctLvl(ADXT adxt);

/*	$func$ �G�t�F�N�^�̐ݒ�
 * [���@��] void ADXT_SetFx(ADXT adxt, Sint32 fxch, Sint32 fxlvl);
 * [���@��] adxt	: ADXT�n���h��
 *			fxch	: �G�t�F�N�^�̓��̓`�����l���ԍ� (0�`15)
 *			fxlvl	: �G�t�F�N�^�̓��̓��x���@(0dB �` -45dB)
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G�t�F�N�^�ւ̏o�͂�ݒ肷��B
 *  Set the effect
 * [Inputs  ] adxt	: ADXT handle
 *			  fxch	: Input channel number to Effector (0-15)
 *			  fxlvl	: Input level to Effector(from 0 to -45[dB])
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets output to the effect.
 */
void ADXT_SetFx(ADXT adxt, Sint32 fxch, Sint32 fxlvl);

/*	$func$ �G�t�F�N�^�ݒ�l�̎擾
 * [���@��] void ADXT_GetFx(ADXT adxt, Sint32 *fxch, Sint32 *fxlvl);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] fxch	: �G�t�F�N�^�ւ̓��̓`�����l���ԍ� (0�`15)
 *			fxlvl	: �G�t�F�N�^�̓��̓��x���@(0dB �` -45dB)
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G�t�F�N�^�̐ݒ�l���擾����B
 *  Get the effect value
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] fxch	: Input channel number to Effector(0-15)
 *			  fxlvl	: Input level to Effector(from 0 to -45[dB])
 * [Return  ] None
 * [Function] Obtains the effect value.
 */
void ADXT_GetFx(ADXT adxt, Sint32 *fxch, Sint32 *fxlvl);

/*	$func$ �t�B���^�̐ݒ�
 * [���@��] void ADXT_SetFilter(ADXT adxt, Sint32 coff, Sint32 q);
 * [���@��] adxt	: ADXT�n���h��
 *			coff	: �J�b�g�I�t���g��
 *			q		: ��s�x
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �t�B���^�ւ̏o�͂�ݒ肷��B
 *  Set the filter
 * [Inputs  ] adxt	: ADXT handle
 *			  coff	: Cut off frequency
 *			  q		: 
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets the filter.
 */
void ADXT_SetFilter(ADXT adxt, Sint32 coff, Sint32 q);

/*	$func$ �t�B���^�ݒ�l�̎擾
 * [���@��] void ADXT_GetFilter(ADXT adxt, Sint32 *coff, Sint32 *q);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] coff	: �J�b�g�I�t���g��
 *			q		: ��s�x
 * [�֐��l] �Ȃ�
 * [�@�@�\] �t�B���^�ւ̏o�͒l���擾����B
 *  Get the filter value
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] coff	: Cut off frequency
 *			  q		: 
 * [Return  ] None
 * [Function] Obtains the filter value.
 */
void ADXT_GetFilter(ADXT adxt, Sint32 *coff, Sint32 *q);

/*	$func$ �g�����X�|�[�Y�̐ݒ�
 * [���@��] void ADXT_SetTranspose(ADXT adxt, Sint32 transps, Sint32 detune);
 * [���@��] adxt	: ADXT�n���h��
 *			transps	: �g�����X�|�[�Y��
 *			detune	: �f�`���[����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �g�����X�|�[�Y��ݒ肷��B
 *  Set transpose
 * [Inputs  ] adxt		: ADXT handle
 *			  transps	: Amount of transpose
 *			  detune	: Amount of detune
 * [Outputs ] None
 * [Return  ] None
 * [Function] Sets the transpose.
 */
void ADXT_SetTranspose(ADXT adxt, Sint32 transps, Sint32 detune);

/*	$func$ �g�����X�|�[�Y�̎擾
 * [���@��] void ADXT_GetTranspose(ADXT adxt, Sint32 *transps, Sint32 *detune);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] transps	: �g�����X�|�[�Y��
 *			detune	: �f�`���[����
 * [�֐��l] �Ȃ�
 * [�@�@�\] �g�����X�|�[�Y�ʂ��擾����B
 *  Get tanspose
 * [Inputs  ] adxt		: ADXT handle
 * [Outputs ] transps	: Amount of transpose
 *			  detune	: Amount of detune
 * [Return  ] None
 * [Function] Obtains the amount of transpose.
 */
void ADXT_GetTranspose(ADXT adxt, Sint32 *transps, Sint32 *detune);

/*	$func$ �G���[�֐��̓o�^
 * [���@��] void ADXT_EntryErrFunc(void (*func)(void *obj, Sint8 *msg),
 *																void *obj);
 * [���@��] func	: �G���[�����֐�
 *			obj		: �G���[�����֐��̑�1����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �G���[�����֐���o�^����B
 *  Entry error callback function
 * [Inputs  ] func	: Error handling function
 *			  obj	: First argument of error handling function
 * [Outputs ] None
 * [Return  ] None
 * [Function] Entry error callback function.
 */
void ADXT_EntryErrFunc(void (*func)(void *obj, Sint8 *msg), void *obj);

/*	$func$ �����f�[�^�̕���
 * [���@��] Sint32 ADXT_DiscardSmpl(ADXT adxt, Sint32 nsmpl)
 * [���@��] adxt	: ADXT�n���h��
 *			nsmpl	: �T���v����
 * [�o�@��] �Ȃ�
 * [�֐��l] �̂Ă��T���v����
 * [�@�@�\] �f�R�[�h���������f�[�^���̂Ă�B
 *  Discard sound data
 * [Inputs  ] adxt	: ADXT handle
 *			  nsmpl	: Number of sample
 * [Outputs ] None
 * [Return  ] sample number discarded
 * [Function] Discards sound data decoded.
 */
Sint32 ADXT_DiscardSmpl(ADXT adxt, Sint32 nsmpl);

/*	���g���C�񐔂̐ݒ�	*/
void ADXT_SetNumRetry(Sint32 num);

/* �w�b�_���̎擾 */
void ADXT_GetHdrInfo(Sint8 *buf, Sint32 bsize, ADXHINFO *hinfo);

/*	$func$ �t�@�C���ǂݍ��݃X�e�[�^�X�̎擾
 * [���@��] Sint32 ADXT_GetStatRead(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] 1=�ǂݍ��ݒ�/�ǂݍ��ݏ������A0=��ǂݍ��ݒ�/��ǂݍ��ݏ�����
 * [�@�@�\] �ǂݍ��ݏ�Ԃ��擾����
 */
Sint32 ADXT_GetStatRead(ADXT adxt);

/***
*			�t�B���^�쐬�p�R�[���o�b�N
*
*			�f�R�[�h���閈�ɓo�^���ꂽ�֐����Ăяo�����B
*			(*user_flt_cbf)(void *obj, Sint32 ch, void *data, Sint32 dtlen);
*			obj:	ADXT_EntryFltFunc�֐��̑�R����
*			ch:		�`�����l���ԍ��@(0:��, 1:�E)
*			data:	�W�J���ꂽ�f�[�^ (ADX�̏ꍇ�́A16bitPCM)
*			dtlen:	�W�J���ꂽ�f�[�^�̃o�C�g��
*			���@�U�����o�@�\�Ƃ͋��p�ł��Ȃ��B
**/

/*	�t�B���^�R�[���o�b�N�֐��̓o�^	*/
void ADXT_EntryFltFunc(ADXT adxt,
		void (*f)(void *obj, Sint32 ch, void *data, Sint32 dtlen), void *obj);

/* $func$ �f�R�[�h�T���v�����̎擾
 * [���@��] Sint32 ADXT_GetDecNumSmpl(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �f�R�[�h���������f�[�^�̑��T���v����
 * [�@�@�\] �f�R�[�h���������f�[�^�̑��T���v�������擾����B
 * [���@�l] ��Ԃ��A�Đ�������(ADXT_STAT_PREP)����Đ��I��(ADXT_STAT_PLAYEND)
 *			�܂ł̎��Ɏ擾�\�B
 *  Get a decoded sample number of sound data
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] decoded sample number of sound data
 * [Function] Obtains a decoded sample number of sound data.
 * [Remarks ] You can obtain a time between status of preparation
 *			  (ADXT_STAT_PREP) and status of play end(ADXT_STAT_PLAYEND).
 */
Sint32 ADXT_GetDecNumSmpl(ADXT adxt);

/***
*		�V�[�����X�A���Đ��@�\
*
*		�E���[�v�ݒ�̖����P����ADX �f�[�^�̂ݘA���Đ��\
*		�E�ő�16�t�@�C���܂œo�^�\
*
***/

/*	�ő�o�^�t�@�C����									*/
/*	Number of maximum files to entry 					*/
#define	ADXT_MAX_ENTRY_FILES		(16)

/*	$func$ �V�[�����X�A���Đ��t�@�C���̓o�^
 * [���@��] void ADXT_EntryFname(ADXT adxt, Sint8 *fname)
 * [���@��] adxt	: ADXT�n���h��
 *			fname	: �t�@�C����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �V�[�����X�A���Đ��p�̃t�@�C����o�^����B
 *			���[�v�ݒ�̂Ȃ��P����ADX�f�[�^�̂ݓo�^�ł���B
 *  Entry file for seamless continuous play
 * [Inputs  ] adxt	: ADXT handle
 *			  fname	: ADX File name
 * [Outputs ] None
 * [Return  ] None
 * [Function] Entry file for seamless continuous play.
 *			  You can only simple ADX data file without looping.
 */
void ADXT_EntryFname(ADXT adxt, Char8 *fname);

/*	$func$ �V�[�����X�A���Đ��T�u�t�@�C���̓o�^
 * [���@��] void ADXT_EntryAfs(ADXT adxt, Sint32 patid, Sint32 fid)
 * [���@��] adxt	: ADXT�n���h��
 *			patid	: �p�[�e�B�V����ID
 *			fid		: �t�@�C��ID
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �V�[�����X�A���Đ��p�̃T�u�t�@�C����o�^����B
 *			���[�v�ݒ�̂Ȃ��P����ADX�f�[�^�̂ݓo�^�ł���B
 *  Entry file for seamless continuous play
 * [Inputs  ] adxt	: ADXT handle
 *			  patid	: Partition ID
 *			  fid	: File ID
 * [Outputs ] None
 * [Return  ] None
 * [Function] Entry subfile for seamless continuous play.
 *			  You can only simple ADX data subfile without looping.
 */
void ADXT_EntryAfs(ADXT adxt, Sint32 patid, Sint32 fid);

/*	$func$ �V�[�����X�A���Đ��̊J�n
 * [���@��] void ADXT_StartSeamless(ADXT adxt)
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �V�[�����X�A���Đ����J�n����B
 *  Start seamless continuous play
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Start seamless continuous play.
 */
void ADXT_StartSeamless(ADXT adxt);

/*	$func$ �V�[�����X���[�v�Đ��̐ݒ�
 * [���@��] void ADXT_SetSeamlessLp(ADXT adxt, Sint32 flg)
 * [���@��] adxt	: ADXT�n���h��
 *			flg		: 0-���[�v�Đ����Ȃ�,1-���[�v�Đ�����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���݁A�o�^����Ă���t�@�C�����J��Ԃ��Đ�����B
 *			�t�@�C���̂��ׂẴf�[�^��ǂݏI���Ǝ����I�ɍēx�o�^�����B
 *  Set seamless loop play
 * [Inputs  ] adxt	: ADXT handle
 *			  flg	: 0-Off, 1-On
 * [Outputs ] None
 * [Return  ] None
 * [Function] You can play all entried files with looping.
 */
void ADXT_SetSeamlessLp(ADXT adxt, Sint32 flg);

/*	$func$ �V�[�����X���[�v�Đ��̊J�n
 * [���@��] void ADXT_StartFnameLp(ADXT adxt, Sint8 *fname)
 * [���@��] adxt	: ADXT�n���h��
 *			fname	: �t�@�C����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �w�肳�ꂽ�t�@�C�����J��Ԃ��Đ�����B
 *  Start seamless loop play
 * [Inputs  ] adxt	: ADXT handle
 *			  fname	: ADX File Name
 * [Outputs ] None
 * [Return  ] None
 * [Function] Start seamless loop plaing your specified file (fname).
 */
void ADXT_StartFnameLp(ADXT adxt, Char8 *fname);

/*	$func$ �V�[�����X�A���Đ��̉���
 * [���@��] void ADXT_ReleaseSeamless(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �V�[�����X�A���Đ��̉�������B
 *  Release seamless continuous play
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Release seamless continuous play.
 */
void ADXT_ReleaseSeamless(ADXT adxt);

/*	$func$ �o�^�t�@�C�����̎擾
 * [���@��] Sint32 ADXT_GetNumFiles(ADXT adxt)
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �o�^����Ă���t�@�C����
 * [�@�@�\] �o�^����Ă���t�@�C�������擾����B
 *  Get number of entried files
 * [Inputs  ] adxt	: ADXT handle
 * [Outputs ] None
 * [Return  ] Number of Entried Files
 * [Function] Get number of entried files
 */
Sint32 ADXT_GetNumFiles(ADXT adxt);

/*	�A���Đ��̐ݒ�@(1:����A0:���Ȃ�)	*/
void ADXT_SetLnkSw(ADXT adxt, Sint32 sw);

/*	�A���Đ��̎擾�@(1:����A0:���Ȃ�)	*/
Sint32 ADXT_GetLnkSw(ADXT adxt);

/*	�t�@�C���̓o�^�����Z�b�g(STOP��Ԃł̂ݗL��)	*/
void ADXT_ResetEntry(ADXT adxt);

/***
*			�U�����o�@�\
***/

/*	�U���擾�p��Ɨ̈�̑傫���̌v�Z	*/
Sint32 ADXT_CalcAmpWork(Sint32 maxnch);
/*	�U���擾�p��Ɨ̈�̐ݒ�	*/
void ADXT_SetAmpWork(ADXT adxt, void *work, Sint32 wksize);
/*	�U���̎擾	*/
Sint32 ADXT_GetAmplitude(ADXT adxt, Sint32 ch);
/*	�U���̎擾 (�����I�t�Z�b�g�w��t��)	*/
Sint32 ADXT_GetAmplitude2(ADXT adxt, Sint32 ch, Sint32 msec, Sint32 *msec2);

/*	�w�b�_���̋����}��	*/
void ADXT_InsertHdrSfa(ADXT adxt, Sint32 nch, Sint32 sfreq, Sint32 nsmpl);
/*	�^�C���I�t�Z�b�g�̐ݒ�	*/
void ADXT_SetTimeOfst(ADXT adxt, Sint32 ofst);

/***
*			Sofdec�p�g���֐�
***/

/*	V-Sync���荞�ݗp�֐�			*/
/*	Shinobi���ł́A���������Ɋ��荞�݂Ɏ����I�ɓo�^�����̂ŁA		*/
/*	�g�p���܂���BNaomi����Sofdec Movie���Đ�����ꍇ�ɂ́A			*/
/*	���̊֐���V-Sync���荞�݂�����s���Ă��������B						*/
void ADXT_VsyncProc(void);

/*	�����̒P�ʂ̐ݒ�@(0:Sfreq(Audio), 1:V-Sync(NTSC), 2:V-sync(PAL)	*/
void ADXT_SetTimeMode(Sint32 mode);

/* ADX�w�b�_�̔��� */
Sint32 ADXT_IsHeader(Sint8 *adr, Sint32 siz, Sint32 *hdrsiz);

/* ADX�I���R�[�h�̔��� */
Sint32 ADXT_IsEndcode(Sint8 *adr, Sint32 siz, Sint32 *endsiz);
/*
	adr   �F�I������|�C���^(ADX�f�[�^��36�o�C�g���E)
	siz   �F�I������T�C�Y (����ɕK�v�ȃT�C�Y�͍��X���o�C�g
			��������܂��񂪁A�t�@�C�����[�h���āA�o�b�t�@��
			�~�ς���Ă���T�C�Y����͂��܂�)
	ndsiz�F�I���R�[�h�T�C�Y�i�t�b�^�T�C�Y�j
*/

/* �����f�[�^�̋����}�� */
Sint32 ADXT_InsertSilence(ADXT adxt, Sint32 nch, Sint32 nsmpl);
/*
	nsmpl �@�F�}���v���T���v���� [sample/1ch]
	�֐��l  �F�}�����s�T���v���� (0 �` nsmpl)
			  ADXT���͗pSJ�ɏ\���ȋ󂫂������ nsmpl �̒[����
			  �؂�̂Ă��l���Ԃ�B
*/

/*			�������m�����o�̓X�C�b�`�̐ݒ�	
[��  ��]	void ADXT_SetOutputMono(Sint32 flag);
[��  ��]	Sint32 flag		�������m�����o�̓t���O(OFF:0, ON:1)
[�߂�l]	�Ȃ�					
[�@  �\]	�X�e���I�f�[�^�������I�Ƀ��m�����f�[�^�Ƃ��ďo�͂���B
[���@�l]	
*/
void ADXT_SetOutputMono(Sint32 flag);

/***
*		AHX �p�֐�
*		Functions for AHX
***/

/*	$func$ AHX�̑g�ݍ���
 * [���@��] void ADXT_AttachAhx(ADXT adxt, void *work, Sint32 worksize);
 * [���@��] adxt	: ADXT�n���h��
 *			work	: AHX���[�N�̈�
 *			worksize: AHX���[�N�̈�̃T�C�Y
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] AHX�̑g�ݍ��݂��s���AAHX�̗��p���\�ɂ���B
 *  Attach AHX
 * [Inputs  ] adxt    : ADXT handle
 *			  work    : Working area for AHX
 *			  worksize: Size of AHX working area(byte)
 * [Outputs ] None
 * [Return  ] None
 * [Function] Attach AHX, Use of AHX is attained.
 */
void ADXT_AttachAhx(ADXT adxt, void *work, Sint32 worksize);

/*	$func$ AHX�̕���
 * [���@��] void ADXT_DetachAhx(ADXT adxt);
 * [���@��] adxt	: ADXT�n���h��
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] AHX�𕪗����AAHX�̗��p����߂�B
 *  Detach AHX
 * [Inputs  ] adxt    : ADXT handle
 * [Outputs ] None
 * [Return  ] None
 * [Function] Detach AHX, Unuse of AHX is attained.
 */
void ADXT_DetachAhx(ADXT adxt);

void ADXT_SetKeyString(ADXT adxt, Char8 *str);
void ADXT_SetDefKeyString(Char8 *str);

void ADXT_SetKeyString(ADXT adxt, Char8 *str);
void ADXT_SetDefKeyString(Char8 *str);

/***
*		ADX�}�l�[�W���֐�
*		ADX Manager Functions
***/

/*	ADX�X���b�h�̏�����					*/
/*	Initialization of ADX Thread 		*/
void ADXM_SetupThrd(ADXM_TPRM *tprm);
/*	ADX�X���b�h�̏I������				*/
/*	Termination of ADX Thread Extended 	*/
void ADXM_ShutdownThrd(void);

/*	ADX�X���b�h�̏�����(�g����)				*/
/*	Initialization of ADX Thread Extended 	*/
void ADXM_SetupThrdEx(ADXM_TPRM_EX *tprm);
/*	ADX�X���b�h�̏I������(�g����)			*/
/*	Termination of ADX Thread Extended 		*/
void ADXM_ShutdownThrdEx(void);

/*	���[�UVSYNC�X���b�h�ւ̊֐��o�^				*/
/*	Set callback function on UsrVsync Thread	*/
void ADXM_SetCbUsrVsync(Bool (*func)(void *obj), void *obj);
/*	���[�U�A�C�h���X���b�h�ւ̊֐��o�^			*/
/*	Set callback function on UsrIdle Thread		*/
void ADXM_SetCbUsrIdle(Bool (*func)(void *obj), void *obj);
/*	���[�U�A�C�h���T�[�o�̋�؂菈��						*/
/*	Execution UsrIdle Thread for termination of function	*/
void ADXM_GotoUsrIdleBdr(void);
/*	UsrVsync�T�[�o�֐��̎��s	*/
/*	Execution UsrVsync Server	*/
Sint32 ADXM_ExecSvrUsrVsync(void);
/*	UsrIdle�T�[�o�֐��̎��s		*/
/*	Execution UsrIdle Server	*/
Sint32 ADXM_ExecSvrUsrIdle(void);

/*	�G���[�֐��̓o�^								*/
void ADXM_SetCbErr(void (*fn)(void *obj, Char8 *emsg), void *obj);
/*	���ב���p�֐�	*/
void ADXM_SetCbSleepMwIdle(void (*fn)(void *), void *obj);
/*	�X���b�h���������s��ꂽ���ۂ��̔���	*/
Bool ADXM_IsSetupThrd(void);

/*	�X���b�h�̃��b�N	*/
void ADXM_Lock(void);
/*	�X���b�h�̃A�����b�N	*/
void ADXM_Unlock(void);
/* ���b�N���x���̎擾 */
Sint32 ADXM_GetLockLevel(void);

/*	V-Sync�҂��֐�	*/
void ADXM_WaitVsync(void);

/*	V-Sync���荞�݃n���h��	*/
Sint32 ADXM_ExecVint(Sint32 arg);

/*	���C���X���b�h�ŌĂяo���֐�	*/
Sint32 ADXM_ExecMain(void);

/***
*		ADXM_SetupThrd�����s���Ȃ��Ƃ��Ɏg�p����֐�
***/
/*	Vsync���ɌĂяo���֐�	*/
Sint32 ADXM_ExecSvrVsync(void);
/*	���C�����[�v���ŌĂяo���֐�	*/
Sint32 ADXM_ExecSvrMain(void);
/*	�~�h���E�F�A�p�X���b�h�ŌĂяo���֐�	*/
Sint32 ADXM_ExecSvrMwIdle(void);

/*	���ׂẴT�[�o�������Ăяo���֐�	*/
Sint32 ADXM_ExecSvrAll(void);

#ifdef __cplusplus
}
#endif

#endif

/* end of file */
