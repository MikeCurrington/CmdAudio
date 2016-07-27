#pragma once
class TransformClamp
{
public:
	TransformClamp( float min, float max );
	~TransformClamp();

	float operator()(float in) {
		return (in > max) ? max : ((in < min) ? min : in);
	}

protected:
	float min, max;
};

