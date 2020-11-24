#pragma once

#include "pch.h"

#include "Library.h"
#include "Settings.h"
#include "CDDAManager.h"
#include "FolderMonitor.h"
#include "resource.h"

#include <CommCtrl.h>

class WndTree
{
	/*	
	*	'instance' - module instance handle.
	*	'parent' - parent window handle.
	*	'library' - media library.
	*	'settings' - application settings.
	*	'cddaManager' - CD audio manager.
	*/
	WndTree(HINSTANCE hInstance, HWND parent, Library& library, Settings& settings, CDDAManager& cddaManager);

	virtual ~WndTree();

	// Returns the default window procedure.
	WNDPROC GetDefaultWndProc();
	
	// Gets the tree control handler.
	HWND GetWindowHandle();

	// Returns the playlist associated with a tree 'node', or a null playlist if it's not a playlist node.
	Playlist::Ptr GetPlaylist(const HTREEITEM node);

	// Returns the currently selected playlist, or a null playlist if one isn't selected.
	Playlist::Ptr GetSelectdPlaylist();

	// Called when a 'command' is received.
	void OnCommand(const UINT command);

	// Displays the context menu at the specified 'position', in screen coordinates.
	void OnContextMenu(const POINT& position);
	
	/*	Called when item albel editing begins.
	*	Retuuns TRUE if label editing is to be prevented.
	*/
	LPARAM OnBeginLabelEdit(WPARAM wParam, LPARAM lParam);

	// Called when the window is destroyed.
	void OnDestroy();

	// Gets the playlists.
	Playlist GetPlaylists();

	// Add a 'playlist'.
	void AddPlaylist(const Playlist::Ptr playlist);
	
	// Create and returns a new playlist.
	Playlist::Ptr NewPlaylist();

	// Deletes the currently selected playlist.
	void DeleteSelectedPlaylist();

	/*	Import a playlist.
	*	'filename' - the playlist to import, or an empty string to launch a file selection dialog.
	*/
	void ImportPlaylist(const std::wstring& filename = std::wstring());

	// Launches a file selector dialog to export the currently selected playlist.
	void ExportSelectedPlaylist();

	// Selects a 'playlist'.
	void SelectPlaylist(const Playlist::Ptr playlist);

	// Selects, and shows if necessary, the 'All Tracks' playlist.
	void SelectAllTracks();

	// Displays the font selection dialog for changing the tree control font.
	void OnSelectFont();

	/* Display the colour selection dialong for changing the tree control colours.
	*  'commandID' - command ID indicating which colour to change.
	*/
	void SelectColout(const UINT commandID);

	// Initialize the tree control playlist structure.
	void Initialise();

	/*	Called when media information has been updated.
	*	'previousmediaInfo' - previous media information.
	*	'updatedMediaInfo' - updated media information.
	*	Returns the playlist that have been updated.
	*/
	Playlist::Set OnUpdatedMedia(const MediaInfo& previousMediaInfo, const MediaInfo& updateMediaInfo);

	// Called when the 'mediaList' has been removed from the media library.
	void OnRemoveMedia(const MediaInfo::List& mediaList);

	// Called when the availabel CD audio discs have been refreshed.
	void OnCDDARefreshed();

	// Toggles 'Favourites' on the tree control.
	void OnFavourites();

	// Toggles 'All Tracks' on the tree control.
	void OnAllTracks();

	// Toggles artists on the tree control.
	void OnArtists();

	// Toggles albums on the tree control.
	void OnAlbums();

	// Toggles genres on the tree control.
	void onGenres();

	// Toggles years on the tree control.
	void OnYears();

	// Retruns whether the tree control node represented by 'commandID' is shown.
	bool IsShown(const UINT commandID) const;

	// Saves the startup 'playlist' to application settings.
	void SaveStartupPllaylist(const Playlist::Ptr playlist);

	// Retruns the highlight colour.
	COLORREF GetHighlightColour() const;

