#include "pch.h"
#include "WndTree.h"

#include <PathCch.h>
#include <Shlwapi.h>
#include <Uxtheme.h>
<<<<<<< HEAD
#include <fstream>

=======
#include <windowsx.h>
>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58

#include <fstream>

#include "Utility.h"
// Tree control ID.
static const UINT_PTR s_WndTreeID = 1900;

// Icon size
static const int s_IconSize = 16;

// User folders for the computer node.
static const std::list<KNOWNFOLDERID> s_UserFolders = { FOLDERID_Desktop,FOLDERID_Documents,FOLDERID_Downloads,FOLDERID_Music };

// Playlist ID for the scratch list.
static const std::string s_ScratchListID = "F641E764-3385-428A-9F39-88E928234E17";

// Initial folder setting for choosing playlists.
static const std::string s_PlaylistFolderSetting = "Playlist";

/* Message ID for adding a folder to the computer node.
*  'wParam' : HTREEITEM - the parent item inder which to add the folder.
*  'lParam' : std::wstring* - folder name, to be deleted by the message handler.
*/
static const UINT MSG_FOLDERADD = WM_APP + 110;

/* Message ID for deleting a folder from the computer node.
*  'wParam' : HTREEITEM - th item to delete.
*  'lParam' : unused.
*/
static const UINT MSG_FOLDERDELETE = WM_APP + 111;

/* Message ID for renaming a folder in the computer node.
*  'wParam' : std::wstring* - old folder path, to be deleted by the message handler.
*  'lParam' : std::wstring* - new folder path, to be deleted by the message handler. 
*/
static const UINT MSG_FOLDERRENAME = WM_APP + 112;

// Root item ordering.
WndTree::OrderMap WndTree::s_RootOrder = {
	{Playlist::Type::Folder, 1},
	{Playlist::Type::CDDA, 2},
	{Playlist::Type::User, 3},
	{Playlist::Type::Favourites, 4},
	{Playlist::Type::All, 5},
	{Playlist::Type::Artist, 6},
	{Playlist::Type::Album, 7},
	{Playlist::Type::Genre, 8},
	{Playlist::Type::Year, 9}
};


WndTree::WndTree(HINSTANCE instance, HWND parent, Library& library, Settings& settings, CDDAManager& cddaManager) :
	m_hInst(instance),
	m_hWnd(nullptr),
	m_DefaultWndProc(nullptr),
	m_NodePlaylists(nullptr),
	m_NodeArtists(nullptr),
	m_NodeAlbums(nullptr),
	m_NodeGenres(nullptr),
	m_NodeYears(nullptr),
	m_NodeAll(nullptr),
	m_NodeFavourites(nullptr),
	m_Library(library),
	m_Settings(settings),
	m_CDDAManager(cddaManager),
	m_PlaylistMap(),
	m_ArtistMap(),
	m_GenreMap(),
	m_YearMap(),
	m_CDDAMap(),
	m_FolderPlaylistMap(),
	m_PlaylistAll(),
	m_PlaylistFavourites(),
	m_ChosenFont(NULL),
	m_ColourHighlight(),
	m_ImageList(nullptr),
	m_IconMap(),
	m_IconIndexComputer(),
	m_IconIndexDrive(),
	m_IconIndexFolder(),
	m_RootComputerFolder(),
	m_FolderNodesMap(),
	m_FolderNodesMapMutex(),
	m_FolderPlaylistMapMutex(),
	m_FolderMonitor(parent),
	m_FileModifiedThread(),
	m_FileModifiedStopEvent(CreateEvent(nullptr/*securityAttributes*/, TRUE/*manualReset*/, FALSE/*initialState*/, L""/*name*/)),
	m_FileModifiedWakeEvent(CreateEvent(nullptr/*securityAttributes*/, TRUE/*manualReset*/, FALSE/*initialState*/, L""/*name*/)),
	m_FilesModified(),
	m_FilesModifiedMutex(),
	m_ScratchListUpdateThread(nullptr),
	m_ScratchListUpdateStopEvent(CreateEvent(nullptr/*securityAttributes*/, TRUE/*manualReset*/, FALSE/*initialState*/, L""/*name*/)),
	m_MergeDuplicates(settings.GetMergeDuplicates()),
	m_SupportedFileExtensions(m_Library.GetAllSupportedFileExtesions())
{
	const DWORD exStyle = 0;
	LPCTSTR className = WC_TREEVIEW;
	LPCTSTR windowName = NULL;
	const DWORD style = WS_CHILD | WS_VISIBLE | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_DISABLEDRAGDROP | TVS_SHOWSELALWAYS | TVS_EDITLABELS;
	const int x = 0;
	const int y = 0;
	const int width = 0;
	const int height = 0;
	LPVOID param = NULL;
	m_hWnd = CreateWindowEx(exStyle, className, windowName, style, x, y, width, height, parent, reinterpret_cast<HMENU>(s_WndTreeID), instance, param);
	TreeView_SetExtendedStyle(m_hWnd, TVS_EX_DOUBLEBUFFER,TVS_EX_DOUBLEBUFFER);
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	m_DefaultWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(TreeProc)));
	ApplySettings();
	CreateImageList();
}

