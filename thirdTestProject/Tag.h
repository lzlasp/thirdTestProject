#pragma once

#include <map>
#include <string>

enum class Tag
{
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
	Artwork
};

// Map a tag type to the UTF-8 encoded tag content.
typedef std::map<Tag, std::string> Tags;