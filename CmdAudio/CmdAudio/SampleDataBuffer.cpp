#include "stdafx.h"
#include "SampleDataBuffer.h"


SampleDataBuffer::SampleDataBuffer(int length)
{
	this->m_length = length;
	this->m_buffer = new float[m_length];
}

SampleDataBuffer::~SampleDataBuffer()
{
	delete [] this->m_buffer;
	this->m_buffer = nullptr;
}


SampleDataBufferView::SampleDataBufferView( const BaseCountedPtr<SampleDataBuffer>& buffer, int startOffset, int length ) : m_sourceBuffer(buffer)
{
    if (startOffset >= buffer->GetLength())
    {
        m_length = 0;
        startOffset = 0;
    }
    else if (length+startOffset > buffer->GetLength())
    {
        m_length = buffer->GetLength() - startOffset;
    }
    else
    {
        m_length = length;
    }
    
    m_buffer = &m_sourceBuffer->Get(startOffset);
}

SampleDataBufferView::~SampleDataBufferView()
{
    m_length = 0;
    m_buffer = nullptr;
}

