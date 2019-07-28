
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>

#else
#include <dlfcn.h>

#endif

#include "interface.h"

inline void dl_error() {
#ifdef _WIN32
	char error[1024];
	FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				   NULL,
				   GetLastError(),
				   LANG_USER_DEFAULT,
				   error,
				   sizeof(error) / sizeof(char),
				   NULL);

	// Use the current system encoding
	std::cerr << error << std::endl;
#else
	std::cerr << dlerror() << std::endl;
#endif
}

template <typename T>
inline void dl_assert(T expr) {
	if (expr == NULL) {
		dl_error();
		std::exit(EXIT_FAILURE);
	}
}

int main() {
	/* Load a library */
#if _WIN32
	HINSTANCE dl_handle = LoadLibraryA("library.dll");
	dl_assert(dl_handle);

	PFN_CreateClass CreateClass = reinterpret_cast<PFN_CreateClass>(
		GetProcAddress(dl_handle, "CreateClass"));
	dl_assert(CreateClass);

	PFN_DestroyClass DestroyClass = reinterpret_cast<PFN_DestroyClass>(
		GetProcAddress(dl_handle, "DestroyClass"));
	dl_assert(DestroyClass);

#else
	void *dl_handle = dlopen("./library.so", RTLD_NOW);
	dl_assert(dl_handle);

	PFN_CreateClass CreateClass =
		reinterpret_cast<PFN_CreateClass>(dlsym(dl_handle, "CreateClass"));
	dl_assert(CreateClass);

	PFN_DestroyClass DestroyClass =
		reinterpret_cast<PFN_DestroyClass>(dlsym(dl_handle, "DestroyClass"));
	dl_assert(DestroyClass);

#endif

	/* Create a class and use it */
	{
		IClass *object = CreateClass();

		std::cout << "object->GetVar():\t\t" << object->GetVar() << std::endl;
		std::cout << "object->SetVar(2)" << std::endl;
		object->SetVar(2);

		std::cout << "object->GetVar():\t\t" << object->GetVar() << std::endl;
		std::cout << "object->Pow(GetVar(), 8):\t"
				  << object->Pow(object->GetVar(), 8) << std::endl;

		DestroyClass(object);
	}

	// Unload library functions
#if _WIN32
	FreeLibrary(dl_handle);
#else
	dlclose(dl_handle);
#endif

	return 0;
}
