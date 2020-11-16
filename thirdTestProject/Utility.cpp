//#include "pch.h"
#include "Utility.h"

#include <chrono>
#include <random>


// Maximum size when converting images.
static const int sMaxConvertImageBytes = 0x1000000;

//
static const long long seed = std::chrono::system_clock::now().time_since_epoch().count();

//
static std::mt19937_64 engine(seed);

std::wstring UTF8ToWideString(const std::string& text)
{
	std::wstring result;
	if (!text.empty())
	{
		const int bufferSize = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1/*strlen*/, nullptr/*buffer*/, 0/*bufferSzie*/);
		if (bufferSize > 0)
		{
			std::vector<WCHAR> buffer(bufferSize);
			if (0 != MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1/*strlen*/, buffer.data(), bufferSize))
			{
				result = buffer.data();
			}
		}
	}
	return result;
}

std::string WideStringToUTF8(const std::wstring& text)
{
	std::string result;
	if (!text.empty())
	{
		const int bufferSize = WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1/*strlen*/, nullptr/*buffer*/, 0/*bufferSzie*/, NULL/*defaultChar*/, NULL/*usedDefaultChar*/);
		if (bufferSize > 0)
		{
			std::vector<char> buffer(bufferSize);
			if (0 != WideCharToMultiByte(CP_UTF8, 0, text.c_str(), -1/*strlen*/, buffer.data(), bufferSize,NULL/*defaultChar*/,NULL/*usedDefaultChar*/))
			{
				result = buffer.data();
			}
		}
	}
	return result;
}

std::wstring AnsiCodePageToWideString(const std::string& text)
{
	std::wstring result;
	if (!text.empty())
	{
		const int bufferSize = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text.c_str(), -1/*strlen*/, nullptr/*buffer*/, 0/*bufferSize3*/);
		if (bufferSize > 0)
		{
			std::vector<WCHAR> buffer(bufferSize);
			if (0 != MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, text.c_str(), -1/*strlen*/, buffer.data(), bufferSize))
			{
				result = buffer.data();
			}
		}
	}
	return result;
}

std::string WideStringToAnsiCodePage(const std::wstring& text)
{
	std::string result;
	if (!text.empty())
	{
		const int bufferSize = WideCharToMultiByte(CP_ACP, 0/*flags*/, text.c_str(), -1/*strlen*/, nullptr/*buffer*/, 0/*bufferSize*/, NULL/*defaultChar*/, NULL/*usedDefaultChar*/);
		if (bufferSize > 0)
		{
			std::vector<char> buffer(bufferSize);
			if (0 != WideCharToMultiByte(CP_ACP, 0/*flags*/, text.c_str(), -1/*strlen*/, buffer.data(), bufferSize, NULL/*defaultChar*/, NULL/*usedDefaultChar*/))
			{
				result = buffer.data();
			}
		}
	}
	return result;
}

