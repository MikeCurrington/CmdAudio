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

void OutputWav::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
    if (strcasecmp(pParamName, "source") == 0)
    {
        this->sourceGenerator = value;
    }
}

void OutputWav::Write(MachineState& machineState, int outputLength)
{
    if (sourceGenerator)
    {
        SampleDataBuffer output(outputLength);
        sourceGenerator->Supply(machineState, output, 0);

        wavWriter->Write("samples.wav", output);
    }
}

