#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>

int main(int argc, char const *argv[])
{
	for (int i = 0; i < 255; ++i)
	{
		/* code */
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		WORD saved_attributes;

		/* Save current attributes */
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		saved_attributes = consoleInfo.wAttributes;

		SetConsoleTextAttribute(hConsole, i);

		printf("%d\n", i);

		/* Restore original attributes */
		SetConsoleTextAttribute(hConsole, saved_attributes);
	}

	return 0;
}