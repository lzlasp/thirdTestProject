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
	struct HotKey
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

