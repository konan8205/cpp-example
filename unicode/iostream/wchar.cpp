/*
	Shinwoo Park
	natural7530@gmail.com

	CC0 1.0 Universal
*/

#include <iostream>

#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
	/*
	https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode
	*/
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
#endif

	// Optimization
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::wcout << L"UTF-16 is useful :)" << std::endl
			   << L"UTF-16は有用です :)" << std::endl
			   << L"UTF-16은 유용합니다 :)" << std::endl;

	return 0;
}
