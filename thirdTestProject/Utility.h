#pragma once

#include "pch.h"


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


