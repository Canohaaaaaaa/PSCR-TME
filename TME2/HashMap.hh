#pragma once
#include <cstddef>
#include <forward_list>

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
	class iterator{
		buckets_t& buckets;
		size_t vit;
		iterator lit;
	public :
		iterator(buckets_t& buckets, size_t vit = 0) : buckets(buckets), vit(vit), lit(buckets[vit].begin()){}
		iterator& operator++(){
			lit++;
			if(!(lit != buckets[vit].end())){
				return &lit;
			}
			size_t i;
			for(i = vit; i < buckets.size(); i++){
				if(buckets[i].size() != 0){
					vit = i;
					lit = buckets[vit].begin();
					return &lit;
				}
			}
			return nullptr;
		}

		bool operator!=(const iterator &other){
			return other.vit == vit && other.lit == lit;
		}

		Entry& operator*(){
			return *lit;
		}
	};
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
	for(begin;begin!=end;begin++){
		if(*begin == val)
			res++;
	}
	return res;
}