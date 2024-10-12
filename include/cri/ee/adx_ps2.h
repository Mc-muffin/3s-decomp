#ifndef _ADX_PS2_H_INCLUDED
#define _ADX_PS2_H_INCLUDED
/************************************************************************/
/*                                                                      */
/*              ADX function for Playstation2(PS2)                      */
/*                                                                      */
/*                  Copyright (c) 2001 CRI-MW                           */
/*                  2001.7.9 written by O.Sato                          */
/*                                                                      */
/************************************************************************/

#include "cri_xpt.h"
#include "cri_adxt.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/*      �萔�}�N��                                                      */
/*      Macro Constant                                                  */
/************************************************************************/
#define ADXPS2_VER	"2.33"		// "ADXPS2" Version number

#define	ADXPS2_RDMODE_NOWAIT	(0)		/* �m�[�E�F�C�g�ǂݍ��݃��[�h	*/
#define	ADXPS2_RDMODE_WAIT		(1)		/* �E�F�C�g�ǂݍ��݃��[�h		*/

#define ADXPS2_PRIO_LOCK	 (1) /* ���b�N���̃X���b�h�v���C�I���e�B	*/
#define ADXPS2_PRIO_SAFE	 (8) /* �Z�[�t�X���b�h�v���C�I���e�B    	*/
#define ADXPS2_PRIO_VSYNC	(16) /* Vsync�T�[�o�p�X���b�h�v���C�I���e�B	*/
#define ADXPS2_PRIO_MAIN	(24) /* �ʏ펞���C���X���b�h�v���C�I���e�B	*/
#define ADXPS2_PRIO_MWIDLE	(25) /*�A�C�h���X���b�h�v���C�I���e�B*/

#define ADXPS2_DEBUG_LEVEL_ALL		(0)	/* �S�Ẵf�o�b�O�o�͂��s�� 	*/
#define ADXPS2_DEBUG_LEVEL_ERROR	(1)	/* �G���[�̂݃f�o�b�O�o�͂��s��	*/
#define ADXPS2_DEBUG_LEVEL_NOTHING	(2)	/* �f�o�b�O�o�͂��s��Ȃ�		*/

/*	�t�@�C���L���b�V�����T�C�Y�̌v�Z									*/
/*	Calc size of file cache information									*/
#define	ADXPS2_CALC_FCSIZE_DVD(nfile, maxflen)	(nfile*sizeof(ADXPS2_FC_DVD)+nfile*(maxflen+1))
#define	ADXPS2_CALC_FCSIZE_HOST(nfile, maxflen)	(nfile*sizeof(ADXPS2_FC_HOST)+nfile*(maxflen+1))

/*	�t�@�C���L���b�V�����Ɋւ���K��l								*/
/*	Default value for file cache information							*/
#define	ADXPS2_DEF_NUM_FILE_DVD	 (40)	/* Number of file(for DVD)		*/
#define	ADXPS2_DEF_NUM_FILE_HOST (13)	/* Number of file(for Host)	  	*/
#define	ADXPS2_DEF_MAXFLEN_DVD	 (128)	/* File length of file(for DVD)	*/
#define	ADXPS2_DEF_MAXFLEN_HOST  (128)	/* File length of file(for Host)*/

#define	ADXPS2_DEF_FCSIZE_DVD	(ADXPS2_CALC_FCSIZE_DVD(ADXPS2_DEF_NUM_FILE_DVD, ADXPS2_DEF_MAXFLEN_DVD))
#define	ADXPS2_DEF_FCSIZE_HOST	(ADXPS2_CALC_FCSIZE_HOST(ADXPS2_DEF_NUM_FILE_HOST, ADXPS2_DEF_MAXFLEN_HOST))

/************************************************************************/
/*      �f�[�^�^                                                        */
/*      Data type declaration                                           */
/************************************************************************/
/* DVD�t�@�C�����L���b�V��											*/
/* DVD File information cache											*/
typedef struct {
	Sint32	lsn;								/* Logical Sector num 	*/
	Sint32	size;								/* File size          	*/
} ADXPS2_FC_DVD;

/* HTCI�t�@�C�����L���b�V��											*/
/* HTCI File information cache											*/
typedef struct {
	Sint32	fd;									/* File descripter		*/
	Sint32	size;								/* File size      		*/
} ADXPS2_FC_HOST;

/*	DVD�t�@�C���V�X�e���̃Z�b�g�A�b�v�p�����[�^�\����					*/
/*	Parameter structure DVD setup function								*/
typedef struct _adxps2_sprm_dvd {
	Sint8	*rtdir;						/*	���[�g�f�B���N�g����		*/
	Sint32	rdmode;						/*	�ǂݍ��݃��[�h				*/
	Sint32	nrtry;						/*	���g���C��(0:255��)		*/
	Sint32	speed;						/*	��]���x					*/
	Sint32	dtype;						/*	�f�[�^�^�C�v(2048byte�Ȃ�)	*/
} ADXPS2_SPRM_DVD;

