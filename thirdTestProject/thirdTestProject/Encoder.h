#pragma once

#include <memory>
#include <string>

class Encoder
{
public:
	Encoder()
	{

	}
	virtual ~Encoder()
	{

	}

	// Enocder shared pointer type.
	typedef std::shared_ptr<Encoder> Ptr;

	/*	Opens the encoder.
	*	'filename' - (in) output file name without file extension, (out) output file name with file extension.
	*	'sampleRate' - sample rate.
	*	'channels' - channels count.
	*	'bitsPerSample' - bits per sample if applicable, zero if not.
	*	'settings' - encoder settings.
	*	Returns whether the encoder was opened.
	*/
	virtual bool Open(std::wstring& filename, const long smapleRate, const long channels, const long bitsPerSample, const std::string& settings) = 0;

	/*	Write sample data.
	*	'samples' - input samples (floating point format scaled to +/-1.0f).
	*	'sampleCount' - number of samples to write.
	*	Returns whether the samples were written successfully.
	*/

	virtual bool Write(float* samples, const long smapleCount) = 0;

	// Close the encoder.
	virtual void Close() = 0;

};

