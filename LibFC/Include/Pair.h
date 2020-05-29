#pragma once

namespace FC {

template<typename Tf, typename Ts>
struct Pair {
	Pair() {}
	Pair(const Tf& first, const Ts& second) 
		: first(first), second(second) {}
	
	Tf first;
	Ts second;
};

}
