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
<<<<<<< HEAD
				showArtists = (0 != sqlite3_column_int(stmt, 0));
=======
			showArtists = (0 != sqlite3_column_int(stmt, 0));
>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58
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
<<<<<<< HEAD

void Settings::RemovePlaylist(const Playlist& playlist)
{
	sqlite3* database = m_Database.GetDatabase();
	if (nullptr != database)
	{
		const std::string& playlistID = playlist.GetID();
		if (IsValidGUID(playlistID))
		{
			const std::string dropFilesTableQuery = "DROP TABLE \"" + playlistID + "\";";
			sqlite3_exec(database, dropFilesTableQuery.c_str(), NULL, NULL, NULL);

			const std::string removePlaylistQuery = "SELECTE FROM Playlists WHERE ID=?1;";
			sqlite3_stmt* stmt = nullptr;
			if (SQLITE_OK == sqlite3_prepare_v2(database, removePlaylistQuery.c_str(), -1, &stmt, nullptr))
			{
				if (SQLITE_OK == sqlite3_bind_text(stmt, 1, playlistID.c_str(), -1, SQLITE_STATIC))
				{
					sqlite3_step(stmt);
				}
				sqlite3_finalize(stmt);
			}
		}
	}
}

bool Settings::IsValidGUID(const std::string& guid)
{
	RPC_CSTR rpcStr = new unsigned char[1 + guid.size()];
	int pos = 0;
	for (const auto& iter : guid)
	{
		rpcStr[pos++] = static_cast<unsigned char>(iter);
	}
	rpcStr[pos] = 0;
	UUID uuid;
	const bool valid = (RPC_S_OK == UuidFromStringA(rpcStr, &uuid));
	delete[] rpcStr;
	return valid;
}
=======
>>>>>>> a6f8ae015e913b8bf8fe8a9bf2d5e43b80ef6e58
