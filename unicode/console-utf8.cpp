/*
    Shinwoo Park
    natural7530@gmail.com
    
    MIT License
*/

#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#include <io.h>

#ifndef _O_U8TEXT
#define _O_U8TEXT 0x00040000
#endif // _O_U8TEXT
#endif // _WIN32

using namespace std;

int main()
{
#ifdef _WIN32
	/*
	Reference:
	https://docs.microsoft.com/en-us/windows/console/console-reference
	https://docs.microsoft.com/en-us/windows/desktop/Intl/code-page-identifiers
	*/
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#else
	locale::global(locale("C.UTF-8"));
#endif // _WIN32
	
	// Optimization
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout<<u8"UTF-8 is beautiful :)"<<endl
		<<u8"UTF-8は美しいです :)"<<endl
		<<u8"UTF-8은 아름답습니다 :)"<<endl;

	return 0;
}
