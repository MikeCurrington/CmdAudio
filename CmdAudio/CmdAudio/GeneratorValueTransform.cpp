#include "stdafx.h"
#include "string.h"
#include <cstddef>
#include "GeneratorValueTransform.h"

GeneratorValueTransform::GeneratorValueTransform() : sourceBuffer(nullptr)
{
}

GeneratorValueTransform::~GeneratorValueTransform()
{
}

void GeneratorValueTransform::AddInput(const char * pParamName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(pParamName, "in") == 0)
	{
		this->sourceBuffer = value;
	}
	else
		GeneratorBase::AddInput(pParamName, value);
}

