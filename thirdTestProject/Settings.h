#pragma once

#include <list>
#include <map>

#include "Database.h"
#include "Library.h"
#include "Playlist.h"


// MOD music fadeout flag.
static const DWORD VUPLAYER_MUSIC_FADEOUT = 0x80000000;

// Application Settings.
class Settings
{
public:
	
	/*
	*	'database' - application database.
	*	'library' - media library.
	*	'settings' - initial settings, used when running in 'protocol' mode.
	*/
	Settings(Database& database, Library& library, const std::string& settings = std::string());

	virtual ~Settings();

	// Playlist column information.
	struct PlaylistColumn
	{
		int ID;		//Column ID.
		int Width;	//Column width.
	};

	// HotKey information.
	struct Hotkey
	{
		int ID;			// ID.
		int Key;		// Key code.
		bool Alt;		// Alt key modifier.
		bool Ctrl;		// Control key modifier.
		bool Shift;		// Shift key modifier.
	};

	//Output mode.
	enum class OutputMode
	{
		Standard,
		WASAPIExclusive,
		ASIO
	};

	// Gain mode.
	enum class GainMode
	{
		Disabled,
		Track,
		Album
	};

	// Limiter mode.
	enum class LimitMode
	{
		None,
		Hard,
		Soft
	};

	//Notification area icon click commands.
	enum class SystrayCommand
	{
		None = 0,
		Play,
		Stop,
		Previous,
		Next,
		ShowHide
	};

	// Pich range ooptions.
	enum class PitchRange
	{
		Samll = 0,
		Medium,
		Large
	};

	// EQ settings.
	struct EQ
	{
		// Maps a centre frequency, in Hz, to a gain value.
		typedef std::map<int, float> GainMap;

		// Indicates that the EQ window is centred.
		static const int Centred = INT_MIN;

		// Maximum gain in dB.
		static const int MaxGain = 9;

		// minimum gain in dB.
		static const int MinGain = -9;

		EQ():
			Visible(false),
			X(Centred),
			Y(Centred),
			Enabled(false),
			Preamp(0),
			Gains({ {80,0.f},{140,0.f},{250,0.f},{500,0.f},{1000,0.f},{2000,0.f},{4000,0.f},{8000,0.f},{14000,0.f} }),
			BandWidth(12)
		{

		}

		bool Visible;			// Indicates whether the EQ window is shown.
		int X;					// EQ window X position.
		int Y;					// EQ window Y position.
		bool Enabled;			// Indicates whether EQ is enabled.	
		float Preamp;			// Preamp in the range -15 to +15dB.
		GainMap Gains;			// Gain in the range -15 to +15dB.
		float BandWidth;		//Bandwidth in semitones.
	};

	// A list of playlist columns.
	typedef std::list<PlaylistColumn> PlaylistColumns;

	// A list of hotkeys.
	typedef std::list<Hotkey> HotkeyList;

	// Maps a pitch range option be a pitch adjustment factor.
	typedef std::map<PitchRange, float> PitchRangeMap;

	/*	Returns the playlist control settings.
	*	'columns' - out, column settings.
	*	'font - out, list control font.
	*	'fontColour' - out list control font colour.
	*	'backgroundColour' - out, list control background colour.
	*	'highlightColour' - out, list control highlight colour.
	*/
	void GetPlaylistSettings(PlaylistColumns& columns, LOGFONT& font, COLORREF& fontColour, COLORREF& backgroundColour, COLORREF& highlightColour);


	/*	Sets the playlist control settings.
	*	'columns' - column settings.
	*	'font' - list control font.
	*	'fontColour' - list control font colour.
	*	'backgroundColour' - list control background colour.
	*	'highlightColour' - list control highligh colour.
	*/
	void SetPlaylistSettings(const PlaylistColumns& columns, const LOGFONT& font, const COLORREF& fontColuor, const COLORREF& backgroundColour, const COLORREF& highlightColour);

