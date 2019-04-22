#pragma once //это декларация компилятору, чтобы заголовки включались единожды
#include <iostream>
#include <vector> //подключили библиотеку векторов
#include "Point.h" //подключили файл с описание класса точка
using namespace std;

/*Этот файл содержит описание класса Полигон*/

class Polygon {
	//класс содержит защищенные, то есть видимые только внутри класса и наследуемые поля:
protected:
	int len; //число вершин
	vector<double> x; //вектор х-координат вершин полигона
	vector<double> y; //вектор y-координат вершин полигона
	//также в классе реализованы публичные методы
public:
	Polygon(); //констуктор по умолчанию
	Polygon(int,vector<double>, vector<double>); //констуктор инициализации, принимающий в качестве параметров
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

