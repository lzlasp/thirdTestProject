// Gracenote (GNSDK) wrapper for VUPlayer.

#ifdef GN_EXPORT
#define gn_export extern "C" __declspec( dllexport )
#else
#define gn_export
#endif

// Track information.
struct gn_track
{
	const char* title;
	const char* artist;
	const char* genre;
	const char* year;
};

// Album information.
struct gn_album
{
	// Artwork data size.
	size_t artwork_data_size;

	// Artwork data.
	const unsigned char* artwork_data;

	// Track information array, with track index zero holding disc information.
	gn_track tracks[ 100 ];
};

// Query result.
struct gn_result
{
	// Indicates (with a non-zero value) if the result is an exact match.
	unsigned char exact_match;

	// Number of albums in the result.
	unsigned char album_count;

	// Album information array.
	gn_album* albums;
};

// Initialises Gracenote services.
// 'userID' - user ID string (if null, a new user ID string will be generated).
// 'userLanguage' - Gracenote language ID (if null, english will be used).
// 'userFolder' - folder to use for logging and caching.
// Returns (and generates, if necessary) the user ID string to use for all future queries.
// Returns nullptr if initialisation has failed.
gn_export const char* init( const char* userID, const char* userLanguage, const char* userFolder );

// Closes Gracenote services for 'userID'.
gn_export void close( const char* userID );

// Queries the Gracenote service for a CD album.
// 'userID' - user ID string.
// 'toc' - CD table of contents.
// Returns vugn_result, or nullptr if there were no matches.
gn_export const gn_result* query( const char* userID, const char* toc );

// Frees all resources for the 'result'.
gn_export void free_result( const gn_result* result );