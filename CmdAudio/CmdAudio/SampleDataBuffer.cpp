#include "stdafx.h"
#include "SampleDataBuffer.h"


SampleDataBuffer::SampleDataBuffer(int length)
{
	this->length = length;
	this->buffer = new float[length];
}

SampleDataBuffer::~SampleDataBuffer()
{
	delete [] this->buffer;
	this->buffer = nullptr;
}
