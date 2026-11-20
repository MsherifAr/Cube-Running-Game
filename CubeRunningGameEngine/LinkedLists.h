#pragma once
#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class List {
	std::vector<T> vector;
	unsigned int size = 0;
public:
	void reserve(int Pre_reserved_memory) {
		vector.reserve(Pre_reserved_memory);
	}

	void append(const T& item) {
		vector.emplace_back(item);
		size++;
	}

	void pop(unsigned int index) {
		vector[index] = std::move(vector.back());
		vector.pop_back();
		size--;
	}

	void clear() {
		int size = get_size();
		for (int i = 0; i < size; i++) {
			pop(0);
		}
	}

	void insert(unsigned int index, T item) {
		vector.insert(vector.begin() + index, item);
		size++;
	}

	T& get(unsigned int index) {
		return vector[index];
	}

	T& operator[](unsigned int index) {
		return vector[index];
	}
	
	int find(const T& item) {
		auto it = std::find(vector.begin(), vector.end(), item);
		if (it != vector.end()) {
			return (std::distance(vector.begin(), it));
		}
		else {
			return -1;
		}
	}

	unsigned int get_size() {
		return size;
	}

};

