/*
    Shinwoo Park
    natural7530@gmail.com

    CC0 1.0 Universal
*/

#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

using namespace std;

int main()
{
#ifdef _WIN32
	/*
	https://docs.microsoft.com/en-us/windows/console/setconsolecp
	*/
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#else
	locale::global(locale("en_US.UTF-8"));
#endif // _WIN32

	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << u8"UTF-8 is beautiful :)" << endl
	     << u8"UTF-8は美しいです :)" << endl
	     << u8"UTF-8은 아름답습니다 :)" << endl;

	return 0;
}
