#include <curses.h>

#include "jconsole_Console.h"

JNIEXPORT void JNICALL Java_jconsole_Console_initialize(JNIEnv *env, jclass class)
{
	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	set_escdelay(25);
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
    jchar result = '\0';

    do {
        int ch = getch();

		// esc or alt pressed
		if (ch == 27) {

			nodelay(stdscr, true);
			ch = getch();
			nodelay(stdscr, false);

			// esc was pressed (ignore alt)
			if (ch == ERR) {
				result = L'\u241B';
			} else {
				result = (jchar)ch;
			}

        // no special character
		} else if (ch <= 127) {
            result = (jchar) ch;

        // special character, convert to unicode representation
        } else {
            switch (ch) {
                case KEY_LEFT:
                    result = L'\u2190';
                    break;

                case KEY_UP:
                    result = L'\u2191';
                    break;

                case KEY_RIGHT:
                    result = L'\u2192';
                    break;

                case KEY_DOWN:
                    result = L'\u2193';
                    break;
            }
        }
    } while (result == '\0');

    return result;
}
