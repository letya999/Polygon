#include <iostream>
#include "Polygon.h" // подключили файл с описанием класс Полигон
#include <vector> //бибилиотека векторов
#include "Point.h" //подключили файл с описание класса точка
using namespace std;

/*Этот файл содержит реализацию всех методов класса Полигон, содержащихся в описании этого класса в файле Polygon.h*/

const double EPS = 1.084202e-19; //константа точности, необходима так как происходит сравнение чисел с плавающей запятой

Polygon::Polygon() {} //конструктор по умолчанию

Polygon::Polygon(int len, vector<double> x, vector<double> y) { //конструктор инициализации
	//принимает число вершин и их координаты и присваивает полученные аргументы полям экземпляра класса
	//этот конструктор нужен для инициализации объектов класса Полигон
	this->len = len;
	this->x = x;
	this->y = y;
}

Polygon::Polygon(const Polygon& tmp) { //конструктор копирования
	//принимает в качестве параметра постоянную ссылку на объект класса Полигон
	//и копирует его содержимое в наш экземпляр
	//этот конструктор нужен для копирования экземпляров класса Полигон
	len = tmp.len;
	x = tmp.x;
	y = tmp.y;
}

Polygon::~Polygon() { //деструктор
	// метод, вызывающийся после того, как экземпляр класса перестает использоваться
	//необходим для освобождени памяти
	while (x.size() > 0 && y.size() > 0) {
		x.pop_back();
		y.pop_back();
	}
}

Polygon& Polygon::addVert(Point point) { //метод добавления вершины
	//принимает точку
	//добавляет ее координаты к координатам вершин Полигона
	x.push_back(point.x); 
	y.push_back(point.y);
	len++; //увеличивает на 1 число вершин
	return *this; //возвращает измененную ссылку на наш экземпляр Полигон
}

Polygon& Polygon::delVert(Point point) { //удаление вершины
	int q = len; 
	for (int i = 0; i < x.size(); i++) {
		if (x[i] == point.x && y[i] == point.y) {
			x.erase(x.begin() + i);
			y.erase(y.begin() + i);
			break;
		}
	}
	if (q != x.size())
		len--;
	return *this;
}

bool Polygon::belong(const Point point) {
	double w;
	int pos = x.size() - 1;
	bool result = false;
	double q = point.x * (y[0] - y[pos]) - point.y * (x[0] - x[pos]) - x[pos] * (y[0] - y[pos]) + y[pos] * (x[0] - x[pos]);
	for (int i = 0; i < x.size() - 1; i++) {
		w = point.x * (y[i + 1] - y[i]) - point.y * (x[i + 1] - x[i]) - x[i] * (y[i + 1] - y[i]) + y[i] * (x[i + 1] - x[i]);
		if ((q >= 0 && w >= 0) || (q < 0 && w < 0))
			result = true;
		else
			return false;
	}
	return result;
}

bool Polygon::intersect(Polygon obj) {
	bool result = false;
	Point t1, t2, t3, t4, t5;
	double w1, w2, w3, w4, a1, a2, b1, b2, c1, c2;
	for (int i = 0; i < x.size() - 1; i++) 
		for (int j = 0; j < obj.x.size() - 1; j++) {
			a1 = y[i + 1] - y[i];
			a2 = obj.y[j + 1] - obj.y[j];
			b1 = x[i + 1] - x[i];
			b2 = obj.x[j + 1] - obj.x[j];
			c1 = -x[i] * a1 + y[i] * b1;
			c2 = -obj.x[j] * a2 + obj.y[j] * b2;
			w1 = (b2*c1 - b1 * c2);
			w2 = (b1*a2 - b2 * a1);
			w3 = (a2*c1 - a1 * c2);
			t5.x = w1 / w2;
			t5.y = w3 / w2;
			if (w1 != 0 && w2 != 0 && w3 != 0 &&
				belong(t5) == true && obj.belong(t5) == true)
				return true;
		}
	return result;
}

Polygon& Polygon::operator=(Polygon obj) {
	this->x = obj.x;
	this->y = obj.x;
	this->len = obj.len;
	return *this;
}

bool Polygon::operator > (Polygon obj) {
		if ((this->len - obj.len) > EPS)
		return true;
	return false;
}

bool Polygon::operator < (Polygon obj) {
	if ((this->len - obj.len) < EPS)
		return true;
	return false;
}

bool Polygon::operator != (Polygon obj) {
	if (abs(this->len - obj.len) > EPS)
		return true;
	return false;
}

bool Polygon::operator >= (Polygon obj) {
	if ((this->len - obj.len) < EPS)
		return false;
	return true;
}

bool Polygon::operator <= (Polygon obj) {
	if ((this->len - obj.len) > EPS)
		return false;
	return true;
}

bool Polygon::operator == (Polygon obj) {
	if (abs(this->len - obj.len) > EPS)
		return false;
	return true;
}

istream& operator >> (istream& in, Polygon& obj) {
	Point point;
	cout << "Введите число вершин полигона(не меньше трех): ";
	in >> obj.len;
	cout << "Введите вершины в последовательном порядке" << endl;
	for (int i = 0; i < obj.len; i++)
	{
		cout << "Введите координаты " << i + 1 << " вершины (x,y):";
		in >> point.x;
		obj.x.push_back(point.x);
		in >> point.y;
		obj.y.push_back(point.y);
	}
	return in;
}

ostream& operator << (ostream& out, Polygon& obj) {
	out << "Число вершин полигона = ";
	out << obj.len << endl;
	for (int i = 0; i < obj.len; i++) {
		out << "Координаты " << i + 1 << " вершины:" << endl;
		out << "x=" << obj.x[i] << endl;
		out << "y=" << obj.y[i] << endl;
	}
	return out;
}


