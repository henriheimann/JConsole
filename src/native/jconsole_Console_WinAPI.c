#include <windows.h>

#include "jconsole_Console.h"

HANDLE hStdout;
HANDLE hStdin;

DWORD initialConsoleMode;

JNIEXPORT void JNICALL Java_jconsole_Console_initialize(JNIEnv *env, jclass class)
{
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleOutputCP(CP_UTF8);

	GetConsoleMode(hStdin, &initialConsoleMode);

	DWORD updatedConsoleMode = initialConsoleMode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	SetConsoleMode(hStdin, updatedConsoleMode);
}

JNIEXPORT void JNICALL Java_jconsole_Console_shutdown(JNIEnv *env, jclass class)
{

	SetConsoleMode(hStdin, initialConsoleMode);
}

JNIEXPORT void JNICALL Java_jconsole_Console_clear(JNIEnv *env, jclass class)
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) {
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(hStdout, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) {
		return;
	}

	if (!GetConsoleScreenBufferInfo(hStdout, &csbi)) {
		return;
	}

	if (!FillConsoleOutputAttribute(hStdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) {
		return;
	}

	SetConsoleCursorPosition(hStdout, coordScreen);
}

JNIEXPORT void JNICALL Java_jconsole_Console_print(JNIEnv *env, jclass class, jstring string)
{
	DWORD written;

	jboolean iscopy;
	const char *text = (*env)->GetStringUTFChars(env, string, &iscopy);

	if (!WriteConsoleA(hStdout, text, (*env)->GetStringUTFLength(env, string), &written, NULL)) {
		return;
	}
}

JNIEXPORT void JNICALL Java_jconsole_Console_showCursor(JNIEnv *env, jclass class, jboolean show)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;

	if (show == JNI_TRUE) {
		info.bVisible = TRUE;
	} else {
		info.bVisible = FALSE;
	}

	SetConsoleCursorInfo(hStdout, &info);
}

JNIEXPORT void JNICALL Java_jconsole_Console_moveCursor(JNIEnv *env, jclass class, jint x, jint y)
{
	COORD coord = { x, y };

	if (!SetConsoleCursorPosition(hStdout, coord)) {
		return;
	}
}

JNIEXPORT jchar JNICALL Java_jconsole_Console_readCharacter(JNIEnv *env, jclass class)
{
	char c = '\0';
	DWORD cCharsRead;

	WaitForSingleObject(hStdin, INFINITE);
	ReadConsoleA(hStdin, &c, 1, &cCharsRead, NULL);

	return c;
}
