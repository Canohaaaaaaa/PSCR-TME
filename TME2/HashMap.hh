#pragma once
#include <vector>
#include <forward_list>
#include <iterator>

template<typename K,typename V>
class HashMap{
	class Entry{
		public:
		const K key;
		V value;
		Entry(K key, V value) : key(key), value(value){}
	};
	typedef std::vector<std::forward_list<Entry>> buckets_t;
	buckets_t buckets;
	public:
	HashMap(size_t init = 100) : buckets(init){}

	V* get(const K &key){
		size_t h = std::hash<K>()(key);
		h = h % buckets.size();
		for(Entry &entry : buckets[h]){
			if(entry.key == key){
				return &(entry.value);
			}
		}
		return nullptr;
	}

	bool put(const K & key, const V & value){
		size_t h = std::hash<K>()(key);
		h = h % buckets.size();
		V* entree = get(key);
		if(entree){
			*entree = value;
			return true;
		}
		else{
			Entry nouvelleEntree(key, value);
			buckets[h].push_front(nouvelleEntree);
			return false;
		}
	}
};

template<class iterator>
size_t count(iterator begin, iterator end){
	size_t res = 0;
	for(begin; begin!=end;begin++){
		res++;
	}
	return res;
}

template<class iterator, typename T>
size_t count_if_equal(iterator begin, iterator end, const T & val){
	size_t res = 0;
	for(begin!=end;begin++){
		if(*begin == val)
			res++;
	}
	return res;
}