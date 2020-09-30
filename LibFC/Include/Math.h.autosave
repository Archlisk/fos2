#pragma once

namespace FC {

template<typename T>
T abs(T val) {
	return val & 0x7FFFFFFFFFFFFFFF;
}

template<typename T>
T max(T v1, T v2) {
	return (v1 > v2) ? v1 : v2;
}

template<typename T>
T min(T v1, T v2) {
	return (v1 < v2) ? v1 : v2;
}

template<typename T>
T clamp(T val, T max, T min) {
	if (val > max)
		return max;
	if (val < min)
		return min;
	return val;
}

}
