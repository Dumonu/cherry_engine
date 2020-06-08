#include <string>
#include <cstdarg>
#include <cstdio>

#include "Exception.h"

namespace CherryEngine {

Exception::Exception() noexcept
{
	msg = "";
}

Exception::Exception(const char* fmt, ...) noexcept
{
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 1024, fmt, args);
	va_end(args);

	msg = buf;
}

Exception& Exception::operator=(const Exception& other) noexcept
{
	msg = other.msg;
	return *this;
}

const char* Exception::what() const noexcept
{
	return msg.c_str();
}

}