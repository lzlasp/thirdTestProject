#pragma once

#include "pch.h"

#include <functional>
#include <map>
#include <mutex>
#include <list>
#include <vector>
#include <set>

//Folder monitor for file & folder changes.
class FolderMonitor
{
public:
	// 'hwnd' - window handle for device informaiton.
	FolderMonitor(const HWND hwnd);

	virtual ~FolderMonitor();

	// Monitor event type.
	enum class Event
	{
		FolderRenamed,		// A folder has been renamed.
		FolderCreated,		// A folder has been created.
		FolderDeleted,		// A folder has been deleted.
		FileRename,			// A File has been renamed.
		FileCreated,		// A file has been created.
		FileDeleted,		// A file has been deleted.
		FileModified		// A file has been modified.
	};

	/*	Event callback.
	*	'monitorEvent' - event type.
	*	'oldFilename' - the old file or folder name.
	*	'newFilename' - the new file or folder name(which will be identical to oldFilename for events others than FolderRenamed & FileRenamed).
	*/
	typedef std::function<void(const Event monitorEvent, const std::wstring& oldFilename, const std::wstring& newFilename)> EventCallback;

	/*	Adds the folder to be monitored.
	*	'folder' - absolute folder file path.
	*	'callback' - event callback.
	*	Returns whether monitoring has successfully started.
	*/
	bool AddFolder(const std::wstring folder, const EventCallback callback);

	// Removes the 'folder' from being monitored.
	void RemoveFolder(const std::wstring folder);

	// Stops all folders from being monitored.
	void  RemoveAllFolders();

	// Called when a file system device 'handle' is being removed.
	void OnDeviceHandleRemoved(const HANDLE handle);

private:
	// Change type.
	enum class ChangeType
	{
		FolderChange,			// Folder changes.
		FileChange				// File changes.
	};

	//
	enum class PendingAction
	{
		FileAdded,				// File has been added.
		FileModified			// File has been modified.
	};

	// Pairs a pending action with a file time.
	typedef std::pair<PendingAction, long long> PendingInfo;

	// Maps a file name to pending information.
	typedef std::map<std::wstring, PendingInfo> PendingMap;

	struct MonitorInfo
	{
		std::wstring DirectoryPath;		// Directory path.
		HANDLE DirectoryHandle;			// Directory Handle.
		HANDLE MonitorThreadHandles;	// Monitor thread handle.
		HANDLE AddFileThreadHandle;		// Add file thread handle.
		HANDLE CancelHandle;			// Cancel event handle.
		HDEVNOTIFY DevNotifyHandle;		// Device notification handle.
		EventCallback Callback;			// Event callback.
		ChangeType ChangeType;			// ChangeType.
		PendingMap PendingMap;			// Pending files.
		std::mutex PendingMutext;		// Pending mutext.
	};

	// A list of monitors.
	typedef std::list<MonitorInfo*> Monitors;

	// Maps a folder to monitor information.
	typedef std::map<std::wstring, Monitors> FolderMap;

	// Monitor thread procedure.
	static DWORD WINAPI MonitorThreadProc(LPVOID lpParam);

	// Add File thread procedure.
	static DWORD WINAPI AddFileThreadProc(LPVOID lpParam);

	/*	Create a monitor.
	*	'folder' - absolute folder file path.
	*	'callback' - event callback.
	*	'changeType' - change type.
	*	Returns whether monitoring has successfully started.
	*/
	bool AddMonitor(const std::wstring folder, const EventCallback callback, const ChangeType changeType);

	// Delete and release all resuources used by the 'monitor'.
	void CloseMonitor(MonitorInfo* monitor);

	// Window handle for device notification.
	const HWND m_hWnd;

	// The information for the monitored folders.
	FolderMap m_Monitors;

};