	// Returns the Favourites playlist.
	Playlist::Ptr GetPlaylistFavourites() const;

	// Returns the All Tracks playlist.
	Playlist::Ptr GetPlaylistAll() const;

	// Returns whether it is possible to delete the currently selected item.
	bool IsPlaylistDeleteEnabled();
	
	// Returns whether it is possible to export the currently selected item.
	bool IsPlaylistExportEnabled();

	// Returns whether it is possible to rename the currently selected item.
	bool IsPlaylistRenameEnabled();

	// Starts editing the name of the currently selected playlist.
	void RenameSelectedPlaylist();

	// Called when a logical 'drive' has arrived.
	void OnItemExpanding(const HTREEITEM item);

	// Called when a logical 'drive' has been removed.
	void OnDriveArrived(const wchar_t drive);

	// Called when file system device 'handle' is being removed.
	void OnDeviceHandleRemoved(const HANDLE  handle);

	/*	Sets and selects the playlist used for files passwd via the shell (e.g on startup).
	*	'mediaList' - media list with which to populate the scratch list.
		Returns the scratch list.
	*/
	Playlist::Ptr SetScratchList(const MediaInfo::List& meidaList);

	// Sets whether duplicate tracks are merged into a single entry (for Artist/Album/Genre/Year playlists).
	void SetMergeDuplicates(const bool mergeDuplicates);

	// Saves the tree control settings to application settings.
	void SaveSettings();

	/*	Selects the Audio CD 'drive'
	*	Returns the playlist if the Audio CD was selected, or nullptr if not.
	*/
	Playlist::Ptr SelectAudioCD(const wchar_t Drive);

private:
	// Window procedure.
	static LRESULT CALLBACK TreeProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	// Thread for updating media information in the scrtch list.
	static DWORD WINAPI ScratchListUpdateProc(LPVOID lpParam);

	// Thread for handing file modification events from the folder monitor.
	static DWORD WINAPI FileModifiedProc(LPVOID lpParam);

	// Information for the scrtch list update thread.
	struct ScratchListUpdateInfo
	{
		// 'library' - media library.
		// 'stopEvent' - indicates whether the thread should stop.
		// ' mediaList' - the media a update.
		ScratchListUpdateInfo(Library& library, const HANDLE stopEvent, const MediaInfo::List& mediaList) :
			MediaLibrary(library),
			StopEvent(stopEvent),
			MediaList(mediaList) {};

		Library& MediaLibrary;
		HANDLE StopEvent;
		MediaInfo::List MediaList;
	};

	// Maps a tree item to a playlist.
	typedef std::map<HTREEITEM, Playlist::Ptr> PlaylistMap;

	// Maps a playllist type to an icon index.
	typedef std::map<Playlist::Type, int> IconMap;

	// Maps a playlist type to an item order value.
	typedef std::map<Playlist::Type, LPARAM> OrderMap;

	// Root folder information.
	enum class RootFolderType{UserFolder, Drive};

	// Root folder information.
	struct RootFolderInfo{
		std::wstring Name;
		std::wstring Path;
		int IconIndex;
		RootFolderType Type;
		bool operator<(const RootFolderInfo& other) const
		{
			return std::tie(Name, Path, IconIndex, Type) < std::tie(other.Name, other.Path, other.IconIndex, other.Type);
		}
		bool operator-(const RootFolderInfo& other) const
		{
			return std::tie(Name, Path, IconIndex, Type) == std::tie(other.Name, other.Path, other.IconIndex, other.Type);
		}
	};

	// A folder information list.
	typedef std::list<RootFolderInfo> RootFolderInfoList;

	// Maps a tree item to folder information.
	typedef std::map<HTREEITEM, RootFolderInfo> RootFolderInfoMap;

	// Map a string to a set of tree item nodes.
	typedef std::map<std::wstring, std::set<HTREEITEM>> StringToNodesMap;

	// Loads playlist.
	void LoadPlaylists();

