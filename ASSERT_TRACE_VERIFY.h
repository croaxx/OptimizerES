#ifndef ASSERT_TRACE_VERIFY_H_
#define ASSERT_TRACE_VERIFY_H_

#ifdef _DEBUG
#include <crtdbg.h>
#include <stdio.h>
#include <windows.h>
#endif

#ifdef _DEBUG
#define ASSERT _ASSERTE
#define VERIFY ASSERT
#define VERIFY_(result, expression) (expression) ASSERT(result==expression)
#else
#define ASSERT __noop
#define VERIFY(expression) (expression)
#define VERIFY_(result, expression) (expression)
#endif

#ifdef _DEBUG
inline auto Trace(wchar_t const * format, ...)-> void
{
	va_list args;
	va_start(args, format);

	wchar_t buffer[256];

	ASSERT(-1 != _vsnwprintf_s(buffer,
		_countof(buffer) - 1,
		format,
		args));

	va_end(args);
	OutputDebugString(buffer);
}

struct Tracer
{
	char const * m_filename;
	unsigned m_line;

	Tracer(char const * filename, unsigned const line) :m_filename( filename ), m_line( line ) {};

	template<typename... Args >
	auto operator()(wchar_t const * format, Args... args) const -> void
	{
		wchar_t buffer[256];
		auto count = swprintf_s(buffer,
			L"%S(%d):",
			m_filename,
			m_line);

		ASSERT(-1 != count);

		ASSERT(-1 != _snwprintf_s(buffer + count,
			_countof(buffer) - count,
			_countof(buffer) - count - 1,
			format,
			args...));

		OutputDebugString(buffer);
	}
};
#endif


#ifdef _DEBUG
#define TRACE Tracer(__FILE__,__LINE__)
#else
#define TRACE __noop
#endif


// example of use - type TRACE(L"1+2=%d\n", 1+2); the ouput in the debugger should appear

#endif //ASSERT_TRACE_VERIFY_H_