<<<<<<< HEAD
LRESULT CALLBACK WndTree::TreeProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WndTree* wndTree = reinterpret_cast<WndTree*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	if (nullptr != wndTree)
	{
		switch (message)
		{
			case WM_COMMAND:
			{
				const UINT commandID = LOWORD(wParam);
				wndTree->OnCommand(commandID);
				break;
			}
		}
	}

}

void WndTree::OnCommand(const UINT command)
{
	switch (command)
	{
		case ID_FILE_NEWPLAYLIST:
		{
			NewPlaylist();
			break;
		}
		case ID_FILE_DELETEPLAYLIST:
		{
			DeleteSelectedPlaylist();
			break;
		}
		case ID_FILE_RENAMEPLAYLIST:
		{
			RenameSelectedPlaylist();
			break;
		}
		case ID_FILE_IMPORTPLAYLIST:
		{
			ImportPlaylist();
			break;
		}
		default:
			break;
=======
WndTree::~WndTree()
{
	SetWindowLongPtr(m_hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_DefaultWndProc));
	if (nullptr != m_ChosenFont)
	{
		DeleteObject(m_ChosenFont);
	}
	ImageList_Destroy(m_ImageList);
	if (nullptr != m_ScratchListUpdateStopEvent)
	{
		CloseHandle(m_ScratchListUpdateStopEvent);
	}
	if (nullptr != m_FileModifiedStopEvent)
	{
		CloseHandle(m_FileModifiedStopEvent);
	}
	if (nullptr != m_FileModifiedWakeEvent)
	{
		CloseHandle(m_FileModifiedWakeEvent);
>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58
	}
}


int WndTree::GetIconIndex(const Playlist::Type type) const
{
	int iconIndex = 0;
	const auto iter = m_IconMap.find(type);
	if (m_IconMap.end() != iter)
	{
		iconIndex = iter->second;
	}
	return iconIndex;
}

LPARAM WndTree::GetItemOrder(const HTREEITEM item) const
{
	TVITEMEX tvItem = {};
	tvItem.mask = TVIF_PARAM;
	tvItem.hItem = item;
	TreeView_GetItem(m_hWnd, &tvItem);
	const LPARAM order = HIWORD(tvItem.lParam);
	return order;
}

<<<<<<< HEAD
Playlist::Ptr WndTree::NewPlaylist()
{
	const int bufSize = 32;
	WCHAR buffer[bufSize] = {};

	std::wstring uniqueName = buffer;
	const std::set<std::wstring> allNames = GetPlaylistNames();
	auto nameIter = allNames.find(uniqueName);
	int playlistNum = 1;
	while (allNames.end() != nameIter)
	{
		uniqueName = buffer;
		uniqueName += L" (" + std::to_wstring(++playlistNum) + L")";
		nameIter = allNames.find(uniqueName);
	}
	wcscpy_s(buffer, bufSize, uniqueName.c_str());

	TVITEMEX tvItem = {};
	tvItem.mask = TVIF_TEXT | TVIF_PARAM | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvItem.pszText = buffer;
	tvItem.lParam = static_cast<LPARAM>(Playlist::Type::User);
	tvItem.iImage = GetIconIndex(Playlist::Type::User);
	tvItem.iSelectedImage = tvItem.iImage;
	TVINSERTSTRUCT tvInsert = {};
	tvInsert.hParent = m_NodePlaylists;
	tvInsert.hInsertAfter = TVI_SORT;
	tvInsert.itemex = tvItem;
	TreeView_SelectItem(m_hWnd, NULL/*hITem*/);
	HTREEITEM hItem = TreeView_InsertItem(m_hWnd, &tvInsert);

	Playlist::Ptr playlist(new Playlist(m_Library, Playlist::Type::User));
	m_PlaylistMap.insert(PlaylistMap::value_type(hItem, playlist));

	SetFocus(m_hWnd);
	TreeView_SelectItem(m_hWnd, hItem);
	TreeView_EditLabel(m_hWnd, hItem);

	return playlist;
}

void WndTree::DeleteSelectedPlaylist()
{
	HTREEITEM hSelectedItem = TreeView_GetSelection(m_hWnd);
	const auto playlistIter = m_PlaylistMap.find(hSelectedItem);
	if (m_PlaylistMap.end() != playlistIter)
	{
		const Playlist::Ptr playlist = playlistIter->second;
		if (playlist)
		{
			m_Settings.RemovePlaylist(*playlist);
			m_PlaylistMap.erase(playlistIter);
			TreeView_DeleteItem(m_hWnd, hSelectedItem);
		}
	}
}

std::wstring WndTree::GetItemLabel(const HTREEITEM item) const
{
	const int bufferSize=256;
	WCHAR buffer[bufferSize] = {};
	TVITEMEX tvItem = {};
	tvItem.mask = TVIF_TEXT;
	tvItem.hItem = item;
	tvItem.cchTextMax = bufferSize;
	tvItem.pszText = buffer;
	if (nullptr != item)
	{
		TreeView_GetItem(m_hWnd, &tvItem);
	}
	const std::wstring label = buffer;
	return buffer;
}

std::set<std::wstring> WndTree::GetPlaylistNames() const
{
	std::set<std::wstring> names;
	if (nullptr != m_NodePlaylists)
	{
		HTREEITEM playlistItem = TreeView_GetChild(m_hWnd, m_NodePlaylists);
		while (nullptr != playlistItem)
		{
			names.insert(GetItemLabel(playlistItem));
			playlistItem = TreeView_GetNextSibling(m_hWnd, playlistItem);
		}
	}
	return names;
}

void WndTree::RenameSelectedPlaylist()
{
	TreeView_EditLabel(m_hWnd, TreeView_GetSelection(m_hWnd));

}

void WndTree::ImportPlaylist(const std::wstring& filename)
{
=======
void WndTree::ApplySettings()
{
	LOGFONT logFont = GetFont();
	COLORREF fontColour = TreeView_GetTextColor(m_hWnd);
	COLORREF backgroundColour = TreeView_GetBkColor(m_hWnd);
	bool favourites = false;
	bool allTracks = false;
	bool artists = false;
	bool albums = false;
	bool genres = false;
	bool years = false;
	m_Settings.GetTreeSettings(logFont, fontColour, backgroundColour, m_ColourHighlight, favourites, allTracks, artists, albums, genres, years);
	TreeView_SetTextColor(m_hWnd, fontColour);
	TreeView_SetBkColor(m_hWnd, backgroundColour);
	SetFont(logFont);
}

void WndTree::CreateImageList()
{
	const float dpiScale = GetDPIScaling();


>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58

}