/*	�z�X�g�t�@�C���V�X�e���̃Z�b�g�A�b�v�p�����[�^�\����				*/
/*	Parameter structure Host setup function								*/
typedef struct _adxps2_sprm_host {
	Sint8	*rtdir;						/*	���[�g�f�B���N�g����		*/
	Sint32	rdmode;						/*	�ǂݍ��݃��[�h				*/
} ADXPS2_SPRM_HOST;

/*** �ȉ��A���o�[�W�����݊��p ***/
/*	DVD/�z�X�g�t�@�C���V�X�e���̃t�@�C�����L���b�V���p�����[�^�\����	*/
/*	Parameter structure DVD/Host file cache								*/
typedef struct _adxps2_fcprm {
	Sint8	*flist;						/*	�t�@�C�����X�g�t�@�C����	*/
	Sint32	maxflen;					/*	�t�@�C�����̍ő咷			*/
	Sint8	*fcbuf;						/*	�t�@�C���L���b�V���̈�		*/
	Sint32	fcsize;						/*	�t�@�C���L���b�V���T�C�Y	*/
} ADXPS2_FCPRM;

/*	PS2�p�X���b�h�p�����[�^�\����		*/
/*	Parameter structure of Thread Param	*/
typedef struct {
	int	prio_lock;		// Main Thread Lock priority
	int	prio_safe;		// Safe Thread priority
	int	prio_adx;		// ADX Thread priority
	int	prio_main;		// Main Thread Normary priority
} ADXPS2_TPRM;

/***
*       PS2 ��p�֐�
*       Functions for PS2
***/

/* $func$ DVD�t�@�C���V�X�e���̃Z�b�g�A�b�v
 * [���@��] void ADXT_SetupDvdFs(ADXT_SPRM *sprm);
 * [���@��] sprm : DVD/Host�t�@�C���V�X�e���Z�b�g�A�b�v�p�����[�^�\����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] DVD�t�@�C���V�X�e���̃Z�b�g�A�b�v����B
 *			�t�@�C�����L���b�V���O����B
 *			������NULL���w�肷��ƃL���b�V���O���Ȃ��B
 *			ADX_Init�֐������O��1�񂾂��ĂԂ��ƁB
 *  Setup of Dvd File Sysytem
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Setup DVD file system.
 *			  This function shuld be called before ADXT_Init().
 */
void ADXPS2_SetupDvdFs(ADXPS2_SPRM_DVD *sprmd);

/* $func$ �z�X�g�t�@�C���V�X�e���̃Z�b�g�A�b�v
 * [���@��] void ADXT_SetupHostFs(ADXT_SPRM *sprm);
 * [���@��] sprm : DVD/Host�t�@�C���V�X�e���Z�b�g�A�b�v�p�����[�^�\����
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �z�X�g�t�@�C���V�X�e���̃Z�b�g�A�b�v����B
 *			�t�@�C�����L���b�V���O����B
 *			������NULL���w�肷��ƃL���b�V���O���Ȃ��B
 *			ADX_Init�֐������O��1�񂾂��ĂԂ��ƁB
 *  Setup of Host File Sysytem
 * [Inputs  ] None
 * [Outputs ] None
 * [Return  ] None
 * [Function] Setup Host file system.
 * 			  This function shuld be called before ADXT_Init().
 */
void ADXPS2_SetupHostFs(ADXPS2_SPRM_HOST *sprmh);

/* $func$ �������t�@�C���V�X�e���̃Z�b�g�A�b�v
 * [���@��] void ADXPS2_SetupMemFs(void *sprm);
 * [���@��] sprm : ���g�p (NULL)
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] �������t�@�C���V�X�e���̃Z�b�g�A�b�v�B
 *  Setup of Memory File Sysytem
 * [Inputs  ] sprm : unused. (NULL)
 * [Outputs ] None
 * [Return  ] None
 * [Function] Setup Memory file system.
 * 			  This function shuld be called before ADXT_Init().
 */
void ADXPS2_SetupMemFs(void *prm);

/*	�t�@�C���|�C���^�̃L���b�V���O(DVD�p)								*/
Sint32 ADXPS2_LoadFcacheDvd(ADXPS2_FCPRM *fcprm);

/*	�ǂݍ��݃��[�h�̐ݒ�(DVD�p)											*/
void ADXPS2_SetRdModeDvd(ADXPS2_SPRM_DVD *sprmd);

