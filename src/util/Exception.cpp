#include <string>
#include <cstdarg>
#include <cstdio>

#include "Exception.h"

namespace CherryEngine {

Exception::Exception() noexcept
{
	memset(msg, 0, 1024);
}

Exception::Exception(const char* fmt, ...) noexcept
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(msg, 1024, fmt, args);
	va_end(args);
}

Exception& Exception::operator=(const Exception& other) noexcept
{
	if (&other == this) {
		return *this;
	}
	memcpy(msg, other.msg, 1024);
	return *this;
}

const char* Exception::what() const noexcept
{
	return msg;
}

}