#include "stdafx.h"
#include "GeneratorBase.h"

static int s_nextId = 1;    // id range shared between generators and generator states (even though the id of a generator does not match that of it's stats)


GeneratorBase::GeneratorBase() : BaseCounted()
{
    id = s_nextId++;
}

void GeneratorBase::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	fprintf(stderr, "Parameter not recognized: %s\n", paramName.c_str());
}

GeneratorStateBase::GeneratorStateBase(int id) : id(id)
{
    
}
