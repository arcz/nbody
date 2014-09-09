#pragma once
class Consts{
	virtual void fun()=0;
	public:
//		static const unsigned MAX_PARTICLES = 500;
		static constexpr float G = 1.0f;//6.673848080E-3;
		static constexpr float minPos = -100.0f;
		static constexpr float maxPos = 100.0f;
		static constexpr float minMass = 10.0f;
		static constexpr float maxMass = 1000.0f;
		static constexpr float minVel = 0.001f;
		static constexpr float maxVel = 1.0f;
		static constexpr float EPS = 1.0E+2;
};

