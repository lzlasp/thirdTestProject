#pragma once

#include "Library.h"

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
	const std::wstring& GetID() const;

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

};

