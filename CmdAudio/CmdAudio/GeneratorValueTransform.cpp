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

void GeneratorValueTransform::AddInput(const std::string& paramName, BaseCountedPtr<GeneratorBase> value)
{
	if (strcasecmp(paramName.c_str(), "in") == 0)
	{
		this->sourceBuffer = value;
	}
	else
		GeneratorBase::AddInput(paramName, value);
}

