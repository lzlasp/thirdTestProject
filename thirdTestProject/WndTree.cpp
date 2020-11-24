#include "pch.h"
#include "WndTree.h"

#include <PathCch.h>
#include <Shlwapi.h>
#include <Uxtheme.h>
#include <windowsx.h>

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

//
static const UINT MSG_FOLDERADD = WM_APP + 110;

//
static const UINT MSG_FOLDERDELETE = WM_APP + 111;

//
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
	}
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



}
