#pragma once
#include <assert.h>

///
/// Sample databuffer
/// Used to pass data between generator stages.
/// Unlike a traditional array reading off the start of the buffer returns the first value,
/// reading off the end returns the last value.
///
class SampleDataBuffer
{
private:
	SampleDataBuffer();									// deliberately not implemented
	SampleDataBuffer & operator=(const SampleDataBuffer &rhs);	// deliberately not implemented so we dont accidentally assign
	SampleDataBuffer(const SampleDataBuffer&);					// deliberately not implemented copy constructor

public:
	SampleDataBuffer(int length);		// Construct a new buffer with the given size (buffer cannot be zero length)
	~SampleDataBuffer();

public:
	inline int GetLength() const
	{
		return length;
	}

	inline float & Get(int i) const
	{
		return buffer[(i < 0) ? 0 : ((i >= length) ? length : i) ];
	}
	inline float & operator[](int i) const
	{
		return Get(i);
	}

protected:
	int length;
	float * buffer;
};

