#pragma once
#include "BaseCounted.h"
#include "SampleDataBuffer.h"
#include <utility>
#include <unordered_map>

// Forward decl
class MachineState;

///
/// Base class for all the sample Generators
/// The job of the generator is to fill (supply) a buffer with samples/value - the contents of which is determined by the inputs to the generator.
///
class GeneratorBase : public BaseCounted<GeneratorBase>
{
public:
	GeneratorBase();

	virtual void AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value);
	virtual void Supply(MachineState& machineState, SampleDataBuffer & rDataBuffer, int startSample) = 0;
};
