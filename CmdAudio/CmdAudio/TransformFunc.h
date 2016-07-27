#pragma once
template<typename T> class TransformFunc
{
public:
	inline float operator()(float i) const {
		return T(i);
	}
};

