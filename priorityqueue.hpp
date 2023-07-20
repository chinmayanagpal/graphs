#include <math.h>
#include <vector>
#include <iostream>
#include <vector>

typedef std::size_t size_t;

template <class T, class S>
struct prioritypair {
	T val;
	S priority;
};

template <class T, class S>
class priorityqueue {
public:
	void insert(T val, S priority);

	T top();

	T pop();

	void change_priority(T val, S priority);

	size_t size();

	bool contains(T val);

	S get_priority(T val);

	void print();

	void setchecks(bool checks = true);

	std::vector<T> as_list();
private:
	std::vector<prioritypair<T, S>> list = {};

	bool checks = false;

	void rejigbottom(size_t current);

	void rejigtop(size_t current);

	size_t parent(size_t n) { return (n - 1) / 2; }

	size_t leftchild(size_t n) { return 2 * n + 1; }

	size_t rightchild(size_t n) { return 2 * n + 2; }
};

template <class T, class S>
void priorityqueue<T, S>::rejigtop(size_t current) {
	// print();
	size_t l = leftchild(current);
	size_t r = rightchild(current);
	size_t s = current;
	if (list.size() > l - 1
	    && list[s].priority > list[l].priority) {
		s = l;
	}
	if (list.size() > r - 1
	    && list[s].priority > list[r].priority) {
		s = r;
	}
	if (s != current) {
		std::swap(list[s], list[current]);
		rejigtop(s);
	}
}

template <class T, class S>
void priorityqueue<T, S>::rejigbottom(size_t curr) {

	if (curr > 0 && list[curr].priority < list[parent(curr)].priority) {

		std::swap(list[curr], list[parent(curr)]);
		rejigbottom(parent(curr));
	}
}

template <class T, class S>
void priorityqueue<T, S>::insert(T val, S priority) {
	if (checks) {
		for(auto pair: list) {
			if (pair.val == val) {
				std::cout<<"PQ already contains val"
					 <<val
					 <<std::endl;
				std::exit(1);
			}
		}
	}
	list.push_back({val, priority});
	rejigbottom(list.size() - 1);
}

template <class T, class S>
T priorityqueue<T, S>::pop() {
	if (list.empty()) {
		std::cout<<"PQ is empty उल्लु दे पठे\n";
	}
	prioritypair<T, S> top = list[0];
	list[0] = list.back();
	list.pop_back();
	rejigtop(0);
	return top.val;
			
}

template <class T, class S>
void priorityqueue<T, S>::change_priority(T val, S priority) {
	for (size_t i = 0; i < list.size(); ++i) {
		if (checks && list[i].priority == priority && list[i].val != val)
		{
			std::cout<<list[i].val
				 <<" already has priority "
				 <<priority
				 <<std::endl;

			std::exit(1);
		}
		if (list[i].val == val) {
			S orig = list[i].priority;
			list[i].priority = priority;
			if (orig > priority)
				rejigbottom(i);
			else if (orig < priority)
				rejigtop(i);
		}
	}
}

template <class T, class S>
T priorityqueue<T, S>::top() {
	return list[0].val;
}

template <class T, class S>
size_t priorityqueue<T, S>::size() {
	return list.size();
}

template <class T, class S>
bool priorityqueue<T, S>::contains(T val) {
	for(auto pair: list)
		if (pair.val == val)
			return true;
	return false;
}

template <class T, class S>
S priorityqueue<T, S>::get_priority(T val) {
	for(auto pair: list)
		if (pair.val == val)
			return pair.priority;
	std::cout<<"Value "<<val<<" is not contained in PQ"<<std::endl;
	exit(1);
}

template <class T, class S>
void priorityqueue<T, S>::print() {
	for (size_t i = 0; i < list.size(); ++i) {
		std::cout<<"("
			 <<list[i].val
			 <<","
			 <<list[i].priority
			 <<")";

		if (((i + 2) & i) == 0 || i == list.size() - 1)
			std::cout<<std::endl;
	}
}

template <class T, class S>
void priorityqueue<T, S>::setchecks(bool checks) {
	this->checks = checks;
}

template <class T, class S>
std::vector<T> priorityqueue<T, S>::as_list() {
	std::vector<T> ret = {};
	for (auto i: list)
		ret.push_back(i.val);
	return ret;
}
