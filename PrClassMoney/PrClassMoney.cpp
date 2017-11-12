/*������� ����� Money ��� ������ � ��������� �������. ����� ������ ���� ������������ 
����� ������: ���� long ��� ������ � ���� unsigned char - ��� ������. ������� �����
(�������) ��� ������ �� ����� ������ ���� �������� �� ����� ����� �������.
����������� ��������, ���������, ������� ����, ������� ����� �� ������� �����,
��������� �� ������� ����� � �������� ���������.
������ ���� ���������� ����� ������������� Init(), ����� ����� ������ � ���������� Read(),
����� ������ ������ �� ����� Display(), �������������� � ������ toString(), ����������
��������� ���������� ��� �������� �������� ��� ������� ������.*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Money
{
/*��� 0 ������ ������� ��������� �� �����, ��� ����� ������ ���� long 
�������� ������������ usigned long � ��� ������� �������� ������� �������� �����*/

public:

	//������������ (Init)
	Money()
	{
		rubles = 0;
		kopecks = 0;
		sumM = 0;
	};

	Money(long rb, int kp)
	{
		rubles = rb;
		if (rubles == 0)
			kopecks = 0;
		else
		{
			//�������� 2 ������� ����� �������
			if (kp >= 100)
			{
				rubles = rubles + kp / 100;
				kopecks = (int)kopecks % 100;
			}
			else
				kopecks = kp;
			sumM = rubles + ((int)kopecks)*0.01;
		}
	};

	//���� � ����������
	void Read()
	{
		cin >> sumM;
		long res_rub;
		int res_kop;
		SplitUp(sumM, &res_rub, &res_kop);
		rubles = res_rub;
		kopecks = res_kop;
	}

	//����� �� �����
	void Display()
	{
		cout << rubles << ",";
		if ((int)kopecks < 10)
			cout << "0";
		cout << (int)kopecks << endl;
	}

	//�������������� � ������
	string toString()
	{
		string strMoney = "";
		strMoney = strMoney + to_string(rubles) + ",";
		if ((int)kopecks < 10)
			strMoney += "0";
		strMoney += to_string(kopecks);
		return strMoney;
	}

	//���������� �������� ��������

	Money operator+ (Money m2) const
	{
		long res_rub = rubles + m2.rubles;
		int res_kop = kopecks + m2.kopecks;
		return Money(res_rub, res_kop);
	}

	Money operator- (Money m2) 
	{
		double sumRes = sumM - m2.sumM;
		long res_rub;
		int res_kop;
		SplitUp(sumRes, &res_rub, &res_kop);
		return Money(res_rub, res_kop);
	}

	Money operator/ (Money m2)
	{
		double sumRes = sumM / m2.sumM;
		long res_rub;
		int res_kop;
		SplitUp(sumRes, &res_rub, &res_kop);
		return Money(res_rub, res_kop);
	}

	Money operator/ (double sumM2)
	{
		double sumRes = sumM / sumM2;
		long res_rub;
		int res_kop;
		SplitUp(sumRes, &res_rub, &res_kop);
		return Money(res_rub, res_kop);
	}
	
	Money operator* (Money m2)
	{
		double sumRes = sumM * m2.sumM;
		long res_rub;
		int res_kop;
		SplitUp(sumRes, &res_rub, &res_kop);
		return Money(res_rub, res_kop);
	}

	Money operator* (double sumM2)
	{
		double sumRes = sumM * sumM2;
		long res_rub;
		int res_kop;
		SplitUp(sumRes, &res_rub, &res_kop);
		return Money(res_rub, res_kop);
	}

	bool operator== (Money m2) const
	{
		return ((rubles == m2.rubles) && (kopecks == m2.kopecks)) ? true : false;
	}

	bool operator> (Money m2) const
	{
		bool res1 = (rubles > m2.rubles) || ((rubles == m2.rubles)&&(kopecks > m2.kopecks));
		//false �������� m1<=m2
		return res1 ? true : false;
	}

	bool operator< (Money m2) const
	{
		bool res1 = (m2.rubles > rubles) || ((rubles == m2.rubles) && (m2.kopecks > kopecks));
		//false �������� m1>=m2
		return res1 ? true : false;
	}

	bool operator>= (Money m2) const
	{
		bool res1 = (m2.rubles > rubles) || ((rubles == m2.rubles) && (m2.kopecks > kopecks));
		//true �������� m1>=m2
		return res1 ? false : true;
	}

	bool operator<= (Money m2) const
	{
		bool res1 = (rubles > m2.rubles) || ((rubles == m2.rubles) && (kopecks > m2.kopecks));
		//false �������� m1<=m2
		return res1 ? false : true;
	}

