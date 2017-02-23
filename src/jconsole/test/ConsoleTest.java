package jconsole.test;

import jconsole.Console;

public class ConsoleTest
{
	public static void main(String[] args)
	{
		Console.showCursor(false);
		Console.clear();

		char c;

		do {

			c = Console.readCharacter();

			Console.clear();
			Console.moveCursor(2, 2);
			Console.print(c + ": " + (int)c);

		} while (c != Console.KEY_ESCAPE);

		Console.clear();
		Console.showCursor(true);
		Console.shutdown();
	}
}
