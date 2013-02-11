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

	if ( (int)h > 32 ) {	/* 正常終了 */
		return 0;
	}

	switch ( (int)h ) {
		case 0:
			printError("メモリまたはリソースが不足しています。");
			break;
		case ERROR_FILE_NOT_FOUND:
			printError("指定されたファイルが見つかりませんでした。");
			break;
		case ERROR_PATH_NOT_FOUND:
			printError("指定されたパスが見つかりませんでした。");
			break;
		case ERROR_BAD_FORMAT:
			printError(".exe ファイルが無効です。Win32 の .exe ではないか、.exe イメージ内にエラーがあります。");
			break;
		case SE_ERR_ACCESSDENIED:
			printError("オペレーティングシステムが、指定されたファイルへのアクセスを拒否しました。");
			break;
		case SE_ERR_ASSOCINCOMPLETE:
			printError("ファイル名の関連付けが不完全または無効です。");
			break;
		case SE_ERR_DDEBUSY:
			printError("ほかの DDE トランザクションが現在処理中なので、DDE トランザクションを完了できませんでした。");
			break;
		case SE_ERR_DDEFAIL:
			printError("DDE トランザクションが失敗しました。");
			break;
		case SE_ERR_DDETIMEOUT:
			printError("要求がタイムアウトしたので、DDE トランザクションを完了できませんでした。");
			break;
		case SE_ERR_DLLNOTFOUND:
			printError("指定されたダイナミックリンクライブラリ（DLL）が見つかりませんでした。");
			break;
		/*
		case SE_ERR_FNF:		// ERROR_FILE_NOT_FOUND と同じようだ。
			printError("指定されたファイルが見つかりませんでした。");
			break;
		*/
		case SE_ERR_NOASSOC:
			printError("指定されたファイル拡張子に関連付けられたアプリケーションがありません。"
						"印刷可能ではないファイルを印刷しようとした場合も、このエラーが返ります。");
			break;
		case SE_ERR_OOM:
			printError("操作を完了するのに十分なメモリがありません。");
			break;
		/*
		case SE_ERR_PNF:	// ERROR_PATH_NOT_FOUND と同じようだ
			printError("指定されたパスが、見つかりませんでした。");
			break;
		*/
		case SE_ERR_SHARE:
			printError("共有違反が発生しました。");
			break;
		default:
			sprintf(errMsg, "想定しないエラーが発生しました。エラー番号：%d", (int)h);
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