	/*	Retunrs the tree control settings.
	*	'font' -out, tree control font.
	*	'fontColour' - out, tree control font colour.
	*	'backgroundColour' - out, tree control background colour.
	*	'highlightColour' - out, tree control hightlight colour.
	*	'showFavourites' - out, whether Favourites is shown.
	*	'showAllTracks' - out, whether All Tracks is shown.
	*	'showArtists' - out, whether Artists are shown.
	*	'showAlbums' -out, whether Albums are shown.
	*	'showGenres' - out, whether Genres are shown.
	*	'showYears' - out, whether Years are shown.
	*/
	void GetTreeSettings(LOGFONT& font, COLORREF& fontColour, COLORREF& backgroundColour, COLORREF& highlightColour,
		bool& showFavourites, bool& showAllTracks, bool& showArtists, bool& showAlbums, bool& showGenres, bool& showYears);

	/*	Sets the tree control settings.
	*	'font' - tree control font.
	*	'fontColour' - tree control font colour,
	*	'backgroundColour' - tree control backgoround colour.
	*	'highlightColour' - tree control highlight colour.
	*	'showFavourtes' - whether Favourites is shown.
	*	'showAllTracks' - whether All Track is shown.
	*	'showArtists' - whether Artists are shown.
	*	'showAlbums' - whether Albums are shown.
	*	'showGenres' - whether Genres are shown.
	*	'showYears' - whether Years are shown.
	*/
	void SetTreeSettings(const LOGFONT& font, const COLORREF& fontColour, const COLORREF& backgroundColour, const COLORREF& highlightColour,
		const bool showFavourites, const bool showAllTracks, const bool showArtists, const bool showAlbums, const bool showGenres, const bool showYears);

	// Gets the playlists.
	Playlists GetPlaylists();
	
	// Gets the playlists.
	Playlist::Ptr GetFavourites();

	// Gets the playlists.
	Playlists GetPlaylists();

	// Gets the Favourites playlsit.
	Playlist::Ptr GetFavourites();

	// Removes a playlist from the database.
	void RemovePlaylist(const Playlist& playlist);

	// Saves a playlist to the database.
	void SavePlaylist(Playlist& playlist);

	// Gets the oscilloscope colour.
	COLORREF GetOscillosecapeColour();

	// Sets the oscilloscope colour.
	void SetOscilloscopeColour(const COLORREF colour);

	// Gets the oscilloscope background colour.
	COLORREF GetOscilloscopeBackground();
	
	// Sets the oscilloscope background colour.
	void SetOscilloscopeBackground(const COLORREF colour);

	/*	 Gets the spectrum analyser settings.
	*	'base' - out, base colour.
	*	'peak' - out, peak colour.
	*	'background' - background colour.
	*/
	void GetSpectrumAnalyserSettings(COLORREF& base, COLORREF& peak, COLORREF& background);

	/*	Sets the spectrum analyser settings.
	*	'base' - out, base colour.
	*	'peak' - out, peak colour.
	*	'background' =out, background colour.
	*/
	void SetSpectrumAnalyserSettings(const COLORREF& base, const COLORREF& peak, const COLORREF& background);

	/*	Gets the peak meter settings.
	*	'base' - out, base colour.
	*	'peak' - peak colour.
	*	'background' - background colour.
	*/
	void GetPeakMeterSettings(COLORREF& base, COLORREF& peak, COLORREF& background);

	/*	Sets the peak meter settings.
	*	'base' - out, base colour.
	*	'peak' - out, peak colour.
	*	'background -out, background colour.
	*/
	void SetPeakMeterSettings(const COLORREF& base, const COLORREF& peak, const COLORREF& background);

	// Gets the VUMeter decay settings.
	float GetVUMeterDecay();

	// Sets the VUMeter decay settings.
	void SetVUMeterDecay(const float decay);

	/*	Gets the application startup position settings.
	*	'x' - out, desktop X position.
	*	'y' - out, desktop Y position.
	*	'width' - out, main window width.
	*	'height' - out, main window height.
	*	'maximised' - out, whether the main window is maximised.
	*	'minimsed' - out, whether the main window is minimised.
	*/
	void GetStartupPosition(int& x, int& y, int& width, int& height, bool& maximised, bool& minimised);

	/*	Sets the application startup position settings.
	*	'x' - desktop X position.
	*	'y' - desktop Y position.
	*	'width' - main window width.
	*	'height' - main window height.
	*	'maximesed' - whether the main window is maximised.
	*	'minimsed' - whether the main window is minimsed.
	*/
	void SetStartupPosition(const int x, const int y, const int width, const int height, const bool maximised, const bool minimised);

	// Retuns the startup visual ID.
	int GetVisualID();

