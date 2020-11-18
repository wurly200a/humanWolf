#include<Windows.h>
#include<ConsoleApi.h>

extern int humanWolfMain(int argc, char* argv[]);

int
main(int argc, char *argv[])
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode;

	GetConsoleMode(hOut, &dwMode);

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	humanWolfMain(argc,argv);
}
