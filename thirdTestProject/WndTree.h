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

	//
	virtual ~WndTree();

	// Returns the default window procedure.
	WNDPROC GetDefaultWndProc();
	
	//
	HWND GetWindowHandle();

	//
	
};

