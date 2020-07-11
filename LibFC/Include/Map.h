#pragma once

#include <Vector.h>
#include <Pair.h>
#include <InitList.h>
#include <Math.h>

#include <TTY.h>

#define MAP_INDEX_NOT_FOUND UINT32_MAX

namespace FC {

template<typename Tk, typename Tv>
class CFMap {
public:
	using Iterator = Pair<Tk, Tv>;
	
	CFMap() {}
	
	constexpr CFMap(const InitList<Iterator>& list) {
		for (auto& elem : list)
			insert(elem.first, elem.second);
	}
	
	Iterator* insert(const Tk& key, const Tv& val) {
		u32 index = find_index(key);
		if (index == MAP_INDEX_NOT_FOUND)
			return end();
		
		m_data.insert(index, Iterator(key, val));
		return &m_data[index];
	}
	
	Iterator* reserve(const Tk& key) {
		u32 index = find_index(key);
		if (index == MAP_INDEX_NOT_FOUND)
			return end();
		
		m_data.insert(index, Iterator(key, Tv()));
		return &m_data[index];
	}
	
	Iterator* find(const Tk& key) {
		u32 index = find_index(key);
		if (index == MAP_INDEX_NOT_FOUND)
			return end();
		
		return &m_data[index];
	}

	u32 find_index(const Tk& key) {
		f32 diff = (f32)size();
		f32 index = ((f32)size() / 2.0f) + 1.0f;
		
		while ((diff /= 2.0f) > 0.5f) {
			u32 i = (i32)index;
		
			if (m_data[i].first < key)
				index += diff;
			else if (m_data[i].first == key)
				return i;
			else
				index -= diff;
			index = clamp<f32>((f32)index, size() - 1, 0);
		}
		
		if (m_data[(i32)index].first >= key)
			return (i32)index;
			
		return MAP_INDEX_NOT_FOUND;
	}

	void erase(const Tk& key) {
		u32 index = find_index(key);
		if (index == MAP_INDEX_NOT_FOUND)
			return;
		
		m_data.erase(index);
	}
	
	Tv& operator[](const Tk& key) { 
		Iterator* it = find(key);
		
		if (it == end())
			return reserve(key)->second;
		else
			return it->second;
	}
	
	void clear() { m_data.clear(); }
	
	Iterator* begin() { return m_data.begin(); }
	Iterator* end() { return m_data.end(); }
	
	u32 size() { return m_data.size(); }

private:
	 Vector<Iterator> m_data;
};

}
