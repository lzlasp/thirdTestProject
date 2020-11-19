#pragma once

#include "pch.h"

#include "Library.h"
#include "Settings.h"
#include "CDDAManager.h"


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


};

