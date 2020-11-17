#pragma once

#include "pch.h"

#include <list>

//class Utility
//{
//};

// Converts UTF8 'text' to a wide string.
std::wstring UTF8ToWideString(const std::string& text);

// Converts wide 'text' to UTF-8.
std::string WideStringToUTF8(const std::wstring& text);

// Converts default Windows ANSI code page 'text' to a wide string.
std::wstring AnsiCodePageToWideString(const std::string& text);

// Converts wide 'text' to the default Windows ANSI code page.
std::string WideStringToAnsiCodePage(const std::wstring& text);


// Converts 'text' to a wide string using the 'codePage'.
std::wstring CodePageToWideString(const std::wstring& text, const UINT codePage);

// Converts 'text' to lowercase.
std::wstring WideStringToLower(const std::wstring& text);

// Converts 'text' to uppercase.
std::wstring WideStringToUpper(const std::wstring& text);

// Converts 'text' to lowercase.
std::string StringToLower(const std::string& text);

// Converts 'text' to uppercase.
std::string StringToUpper(const std::string& text);

/*	Converts a file size to a string.
*	'instance' - module instance handle.
*	'filesize' - file size to convert.
*/
std::wstring FilesizeToString(const HINSTANCE instance, const long long filesize);

/*	 Converts a duration to a string.
*	'instance' - module instance handle.
*	'duration' - duration to converts.
*	'colonDelimited' - true to delimit with colons, false to delimit with resource string.
*/
std::wstring DurationToString(const HINSTANCE instance, const float duartion, const bool colonDelimited);

/*	Converts a byte array to a base64 encoded string.
*	'bytes' - byte array.
*	'byteCount' - number of bytes.
*/
std::string Base64Encode(const BYTE* bytes, const int byteCount);

// Converts a base64 encoded 'text' to a byte array.
std::vector<BYTE> Base64Decode(const std::string& text);

/*	Gets image information.
*	'image' - base64 encoded iamge.
*	'mimeType' -out, MIME type.
*	'width' - out, width in pixels.
*	'height' - out, bits per pixels.
*	'depth' - out bits per pixels.
*	'colours' - out, mumber of colours (for palette indexed images).
*/
void GetImageInformation(const std::string& image, std::string& mimeType, int& width, int& height, int& depth, int& colous);

// Converts 'image' to a base64 encoded from, convertion non-PNG/JPG/GIF images to PNG format.
std::string ConvertImage(const std::vector<BYTE>& image);

// generates a GUID.
GUID GenerateGUID();

// Generates a GUID.
std::string GenerateGUIDString();

// Replaces all occurences of the 'original' substring with 'replacement' in 'text'
void WideStringReplace(std::wstring& text, const std::wstring& original, const std::wstring& replacement);

// Joins 'parts' using the 'delimiter', returning the string parts (or the original string as a single part if it is not delimieted).
std::wstring WideStringJoin(const std::list<std::wstring>& parts, const wchar_t delimiter);

// Gets the system DPI scaling factor.
float GetDPIScaling();

// Returns a random number in the range ['minimum', 'maximum;]
long long GetRandomNumber(const long long minimum, const long long maximum);

// Returns whether the 'folder' exists.
bool FolderExists(const std::wstring& folder);

/*	Replaces invalid characters in 'filename' with 'replacement'.
*	'ReplaceFolderDelimiter' - whether folder delimiters should be replaced.
*/
void WideStringReplaceInvalidFilenameCharcters(std::wstring& filename, const std::wstring& replacement, const bool replaceFolderDelimiters);

// Converts a 'gain' value to a string (returns an empty string if the gain is not valid).
std::wstring GainToWideString(const float gain);

// Converts a 'gain' value to a string (returns an empty string if the gain is not valid).
std::string GainToString(const float gain);

// Centres a 'dialog' with respect to its parent its parent window. or the desktop window if the parent is not visible.
void CentreDialog(const HWND dialog);

// Converts a floating point sample 'value' to 24-bit (clamping any value outside the range -1.0 to +1.0).
int FloatTo24(const float value);

// Converts a floating point sample 'value' to 16-bit (clamping any value outside the range -1.0 to +1.0).
short FloatTo16(const float value);

// Converts a floating point sample 'value' to signed 8-bit (clamping any value outside the range -1.0 to +1.0).
char FloatToSigned8(const float value);

// Converts a floating point sample 'value' to unsigned 8-bit(clamping any value outside the range -1.0 to +1.0).
unsigned char FloatToUnsigned8(const float value);

// Returns the 'filename' extension in lowercase.
std::wstring GetFileExtension(const std::wstring filename);