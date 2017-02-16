package jconsole;

/**
 * This class provides platform-independent access to lowlevel console functions.
 *
 * <p>The underlying library is initialized automatically after the class has been loaded,
 * but should be manually deinitialized using {@link #shutdown()} to
 * return the console to its original operating mode.</p>
 *
 * @author Henri Heimann
 * @version 0.1
 */
public final class Console
{
    // Load and initialize native library
    static
    {
        System.loadLibrary("jconsole");
        initialize();
    }

    // Suppress instantiation of class
    private Console()
    {

    }

    /**
     * Initializes the native library.
     */
    private static native void initialize();

    /**
     * Deinitializes the native library and return the console to its original operating mode.
     */
    public static native void shutdown();

    /**
     * Clears the console window and resets the text and background color to the default.
     */
    public static native void clear();

    /**
     * Prints the specified text starting at the current cursor position which may be set
     * using {@link #moveCursor(int, int)}. A linebreak should be represented by "\n\r".
     * @param text      Text to print
     */
    public static native void print(String text);

    /**
     * Sets the visibility of the cursor. A visible cursor may be represented differently
     * on different platforms.
     * @param show      true to show the cursor, false to hide it
     */
    public static native void showCursor(boolean show);

    /**
     * Moves the cursor instantly to the specified coordinates.
     * @param x         Column to move to
     * @param y         Row to move to
     */
    public static native void moveCursor(int x, int y);

    /**
     * Waits until any key is pressed and returns the corresponding character.
     * @return          Character representation of the pressed key
     */
    public static native char readCharacter();
}
