﻿#include <iostream> 
#include <queue>
#include <functional>
#include <algorithm>
#include <random>

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

    void Print() { cout << firstNum << " : " << secondNum; }

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

void randomize(Pair& p) {

    int x = rand() % 1001;
    double y = (rand() % 100001) * 0.01;

    p = Pair(x, y);
}

class GreaterThanPair {

public:

    bool operator()(Pair& p1, Pair& p2) { return p1 < p2; }
};

void generateQ(priority_queue<Pair, vector<Pair>, GreaterThanPair>& myQ, int qSize) {

    Pair qwe(0, 0);

    for (int i = 0; i < qSize; i++) {

        randomize(qwe);
        myQ.push(qwe);
    }
}

ostream& operator<<(ostream& stream, priority_queue<Pair, vector<Pair>, GreaterThanPair> myQ) {

    while (!myQ.empty()) {

        Pair user = myQ.top();

        cout << user << endl;

        myQ.pop();
    }

    return stream;
}

Pair allSum(priority_queue<Pair, vector<Pair>, GreaterThanPair> myQ) {

    Pair p(0, 0);

    while (!myQ.empty()) {

        Pair upp = myQ.top();

        p = p + upp;

        myQ.pop();
    }

    return p;
}

void removeFromRange(priority_queue<Pair, vector<Pair>, GreaterThanPair>& myQ, Pair& range1, Pair& range2) {

    priority_queue<Pair, vector<Pair>, GreaterThanPair> queueOne;

    while (!myQ.empty()) {

        Pair upp = myQ.top();

        if (!(upp > range1 && upp < range2)) {
            queueOne.push(upp);
        }

        myQ.pop();
    }

    myQ = queueOne;
}

Pair maxPair(priority_queue<Pair, vector<Pair>, GreaterThanPair> myQ) {

    Pair maxP = myQ.top();

    return maxP;
}

Pair minPair(priority_queue<Pair, vector<Pair>, GreaterThanPair> myQ) {

    Pair minP;

    while (!myQ.empty()) {

        minP = myQ.top();
        myQ.pop();
    }

    return minP;
}

priority_queue<Pair, vector<Pair>, GreaterThanPair> addToAll(priority_queue<Pair, vector<Pair>, GreaterThanPair>& myQ, Pair& para) {

    priority_queue<Pair, vector<Pair>, GreaterThanPair> queueOne;

    Pair upp = myQ.top();

    while (!myQ.empty()) {

        upp = myQ.top();
        queueOne.push(upp + para);
        myQ.pop();
    }

    return queueOne;
}

bool findPair(priority_queue<Pair, vector<Pair>, GreaterThanPair> myQ, int& x, Pair& p) {

    bool flag = false;

    while (!myQ.empty() && !flag) {

        p = myQ.top();

        if (x == p.getFirst()) { flag = true; }

        myQ.pop();
    }

    return flag;
}

int main() {

    system("chcp 1251 > Null");
    srand(time(0));

    int queueSize;

    do {

        cout << "Введите размер очереди: "; cin >> queueSize;

    } while (queueSize < 1);

    priority_queue<Pair, vector<Pair>, GreaterThanPair> qst;
    generateQ(qst, queueSize);

    cout << "\nОчередь\n\n" << qst << endl;;

    Pair summa = allSum(qst);

    summa.setFirst(summa.getFirst() / qst.size());
    summa.setSecond(((summa.getSecond() * 1000) / qst.size()) * 0.001);

    cout << endl << "Средне арифметическое: " << summa << endl << endl;

    qst.push(summa);

    cout << "После добавления средне арифметического\n\n" << qst << endl;

    Pair oneEl, twoEl;

    cout << "\nВведите две пары чисел, из диапазона которых будут удалены пары из очереди\n";
    cout << "\nПервая пара: "; cin >> oneEl;
    cout << "\nВторая пара: "; cin >> twoEl;

    if (oneEl > twoEl) swap(oneEl, twoEl);

    removeFromRange(qst, oneEl, twoEl);

    cout << "\nОчередь после удаления из диапазона\n\n" << qst << endl;

    Pair maxEl = maxPair(qst);
    Pair minEl = minPair(qst);

    cout << "\nМинимальная пара: " << minEl << endl;
    cout << "\nМаксимальный пара: " << maxEl << endl;

    summa = minEl + maxEl;

    cout << "\nСумма max и min элементов: " << summa << endl;

    qst = addToAll(qst, summa);

    cout << "\nПосле добавления суммы max и min к каждой паре\n\n" << qst << endl;

    int ptr;

    cout << "Введите значение первого числа из пары, по которому нужно найти пару: "; cin >> ptr;

    bool flag = findPair(qst, ptr, summa);

    if (flag) {

        cout << "\nЭлемент найден: " << summa << endl;
    }
    else {
        cout << "\nЭлемент не найден.\n";
    }

    return 0;
}
