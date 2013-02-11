/*
	2010/05/15 new
	2010/06/05 Sleep中に1秒ごとに文字を印字するオプションを追加
	2010/07/02 使い方メッセージに作者のブログのURLを追加
	2012/03024 Linux と Mac OS X に対応

	http://d.hatena.ne.jp/higedice/
*/


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifdef _WIN32 // _WIN32 is defined by all Windows 32 compilers, but not by others.
#include <windows.h>
#elif __unix
#include <unistd.h>
#else
#endif


void printUsage(void);
void printError(const char *s);
long makeItSleep(long mSecond, const char *progress);



#define PROGRAM_NAME "sleepsec"


int main(int argc, char* argv[])
{
	long wait;
	char *progress;

	if ( argc < 2 || argc > 3 ) {
		printUsage();
		return -1;
	}

	wait = strtol(argv[1], NULL, 10);
	if ( wait == 0 ) {
		printUsage();
		return -2;
	}
	else if (wait == LONG_MAX) {
		printError("Too Long Time.");
		printUsage();
		return -3;
	}
	else if (wait < 1 || wait == LONG_MIN) {
		printError("Too Minimal Time.");
		printUsage();
		return -4;
	}

	if ( argc == 3 ) {
		progress = argv[2];
		if ( strlen( progress ) > 1) {
			printError("Progress Charactor is too long.");
			printUsage();
			return -5;
		}
	}
	else {
		progress = "";
	}

	wait = atol(argv[1]);

	if ( strlen( progress ) > 0 ) {
		printf("%s: Wait %ld seconds...\n", PROGRAM_NAME, wait);
	}

	makeItSleep( wait, progress );

	if ( strlen( progress ) > 0 ) {
		printf(" Done.\n");
	}

	return 0;
}


void printError(const char *s) {
	fprintf(stderr, "%s: %s\n", PROGRAM_NAME, s);
}


void printUsage(void) {
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage: sleepsec [Second] [Progress Charactor]\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "http://d.hatena.ne.jp/higedice/ \n");
}


long makeItSleep(long mSecond, const char *progress) {

	long i;

	// 1秒Sleepするのを指定回数実行する

	if ( strlen(progress) > 0 ) {
		for ( i = 0; i < mSecond; i++) {
			printf(progress);
#ifdef _WIN32
			Sleep(1000);
#elif __unix
			sleep(1);
			fflush(stdout);
#else
			sleep(1);
			fflush(stdout);
#endif
		}
	}
	else {
		for ( i = 0; i < mSecond; i++) {
#ifdef _WIN32
			Sleep(1000);
#elif __unix
			sleep(1);
#else
			sleep(1);
#endif
		}
	}

	return mSecond;
}

