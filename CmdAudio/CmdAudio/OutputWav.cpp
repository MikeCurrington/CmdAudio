//
//  GeneratorOutputWav.cpp
//  CmdAudio
//
//  Created by Michael Currington on 11/12/15.
//  Copyright (c) 2015 Doodleoo Games. All rights reserved.
//
#include "OutputWav.h"

#include "WavWriter.h"
#include "string.h"
#include "MachineState.h"


OutputWav::OutputWav(int sampleRate) : OutputBase(), sourceGenerator(nullptr)
{
    wavWriter = new WavWriter(sampleRate);
}

OutputWav::~OutputWav()
{
    delete wavWriter;
}

void OutputWav::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(paramName.c_str(), "source") == 0)
    {
        this->sourceGenerator = value;
    }
}

void OutputWav::Write(MachineState& machineState, int outputLength)
{
    if (sourceGenerator)
    {
        SampleDataBuffer output(outputLength);
        
        int offset = 0;
        int remaining = outputLength;
        while(remaining > 0)
        {
            int chunkLength = 22050;
            if (chunkLength > remaining)
                chunkLength = remaining;
            SampleDataBufferView chunkView(&output, offset, chunkLength);
            
            sourceGenerator->Supply(machineState, chunkView, offset);
            remaining -= chunkLength;
            offset += chunkLength;
        }
        
        wavWriter->Write("samples.wav", output);
    }
}

