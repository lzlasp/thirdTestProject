#pragma once

#include "Database.h"
#include "Handlers.h"
#include "MediaInfo.h"

#include <vector>
#include <set>

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

	/*	Updates media information and write out tag information to file.
	*	'previousMediaInfo' - previous media information.
	*	'updateMediaInfo' - updated media information.
	*/
	void UpdateMediaInfo(const MediaInfo& previousMediaInfo, const MediaInfo& updateMediaInfo);

	/*	Gets media artwork.
	*	'mediaInfo; - media information.
	*	Retruns the artwork image, or an empty array if there is no artwork.
	*/
	std::vector<BYTE> GetMediaArtwork(const MediaInfo& mediaInfo);

	/*	Adds media artwork to the database if does not already exist.
	*	'image' - artwork image.
	*	Returns the artwork ID.
	*/
	std::wstring AddArtwork(const std::vector<BYTE>& image);

	// Returns the artists contained in the media library.
	std::set<std::wstring> GetArtists();

	// Returns the ablums by 'artist' contained in the media library.
	std::set<std::wstring> GetAlbum();

	// Returns the genres contained in the media library.
	std::set<std::wstring> GetGenre();

	// Retruns the year contained in the media library.
	std::set<long> GetYears();

	// Returns the media information by 'artist' contained in the media library.
	MediaInfo::List GetMediaByArtist(const std::wstring& artist);

	// Returns the media information by 'album' contained in the media library.
	MediaInfo::List GetMediaByAlbum(const std::wstring& album);

	// Returns the miedia information by 'artist' & 'ablum' contained in the media library.
	MediaInfo::List GetMediaByArtistAndAlbum(const std::wstring& artist, const std::wstring& album);

	// Returns the media information by 'gener' contained in the media library.
	MediaInfo::List GetMediaByGenre(const std::wstring& genre);

	// Returns the media information by 'year' contained in the library.
	MediaInfo::List GetMeidaByYear(const long year);

	// Returns all media information contained in the meida library.
	MediaInfo::List GetAllMedia();

	//Returns whether the 'artist' exists in the media library.
	bool GetArtistExists(const std::wstring& artist);

	//	Returns whether the 'album' exists in the media library.
	bool GetAlbumExists(const std::wstring& album);

	// Returns whether the 'artist' & 'album' exists in the media library.
	bool GetArtistAndAlbumExists(const std::wstring& artist, const std::wstring& album);

	// Returns whether the 'genre' exists in the media library.
	bool GetGenreExists(const std::wstring& genre);

	// Returns whether the 'yearexists in the media libaray.
	bool GetYearExists(const long year);

	/*	Removes 'mediaInfo' from the library.
	*	Returns true if the library was updated.
	*/
	bool RemoveFromLibrary(const MediaInfo& mediaInfo);

	// Returns all th file extensions supported by the handlers, as a set of lowercase strings.
	std::set<std::wstring> GetAllSupportedFileExtesions() const;

	// Returns he 'mediaInfo' as tags.
	Tags GetTagw(const MediaInfo& mediaInfo);

	// Updates the track gain from the 'mediaInfo', returning whether the library was updated.
	bool UpdateTrackGain(const MediaInfo& mediaInfo);

private:
	// Media library columns.
	typedef std::map<std::string, Column> Columns;

	// Maps a filename to tag information.
	typedef std::map<std::wstring, Tags> FileTags;

	// Updates the database to the current version if necessary.
	void UpdateDatabase();

	// Updates the media table if necessary.
	void UpdateMediaTable();

	// Updates CDDA table if necessary.
	void UpdateCDDATable();

	// Updates the artgwork trable if necessary.
	void UpdateArtworkTable();


	// Create indices if necessary.
	void CreateIndices();

	/*	Updates the media library.
	*	'mediaInfo' - media information.
	*	Returns true if the library was updated.
	*/
	void UpdateMediaLibrary(const MediaInfo& mediaInfo);

	/*	Writes out tag information to file.
	*	'mediaInfo' - in/out, media oinformation which will be modified if tags are successfully wrtten.
	*	'tags' - tags to write.
	*/
	void WriteFileTags(MediaInfo& mediaInfo, const Tags& tags);

	/*	Adds an artwork to the media library.
	*	'id' - artwork ID.
	*	'artwork' - artwork image.
	*/
	bool AddArtwork(const std::wstring& id, const std::vector<BYTE>& image);

	/*	Searches the artwork table for a matching 'image'.
	*	Returns the image ID if an image was found, or an empty string if there was no match.
	*/
	std::wstring FindArtwork(const std::vector<BYTE>& image);

	// Sets 'mediaInfo' form a SQLITE 'stmt'.
	void ExtractMediaInfo(sqlite3_stmt* stmt, MediaInfo& mediaInfo);

	// Returns the library columns corresponding to 'source'.
	const Columns& GetColumns(const MediaInfo::Source source) const;

	// Updates 'mediInfo' with the 'tags'.
	void UpdateMediaInfoFromTags(MediaInfo& mediaINfo, const Tags& tags);

	// Adds any pending 'tags' for the 'filename', to be wrtten out at the next opportunity.
	void AddPendingTags(const std::wstring& filename, const Tags& tags);

	/*	Gets any pending 'tags' for the 'filename'.
	*	Retruns whether there are any pending tags.	
	*/
	bool GetPendingTags(const std::wstring& filename, Tags& tags) const;

	// Database.
	Database& m_Database;

	// The vailable handlers.
	const Handlers& m_Handlers;

	// Tag information waiting to be written.
	FileTags m_PendingTags;
	
	// Media library columns.
	Columns m_MediaColumns;

	// CD audio columns.
	Columns m_CDDAColumns;







};

