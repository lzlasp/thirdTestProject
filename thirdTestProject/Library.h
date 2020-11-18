#pragma once

#include "Database.h"
#include "Handlers.h"
#include "MediaInfo.h"

#include <vector>

class Library
{
public:
	/*
	*	'database' - application database.
	*	'handlers' - available handlers.
	*/
	Library(Database& database, const Handlers& Handlers);

	virtual ~Library();

	// Media library column type.
	enum class Column
	{
		Filename=1,
		Filetime,
		Fileszie,
		Duration,
		SampleRate,
		BitsPerSample,
		Channels,
		Artist,
		Title,
		Album,
		Genre,
		Year,
		Comment,
		Track,
		Version,
		GainTrack,
		GainAlbum,
		//PeakTrack = 18, *DEPRECATED*
		//PeakAlbum = 19, *DEPRECATED*
		Artwork =20,
		CDDB = 21,

		_Undefined
	};

	/*	Gets media information.
	*	'mediaInfo' - in/out, media information containing the filename to query.
	*	'checkFileAttributes' - whether to check if the time/size of the file matches any existing entry.
	*	'scanMedia' - whether to scan the file specified in 'mediaInfo' if no matching database entry is found.
	*	'sendNotification' - whether to notify the main app if 'mediaInfo' has changed.
	*	'removeMissing' - whether to remove media information from the library if the file specified in 'mediaInfo' cannot be opened.
	*	Returns true if media information was returned.
	*/
	bool GetMediaInfo(MediaInfo& mediaInfo, const bool checkFileAttributes = true, const bool scanMedia = true, const bool sendNotification = true, const bool removeMissing = false);


};