	// Imports a VPL playlist from 'filename', returning the playlist.
	Playlist::Ptr ImportPlaylistVPL(const std::wstring& filename);

	// Imports a M3U playlist from 'filename', returning the playlist.
	Playlist::Ptr ImportPlaylistM3U(const std::wstring& filename);

	// Imports a PLS playlist from 'filename', returning the playlist.
	Playlist::Ptr ImportPlaylistPLS(const std::wstring& filename);

	// Gets the current tree control font.
	LOGFONT GetFont();

	// Sets the current tree control font.
	void SetFont(const LOGFONT& logFont);

	// Initializes the tree control from application settings.
	void ApplySettings();

	// Adds 'Favourites' to the tree control.
	void AddFavourites();

	// Adds 'All Tracks' to the tree control.
	void AddTracks();

	// Adds 'Artists to the control.
	void AddArtists();

	// Adds albums to the tree control.
	void AddAlbums();

	// Adds genres to the tree control.
	void AddGenres();

	// Adds years to the tree control.
	void AddYears();

	// Adds CD Audio discs to the tree control.
	void AddCDDA();

	// Remvoe 'Favourites' from the tree control.
	void RemoveFavourites();

	// Remove 'All Tracks' from the tree control.
	void RemoveAllTracks();

	// Removes artists from the tree control.
	void RemoveArtists();

	// Removes ablums from the tree control.
	void RemoveAlbums();

	// Removes genres from the tree control.
	void RemoveGenres();

	// Removes years from the tree control.
	void RemoveYears();

	// Removes CD Audio discs from the tree control.
	void RemoveCDDA();

	/*	Adds item to the tree control.
	*	'parentItem' - parent tree item.
	*	'label' - item label.
	*	'type' - item type.
	*	'redraw' - whether to redraw the control.
	*	Returns the added item.
	*/
	HTREEITEM AddItem(const HTREEITEM parentItem, const std::wstring& label, const Playlist::Type type, const bool redraw = true);

	/*	Remvoe an item from the tree control.
	*	'item' - item to remove.
	*/
	void RemoveItem(const HTREEITEM item);

	// Gets the tree 'item' type.
	Playlist::Type GetItemType(const HTREEITEM item) const;

	// Gets the tree 'item' label.
	std::wstring GetItemLabel(const HTREEITEM item) const;

	// Sets the tree 'item' label'.
	void SetItemLabel(const HTREEITEM item, const std::wstring& label) const;

	// Returns all the playlists anmes.
	std::set<std::wstring> GetPlaylistNames() const;

	// Processes any playlists with pending files.
	void ProcessPendingPlaylists();

	/* Updates artist when media inforamtion as been updated.
	*  'previousMediaInfo' - previous media information.	
	*  'updatedMediaInfo' - updated media information.
	*  'updatedPalylists' - in/out, the playlist that have been updated.
	*/
	void UpdateArtists(const MediaInfo& previousMediaInfo, const MediaInfo& updateMediaInfo, Playlist::Set& updatedPlaylist);
	
	/* Update albums when media information has been updated.
	*  'parentItem' - the parent tree item containing the albums.
	*  'previousMediainfo' - previous media information.
	*  'updatedMediaInfo' - updated meida information.
	*  'updatedPlaylists' - in/out, the playlists that have been updated.
	*/
	void UpdateAlbums(const HTREEITEM parentItem, const MediaInfo& previousMediaInfo, const MediaInfo& updatedMediaInfo, Playlist::Set& updatedPlaylists);

	/* 'Updates genres media information has been updated.
	*  'previousMediaInfo' - previous media information.
	*  'updatedMediaInfo' - updated media information.
	*  'updatedPlaylists' - in/out, the playlsits that have been updated.
	*/
	void UpdateGenres(const MediaInfo& previousMediaInfo, const MediaInfo& updatedMediaInfo, Playlist::Set& updatedPlaylists);
	
