#pragma once //��� ���������� �����������, ����� ��������� ���������� ��������
#include <iostream>
#include <vector> //���������� ���������� ��������
#include "Point.h" //���������� ���� � �������� ������ �����
using namespace std;

/*���� ���� �������� �������� ������ �������*/

class Polygon {
	//����� �������� ����������, �� ���� ������� ������ ������ ������ � ����������� ����:
protected:
	int len; //����� ������
	vector<double> x; //������ �-��������� ������ ��������
	vector<double> y; //������ y-��������� ������ ��������
	//����� � ������ ����������� ��������� ������
public:
	Polygon(); //���������� �� ���������
	Polygon(int,vector<double>, vector<double>); //���������� �������������, ����������� � �������� ����������
	//����� ������ � ������� ���������
	Polygon(const Polygon&); //����������� �����������
	~Polygon(); //����������
	Polygon& addVert(Point); //���������� ����� �������
	Polygon& delVert(Point); //�������� �������
	bool belong(const Point); //�������� �� �������������� ������� ��������
	bool intersect(Polygon); //�������� ����������� ���������
	int getNumbVert() { return this->len; } //����� ������

	Polygon& operator=(Polygon); //�������� ������������
	bool operator > (Polygon); //�������� ������
	bool operator < (Polygon); //�������� ������
	bool operator != (Polygon); //�������� �������
	bool operator >= (Polygon); //�������� ������ ��� �����
	bool operator <= (Polygon); //�������� ������ ��� �����
	bool operator == (Polygon); //�������� ���������
	friend ostream& operator << (ostream&, Polygon&); //�������� ������ � �����
	friend istream& operator >> (istream&, Polygon&); //�������� ����� � �����
};

