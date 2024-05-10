﻿#include <iostream> 
#include <list>
#include <functional>
#include <algorithm>
#include <ctime>

using namespace std;

class Pair {

	int firstNum;
	double secondNum;

public:

	Pair() {

		firstNum = 0;
		secondNum = 0;
	}

	Pair(int firstOfNums, double secondOfNums) {

		firstNum = firstOfNums;
		secondNum = secondOfNums;
	}

	Pair(const Pair& someNum) {

		firstNum = someNum.firstNum;
		secondNum = someNum.secondNum;
	}

	~Pair() {}

	void Print() {
		cout << firstNum << " : " << secondNum;
	}

	Pair operator+(const Pair& other) const {

		Pair result;

		result.firstNum = firstNum + other.firstNum;
		result.secondNum = secondNum + other.secondNum;

		return result;
	}

	void operator-(const Pair& number) {

		firstNum -= number.firstNum;
		secondNum -= number.secondNum;
	}

	void setFirst(int num) { firstNum = num; }
	void setSecond(double num) { secondNum = num; }

	int getFirst() const { return firstNum; }
	double getSecond() const { return secondNum; }

	void operator=(const Pair& number) {

		firstNum = number.firstNum;
		secondNum = number.secondNum;
	}

	friend ostream& operator<<(ostream& stream, const Pair& p);
	friend istream& operator>>(istream& stream, Pair& p);

	bool operator>(const Pair& p) const { return firstNum > p.firstNum; }

	bool operator<(const Pair& p) const { return firstNum < p.firstNum; }
};

ostream& operator<<(ostream& stream, const Pair& p) {

	stream << p.firstNum << " : " << p.secondNum;

	return stream;
}

istream& operator>>(istream& stream, Pair& p) {

	stream >> p.firstNum >> p.secondNum;

	return stream;
}

int main() {

	system("chcp 1251 > Null");
	srand(time(0));

	int listSize;

	do {

		cout << "Введите размер списка: "; cin >> listSize;

	} while (listSize < 1);

	Pair summa;

	list<Pair> workList(listSize);

	generate(workList.begin(), workList.end(), []() { Pair p; p.setFirst(rand() % 1001); p.setSecond((rand() % 100001) * 0.01); return p; });

	cout << "\nСписок\n\n";

	for (auto& p : workList) cout << p << endl;

	for_each(workList.begin(), workList.end(), [&summa](const Pair& p) { summa = summa + p; });

	summa.setFirst(summa.getFirst() / workList.size());
	summa.setSecond(((summa.getSecond() * 10000 / workList.size()) * 0.0001));

	cout << "\nСреднее арифметическое: " << summa << endl << endl;

	workList.push_back(summa);

	cout << "Список после добавления среднего арифметического\n\n";
	for (auto& p : workList) cout << p << endl;

	Pair oneEl, twoEl;

	cout << "\nВведите две пары чисел, из диапазона которых будут удалены пары из списка\n";

	cout << "\nПервая пара: "; cin >> oneEl;
	cout << "\nВторая пара: "; cin >> twoEl;

	if (oneEl > twoEl) swap(oneEl, twoEl);

	list<Pair>::iterator s = remove_if(workList.begin(), workList.end(), [oneEl, twoEl](Pair& p) { return (p > oneEl) && (p < twoEl); });
	workList.erase(s, workList.end());

	cout << "\nСписок после удаления из диапазона\n\n";
	for (auto& p : workList) cout << p << endl;

	auto stl_pair = minmax_element(workList.begin(), workList.end());

	cout << "\nМинимальный элемент: " << *stl_pair.first << endl;
	cout << "\nМаксимальный элемент: " << *stl_pair.second << endl;

	Pair sum_pair(stl_pair.first->getFirst() + stl_pair.second->getFirst(), stl_pair.first->getSecond() + stl_pair.second->getSecond());

	cout << "\nСумма максимального и минимального элементов: " << sum_pair << endl;

	for_each(workList.begin(), workList.end(), [&sum_pair](Pair& p) { p = p + sum_pair; });

	cout << "\nСписок после добавления суммы максимального и минимального к каждой паре\n\n";
	for (auto& p : workList) cout << p << endl;

	cout << "\nСортировка по возрастанию\n\n";
	workList.sort([](const Pair& a, const Pair& b) { return a < b; });
	for (auto& p : workList) cout << p << endl;

	cout << "\nСортировка по убыванию\n";
	workList.sort([](const Pair& a, const Pair& b) { return a > b; });
	for (auto& p : workList) cout << p << endl;

	int ptr;

	cout << "\nВведите значение first, по которому необходимо найти пару: "; cin >> ptr;

	auto i = find_if(workList.begin(), workList.end(), [&ptr](const Pair& p) { return ptr == p.getFirst(); });

	if (i != end(workList)) { cout << "\nЭлемент найден: " << *i << endl; }
	else { cout << "\nЭлемент не найден.\n"; };

	return 0;
}
