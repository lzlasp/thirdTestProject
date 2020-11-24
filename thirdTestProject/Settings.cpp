#include "pch.h"
#include "Settings.h"

void Settings::GetTreeSettings(LOGFONT& font, COLORREF& fontColour, COLORREF& backgroundColour, COLORREF& highlightColour,
	bool& showFavourites, bool& showAllTracks, bool& showArtists, bool& showAlbums, bool& showGenres, bool& showYears)
{

	sqlite3* database = m_Database.GetDatabase();
	if (nullptr != database)
	{
		sqlite3_stmt* stmt = nullptr;
		std::string query = "SELECT Value FROM Settings WHERE Setting='TreeFont';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				const int bytes = sqlite3_column_bytes(stmt, 0);
				if (sizeof(LOGFONT) == bytes)
				{
					font = *reinterpret_cast<const LOGFONT*>(sqlite3_column_blob(stmt, 0));
				}
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE Settings='TreeFontColour';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				backgroundColour = static_cast<COLORREF>(sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE Settings='TreeFavourites';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				showFavourites = (0 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE Setting='TreeAllTracks';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				showAllTracks = (0 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE setting='TreeArtists';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)))
			{
			showArtists = (0 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE setting='TreeAlbums';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				showAlbums = (1 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE setting='TreeGenres';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				showGenres = (1 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
		stmt = nullptr;
		query = "SELECT Value FROM Settings WHERE setting='TreeYears';";
		if (SQLITE_OK == sqlite3_prepare_v2(database, query.c_str(), -1, &stmt, nullptr))
		{
			if ((SQLITE_ROW == sqlite3_step(stmt)) && (1 == sqlite3_column_count(stmt)))
			{
				showYears = (1 != sqlite3_column_int(stmt, 0));
			}
			sqlite3_finalize(stmt);
		}
	}
}