/*	�t�@�C�����L���b�V�����݂̔���(DVD�p)								*/
Sint32 ADXPS2_IsExistFcacheDvd(Sint8 *fname);

/*	�t�@�C���I�[�v�����[�h�̐ݒ�(Host�p)								*/
void ADXPS2_SetRdModeHost(ADXPS2_SPRM_HOST *sprmh);

/*	�t�@�C���|�C���^�̃L���b�V���O(Host�p)								*/
Sint32 ADXPS2_LoadFcacheHost(ADXPS2_FCPRM *fcprm);

/*	�t�@�C�����L���b�V�����݂̔���(Host�p)							*/
Sint32 ADXPS2_IsExistFcacheHost(Sint8 *fname);

/*	�f�o�b�O�o�̓��x���̐ݒ�											*/
void ADXPS2_SetOutputDebugLevel(Sint32 lv);

/*	V-SYNC���荞�ݏ���													*/
/*	���[�U�[��V-Sync���荞�ݏ�������Ăяo�����߂̃G���g���B			*/
/*	�ʏ�g�p���Ȃ��B													*/
int ADXPS2_VsyncCallback(int arg);

/*	���荞�݃n���h����o�^���Ȃ���										*/
void ADXPS2_RestoreVsyncCallback(void);

/*	�T�[�o�[�̎��s														*/
/*	�ʏ�͎g�p���Ȃ��B													*/
/*	ADXPS2_SetupUsvr���g�p��A���C���X���b�h�������I�Ɏ��s����B		*/
void ADXPS2_ExecServer(void);

/*** �ȉ��A���o�[�W�����݊��p ***/
/*	�X���b�h�̃Z�b�g�A�b�v												*/
/*	ADX�T�[�o�֐���V-Sync���荞�݂ŌĂяo�����߂̃X���b�h�̏�����		*/
void ADXPS2_SetupThrd(ADXPS2_TPRM *tprm);

/*	�X���b�h�̃V���b�g�_�E��											*/
void ADXPS2_ShutdownThrd(void);

/*	�X���b�h�̃��b�N													*/
void ADXPS2_Lock(void);

/*	�X���b�h�̃��b�N����												*/
void ADXPS2_Unlock(void);

/* Unused */
void ADXPS2_SetupUsvr(void);
void ADXPS2_Shutdown(void);

/* $func$ �{�C�X�̃Z�b�g�A�b�v
 * [���@��] void ADXPS2_SetupVoice(Sint32 nste, Sint32 nmono);
 * [���@��] nste  : �Đ�����X�e���I�̐�
 *          nmono : �Đ����郂�m�����̐�
 * [�o�@��] �Ȃ�
 * [�֐��l] �Ȃ�
 * [�@�@�\] ���͂��ꂽ�X�e���I�E���m�����̐��ɍ��킹�Ďg�p����{�C�X��
 *			�Z�b�g�A�b�v����B
 *  Setup voice resource
 * [Inputs  ] nste  : Number of stereo
 *            nmono : Number of monoral
 * [Outputs ] None
 * [Return  ] None
 * [Function] Setup voice resource from input number of stereo and monoral.
 */
void ADXPS2_SetupVoice(Sint32 nste, Sint32 nmono);

/***
*			PS2��p�֐�(ADXM)
***/

/*	V-Sync���荞�݃n���h��												*/
int ADXPS2_ExecVint(int arg);
/*	V-Sync�҂��֐�														*/
void ADXPS2_WaitVsync(void);
/*	V-Sync���ɌĂ΂��֐�												*/
Bool ADXPS2_ExecServerEx(void *obj);

/* ���C���X���b�h�̃X���[�v */
void ADXPS2_SleepMainThrd(void);
/* ���C���X���b�h�̋N�� */
void ADXPS2_WakeupMainThrd(void);
/*	�A�C�h���X���b�h�̃��W���[��	*/
void ADXPS2_ResumeIdleThrd(void);


/***
*			�f�o�b�O�p
***/

/*	EE-IOP�Ԃ̃f�[�^���ʃ`�F�b�N�֐�	*/
Sint32 ADXPS2_GetNumDataSjtmp(ADXT adxt, Sint32 chno);
Sint32 ADXPS2_GetNumRoomSjtmp(ADXT adxt, Sint32 chno);
Sint32 ADXPS2_GetNumDataSjiop(ADXT adxt, Sint32 chno);
Sint32 ADXPS2_GetNumRoomSjiop(ADXT adxt, Sint32 chno);

/* Dual Layer DVD */
void ADXPS2_SetDvdLayer(Sint32 layer);
Sint32 ADXPS2_GetDvdLayer(void);


#ifdef __cplusplus
}
#endif

#endif

/* end of file */
