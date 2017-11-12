/*Создать класс Money для работы с денежными суммами. Число должно быть представлено 
двумя полями: типа long для рублей и типа unsigned char - для копеек. Дробная часть
(копейки) при выводе на экран должна быть отделена от целой части запятой.
Реализовать сложение, вычитание, деление сумм, деление суммы на дробное число,
умножение на дробное число и операции сравнения.
Должен быть реализован метод инициализации Init(), метод ввода данных с клавиатуры Read(),
метод вывода данных на экран Display(), преобразование в строку toString(), необходимо
выполнить перегрузку для основных операций для методов класса.*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Money
{
/*При 0 рублях копейки считаться не будут, ибо тогда вместо типа long 
придется использовать usigned long и для каждого значения хранить отдельно минус*/

public:

	//конструкторы (Init)
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
			//точность 2 символа после запятой
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

	//ввод с клавиатуры
	void Read()
	{
		cin >> sumM;
		long res_rub;
		int res_kop;
		SplitUp(sumM, &res_rub, &res_kop);
		rubles = res_rub;
		kopecks = res_kop;
	}

	//вывод на экран
	void Display()
	{
		cout << rubles << ",";
		if ((int)kopecks < 10)
			cout << "0";
		cout << (int)kopecks << endl;
	}

	//преобразование в строку
	string toString()
	{
		string strMoney = "";
		strMoney = strMoney + to_string(rubles) + ",";
		if ((int)kopecks < 10)
			strMoney += "0";
		strMoney += to_string(kopecks);
		return strMoney;
	}

	//ПЕРЕГРУЗКА ОСНОВНЫХ ОПЕРАЦИЙ

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
		//false включает m1<=m2
		return res1 ? true : false;
	}

	bool operator< (Money m2) const
	{
		bool res1 = (m2.rubles > rubles) || ((rubles == m2.rubles) && (m2.kopecks > kopecks));
		//false включает m1>=m2
		return res1 ? true : false;
	}

	bool operator>= (Money m2) const
	{
		bool res1 = (m2.rubles > rubles) || ((rubles == m2.rubles) && (m2.kopecks > kopecks));
		//true включает m1>=m2
		return res1 ? false : true;
	}

	bool operator<= (Money m2) const
	{
		bool res1 = (rubles > m2.rubles) || ((rubles == m2.rubles) && (kopecks > m2.kopecks));
		//false включает m1<=m2
		return res1 ? false : true;
	}

private:

	long rubles;
	unsigned char kopecks;
	double sumM;

	//выделение рублей и копеек из их суммы 
	void SplitUp(double sum, long* rb, int* kp)
	{
		*rb = (int)sum;
		*kp = 0;
		if (*rb != 0)
		{
			//точность 3 символа после запятой
			*kp = (sum - (int)sum) * 1000;
			if (*kp < 0)
				*kp *= -1;
			if (*kp % 10 == 9)
				//++*kp;
				*kp += 1;
			//сокращаем до двух символов
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
	Money c; //результат операций над a и b
	double d;
	int number;

	for (; ;)
	{
		cout << "--------------------------------------" << endl;
		cout << "                 МЕНЮ                 " << endl;
		cout << "--------------------------------------" << endl;
		cout << "1 - Ввод денежной суммы" << endl;
		cout << "2 - Вывод денежной суммы на экран" << endl;
		cout << "3 - Перевод денежной суммы в строку " << endl;
		cout << "4 - Сложить суммы" << endl;
		cout << "5 - Вычесть суммы" << endl;
		cout << "6 - Поделить суммы" << endl;
		cout << "7 - Поделить сумму на дробное число" << endl;
		cout << "8 - Перемножить суммы" << endl;
		cout << "9 - Умножить сумму на дробное число" << endl;
		cout << "0 - Выход " << endl;
		cout << "--------------------------------------" << endl;
		cout << "Введите номер: ";
		cin >> number;
		cout << "--------------------------------------" << endl;

		switch (number)
		{
			case 1: 
			{
				cout << "Введите денежную сумму." << endl;
				a.Read();
			}
			break;
			case 2: 
			{
				cout << "Результат работы функции Display(): ";
				a.Display();
			}
			break;
			case 3: 
			{
				cout << "Результат работы функции toString(): " << a.toString() << endl;
			}
			break;
			case 4: 
			{
				cout << "Введите денежную сумму для сложения с первой" << endl;
				b.Read();
				c = a + b;
				cout << "Результат сложения: " << c.toString() << endl;
				if (c == a)
					cout << "Результат равен исходному числу" << endl;
				else
					cout << "Результат не равен исходному числу" << endl;
			}
			break;
			case 5:
			{
				cout << "Введите денежную сумму для вычитания из первой" << endl;
				b.Read();
				c = a - b;
				cout << "Результат вычитания: " << c.toString() << endl;
				if (c < a)
					cout << "Результат меньше исходного числа" << endl;
				else
					cout << "Результат больше или равен исходному числу" << endl;
			}
			break;
			case 6: 
			{
				cout << "Введите денежную сумму для деления с первой" << endl;
				b.Read();
				c = a / b;
				cout << "Результат деления: " << c.toString() << endl;
				if (c > a)
					cout << "Результат больше исходного числа" << endl;
				else
					cout << "Результат меньше или равен исходному числу" << endl;
			}
			break;
			case 7: 
			{
				cout << "Введите дробное число для деления" << endl;
				cin >> d;
				c = a / d;
				cout << "Результат деления: " << c.toString() << endl;
				if (c <= a)
					cout << "Результат меньше или равен исходному числу" << endl;
				else
					cout << "Результат больше исходного числа" << endl;
			}
			break;
			case 8: 
			{
				cout << "Введите вторую сумму для умножения с первой" << endl;
				b.Read();
				c = a * b;
				cout << "Результат умножения: " << c.toString() << endl;
				if (c >= a)
					cout << "Результат больше или равен исходному числу" << endl;
				else
					cout << "Результат меньше исходного числа" << endl;
			}
			break;
			case 9:
			{
				cout << "Введите дробное число для умножения" << endl;
				cin >> d;
				c = a * d;
				cout << "Результат умножения: " << c.toString() << endl;
				if (c > a)
					cout << "Результат больше исходного числа" << endl;
				else
					cout << "Результат меньше или равен исходному числу" << endl;
			}
			break;
			case 0: exit(1); break;
			default: cout << "Некорретный ввод " << endl; break;
		}
		getchar();

	}
    return 0;
}

