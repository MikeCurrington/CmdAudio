#pragma once
#include <assert.h>
#include <string.h>
#include "BaseCounted.h"

///
/// Sample databuffer
/// Used to pass data between generator stages.
/// Unlike a traditional array reading off the start of the buffer returns the first value,
/// reading off the end returns the last value.
///
class SampleDataBuffer
{
protected:
    SampleDataBuffer() : m_length(0), m_buffer(nullptr) {}
private:
    SampleDataBuffer & operator=(const SampleDataBuffer &rhs);	// deliberately not implemented so we dont accidentally assign
	SampleDataBuffer(const SampleDataBuffer&);					// deliberately not implemented copy constructor

public:
	SampleDataBuffer(int length);		// Construct a new buffer with the given size (buffer cannot be zero length)
	~SampleDataBuffer();

public:
	inline int GetLength() const
	{
		return m_length;
	}

	inline float & Get(int i) const
	{
		return m_buffer[(i < 0) ? 0 : ((i >= m_length) ? m_length-1 : i) ];
	}
	inline float & operator[](int i) const
	{
		return Get(i);
	}
    void Clear()
    {
        memset( m_buffer, 0, GetLength()*sizeof(float) );
    }

protected:
	int m_length;
	float * m_buffer;
};

class SampleDataBufferView : public SampleDataBuffer
{
public:
    SampleDataBufferView( SampleDataBuffer * buffer, int startOffset, int length );
    ~SampleDataBufferView();
protected:
    SampleDataBuffer* m_sourceBuffer;   ///TODO: do we want to switch to refcounting buffers, if the buffer goes out of scope before the bufer view we will have a dangling pointer
};

