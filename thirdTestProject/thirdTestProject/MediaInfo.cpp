#include "pch.h"
#include "MediaInfo.h"


MediaInfo::MediaInfo(const std::wstring& filename) :
	m_Filename(filename),
	m_Filetime(0),
	m_Filesize(0),
	m_Duration(0),
	m_SampleRate(0),
	m_BitsPerSample(0),
	m_Channels(0),
	m_Artist(),
	m_Title(),
	m_Album(),
	m_Genre(),
	m_Year(0),
	m_Comment(),
	m_Track(0),
	m_Version(),
	m_GainTrack(NAN),
	m_GainAlbum(NAN),
	m_Source(Source::File),
	m_CDDB(0)
{

}

MediaInfo::MediaInfo(const long cddbID) :
	MediaInfo()
{
	m_Source = Source::CDDA;
	m_CDDB = cddbID;
}

MediaInfo::~MediaInfo()
{

}

bool MediaInfo::operator<(const MediaInfo& other) const
{
	const bool lessThan = std::tie(m_Filename, m_Filetime, m_Filesize, m_Duration, m_SampleRate, m_BitsPerSample, m_Channels, m_Artist,
		m_Title, m_Album, m_Genre, m_Year, m_Comment, m_Track, m_Version, m_GainTrack, m_GainAlbum, m_ArtworkID, m_Source, m_CDDB) <
		std::tie(other.m_Filename, other.m_Filetime, other.m_Filesize, other.m_Duration, other.m_SampleRate, other.m_BitsPerSample, other.m_Channels, other.m_Artist,
			other.m_Title, other.m_Album, other.m_Genre, other.m_Year, other.m_Comment, other.m_Track, other.m_Version, other.m_GainTrack, other.m_GainAlbum,
			other.m_ArtworkID, other.m_Source, m_CDDB);
	return lessThan;
}
