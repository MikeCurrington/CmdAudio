#include "stdafx.h"
#include "GeneratorBase.h"

GeneratorBase::GeneratorBase() : BaseCounted()
{
}

void GeneratorBase::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	fprintf(stderr, "Parameter not recognized: %s\n", pParamName);
}
