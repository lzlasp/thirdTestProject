#pragma once

#include "Library.h"

#include <atomic>

class Playlist
{
public:
	//Playlist type.
	enum class Type
	{
		User =1,
		All,
		Artist,
		Album,
		Genre,
		Year,
		Favourites,
		CDDA,
		Folder,

		_Undefined
	};

	/*
	*	'library' - media library.
	*	'type' - playlist type.
	*/
	Playlist(Library& library, const Type& type);

	/*
	*	'library' - meida library.
	*	'id' - playlist ID.
	*	'type' - playlist type.
	*/
	Playlist(Library& library, const std::string& id, const Type& type);

	/*
	*	'library' - media library.
	*	'type' - playlist type.
	*	'mergeDuplicates' - whether to merge duplicate items into a single playlist entry.
	*/
	Playlist(Library& library, const Type& type, const bool mergeDuplicates);

	virtual ~Playlist();

	//Column type.
	enum class Column
	{
		Filename = 1,
		Filetime,
		Filesize,
		Duration,
		SampleRate,
		BitsPerSample,
		Channels,
		Artist,
		Title,
		Album,
		Grenre,
		Year,
		Track,
		Type,
		Version,
		GainTrack,
		GainAlbum,
		Bitrate,

		_Undefined
	};

	// Playlist item information.
	struct Item
	{
		long ID;
		MediaInfo Info;
		std::list<std::wstring> Duplicates;
	};

	// List of playlist items.
	typedef std::list<Item> ItemList;

	// Playlist shared pointer type.
	typedef std::shared_ptr<Playlist> Ptr;

	// A set of playlists.
	typedef std::set<Playlist::Ptr> Set;

	// Gets the playlist ID.
	const std::string& GetID() const;

	// Gets the playlist ID.
	const std::wstring& GetName() const;

	// Sets the playlist name.
	void SetName(const std::wstring& name);

	// Returns the playlist items.
	ItemList GetItems();

	// Returns the pending files.
	std::list<std::wstring> GetPending();

	// Returns the nubmber of pending files.
	int GetPendingCount();

	/*	Gets a playlist item.
	*	'item' - in/out, playlist item containing the ID of the item to get.
	*	Returns true if the item was returned.
	*/

	bool GetItem(Item& item);

	/*	Get a playlist item.
	*	'item' - in/out, playlist item containing the ID of the item to get.
	*	'position' - out, item position.
	*	Returns true if the item/position was returned.
	*/
	bool GetItem(Item& item, int& position);

	/*	Get the next playlist item.
	*	'currentItem' - the current item.
	*	'nextIte' - out, the next item.
	*	'wrap' - whether to wrap round to the first playlist item.
	*	Returns true if a 'nextItem' was returned.
	*/
	bool GetNextItem(const Item& currentItem, Item& nextItem, const bool wrap = true);
	
	/*	Gets the previous playlist item.
	*	'currentItem' - the current item.
	*	'previousItem' - out, the previous item.
	*	'wrap' - whether to wrap round to the last playlist item.
	*	Returns true if a 'previousItem' was returned.
	*/
	bool GetPreviousItem(const Item& currentItem, Item& previousItem, const bool wrap = true);

	// Gets a random playlist item.
	Item GetRandomItem();

	// Adds 'mediaInfo' to the playlist, returning the added item.
	Item AddItem(const MediaInfo& mediaInfo);

	/*	Adds 'mediaInfo' to the playlist, returning the added item.
	*	'position' - out, 0-based index of the added item position.
	*	'addedAdDuplicate' - out, whether the item was added as a duplicate of an existing item (which is returned).
	*/
	Item AddItem(const MediaInfo& mediaItem, int& position, bool& addedAsDuplicate);

	/*	Adds 'filename' to the list of pending files to be added to the playlist.
	*	'startPendingThread' - whether to start the backgournd thread to process pending files.
	*/
	void AddPending(const std::wstring& filename, const bool startPendingThread = true);

