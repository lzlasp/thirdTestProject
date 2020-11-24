//#include "pch.h"
#include "Utility.h"

#include <chrono>
#include <random>
#include <iomanip>
#include <sstream>

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

void GetImageInformation(const std::string& image, std::string& mimeType, int& width, int& height, int& depth, int& colous)
{
}

std::string ConvertImage(const std::vector<BYTE>& image)
{
	return std::string();
}

GUID GenerateGUID()
{
	return GUID();
}

std::string GenerateGUIDString()
{
	return std::string();
}

void WideStringReplace(std::wstring& text, const std::wstring& original, const std::wstring& replacement)
{
}

std::wstring WideStringJoin(const std::list<std::wstring>& parts, const wchar_t delimiter)
{
	return std::wstring();
}

float GetDPIScaling()
{
	HDC hdc = GetDC(NULL);
	const float scaling = static_cast<float>(GetDeviceCaps(hdc, LOGPIXELSX)) / 96;
<<<<<<< HEAD
	ReleaseDC(0, hdc);
=======
	ReleaseDC(0,hdc);
>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58
	return scaling;
}

long long GetRandomNumber(const long long minimum, const long long maximum)
{
	return 0;
}

bool FolderExists(const std::wstring& folder)
{
	return false;
}

void WideStringReplaceInvalidFilenameCharcters(std::wstring& filename, const std::wstring& replacement, const bool replaceFolderDelimiters)
{
}

std::wstring GainToWideString(const float gain)
{
	std::wstringstream ss;
	if (!std::isnan(gain))
	{
		ss << std::fixed << std::setprecision(2) << std::showpos << gain << L" dB";
	}
	return ss.str();
}

std::string GainToString(const float gain)
{
	std::stringstream ss;
	if (!std::isnan(gain))
	{
		ss << std::fixed << std::setprecision(2) << std::showpos << gain << " dB";
	}
	return ss.str();
}

void CentreDialog(const HWND dialog)
{
}

int FloatTo24(const float value)
{
	return 0;
}

short FloatTo16(const float value)
{
	return 0;
}

char FloatToSigned8(const float value)
{
	return 0;
}

unsigned char FloatToUnsigned8(const float value)
{
	return 0;
}

std::wstring GetFileExtension(const std::wstring filename)
{
	return std::wstring();
}