	// Sets the startup visual ID.
	void SetVisualID(const int visualID);

	//	Returns the startup split width.
	int GetSplitWidth();

	// Sets the startup split width.
	void SetSplitWidth(const int width);

	// Returns the startup volume level.
	float GetVolume();

	// Sets the startup volume level.
	void SetVolume(const float volume);

	// Gets the startup 'playlist'.
	std::wstring GetStartupPlaylist();

	// Sets the startup 'playlist'.
	void SetStartupPlaylist(const std::wstring& playlist);

	// Gets the startup 'filename'.
	std::wstring GetStartupFilename();

	// Sets the startup 'filename'.
	void SetStartupFilename(const std::wstring& filename);

	/*	Gets the counter settings.
	*	'font - out, counter font.
	*	'fontColour' - out, counter colour.
	*	'showRemaining' - out, true to diaplay remianing time, false for elapsed time.
	*/
	void GetCounterSettings(LOGFONT& font, COLORREF& colour, bool& showRemaining);

	/*	Sets the counter settings.
	*	'font -counter font.
	*	'fontCOlour' - counter colour.
	*	'showRemaining' - true to diaplay remaining time, false for elapsed time.
	*/
	void SetCounterSettings(const LOGFONT& font, const COLORREF colour, const bool showRmaining);

	/*	Gets the outout settings.
	*	'deviceName' - out, device name (or an empty string for the default device).
	*	'mode' - out, output mode.
	*/
	void GetOutputSettings(std::wstring& deviceName, OutputMode& mode);

	/*	Sets the output settings.
	*	'deviceName' - device anem (or an empty string for the default device).
	*	'mode' - ouput mode.
	*/
	void SetOutputSettings(std::wstring& deviceName, const OutputMode mode);

	/*	Gets default MOD music settings.
	*	'mod' -out, MOD settings.
	*	'mtm' - out, MTM settings.
	*	's3m' - out, S3M settings.
	*	'xm' - out, XM settings.
	*	'it' - out, IT settings.
	*/
	void GetDefaultMODSettings(long long& mod, long long& mtm, long long& s3m, long long& xm, long long& it);

	/*	Gets default MOD music settings.
	*	'mod' - outMOD settings.
	*	'mtm' - out, MTM settings.
	*	's3m' - out, S3M settings.
	*	'xm' - out, XM settings.
	*	'it' - out, IT settings.
	*/
	void GetMODSettings(long long& mod, long long& mtm, long long& s3m, long long& xm, long long& it);

	/*	Sets MOD music settings.
	*	'mod' - MOD settings.
	*	'mtm' - MTM settings.
	*	's3m' - S3M settings.
	*	'xm' - XM settings.
	*	'it' - IT settings.
	*/
	void SetMODSettings(const long long mod, const long long mtm, const long long s3m, const long long xm, const long long it);

	/*	Gets default gain settings.
	*	'gainMode' - out, gain mode.
	*	'limitMode' - out, limiter mode.
	*	'preamp' - out, preamp in dB.
	*/
	void GetDefaultGainSettings(GainMode& gainMode, LimitMode& limitMode, float& preamp);

	/*	Gets gain settings.
	*	'gainMode' - out, gain mode.
	*	'limitMode' - out, limiter mode.
	*	'preamp' - out, preamp in dB.
	*/
	void GetGainSetitings(GainMode& gainMode, LimitMode& limitMode, float& preamp);

	/*	Sets gain settings.
	*	'gainMode' - gin mode.
	*	'limitMode' - limitMode.
	*	'preamp' - preamp in dB.
	*/
	void SetGainSettings(const GainMode gainMode, const LimitMode limitMode, const float preamp);

	/*	Gets notification area settings.
	*	'enable' - out, whether the notification area icon is show.
	*	'singleClick' - out, single click action.
	*	'doubleClick' - out, double click action.
	*/
	void GetSystraySettings(bool& enable, SystrayCommand& singleClick, SystrayCommand& doubleClick);

	/*	Sest notification area settings.
	*	'enable' - whether the notification area icon is shown.
	*	'singleClick' - single click action.
	*	'dobleClick' - double click action.
	*/
	void SetSystraySettings(const bool enable, const SystrayCommand singleClick, SystrayCommand doubleClick);

