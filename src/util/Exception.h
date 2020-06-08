#ifndef EXCEPTION_H_02242020
#define EXCEPTION_H_02242020

#include <string>

namespace CherryEngine {

class Exception
{
public:
	Exception() noexcept;
	Exception(const char* fmt, ...) noexcept;

//	~Exception();

	Exception& operator=(const Exception& other) noexcept;
	const char* what() const noexcept;
private:
	std::string msg;
};

}

#endif