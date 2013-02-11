/*
	2011/02/10 new

	http://d.hatena.ne.jp/higedice/

	http://msdn.microsoft.com/ja-jp/library/cc422072.aspx
*/


#include <stdio.h>
#include <string.h>

#include <windows.h>


void printUsage(void);
void printError(const char *s);
HINSTANCE doBackGround(const char *command, const char *opt);



#define PROGRAM_NAME "startbg.exe"
#define MAX_OPTION_LENGTH 1024
#define MAX_MSG_LENGTH 1024

long main(int argc, char* argv[])
{
	char opt[MAX_MSG_LENGTH] = "";
	char errMsg[MAX_MSG_LENGTH] = "";
	int len;
	int i;
	HINSTANCE h;


	if ( argc < 2 ) {
		printUsage();
		return -1;
	}

	for ( i = 2, len = 1; i < argc; i++ ) {
		if ( strlen(argv[i]) +  len + 1  > MAX_OPTION_LENGTH ) {
			printError("Too Long Command.");
			return -1;
		}

		strcat( opt, " " );
		strcat( opt, argv[i] );
		len += strlen(argv[i]);
	}

	h = doBackGround( argv[1], opt );

	if ( (int)h > 32 ) {	/* ����I�� */
		return 0;
	}

	switch ( (int)h ) {
		case 0:
			printError("�������܂��̓��\�[�X���s�����Ă��܂��B");
			break;
		case ERROR_FILE_NOT_FOUND:
			printError("�w�肳�ꂽ�t�@�C����������܂���ł����B");
			break;
		case ERROR_PATH_NOT_FOUND:
			printError("�w�肳�ꂽ�p�X��������܂���ł����B");
			break;
		case ERROR_BAD_FORMAT:
			printError(".exe �t�@�C���������ł��BWin32 �� .exe �ł͂Ȃ����A.exe �C���[�W���ɃG���[������܂��B");
			break;
		case SE_ERR_ACCESSDENIED:
			printError("�I�y���[�e�B���O�V�X�e�����A�w�肳�ꂽ�t�@�C���ւ̃A�N�Z�X�����ۂ��܂����B");
			break;
		case SE_ERR_ASSOCINCOMPLETE:
			printError("�t�@�C�����̊֘A�t�����s���S�܂��͖����ł��B");
			break;
		case SE_ERR_DDEBUSY:
			printError("�ق��� DDE �g�����U�N�V���������ݏ������Ȃ̂ŁADDE �g�����U�N�V�����������ł��܂���ł����B");
			break;
		case SE_ERR_DDEFAIL:
			printError("DDE �g�����U�N�V���������s���܂����B");
			break;
		case SE_ERR_DDETIMEOUT:
			printError("�v�����^�C���A�E�g�����̂ŁADDE �g�����U�N�V�����������ł��܂���ł����B");
			break;
		case SE_ERR_DLLNOTFOUND:
			printError("�w�肳�ꂽ�_�C�i�~�b�N�����N���C�u�����iDLL�j��������܂���ł����B");
			break;
		/*
		case SE_ERR_FNF:		// ERROR_FILE_NOT_FOUND �Ɠ����悤���B
			printError("�w�肳�ꂽ�t�@�C����������܂���ł����B");
			break;
		*/
		case SE_ERR_NOASSOC:
			printError("�w�肳�ꂽ�t�@�C���g���q�Ɋ֘A�t����ꂽ�A�v���P�[�V����������܂���B"
						"����\�ł͂Ȃ��t�@�C����������悤�Ƃ����ꍇ���A���̃G���[���Ԃ�܂��B");
			break;
		case SE_ERR_OOM:
			printError("�������������̂ɏ\���ȃ�����������܂���B");
			break;
		/*
		case SE_ERR_PNF:	// ERROR_PATH_NOT_FOUND �Ɠ����悤��
			printError("�w�肳�ꂽ�p�X���A������܂���ł����B");
			break;
		*/
		case SE_ERR_SHARE:
			printError("���L�ᔽ���������܂����B");
			break;
		default:
			sprintf(errMsg, "�z�肵�Ȃ��G���[���������܂����B�G���[�ԍ��F%d", (int)h);
			printError(errMsg);
	}

	return -1;
}


void printError(const char *s) {
	fprintf(stderr, "%s: %s\n", PROGRAM_NAME, s);
}


void printUsage(void) {
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: startbg [command] [options]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "This program runs another following Windows execute file in the background\n");
	fprintf(stderr, "like an ampersand (&) is at the end of the command line on UNIX shells.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "The called process runs in the current directory.\n");
	fprintf(stderr, "So that directory is ROCKED while the sub process is running.\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "http://d.hatena.ne.jp/higedice/\n");
}


HINSTANCE doBackGround(const char *command, const char *opt) {

	HINSTANCE h;

	h = ShellExecute(NULL, "open", command, opt, NULL, SW_SHOW);

	return h;
}



