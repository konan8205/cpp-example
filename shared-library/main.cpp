
#include <cstdlib>
#include <functional>
#include <iostream>

#if _WIN32
#define NOMINMAX
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

	/* Load a library */
#if _WIN32
	HINSTANCE dl_handle = LoadLibraryA("library.dll");
	if (!dl_handle) {
		std::cerr << "Cannot load a library" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass = reinterpret_cast<PFN_CreateClass>(
	    GetProcAddress(dl_handle, "CreateClass"));
	PFN_DestroyClass DestroyClass = reinterpret_cast<PFN_DestroyClass>(
	    GetProcAddress(dl_handle, "DestroyClass"));
#else
	void *dl_handle = dlopen("./library.so", RTLD_NOW);
	if (!dl_handle) {
		std::cerr << dlerror() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	PFN_CreateClass CreateClass =
	    reinterpret_cast<PFN_CreateClass>(dlsym(dl_handle, "CreateClass"));
	PFN_DestroyClass DestroyClass =
	    reinterpret_cast<PFN_DestroyClass>(dlsym(dl_handle, "DestroyClass"));
#endif

	if (CreateClass == NULL || DestroyClass == NULL) {
		std::cerr << "Cannot get function address" << std::endl;
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