private:

	long rubles;
	unsigned char kopecks;
	double sumM;

	//��������� ������ � ������ �� �� ����� 
	void SplitUp(double sum, long* rb, int* kp)
	{
		*rb = (int)sum;
		*kp = 0;
		if (*rb != 0)
		{
			//�������� 3 ������� ����� �������
			*kp = (sum - (int)sum) * 1000;
			if (*kp < 0)
				*kp *= -1;
			if (*kp % 10 == 9)
				//++*kp;
				*kp += 1;
			//��������� �� ���� ��������
			*kp = *kp / 10;
		}
	}

};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Money a;
	Money b;
	Money c; //��������� �������� ��� a � b
	double d;
	int number;

	for (; ;)
	{
		cout << "--------------------------------------" << endl;
		cout << "                 ����                 " << endl;
		cout << "--------------------------------------" << endl;
		cout << "1 - ���� �������� �����" << endl;
		cout << "2 - ����� �������� ����� �� �����" << endl;
		cout << "3 - ������� �������� ����� � ������ " << endl;
		cout << "4 - ������� �����" << endl;
		cout << "5 - ������� �����" << endl;
		cout << "6 - �������� �����" << endl;
		cout << "7 - �������� ����� �� ������� �����" << endl;
		cout << "8 - ����������� �����" << endl;
		cout << "9 - �������� ����� �� ������� �����" << endl;
		cout << "0 - ����� " << endl;
		cout << "--------------------------------------" << endl;
		cout << "������� �����: ";
		cin >> number;
		cout << "--------------------------------------" << endl;

		switch (number)
		{
			case 1: 
			{
				cout << "������� �������� �����." << endl;
				a.Read();
			}
			break;
			case 2: 
			{
				cout << "��������� ������ ������� Display(): ";
				a.Display();
			}
			break;
			case 3: 
			{
				cout << "��������� ������ ������� toString(): " << a.toString() << endl;
			}
			break;
			case 4: 
			{
				cout << "������� �������� ����� ��� �������� � ������" << endl;
				b.Read();
				c = a + b;
				cout << "��������� ��������: " << c.toString() << endl;
				if (c == a)
					cout << "��������� ����� ��������� �����" << endl;
				else
					cout << "��������� �� ����� ��������� �����" << endl;
			}
			break;
			case 5:
			{
				cout << "������� �������� ����� ��� ��������� �� ������" << endl;
				b.Read();
				c = a - b;
				cout << "��������� ���������: " << c.toString() << endl;
				if (c < a)
					cout << "��������� ������ ��������� �����" << endl;
				else
					cout << "��������� ������ ��� ����� ��������� �����" << endl;
			}
			break;
			case 6: 
			{
				cout << "������� �������� ����� ��� ������� � ������" << endl;
				b.Read();
				c = a / b;
				cout << "��������� �������: " << c.toString() << endl;
				if (c > a)
					cout << "��������� ������ ��������� �����" << endl;
				else
					cout << "��������� ������ ��� ����� ��������� �����" << endl;
			}
			break;
			case 7: 
			{
				cout << "������� ������� ����� ��� �������" << endl;
				cin >> d;
				c = a / d;
				cout << "��������� �������: " << c.toString() << endl;
				if (c <= a)
					cout << "��������� ������ ��� ����� ��������� �����" << endl;
				else
					cout << "��������� ������ ��������� �����" << endl;
			}
			break;
			case 8: 
			{
				cout << "������� ������ ����� ��� ��������� � ������" << endl;
				b.Read();
				c = a * b;
				cout << "��������� ���������: " << c.toString() << endl;
				if (c >= a)
					cout << "��������� ������ ��� ����� ��������� �����" << endl;
				else
					cout << "��������� ������ ��������� �����" << endl;
			}
			break;
			case 9:
			{
				cout << "������� ������� ����� ��� ���������" << endl;
				cin >> d;
				c = a * d;
				cout << "��������� ���������: " << c.toString() << endl;
				if (c > a)
					cout << "��������� ������ ��������� �����" << endl;
				else
					cout << "��������� ������ ��� ����� ��������� �����" << endl;
			}
			break;
			case 0: exit(1); break;
			default: cout << "����������� ���� " << endl; break;
		}
		getchar();

	}
    return 0;
}

