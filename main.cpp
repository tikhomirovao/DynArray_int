#include <iostream>
#include "DynArray.h"

using namespace std;

//функция создания и заполнение массива случайными числами
DynArray CreateArray(size_t Size)
{
	DynArray TMP(Size); //создает локальный lvalue объект функции, указанного размера
	TMP.Randomize(-99, 99); //заполняет объект случайными числами от -99 до 99 включительно
	return TMP;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand((unsigned int)time(nullptr));


	DynArray Array((size_t)20);
	cout << Array << endl;

	Array.Randomize(-99, 99);
	cout << Array << endl;
	cout << endl;

	DynArray D = Array + 5;
	cout << "Результат прибавления 5 " << endl;
	cout << D << endl;
	cout << endl;

	DynArray B = Array - 10;
	cout << "Результат вычитания 10 " << endl;
	cout << B << endl;
	cout << endl;

	DynArray C = Array * 2;
	cout << "Результат умножения на 2 " << endl;
	cout << C << endl;
	cout << endl;

	DynArray E = Array / 3;
	cout << "Результат деления на 3 " << endl;
	cout << E << endl;
	cout << endl;

	DynArray F = 10 + Array;
	cout << "Результат прибавления к 10 " << endl;
	cout << F << endl;
	cout << endl;

	DynArray G = 100 - Array;
	cout << "Результат вычитания из 100 " << endl;
	cout << G << endl;
	cout << endl;

	DynArray K = 2 * Array;
	cout << "Результат умножение 2 на массив " << endl;
	cout << K << endl;
	cout << endl;

	DynArray L = 150 / Array;
	cout << "Результат деления 150 на массив " << endl;
	cout << L << endl;
	cout << endl;
}