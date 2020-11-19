#pragma once

#include "Handler.h"

class Handlers
{
public:
	Handlers();
	virtual ~Handlers();

	/*	Opens a decoder.
	*	'filename' - file to open.
	*	Returns the decoder, or nullptr if the stream could not be opened.
	*/
	Decoder::Ptr OpenDecoder(const std::wstring& filename) const;

	//	Reads 'tags' from 'filename', returning true if the tags were read.
	bool GetTags(const std::wstring& filename, Tags& tags) const;

	//	Writes 'tags' to 'filename', returning true if the tags were written.
	bool SetTags(const std::wstring& fileanme, const Tags& tags) const;

	//	Returns all the file extensions supported by the decoders, as set of lowercase strings.
	std::set<std::wstring> GetAllSupportedFileExtensions() const;

	//	Returns the BASS library version.
	std::wstring GetBaseVersion() const;

	//	Adds a 'handler'.
	void AddHandler(Handler::Ptr handler);
	
	//	Returns the available encoders.
	Handler::List GetEncoder() const;

	/*	Open a encoder matching the 'desciption'.
	*	Returns the encoder, or nullptr if an encoder could not opened.
	*/
	Encoder::Ptr OpenEncoder(const std::wstring& description) const;

	// Called when the application 'settings' have changed.
	void SettingsChanged(Settings& settings) const;

	// Initialises the handlers with the application 'settings'.
	void Init(Settings& settings);

private:
	//	Returns a decoder handler supported by the 'filename' extension, or nullptr of there was no match.
	Handler::Ptr FindDecoderHandler(const std::wstring& filename) const;

	// Available Handlers.
	Handler::List m_Handlers;
	
	//	Available decoders.
	Handler::List m_Decoders;

	//	Available encoders.
	Handler::List m_Encoders;
};

