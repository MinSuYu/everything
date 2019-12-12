#include <QtCore/QCoreApplication>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <stdlib.h>
#include <cstring>
#include <functional>

using namespace std;
using namespace chrono;

template <typename T>
void swap(T& a, T& b) {
	T temp = b;
	b = a;
	a = temp;
}

void test1() {
	std::string hello = "World!";
	std::string world = "Hello, ";

	swap(hello, world);

	std::cout << hello << world << std::endl;
}

template <typename T>
class Vector {
public:
	Vector() {
		capacity_ = 100;
		array_ = new T[capacity_];
	}
	~Vector() {

	}
	const T& at(int index) const {
		return array_[index];
	}
	const T value(int index) const {
		if (size_ <= index) {
			return T();
		}
		return array_[index];
	}
	int size() const {
		return size_;
	}
	bool empty() {
		return size_ == 0;
	}

	void push_back(const T& value) {
		array_[size_++] = value;
	}
	void resize(int size) {

	}
	void reserve(int capacity) {

	}

	/*typedef T* iterator;
	iterator begin() {
		return array_;
	}
	iterator end() {
		return T();
	}*/

	T& operator [] (int index) {
		return array_[index];
	}
	const T& operator [] (int index) const {
		return at(index);
	}
	bool operator == (const Vector<T>& other) {
		if (size_ == other.size_) {
			for (int i = 0; i < size_; i++) {
				if (array_[i] != other.array_[i]) {
					return false;
				}
			}
		}
		else {
			return false;
		}
		return true;
	}
	bool operator < (const Vector<T>& other) {
		int size = std::min(size_, other.size_);

		for (int i = 0; i < size; i++) {
			if (array_[i] < other.array_[i]){
				return true;
			}
			else if (array_[i] > other.array_[i]) {
				return false;
			}
		}

		return size_ < other.size_;
	}
private:
	T* array_ = nullptr;
	int size_ = 0;
	int capacity_ = 0;
};

void test2() {
	Vector<int> vector;

	if (vector.empty()) {
		vector.push_back(1);
	}

	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);

	std::cout << vector.size() << std::endl;
	for (int i = 0; i < vector.size(); i++) {
		std::cout << vector.at(i) << std::endl;
	}
}

template <typename T>
void dumpContainer(T& container) {
	for (T::iterator it = container.begin(); it != container.end(); it++) {
		std::cout << *it << " ";
	}

	std::cout << std::endl;
}

void test3() {
	std::list<int> list = { 1, 2, 3, 4, 5 };
	std::vector<int> vector = { 4, 5, 6, 7, 8, };

	dumpContainer<std::list<int>>(list);
	//dumpContainer(vector);
}

void test4() {
	Vector<int> vector;
	vector.push_back(1);
	vector.push_back(2);
	vector.push_back(3);
	vector.push_back(4);
	vector.push_back(5);

	//dumpContainer(vector);
}

template <typename T>
void search(const T& container, int value) {
	if (std::binary_search(container.begin(), container.end(), value)) {
		std::cout << "search value " << value << std::endl;
	}
	else {
		std::cout << "No search value " << value << std::endl;
	}
}

void test5() {
	std::vector<int> vector = { 3, 5, 2, 7, 6, 0, -9 };

	sort(vector.begin(), vector.end());

	dumpContainer(vector);

	search(vector, 3);
	search(vector, 1);
}

class Value {
public:
	Value(int value = 0) : value_(value) {}

	int value() { return value_; }

	bool operator == (const Value& other) const {
		return value_ == other.value_;
	}

	bool operator != (const Value& other) const {
		return !(operator == (other));
	}

	bool operator < (const Value& other) const {
		return value_ < other.value_;
	}
private:
	int value_;
};

void test6() {
	Vector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector1.push_back(5);

	Vector<int> vector2;
	vector2.push_back(2);
	vector2.push_back(1);
	vector2.push_back(3);
	vector2.push_back(5);

	std::cout << vector1[1] << std::endl;
	std::cout << (vector1 < vector2) << std::endl;
	std::cout << (vector1 == vector2) << std::endl;
}

void test6_1() {
	Vector<Value> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector1.push_back(5);

	Vector<Value> vector2;
	vector2.push_back(2);
	vector2.push_back(1);
	vector2.push_back(3);
	vector2.push_back(5);

	std::cout << vector1[1].value() << std::endl;
	//std::cout << (vector1 < vector2) << std::endl;
	std::cout << (vector1 == vector2) << std::endl;
}

class LargeData {
public:
	explicit LargeData(int size = 1000) : size_(size) {
		data_ = new char[size_];
		memset(data_, 0, size_);
	}
	LargeData(const LargeData& other) {
		operator=(other);
	}

	LargeData& operator = (const LargeData& other) {
		if (data_) {
			delete[] data_;
		}
		data_ = new char[other.size_];
		memcpy(data_, other.data_, other.size_);
		size_ = other.size_;
		return *this;
	}

	LargeData& operator = (LargeData&& other) {
		std::swap(data_, other.data_);
		return *this;
	}

	~LargeData() {
		if (data_) {
			delete[] data_;
		}
	}
private:
	char* data_ = nullptr;
	int size_;
};

LargeData createLargeData() {
	return LargeData(500000000);
}

void test7() {
	LargeData a;
	system_clock::time_point start = system_clock::now();

	a = createLargeData();

	system_clock::time_point end = system_clock::now();

	duration<double> lab = end - start;

	std::cout << lab.count() << std::endl;

}

template <typename T>
void swap2(T& v1, T& v2) {
	T temp(std::move(v1));
	v1 = std::move(v2);
	v2 = std::move(temp);
	//v1 = v2;
	//v2 = temp;
}

void test8() {
	LargeData a(1000000), b(10000000);
	system_clock::time_point start = system_clock::now();

	swap2(a, b);
	swap2(a, b);

	system_clock::time_point end = system_clock::now();

	duration<double> lab = end - start;

	std::cout << lab.count() << std::endl;
}

typedef std::function<int(int)> Func;

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test6_1();
	//test7();
	//test8();

	double money = 0;
	for (int i = 0; i < 12 * 10; i++) {
		money += 500000;
		money *= (1.0 + 0.02 / 12);
	}

	std::cout << money << std::endl;

	int result = 0;
	Func sum = [&result, &sum](int maxNum) -> int {	
		if (maxNum <= 1) {
			return maxNum;
		}
		else {
			return maxNum + sum(maxNum - 1);
		}
	};

	std::cout << sum(10) << std::endl;

	//return a.exec();
	return 0;
}
