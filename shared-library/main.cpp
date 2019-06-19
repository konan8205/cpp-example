
#include <cstdlib>
#include <functional>
#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>

// UTF-16 support
#include <fcntl.h>
#include <io.h>

#else
#include <cstring>
#include <string>

#include <dlfcn.h>
#include <string.h>
#include <unistd.h>
#endif

#include "interface.h"

inline void print_error() {
#ifdef _WIN32
	wchar_t error[1024];

	FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	               NULL, GetLastError(),
	               MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), error,
	               sizeof(error) / sizeof(wchar_t), NULL);

	std::wcerr << error << std::endl;
#else
	std::cerr << dlerror() << std::endl;
#endif
}

int main() {
	using PFN_CreateClass = IClass *(*)();
	using PFN_DestroyClass = void (*)(IClass *);

	/* Load a library */
#if _WIN32
	// stderr must be handled with wide character functions
	_setmode(_fileno(stderr), _O_U16TEXT);

	HINSTANCE dl_handle = LoadLibraryA("library.dll");
	if (!dl_handle) {
		print_error();
		std::exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass = reinterpret_cast<PFN_CreateClass>(
	    GetProcAddress(dl_handle, "CreateClass"));
	PFN_DestroyClass DestroyClass = reinterpret_cast<PFN_DestroyClass>(
	    GetProcAddress(dl_handle, "DestroyClass"));
#else
	void *dl_handle = dlopen("./library.so", RTLD_NOW);
	if (!dl_handle) {
		print_error();
		std::exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass =
	    reinterpret_cast<PFN_CreateClass>(dlsym(dl_handle, "CreateClass"));
	PFN_DestroyClass DestroyClass =
	    reinterpret_cast<PFN_DestroyClass>(dlsym(dl_handle, "DestroyClass"));
#endif

	if (CreateClass == NULL || DestroyClass == NULL) {
		print_error();
		std::exit(EXIT_FAILURE);
	}

	IClass *object = CreateClass();

	std::cout << "Initial value:\t\t" << object->var << std::endl;
	std::cout << "The square of value:\t" << object->Pow(object->var, 8)
	          << std::endl;

	DestroyClass(object);

#if _WIN32
	FreeLibrary(dl_handle);
#else
	dlclose(dl_handle);
#endif

	return 0;
}