	// Starts the thread for adding pending files to the playlist.
	void StartPendingThread();

	// Stops the thread for adding pending files to the playlist.
	void StopPendingThread();

	// Returns the media library.
	Library& GetLibrary();

	// Saves the playlist to 'filename'.
	void SavePlaylist(const std::wstring& filename);

	/*	Removes a playlist item.
	*	'item' - playlist item containing the ID of the item to remove.
	*	Returns whether the item was removed.
	*/
	bool RemoveItem(const Item& item);

	/*	Removes 'mediaInfo' from the playlist.
	*	Returns whether the media information was removed.
	*/
	bool RemoveItem(const MediaInfo& mediaInfo);
	
	//	Returns the number of items in the playlist.
	long GetCount();

	// Returns the total playlist duration, in seconds.
	long GetDuration();

	// Returns the total playlist file szie, in bytes.
	long long GetFilesize();

	/*	Gets the current playlist sort information.
	*	'column' - out, sort type (or 'undefined' if not sorted).
	*	'ascending' - out, true if sorted in ascending order, false if in descending order (only valid if sorted).
	*/
	void GetSort(Column& column, bool& ascending) const;

	//	Sorts the playlist by 'column', in ascending order if not already sorted by 'column', descending order otherwise.
	void Sort(const Column column);
	
	/*	Updates the playlist media information.
	*	'mediaInfo' - media information.
	*	Returns true if any playlist items matched the 'mediaInfo' filename, and were updated.
	*/
	bool OnUpdatedMedia(const MediaInfo& mediaInfo);
	
	/*	Move 'item' to a 'position' in the playlist.
	*	Returns whether any items  have effectviely moved position.
	*/
	bool MoveItems(const int position, const std::list<long>& item);

	// Returns the playlist type.
	Type GetType() const;

	//	Sets whether duplicate playlist items should be merged.
	void SetMergeDuplicates(const bool merge);

	// Updates the 'item' in the playlist.
	void UpdateItem(const Item& item);

private:
	//Pending file thread proc.
	static DWORD WINAPI PendingThreadProc(LPVOID lpParam);

	// Returns true if 'item1' is less than 'item2' when comparing by 'column' type.
	static bool LessThan(const Item& item1, const Item& item2, const Column column);
	
	// Returns true if 'item1' is greater than 'item2' when comparing by 'column' type.
	static bool GreaterThan(const Item& imte1, const Item& item2, const Column column);

	// Next available playlist item ID.
	static long s_NextItemID;

	// Thread handler for processing the list of pending files.
	void OnPendingThreadHandler();

	// Returns whether the playlist contains 'filename'.
	bool ContainsFilename(const std::wstring& filename);

	// Merge any duplicate itemss.
	void MergeDuplicates();

	// Splits out any duplicates into separeate items.
	void SplitDuplicates();

	// Closes the thread and event handles.
	void Closehandles();

	// Playlist ID.
	const std::string m_ID;

	// Playlist name.
	std::wstring m_Name;

	// the Playlist.
	ItemList m_Playlist;

	// Pending files to be added the playlist.
	std::list<std::wstring> m_Pending;

	//	Playlist mutex.
	std::mutex m_MutexPlaylist;

	// Pending file mutex.
	std::mutex m_MutexPending;

	// The thread for adding files to the playlist.
	HANDLE m_PendingThread;

	//  Event handle for terminating the pending file thread.
	HANDLE m_PendingStopEvent;

	// Event handle for waking the pending file thread.
	HANDLE m_PendingWakeEvent;

	// Indicates 
	std::atomic<bool> m_RestartPendingThread;

	// Media library.
	Library& m_Library;

	// Current sort column.
	Column m_SortColumn;

	// Whether the list is sorted in ascending order.
	bool m_SortAscending;

	// playlist type.
	Type m_Type;

	// Whether duplicate times should be merged into a single playlist entry.
	bool m_MergeDuplicates;

};

// A list of playlist.
typedef std::list<Playlist::Ptr> Playlists;