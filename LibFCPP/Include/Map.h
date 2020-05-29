#pragma once

#include <Vector.h>
#include <Pair.h>

namespace FCPP {

template<typename Tk, typename Tv>
class Map {
public:
	using Iterator = Pair<Tk, Tv>;

	inline Iterator* insert(const Tk&, const Tv&) {
		
	}
	
	inline Iterator* reserve(const Tk&) {
		
	}
	
	inline Iterator* find(const Tk&) {
		
	}

	inline void erase(const Tk&) {}
	
	inline Tv& operator[](const Tk& key) { 
		Iterator it = find(key);
		
		if (it == end())
			return reserve(key)->second;
		else
			return it.second;
	}
	
	inline void erase(u32 index) { m_data.erase(index); }
	inline void clear() { m_data.clear(); }
	
	inline Iterator* begin() { return m_data.begin(); }
	inline Iterator* end() { return m_data.end(); }
	
	inline u32 size() { return m_data.size(); }

private:
	 Vector<Iterator> m_data;
};

}
