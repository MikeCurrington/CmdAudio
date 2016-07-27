#include "stdafx.h"
#include "math.h"
#include "WavWriter.h"

#if false
#define ENDIANSWAP16(x) ((((unsigned short)(x)) >> 8) | ((((unsigned short)(x)) & 0xff) << 8))
#define ENDIANSWAP32(x) ((ENDIANSWAP16(((unsigned int)x)&0xffff) << 16) | (ENDIANSWAP16(((unsigned int)x)>>16)))
#else
#define ENDIANSWAP16(x) ((unsigned short)(x))
#define ENDIANSWAP32(x) ((unsigned int)(x))
#endif


WavWriter::WavWriter( int sampleRate ) : sampleRate(sampleRate)
{
}

WavWriter::~WavWriter()
{
}


///
/// Write .wav file containing the given output data
///
void WavWriter::Write(const char * const filename, const SampleDataBuffer & output)
{
	// get 16bit samples
	int outputLength = output.GetLength();
	unsigned short *ouput16bit = new unsigned short[outputLength];
	for (int i = 0; i < outputLength; i++)
	{
		short o = (short)(fmax(fmin(output[i], 1.0f), -1.0f) * 32767.0f);
		ouput16bit[i] = ENDIANSWAP16(o);
	}

	// hacked fileio
	FILE * file = NULL;
    file = fopen( filename, "wb" );
    //	auto err = fopen_s(&file, filename, "wb");
	if (file != NULL)
	{
		// write wav header
		// wav is a little endian format (unlike windows i86)
		fputc('R', file);
		fputc('I', file);
		fputc('F', file);
		fputc('F', file);
		int dataSubChunkSize = 2 * outputLength;
		int mainChunkSize = 36 + dataSubChunkSize;
		unsigned int data32 = ENDIANSWAP32(mainChunkSize);
		fwrite(&data32, 4, 1, file);
		fputc('W', file);
		fputc('A', file);
		fputc('V', file);
		fputc('E', file);

		fputc('f', file);
		fputc('m', file);
		fputc('t', file);
		fputc(' ', file);
		data32 = ENDIANSWAP32(16);	// fmt bock size (excluding this size and the prior 4 bytes for the type 4 bytes)
		fwrite(&data32, 4, 1, file);
		short data16 = ENDIANSWAP16(1);	// uncompressed pcm
		fwrite(&data16, 2, 1, file);
		data16 = ENDIANSWAP16(1);	// mono
		fwrite(&data16, 2, 1, file);
		data32 = ENDIANSWAP32(sampleRate);	// sample rate
		fwrite(&data32, 4, 1, file);
		data32 = ENDIANSWAP32(sampleRate * 2);	// byte rate
		fwrite(&data32, 4, 1, file);
		data16 = ENDIANSWAP16(2);	// blockalign
		fwrite(&data16, 2, 1, file);
		data16 = ENDIANSWAP16(16);	// bits per sample
		fwrite(&data16, 2, 1, file);

		fputc('d', file);
		fputc('a', file);
		fputc('t', file);
		fputc('a', file);
		data32 = ENDIANSWAP32(dataSubChunkSize);// data bock size (excluding this size and the prior 4 bytes for the type 4 bytes)
		fwrite(&data32, 4, 1, file);

		fwrite(ouput16bit, sizeof(short), outputLength, file);
		fclose(file);

		delete[]ouput16bit;
		ouput16bit = nullptr;

		fprintf(stdout, "Wrote samples file");
	}
}
