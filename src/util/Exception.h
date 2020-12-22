#ifndef EXCEPTION_H_02242020
#define EXCEPTION_H_02242020

#include <string>

#include "global.h"

namespace CherryEngine {

class EXPORT Exception
{
public:
	Exception() noexcept;
	Exception(const char* fmt, ...) noexcept;

//	~Exception();

	Exception& operator=(const Exception& other) noexcept;
	const char* what() const noexcept;
private:
	// This is a C-str because MSVC throws warning C4251 when exporting a class
	// with an STL member. This is due to potential ABI mismatches.
	char msg[1024];
};

}

#endif