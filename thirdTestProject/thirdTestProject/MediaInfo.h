#pragma once

#include <list>
#include <string>

#include "Tag.h"

// Minimum valid year.
static const long MINYEAR = 1000;

// Maximum valid Year.
static const long MAXYEAR = 9999;

// Loudness reference level in LUFS.
static const float LOUDNESS_REFERENCE = -18.0f;

// Media information.
class MediaInfo
{
	// A list of media information.
	typedef std::list<MediaInfo> List;

	// Source types.
	enum class Source
	{
		File,
		CDDA
	};

	// 'filename' - media file name (from file sources).
	MediaInfo(const std::wstring& filename = std::wstring());

	// 'cddbID' - CDDB ID (for CDDA sources).
	MediaInfo(const long cddbID);

	virtual ~MediaInfo();

	// less than operator.
	bool operator<(const MediaInfo& other) const;

	// Tags cast operator.
	operator Tags() const;

	// Returns the filename.
	const std::wstring& GetFilename() const;

	// Sets the filename.
	void SetFilename(const std::wstring& filename);

	// Returns the last modified timestamp.
	long long GetFiletime() const;

	// Sets the last modified timestamp.
	void SetFiletime(const long long filetime);

	// Returns the filesize, in bytes.
	long long GetFilesize() const;

	// Sets the filesize, in bytes.
	void SetFilesize(long long filesize);

	// Returns the duration, in seconds.
	float GetDuration() const;

	// Sets the duration, in seconds.
	void SetDuration(const float duration);

	// Returns the Smaple rate.
	long GetSampleRate() const;

	// Sets the sample rate.
	void SetSampleRate(const long sampleRate);

	// Returns the bits per smaple, if relevant.
	long GetBitsPerSample() const;

	// Sets the bits per sample, if relevant.
	void SetBitsPerSample(const long bitsPerSample);

	// Returns the channels cout.
	long GetChannels()const;
	
	// Sets the channles count.
	void SetChannels(const long channels);

	// Returns the artist.
	const std::wstring& GetArtist() const;

	// Sets the artist.
	void SetArtist(const std::wstring& artist);

	// Sets the title.
	void SetTitle(const std::wstring& title);

	// Returns the album.
	const std::wstring& GetAlbum() const;

	//
	void SetAlbum(const std::wstring& album);

	// Returns the genre.
	const std::wstring& GetGenre() const;

	// Sets the genre.
	void SetGenre(const std::wstring& genre);

	// Returns the year.
	long GetYear() const;

	// Sets the year.
	void SetYear(const long year);

	// Returns the comment.
	const std::wstring& GetComment() const;

	// Sets the comment.
	void SetComment(const std::wstring& commnet);

	// Returns the track number.
	long GetTrack() const;

	// Sets the track number.
	void SetTrack(const long track);

	// Returns the format version.
	const std::wstring& GetVersion() const;

	// Sets the format version.
	void SetVersion(const std::wstring& version);

	// Returns the track gain, in dB(or NaN if there is no gain).
	float GetGainTrack() const;

	// Sets the track gain, in dB.
	void SetGainTrack(const float gain);

	// Returns the album gain, in dB(or NaN if there is no gain.)
	float GetGainAlbum() const;

	// Sets the album gain, in dB.
	void SetGainAlbum(const float gain);

	// Returns the title.
	// 'filenameAsTitle' - whether to return the filename if there is no title.
	std::wstring GetTitle(const bool filenameAsTitle = false) const;

	// Returns the filename extension.
	std::wstring GetType() const;

	// Returns the bitrate.
	long GetBitRate() const;

	/*	Returns the artwork ID.
	*	'checkFolder' - if ture and there is no artwork ID, returns the filename of any artwork in the media file's folder.
	*/
	std::wstring GetArtworkID(const bool checkFolder = false) const;

	// Sets the artwork ID.
	void SetArtworkID(const std::wstring& id);

	// Returns the media source.
	Source GetSource() const;

	// Returns the CDDB ID.
	long GetCDDB() const;

	// Returns whether the 'other' media information is a duplication of this one.
	bool IsDuplicate(const MediaInfo& other) const;

	/*	Gets common media information (restricted to artist, title, ablum, genre, year, comment, track, artwork).
	*	'mediaList' - the list of media to query.
	*	'commonInfo' - out, common media information.
	*	Returns whether any common information was retrieved.
	*/
	static bool GetCommonInfo(const List& mediaList, MediaInfo& commonInfo);

private:
	std::wstring m_Filename;
	long long m_Filetime;
	long long m_Filesize;
	float m_Duration;
	long m_SampleRate;
	long m_BitsPerSample;
	long m_Channels;
	std::wstring m_Artist;
	std::wstring m_Title;
	std::wstring m_Album;
	std::wstring m_Genre;
	long m_Year;
	std::wstring m_Comment;
	long m_Track;
	std::wstring m_Version;
	float m_GainTrack;
	float m_GainAlbum;
	std::wstring m_ArtworkID;
	Source m_Source;
	long m_CDDB;
};

