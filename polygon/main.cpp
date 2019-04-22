#include <iostream>
#include <vector>

using namespace std;
const double EPS = 1.084202e-19; //константа точности, необходима так как происходит сравнение чисел с плавающей запятой

class Point {
public:
	double x; //х-координата точки
	double y; //y-координата точки
	Point(double x = 0, double y = 0) { //конструктор с параметрами, одновременно выполянющий
		//роль конструктора по умолчанию
		this->x = x;
		this->y = y;
	}
	~Point() {} //деструктор
};


class Polygon {
	//класс содержит защищенные, то есть видимые только внутри класса и наследуемые поля:
protected:
	int len; //число вершин
	vector<double> x; //вектор х-координат вершин полигона
	vector<double> y; //вектор y-координат вершин полигона
	//также в классе реализованы публичные методы
public:
	Polygon(); //констуктор по умолчанию
	Polygon(int, vector<double>, vector<double>); //констуктор инициализации, принимающий в качестве параметров
	//число вершин и векторы координат
	Polygon(const Polygon&); //конструктор копирования
	~Polygon(); //деструктор
	Polygon& addVert(Point); //добавление новой вершины
	Polygon& delVert(Point); //удаление вершины
	bool belong(const Point); //проверка на принадлежность вершины полигону
	bool intersect(Polygon); //проверка пересечения полигонов
	int getNumbVert() { return this->len; } //число вершин

	Polygon& operator=(Polygon); //оператор присваивания
	bool operator > (Polygon); //оператор больше
	bool operator < (Polygon); //оператор меньше
	bool operator != (Polygon); //оператор неравно
	bool operator >= (Polygon); //оператор больше или равно
	bool operator <= (Polygon); //оператор меньше или равно
	bool operator == (Polygon); //оператор сравнения
	friend ostream& operator << (ostream&, Polygon&); //оператор вывода в поток
	friend istream& operator >> (istream&, Polygon&); //оператор ввода в поток
};

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


class MyPolygon :
	public Polygon
{
public:
	MyPolygon() : Polygon() {}
	MyPolygon(int len, vector<double>x, vector<double>y) : Polygon(len, x, y) {}
	MyPolygon(const Polygon& tmp) : Polygon(tmp) {}
	~MyPolygon() { Polygon::~Polygon(); }

	double perimeter() {
		double l = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
		return l * len;
	}

	double square() {
		double l = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
		return (this->len * l * l) / (4 * tan(3.14 / this->len));
	}
};





int main() {
	setlocale(LC_ALL, "RUS"); //переводим консоль в русскую кодировку
	Point A; // объявление точки А
	vector<double>x1 = { 0,0,5,5 }; //вектор х-координат
	vector<double>y1 = {0, 10, 10,0}; //вектор y-координат
	// по заданию требуется зайдействовать все реализованные методы
	Polygon qwerty1; //конструктор по умолчанию 
	Polygon qwerty2(4, x1, y1); //конструктор инициализации 
	Polygon qwerty3(qwerty2); //конструктор копирования 
	Polygon qwerty5;
	qwerty5 = qwerty3; // оператор присваивания
	cin >> qwerty1; //оператор ввода в поток 
	cout << qwerty1; //оператор вывода в поток
	cout << "Введите точку" << endl;
	cin >> A.x >> A.y; //вводим координаты точки А
	if(qwerty1.belong(A)) //проверка принадлежноости точки полигону
	    cout << "Точка внутри полигона" << endl;
	else cout << "Точка вне полигона" << endl;
	if(qwerty2.intersect(qwerty1)) //проверка пересечания полигонов 
		cout << "Полиномы пересекаются" << endl;
	else cout << "Полиномы не пересекаются" << endl;
	MyPolygon qwerty6 = qwerty1; //инициализация экземпляра класса наследника
	cout <<"Perimeter "<< qwerty6.perimeter() << endl; //рассчет периметра полигона
	cout << "Number of vertex " << qwerty6.getNumbVert() << endl; //число вершин полигона
	//проверка всех операторов сравнения для полигонов
	if (qwerty1 > qwerty2) //оператор больше
		cout << "1 больше 2" << endl;
	else
		cout << "1 меньше 2" << endl;
	if (qwerty1 <= qwerty2) //оператор меньше равно
		cout << "1 меньше или равно 2" << endl;
	else
		cout << "1 больше 2" << endl;
	if (qwerty1 != qwerty2) //оператор неравно
		cout << "1 не равен 2" << endl;
	else
		cout << "1 равен 2" << endl;
	if(qwerty6 == qwerty1) //оператор сравнения
		cout << "1 равен 2" << endl;
	else
		cout << "1 не равен 2" << endl;
	//добавление вершины 
	cout << "До добавления вершины вершины" << endl;
	cout << qwerty1;
	qwerty1.addVert(A); //добавление вершины А
	cout << "После добавления вершины вершины" << endl;
	cout << qwerty1;
	//удаление вершины 
	cout << "До удаления вершины вершины" << endl;
	cout << qwerty1;
	qwerty1.delVert(A); //удаление вершины А
	cout << "После удаления вершины вершины" << endl;
	cout << qwerty1;
	system("pause");
}