	/* 'Updates years when media information has been updated.
	*  'previousMediaInfo' - previous media information.
	*  'updatedMediaInfo' - updated media information.
	*  'updatedPlaylists' - in/out, the playlists that have been updated.
	*/
	void UpdatedYears(const MediaInfo& previousMediaInfo, const MediaInfo& updatedMediaInfo, Playlist::Set& updatedPlaylists);

	/* Updates playlists when media information has been updated.
	*  'updatedMediaInfo' - updated media information.
	*  'updatedPlaylists' - in/out, the playlists that have been updated.
	*/
	void UdpatePlaylists(const MediaInfo& updatedMediaInfo, Playlist::Set& updatedPlaylists);

	/* Updates CD Auio playlists when CD Audio discs information has been updated.
	*  'updatedMedia' - updated media informtion.
	*  'updatedPlaylists' - in/out, the playlists that have been updated.
	*/
	void UpdateCDDA(const MediaInfo& updatedMediaInfo, Playlist::Set& updatedPlaylists);

	// Returns the initial selected tree item from application settings.
	HTREEITEM GetStartupItem();

	// Populate the tree.
	void Populate();

	// Creates the image list.
	void CreateImageList();

	// Gets the icon index corresponding to a playlist 'type'.
	int GetIconIndex(const Playlist::Type type) const;

	// Loads the 'All Tracks' playlist.
	void LoadAllTracks();

	// Loads the 'Favourites' playlist.
	void LoadFavourites();

	// Returns the item order for root 'item'.
	LPARAM GetItemOrder(const HTREEITEM item) const;

	// Returns the tree insertion position for a root item corresponding to a playlist 'type'.
	HTREEITEM GetInsertAfter();

	// Refershes the computer tree control item.
	void RefreshComputerNode();

	// Returns the user folder.
	RootFolderInfoList GetUserFolders() const;

	// Returns the logical drives.
	RootFolderInfoList GetComputerDrivers() const;

	// Returns the sub folders of the 'parent' folder.
	std::set<std::wstring> GetSubFolders(const std::wstring& parent) const;

	// Gets the folder 'path' of the tree 'item'.
	void GetFolderPath(const HTREEITEM item, std::wstring& path) const;

	// Adds sub folders to the tree 'item'.
	void AddSubFolders(const HTREEITEM item);

	// Adds tracks to the folder 'playlist' represented by the tree 'item'.
	void AddFodlerTracks(const HTREEITEM item, Playlist::Ptr playlist) const;

	/* Folder monitor callback.
	*  'monitorEvent' - event type.
	*  'oldFilename' - the old file or folder name.
	*  'newFilename' - the new file or folder name.
	*/
	void OnFolderMonitorCallback(const FolderMonitor::Event monitorEvent, const std::wstring& olderFilename, const std::wstring& newFilename);

	// File modeification thread handler.
	void OnFileModifiedHandler();

	// Returns the 'children' (including all sub-children) of the tree 'item'.
	void GetAllChildren(const HTREEITEM item, std::set<HTREEITEM>& children) const;

	/* Called when a 'folder' needs to be added to the 'parent' tree item.
	*  Returns the added folder tree item.
	*/
	HTREEITEM OnFolderAdd(const HTREEITEM parent, const std::wstring& folder);

	// Called when a folder 'item' needs to be deleted from the tree.
	void OnFolderDelete(const HTREEITEM item);

	// Called when an 'oldFolderPath' has been renamed to 'newFolderPath'.
	void OnFolderRename(const std::wstring& oldFolderPath, const std::wstring& newFolderPath);

	// Adds the tree 'item' to the folder nodes map.
	void  AddToFolderNodesMap(const HTREEITEM item);

	// Removes a tree 'item' from the folder nodes map.
	void RemoveFromFolderNodesMap(const HTREEITEM item);

	// Returns the tree item corresponding to the computer 'folder', or nullptr ifthe node was not found.
	HTREEITEM GetComputerFolderNode(const std::wstring& folder);

