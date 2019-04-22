#include <iostream>
#include <vector>

using namespace std;
const double EPS = 1.084202e-19; //��������� ��������, ���������� ��� ��� ���������� ��������� ����� � ��������� �������

class Point {
public:
	double x; //�-���������� �����
	double y; //y-���������� �����
	Point(double x = 0, double y = 0) { //����������� � �����������, ������������ �����������
		//���� ������������ �� ���������
		this->x = x;
		this->y = y;
	}
	~Point() {} //����������
};


class Polygon {
	//����� �������� ����������, �� ���� ������� ������ ������ ������ � ����������� ����:
protected:
	int len; //����� ������
	vector<double> x; //������ �-��������� ������ ��������
	vector<double> y; //������ y-��������� ������ ��������
	//����� � ������ ����������� ��������� ������
public:
	Polygon(); //���������� �� ���������
	Polygon(int, vector<double>, vector<double>); //���������� �������������, ����������� � �������� ����������
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

Polygon::Polygon(int len, vector<double> x, vector<double> y) { //����������� �������������
	//��������� ����� ������ � �� ���������� � ����������� ���������� ��������� ����� ���������� ������
	//���� ����������� ����� ��� ������������� �������� ������ �������
	this->len = len;
	this->x = x;
	this->y = y;
}

Polygon::Polygon(const Polygon& tmp) { //����������� �����������
	//��������� � �������� ��������� ���������� ������ �� ������ ������ �������
	//� �������� ��� ���������� � ��� ���������
	//���� ����������� ����� ��� ����������� ����������� ������ �������
	len = tmp.len;
	x = tmp.x;
	y = tmp.y;
}

Polygon::~Polygon() { //����������
	// �����, ������������ ����� ����, ��� ��������� ������ ��������� ��������������
	//��������� ��� ����������� ������
	while (x.size() > 0 && y.size() > 0) {
		x.pop_back();
		y.pop_back();
	}
}

Polygon& Polygon::addVert(Point point) { //����� ���������� �������
	//��������� �����
	//��������� �� ���������� � ����������� ������ ��������
	x.push_back(point.x);
	y.push_back(point.y);
	len++; //����������� �� 1 ����� ������
	return *this; //���������� ���������� ������ �� ��� ��������� �������
}

Polygon& Polygon::delVert(Point point) { //�������� �������
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
	cout << "������� ����� ������ ��������(�� ������ ����): ";
	in >> obj.len;
	cout << "������� ������� � ���������������� �������" << endl;
	for (int i = 0; i < obj.len; i++)
	{
		cout << "������� ���������� " << i + 1 << " ������� (x,y):";
		in >> point.x;
		obj.x.push_back(point.x);
		in >> point.y;
		obj.y.push_back(point.y);
	}
	return in;
}

ostream& operator << (ostream& out, Polygon& obj) {
	out << "����� ������ �������� = ";
	out << obj.len << endl;
	for (int i = 0; i < obj.len; i++) {
		out << "���������� " << i + 1 << " �������:" << endl;
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
	setlocale(LC_ALL, "RUS"); //��������� ������� � ������� ���������
	Point A; // ���������� ����� �
	vector<double>x1 = { 0,0,5,5 }; //������ �-���������
	vector<double>y1 = {0, 10, 10,0}; //������ y-���������
	// �� ������� ��������� �������������� ��� ������������� ������
	Polygon qwerty1; //����������� �� ��������� 
	Polygon qwerty2(4, x1, y1); //����������� ������������� 
	Polygon qwerty3(qwerty2); //����������� ����������� 
	Polygon qwerty5;
	qwerty5 = qwerty3; // �������� ������������
	cin >> qwerty1; //�������� ����� � ����� 
	cout << qwerty1; //�������� ������ � �����
	cout << "������� �����" << endl;
	cin >> A.x >> A.y; //������ ���������� ����� �
	if(qwerty1.belong(A)) //�������� ��������������� ����� ��������
	    cout << "����� ������ ��������" << endl;
	else cout << "����� ��� ��������" << endl;
	if(qwerty2.intersect(qwerty1)) //�������� ����������� ��������� 
		cout << "�������� ������������" << endl;
	else cout << "�������� �� ������������" << endl;
	MyPolygon qwerty6 = qwerty1; //������������� ���������� ������ ����������
	cout <<"Perimeter "<< qwerty6.perimeter() << endl; //������� ��������� ��������
	cout << "Number of vertex " << qwerty6.getNumbVert() << endl; //����� ������ ��������
	//�������� ���� ���������� ��������� ��� ���������
	if (qwerty1 > qwerty2) //�������� ������
		cout << "1 ������ 2" << endl;
	else
		cout << "1 ������ 2" << endl;
	if (qwerty1 <= qwerty2) //�������� ������ �����
		cout << "1 ������ ��� ����� 2" << endl;
	else
		cout << "1 ������ 2" << endl;
	if (qwerty1 != qwerty2) //�������� �������
		cout << "1 �� ����� 2" << endl;
	else
		cout << "1 ����� 2" << endl;
	if(qwerty6 == qwerty1) //�������� ���������
		cout << "1 ����� 2" << endl;
	else
		cout << "1 �� ����� 2" << endl;
	//���������� ������� 
	cout << "�� ���������� ������� �������" << endl;
	cout << qwerty1;
	qwerty1.addVert(A); //���������� ������� �
	cout << "����� ���������� ������� �������" << endl;
	cout << qwerty1;
	//�������� ������� 
	cout << "�� �������� ������� �������" << endl;
	cout << qwerty1;
	qwerty1.delVert(A); //�������� ������� �
	cout << "����� �������� ������� �������" << endl;
	cout << qwerty1;
	system("pause");
}