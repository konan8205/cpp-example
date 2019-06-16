
#include <cstdlib>
#include <functional>
#include <iostream>

#if _WIN32
#include <Windows.h>
#else
#include <cstring>
#include <string>

#include <dlfcn.h>
#include <unistd.h>
#endif

#include "interface.h"

int main() {
	using PFN_CreateClass = IClass *(*)();
	using PFN_DestroyClass = void (*)(IClass *);

#if _WIN32
	/* Load a library */
	HINSTANCE dl_handle = LoadLibraryA("library.dll");
	if (!dl_handle) {
		std::cerr << "Cannot load a library" << std::endl;
		exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass =
	    (PFN_CreateClass)GetProcAddress(dl_handle, "CreateClass");
	PFN_DestroyClass DestroyClass =
	    (PFN_DestroyClass)GetProcAddress(dl_handle, "DestroyClass");

#else
#ifdef __linux__
	std::string dl_path = "./library.so";
#else
	/*
	The POSIX standard requires a complete path in the dlopen function.
	*/

	std::string dl_path;
	dl_path.resize(256);
	dl_path.reserve(256);

	/* Get current path */
	{
		char *cwd_result = NULL;
		for (; cwd_result == NULL;) {
			dl_path.resize(dl_path.size() * 2);

			cwd_result = getcwd((char *)dl_path.c_str(), dl_path.size() + 1);
			if (cwd_result == NULL && errno != ERANGE) {
				std::cerr << std::strerror(errno) << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		dl_path.resize(std::strlen(dl_path.c_str()));
	}

	dl_path += "/library.so";
#endif

	/* Load a library */
	void *dl_handle = dlopen(dl_path.c_str(), RTLD_NOW);
	if (!dl_handle) {
		std::cerr << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass =
	    (PFN_CreateClass)dlsym(dl_handle, "CreateClass");
	PFN_DestroyClass DestroyClass =
	    (PFN_DestroyClass)dlsym(dl_handle, "DestroyClass");
#endif

	if (CreateClass == NULL || DestroyClass == NULL) {
		std::cerr << "Cannot get function address" << std::endl;
		exit(EXIT_FAILURE);
	}

	IClass *object = CreateClass();

	std::cout << "Initial value:\t\t" << object->var << std::endl;
	std::cout << "The square of value:\t" << object->Square(object->var)
	          << std::endl;

	DestroyClass(object);

#if _WIN32
	FreeLibrary(dl_handle);
#else
	dlclose(dl_handle);
#endif

	return 0;
}