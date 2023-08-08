#pragma once
#include <cmath>
#include <utility>

namespace kda {
	const float pi = 3.14159265358979323f;
	const float pi2 = (pi * 2);
	const float halfpi = pi / 2;

	constexpr float RadiansToDegrees(float radians) { return radians * (180.0f / pi); }
	constexpr float DegreesToRadians(float degrees) { return degrees * (pi /180.0f); }

	constexpr int wrap(int value, int max) {
		return value % max + ((value < 0) ? max : 0);
	}

	inline float wrap(float value, float max) {
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T> 
	inline T max(T a, T b) {
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T min(T a, T b) {
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max) {
		if (min > max) std::swap(min, max);
		return (value < min) ? min : (value > max) ? max : value;
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t)
	{
		return (a * (1.0f - t)) + (b * t);
	}
}