	/*	Gets playback settings.
	*	'randomPlay' - whther random playback is enabled.
	*	'repeatTrack' - whether repeatTrack is enabled.
	*	'repeatPlaylist' - whether repeat playlist is enabled.
	*	'crossfade' - whether crossfade is enabled.
	*/
	void GetPlaybackSettings(bool& randomPlay, bool& repeatTrack, bool& repeatPlaylist, bool& crossfade);

	/*	Sets playback settings.
	*	'randomPlay' - whether random playback is enabled.
	*	'repeatTrack' - whether repeat track is enabled.
	*	'repeatPlaylist' - ehrther repeat playlist is enabled.
	*	'crossfade' - whether crossfade is enabled.
	*/
	void SetPlaybackSettings(const bool randomPlay, const bool repeatTrack, const bool repeatPlaylist, const bool crossfade);

	/*	Gets hotkey settings.
	*	'enable' - out, whether hotkeys are enabled.
	*	'hotkeys' - out, hotkeys.
	*/
	void GetHotkeySettings(bool& enable, HotkeyList& hotkeys);

	/*	Sets the hitkey settings.
	*	'enabled' - whether hotkeys are enabled.
	*	'hokeys' hotkeys.
	*/
	void SetHotkeySettings(const bool enable, const HotkeyList& hotkeys);

	// Gets the pitch range.
	PitchRange GetPitchRange();

	// Sets the pitch range.
	void SetPitchRange(const PitchRange range);

	// Returns the available pitch range options.
	PitchRangeMap GetPitchRangeOptions() const;

	// Gets the output control type (volume, pitch,etc).
	int GetOutputControlType();

	// Sets the output control type (volume, pitch,etc).
	void SetOutputControlType(const int type);

	//	Returns the track conversion/extraction settings.
	void GetExtractSettings(std::wstring& folder, std::wstring& filename, bool& addToLibrary, bool& joinTracks);

	//	Sets the track conversion/extraction settings. 
	void SetExtrackSettings(const std::wstring folder, const std::wstring filename, const bool addToLibrary, const bool jonTracks);

	/*	Gets Gracenote Settings.
	*	'userID' - Gracenote user ID string.
	*	'enable' whether to enalbe Gracenote functionality.
	*	'enableLog' - whether to enalbe loggin of Gracenote functionality.
	*/
	void GetGracenoteSettings(std::string& userID, bool& eanble, bool& enableLog);

	/*	Sets Gracenote settings.
	*	'userID' - Gracenote user ID string.
	*	'enable' - shether to enable Gracenote functionnality.
	*	'enableLog' - whether to enalbel logging of Gracenote functionality.
	*/
	void SetGracenoteSettings(const std::string& userID, const bool enale, const bool enableLog);

	// Gets EQ settings.
	EQ GetEQSettings();

	// Sets EQ settings.
	void SeEQSettings(const EQ& eq);

	// Gets the name of the 'eccoder' to use for voncersion.
	std::wstring GetEncoder();

	// Sets the name of the 'encoder' to use for conversion.
	void SetEncoder(const std::wstring& encoder);

	// Gets the 'settings' for the 'encoder' name.
	std::string GetEncoderSettings(const std::wstring& encoder);

	// Sets the 'settings' for the 'encoder' name.
	void SetEncoderSettings(const std::wstring& encoder, const std::string& settings);

	// Gets the soundfont file name to use for MIDI palyback.
	std::wstring GetSoundFont();

	// Sets the soundfont file name to use for MIDI playback.
	void SetSoundFont(const std::wstring& filename);

	// Returns whether the 'toolbarID' is enabled.
	bool GetToolbarEnabled(const int toolbarID);

	// Sets whether the 'toolbarID' is 'enabled'.
	void SetToolbarEnabled(const int toolbarID, const bool enabled);

	// Returns ehther duplicate tracks are merged (for Artist/Ablum/Genre/Year playlists).
	bool GetMergeDuplicates();

	// Sets whether duplicate tracks are merged ( for Artist/Album/Genre/Year playlists).
	void GetMergeDuplicates(const bool mergeDuplicates);

	// Returns the last user selected folder for the 'folderType'.
	std::wstring GetLastFolder(const std::string& folderType);

	// Sets the last user selected 'folder' for the 'folderType'.
	void SetLastFolder(const std::wstring& folderType, const std::wstring& folder);

	// Retruns whether scrobbling is enabled.
	bool GetscrobblerEnabled();

