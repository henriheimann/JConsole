package jconsole;

import java.io.File;
import java.net.URISyntaxException;

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
	static
	{
		// First try loading using loadLibrary and then search the directory of the containing jar
		if (!tryLoadingLibrary() && !tryLoadingLibraryDirect()) {
			System.err.println("Unable to load native library for jconsole.");
			System.exit(0);
		}

		// Initialize native library
		initialize();
	}

	/**
	 * Try to load the jconsole library using the System.loadLibrary method.
	 * @return		true if loading succeeds, false if it doesn't
	 */
	private static boolean tryLoadingLibrary()
	{
		try {
			System.loadLibrary("jconsole");
			return true;
		} catch (UnsatisfiedLinkError e) {
			return false;
		}
	}

	/**
	 * Try to search the directory of the containing jar and load the jconsole library.
	 * @return		true if loading succeeds, false if it doesn't
	 */
	private static boolean tryLoadingLibraryDirect()
	{
		File jar = null;

		try {
			jar = new File(Console.class.getProtectionDomain().getCodeSource().getLocation().toURI());
		} catch (URISyntaxException e) {
			return false;
		}

		File[] directory = jar.getParentFile().listFiles();

		if (directory == null) {
			return false;
		}

		for (File file : directory) {

			String name = file.getName();

			if (isWindows() && name.startsWith("jconsole") && name.endsWith("dll")) {
				System.load(file.getAbsolutePath());
				return true;
			}

			if (isLinux() && name.startsWith("libjconsole") && name.endsWith("so")) {
				System.load(file.getAbsolutePath());
				return true;
			}

			if (isMac() && name.startsWith("libjconsole") && name.endsWith("dylib")) {
				System.load(file.getAbsolutePath());
				return true;
			}
		}

		return false;
	}

	private static boolean isWindows()
	{
		return (System.getProperty("os.name").toLowerCase().contains("win"));
	}

	private static boolean isLinux()
	{
		return (System.getProperty("os.name").toLowerCase().contains("nux"));
	}

	private static boolean isMac()
	{
		return (System.getProperty("os.name").toLowerCase().contains("mac"));
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
