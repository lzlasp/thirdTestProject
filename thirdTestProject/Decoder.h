#pragma once

#include <memory>
#include <string>

class Decoder
{
public:
	Decoder();
	virtual ~Decoder();

	//
	typedef std::shared_ptr<Decoder> Ptr;

	/***/
	virtual long Read(float* buffer, const long sampleCount) = 0;

	/**/
	virtual float Seek(const float position) = 0;


};

