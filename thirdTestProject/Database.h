#pragma once
#include "pch.h"

#include "sqlite3.h"

#include <list>
#include <mutex>
#include <string>

class Database
{
public:
	//Database access mode.
	enum class Mode
	{
		Disk,		// Direct access from disk.
		Temp,		// Use a temporary (disk & memory cached) copy of the database, which gets flushed back out to disk when closed.
		Memory		// Use a pure in-memory copy of the database, which gets flushed back out to disk when closed.
	};

	/*
	*
	*/
	Database(const std::wstring& filename, const Mode mode);

	virtual ~Database();

	// Returns the SQLite database.
	sqlite3* GetDatabase();

private:
	// Append an 'errorCode' & 'message' entry to the error log.
	void AppendToErrorLog(const int errorCode, const std::string& message);

	// SQLite error callback.
	static void ErrorLogCallback(void* arg, int errorCode, const char* message);

	//SQlite error callback.
	sqlite3* m_Database;

	// Disk database file name.
	std::wstring m_Filename;

	// Database access mode.
	Mode m_Mode;

	// Error log mutex.
	std::mutex m_LogMutex;

	// Error log, pairing a SQLite error code with the error description.
	std::list<std::pair<int, std::string>> m_Log;


};