	// Starts the thread which updates the media information for the 'scratchList'.
	void StartScratchListUpdateThread(Playlist::Ptr scratchList);

	//  Stop the thread which updates the media information for the scratch list.
	void StopScratchListUpdateThread();

	// Starts the thread which handles file modification notifications.
	void StartFileModifiedThread();

	// Stop the thread which handles file modification notifications.
	void StopFileModeifiedThread();

	// Returns whether to ignore a file monitor event for the 'filename'.
	bool IgnoreFileMonitorEvent(const std::wstring& filename) const;

	// Moddule instance handle.
	HINSTANCE m_hInst;

	// Window handle.
	HWND m_hWnd;

	// Defualt window procedure.
	WNDPROC m_DefaultWndProc;

	// Playlists node.
	HTREEITEM m_NodePlaylists;

	// Artists node.
	HTREEITEM m_NodeArtists;

	// Albums node.
	HTREEITEM m_NodeAlbums;

	// Genres node.
	HTREEITEM m_NodeGenres;

	// Years node.
	HTREEITEM m_NodeYears;

	// All Tracks node.
	HTREEITEM m_NodeAll;

	// Favourites node.
	HTREEITEM m_NodeFavourites;

	// Computer node.
	HTREEITEM m_NodeComputer;

	// Media library.
	Library& m_Library;

	// Application settings.
	Settings& m_Settings;

	// CD Audio manager.
	CDDAManager& m_CDDAManager;

	// Plyalists.
	PlaylistMap m_PlaylistMap;

	// Artists.
	PlaylistMap m_ArtistMap;

	// Albums.
	PlaylistMap m_AlbumMap;

	// Genres.
	PlaylistMap m_GenreMap;

	// Years.
	PlaylistMap m_YearMap;

	// CD Audio playlists.
	PlaylistMap m_CDDAMap;

	// Fodler playlists.
	PlaylistMap m_FolderPlaylistMap;

	// All Tracks playlist.
	Playlist::Ptr m_PlaylistAll;

	// Favourites playlist.
	Playlist::Ptr m_PlaylistFavourites;

	// The font resulting from the font selection dialog.
	HFONT m_ChosenFont;

	// Hightlight colour.
	COLORREF m_ColourHighlight;

	// Image list.
	HIMAGELIST m_ImageList;

	// Icon Map.
	IconMap m_IconMap;

	// Icon index for the computer icon.
	int m_IconIndexComputer;

	// Icon index for the folder icon.
	int m_IconIndexFolder;

	// Icon index for the drive icon.
	int m_IconIndexDrive;

	// The root computer folders.
	RootFolderInfoMap m_RootComputerFolder;

	// Maps a folder path to the set of tree items.
	StringToNodesMap m_FolderNodesMap;

	// Mutex for the folder nodes map.
	std::mutex m_FolderNodesMapMutex;

	// Mutex for the folder playlist map.
	std::mutex m_FolderPlaylistMapMutex;

	// Folder monitor.
	FolderMonitor m_FolderMonitor;

	// FileModification thread handle.
	HANDLE m_FileModifiedThread;

	// File modification thread stop event.
	HANDLE m_FileModifiedStopEvent;

	// File modification thread wake event.
	HANDLE m_FileModifiedWakeEvent;

	// Files modified.
	std::set<std::wstring> m_FilesModified;

	// Mutex for the files modified.
	std::mutex m_FilesModifiedMutex;

	// Scratch list update thread handle.
	HANDLE m_ScratchListUpdateThread;

	// Scratch list stop event handle.
	HANDLE m_ScratchListUpdateStopEvent;

	// Whether duplicate tracks are mergerd into a single entry (for Artist/Album/Genre/Year playlists).
	bool m_MergeDuplicates;

	// All file extensions supported by the(decoder) handlers.
	const std::set<std::wstring> m_SupportedFileExtensions;

	// Root item ordering.
	static OrderMap s_RootOrder;
};