	// Sets whether scrobbling is enabled.
	void GetScrobblerEnabled(const bool enabled);

	// Returns the scrobbler session key.
	std::string GetScrobblerKey();

	// Sets the scrobbler session 'key'.
	void SetScrobblerKey(const std::string& key);

	// Exports the settings in JSON format to 'output'.
	void ExportSettings(std::string& output);

	/*	Gets the default (and maximum allowed) advanced WASAPI exlusive mode settings.
	*	'useDeviceDefaultFormat' - out, true to use the device's default sample format, false to use the source sample format.
	*	'bufferLength' - out, buffer length, in milliseconds.
	*	'leadIn' - out, lead-in length, in milliseconds.
	*	'maxBufferLength' - out, maximum buffer length, in milliseconds.
	*	'maxLeadIn' - out, maximum lead-in length, in milliseconds.
	*/
	void GetDefaultAdvancedWasapiExclusiveSettings(bool& useDeviceDefaultFormat, int& bufferLength, int& leadIn, int& maxBufferLength, int& maxLeadIn);

	/*	Gets the advanced WASAPI exclusive mode settings.
	*	'useDeviceDefaultFormat' - out, true to use the device's default sample format, false to use the source sample format.
	*	'bufferLength' - out, buffer length, in milliseconds.
	*	'lead-in' out, lead-in length, in milliseconds.
	*/
	void GetAdvancedWasapiExclusiveSettings(bool& useDeviceDefualtFormat, int& bufferLength, int& leadIn);

	/*	Sets the advanced WASAPI exclusive mode settings.
	*	'useDeviceDefaultFormat' - true to use the device's default sample format, false to use the source sampel format.
	*	'bufferLength' - buffer elngth, in nilliseconds.
	*	'leadIn' - lead0in length, in milliseconds.
	*/
	void SetAdvancedWasapiExclusiveSettings(const bool useDeviceDefaultFormat, const int bufferLength, const int leadIn);

	/*	Gets the default (and maximum allowed) advanced ASIO settings.
	*	'useDefaultSamplerate' - out, true to use the default sample rate, false to use the source sample rate.
	*	'defaultSamplerate' - out, default sample rate, in Hz.
	*	'leadIn' - out, lead-in length, in milliseconds.
	*	'maxDefaultSamplerate' - out, maximum sample rate, in Hz.
	*	'maxLeadIn' - out, maxmum lead-in length, in milliseconds.
	*/
	void GetDefaultAdvancedASIOSettings(bool& useDefaultSamplerate, int& defaultSamplerate, int& leadIn, int& maxDefaultSamplerate, int& maxLeadIn);

	/*	Gets the advanced ASIO settings.
	*	'useDefaultSamplerate' - out, true to use the default sample rate, false to use the source sample rate.
	*	'defaultSamplerate' - out, default sample rate, in Hz.
	*	'leadIn - out, lead-in length, in milliseconds.
	*/
	void GetAdvancedASIOSettings(bool& useDefaultSamplerate, int& defaultSamplerate, int& leadIn);

	/*	Sets the advanced ASIO settings.
	*	'useDefaultSamplerate' - true to use the default smaple rate, false to use the source sample rate.
	*	'defaultSamplerate' - default sample rate, in Hz.
	*	'leadIn' - lead-in length, in milliseconds.
	*/
	void SetAdvancedASIOSettings(const bool useDefaultSamplrate, const int defaultSamplerate, const int leadIn);




private:
	// Updates the database to the current version if necessary.
	void UpdateDatabse();

	// Updates the settings table if necessary.
	void UpdateSettingsTable();

	// Updates the playlist columns table if necessary.
	void UpdatePlaylistColumnTable();

	// Updates the playlist resources table if necessary.
	void UpdatePlaylistsTable();

	// Updates the hotkeys table if necessary.
	void UpdateHotkeysTable();

	// Updates the playlist table if necessary.
	void UpdatePlaylistTable(const std::string& table);

	// Sets the playlist files from the database.
	void ReadPlayListFiles(Playlist& playlist);

	// Imports the JSON format settings from 'input'. 
	void ImportSettings(const std::string& input);

	// Returns whether a GUID string is valid.
	static bool IsValueGUID(const std::string& guid);

	// Database.
	Database& m_Database;
	// Media library.
	Library& m_Library;
};

