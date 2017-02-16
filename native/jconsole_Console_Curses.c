#include <curses.h>

#include "jconsole_Console.h"

JNIEXPORT void JNICALL Java_jconsole_Console_initialize(JNIEnv *env, jclass class)
{
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
}

JNIEXPORT void JNICALL Java_jconsole_Console_shutdown(JNIEnv *env, jclass class)
{
	endwin();
}

JNIEXPORT void JNICALL Java_jconsole_Console_clear(JNIEnv *env, jclass class)
{
	wclear(stdscr);
}

JNIEXPORT void JNICALL Java_jconsole_Console_print(JNIEnv *env, jclass class, jstring string)
{
	jboolean iscopy;
	const char *text = (*env)->GetStringUTFChars(env, string, &iscopy);
	printw("%s", text);
	refresh();
}

JNIEXPORT void JNICALL Java_jconsole_Console_showCursor(JNIEnv *env, jclass class, jboolean show)
{
	if (show == JNI_TRUE) {
		curs_set(1);
	} else {
		curs_set(0);
	}
}

JNIEXPORT void JNICALL Java_jconsole_Console_moveCursor(JNIEnv *env, jclass class, jint x, jint y)
{
	wmove(stdscr, y, x);
	refresh();
}

JNIEXPORT jchar JNICALL Java_jconsole_Console_readCharacter(JNIEnv *env, jclass class)
{
	int c = wgetch(stdscr);
	return c;
}
