#include "DynArray.h"
//Конструктор с параметрами
DynArray::DynArray(size_t Size) : size{ Size }, array{ new int[size] {} }
{
	if (!array) //проверка выделения памяти
	{
		cout << "Ошибка выделения памяти! Создан пустой массив!" << endl;
		size = 0; //тогда создаем пустой массив
	}
	//else cout<<"Память для поля array объекта "<<this<<" успешно выделена в конструкторе с параметром!"<<endl; //для теста
}
//конструктор копирования принемает константную lvalue ссылку на постоянный именованный объект(Original)
DynArray::DynArray(const DynArray& Original) : size{ Original.size }, array{ new int[size] {} }
{
	if (!array) //проверка выделения памяти
	{
		cout << "Ошибка выделения памяти! Создан пустой массив!" << endl;
		size = 0; //тогда создаем пустой массив
	}
	else
	{
		//cout<<"Память для поля array объекта "<<this<<" - копии объекта "<<&Original
		//	<<" успешно выделена в конструкторе копирования!"<<endl; //для теста
		for (int i = 0; i < size; i++)
		{
			this->array[i] = Original.array[i]; //копируем значения элементов из поля array объекта Original в новый объект(в копию) this
		}
	}
}
//если в классе перегружен оператор копирующего присваивания, то его можно использовать в конструткоре копирования
//DynArray::DynArray(const DynArray& Original)
//{
//	*this = Original; //использование перегруженного оператора копирующего присваивания
//}

//конструктор перемещения rvalue ссылка в качестве параметра принимает временный безымянный rvalue объект класса DynArray
DynArray::DynArray(DynArray&& rVal) : size{ rVal.size }, array{ rVal.array } //копириуем адрес памяти, выделенной в исходном(временном безымянном объекте)
//по ссылке rVal в новый постоянный именованный объект
{
	//отбираем право владения памятью у исходного(временного безымянного) объекта и "обнуляем" его
	rVal.array = nullptr;
	rVal.size = (size_t)0;
	//cout<<"Сработал конструктор перемещения для объекта "<<this<<". Объект "<<&rVal<<" был опустошен!"<<endl;//для теста!
}
//конструктор списочной инициализации
//Делегирование - явный вызов конструктора с параметрами
DynArray::DynArray(const initializer_list<int>& list) : DynArray(list.size())
{
	int i = 0;
	//range-base цикл
	for (int element : list) //for (auto element : list)
		//вместо auto будет подставлен тип данных, соответсвующий содержимому
	{
		array[i] = element; //element - буфер в который на каждом шаге цикла копируются значения
		//из объекта list класса initializer_list<int> с первого до последнего включительно
		i++;
	}
	//cout << "Сработал конструктор списочной инициализации для объекта " << this << endl; //для теста
}
//Деструктор
DynArray::~DynArray()
{
	if (array) //если объект не "пустой"
	{
		delete[] array; //освобождение памяти, выделенной под поле array
		array = nullptr;
		size = 0;
		//cout << "Память для поля array объекта " << this << " успешно освобождена!" << endl; //для теста
	}
	//иначе если явно вызывался деструктор или объект пустым изначально или был "опустошен"
	//else cout<<"Память для поля array объекта "<<this<<" уже была освобождена!"<<endl; //для теста
}
//сеттеры:
//Метод заполнения массива случайными числами от указанного до указанного числа
void DynArray::Randomize(int Begin, int End)
{
	//сдвиг генератора случайных чисел в main
	//если массив пустой, то можно запросить размер, выделить память и заполнить
	for (int i = 0; i < size; i++)
	{
		//проверка если Begin>End
		array[i] = (Begin < End) ? rand() % (End + 1 - Begin) + Begin : rand() % (Begin + 1 - End) + End;
	}
}
//метод изменения размера массива внутри объекта класса DynArray
void DynArray::ReSize(size_t NewSize)
{
	if (this->size == NewSize)return; //если текущий размер и новый размер совпадают
	int* temp = new int[NewSize] {}; //выделяем память под элементы типа данных int новым кол-вом
	if (!temp)//проверка выделения памяти!
	{
		cout << "Ошибка выделения памяти! Размер массива не будет изменен!" << endl;
		return; //тогда не изменяем массив
	}
	if (this->size != 0) //if(size!=0)  //if(size)
	{
		for (int i = 0; i < NewSize; i++) //копируем элементы из поля array текущего объекта в новую память
		{
			if (i < size)temp[i] = array[i]; //если ещё есть элементы в текущем объекте
			else break; //иначе выход из цикла копирования элементов из поля array текущего объекта в новую память
		}
		delete[] array; //освобождаем старую память поля array
	}
	size = NewSize; //изменяем размер текущего объекта
	array = temp; //помещаем в поле array текущего объекта адрес новой памяти нужного размера
}
//геттеры:
//Метод получения текущего размера массива(кол-ва элементов)
size_t DynArray::Size() const
{
	return size;
}
//реализация метода сортировки массива
void DynArray::Sort()
{
	bool Type = 0;
	cout << R"(
Выберите как отсортировать массив:
0 - от меньшего к большему(по возрастанию значений)
1 - от большего к меньшему(по убыванию значений)
)";
	cin >> Type;
	cout << endl;
	for (int i = 0; i < size - 1; i++)// i - индекс последнего из упорядоченных элементов
	{
		// элемент Array[i+1] - следующий элемент, который необходимо вставить на нужное место от 0 до i+1
		int tmp = array[i + 1];// копируем в переменную для обмена
		int j = i;// счетчик, движется от конца упорядоченной части
		if (Type)//от Мин. к Макс. (по возрастанию значений)
		{
			while (j >= 0 && array[j] < tmp)// пока счетчик не дошел до начала массива и элемент из упорядоченного массива больше tmp 
				// пока не найдено место
			{
				array[j + 1] = array[j];// сдвигаем элемент вправо
				j--;
			}
			array[j + 1] = tmp;// когда найдено значения, после которого нужно вставить элемент
		}
		else//от Макс. к Мин. (по убыванию значений)
		{
			while (j >= 0 && array[j] > tmp)
			{
				array[j + 1] = array[j];
				j--;
			}
			array[j + 1] = tmp;
		}
	}
}


//перегрузка операторов как методов класса:
//перегрузка оператора индексирования []
int& DynArray::operator[](int index)
{
	//проверка выхода за границы массива
	while (index < 0 || index >= size)
	{
		cout << "Выход за границы массива! Введите индекс: " << endl;
		cin >> index;
		/*return array[0];
		delete[] array;
		exit(3);
		this->~DynArray();
		exit(3);*/
	}
	return array[index]; //возвращаем ссылку на элемент с указанным индексом
}
//константная перегрузка оператора индексирования []
const int DynArray::operator[](int index) const
{
	bool Error = (index >= 0 && index < size); //условие корреткного индекса
	if (!Error)this->~DynArray(); //если вышли за границы массива освобождаем память
	assert(Error && "Выход за границы массива!"); //сработает когда условие в скобках ложно
	return array[index]; //возвращаем значение элемента с указанным индексом
}
//перегрузка оператора копирующего присваивания
DynArray& DynArray::operator=(const DynArray& Original) //*this=Original
{
	//Original = Original;
	if (this != &Original) //если не один и тот же объект
	{
		if (this->size != Original.size) //если не равны размеры массивов внутри объектов this и Original
		{
			delete[] this->array; //освобождаем старую память поля array текущего объекта this
			this->array = nullptr; //обнуляем указатель
			this->size = Original.size; //получаем новый размер из копируемого объекта Original
			if (this->size) //если новый(полученный) размер не нулевой, выделяем память нужного размера
			{
				array = new int[size] {}; //this->array = new int[this->size]{};
				if (!array)
				{
					cout << "Ошибка выделения памяти!" << endl;
					size = 0; //тогда оставляем текущий массив пустым
				}
			}
		}
		for (int i = 0; i < size; ++i)
		{
			this->array[i] = Original.array[i]; //коируем элементы из копируемого объекта Original в текущий объект this
		}
	}
	//cout<<"Оператор копирующего присваивания из объекта "<<&Original<<" в объект "<<this<<endl; //для теста
	return *this;//возвращаем ссылку на объект для которого вызывался оператор
}
//перегрузка оператора перемещающего присваивания = 
DynArray& DynArray::operator=(DynArray&& rVal)
{
	//rVal = move(rVal);
	if (this != &rVal) //если это не один и тот же объект
	{
		delete[] array; //delete[] this->array; //осо-вобождаем старую память поля array текущего объекта
		array = rVal.array; //this->array = rVal.array; //копируем адрес памяти из присваиваемого объекта, полученнного по rvalue ссылке rVal в текущий this 
		size = rVal.size; //this->size = rVal.size; //получаем новый размер из присваиваемого объекта, полученнного по rvalue ссылке rVal в текущий this 
		//"обнуляем" присваиваемый объект,  полученнный по rvalue ссылке rVal
		rVal.array = nullptr;
		rVal.size = 0;
	}
	//cout << "Оператор перемещающего присваивания из объекта " << &rVal << " в объект " << this << endl; //для теста
	return *this;//возвращаем ссылку на объект для которого вызывался оператор
}
//перегрузка оператора провреки на равенство ==
bool DynArray::operator==(const DynArray& A) const //*this==A
{
	if (this->size != A.size) //если размеры не равны
		return false;
	for (int i = 0; i < size; ++i)
	{
		//как только найдены неравные элементы
		if (array[i] != A.array[i]) //if(this->array[i]!=A.array[i])
			return false;
	}
	return true; //массивы равны
}
//перегрузка оператора провреки на равенство !=
bool DynArray::operator!=(const DynArray& A) const
{
	return !(*this == A); //обратный результат перегруженного оператора проверки на равенство ==
	//текущего объекта - разыменованный указатель *this и сравниваемого с ним объекта А
}
//перегрузка операторов работы с динамической памятью
void* DynArray::operator new(size_t Size)
{
	//this; //операторы new и delete - статические
	void* Pointer = malloc(Size); //функция выделения памяти
	//int* A = (int*)malloc(sizeof(int)); //выделение памяти под одну переменную в языке С	

	if (!Pointer)
	{
		cout << "Ошибка выделения памяти!" << endl;
		//exit(3);
		//добавить исключения
	}
	//else cout << "\nПамять успешно выделена!" << endl; //для теста
	return Pointer;
	//return malloc(Size);
}
void DynArray::operator delete(void* Pointer)
{
	if (Pointer)
	{
		//Pointer = realloc(Pointer, sizeof(int));
		//функция освобождения старой памяти и выделения новой памяти нужного размера
		free(Pointer); //функция освобождения памяти из языка С
		//cout << "Память была успешно освобождена!" << endl; //для теста
	}
	//else cout<<"Память уже была освобождена!"<<endl; //для теста
}
void* DynArray::operator new[](size_t Size)
{
	//this; //операторы new и delete - статические
	void* Pointer = malloc(Size); //функция выделения памяти
	//int* Array = (int*)malloc(Size*sizeof(int)); //выделение памяти под массив переменных в языке С	

	if (!Pointer)
	{
		cout << "Ошибка выделения памяти!" << endl;
		//exit(3);
		//добавить исключения
	}
	//else cout << "\nПамять успешно выделена!" << endl; //для теста
	return Pointer;
	//return malloc(Size);
}
void DynArray::operator delete[](void* Pointer)
{
	if (Pointer)
	{
		//Pointer = realloc(Pointer, NewSize * sizeof(int));
		//функция освобождения старой памяти и выделения новой памяти нужного размера под массив
		free(Pointer); //функция освобождения памяти из языка С
		//cout << "Память была успешно освобождена!" << endl; //для теста
	}
	//else cout << "Память уже была освобождена!" << endl; //для теста
}

//перегрузка оператора сложения для ситуации DynArray+int
DynArray DynArray::operator+(int Digit)
{
	DynArray Result(size);//Временный обект для хранения результата

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] + Digit;
	}
	return Result;//Возвращаем временный обект
}
//перегрузка оператора вычитания для ситуации DynArray-int
DynArray DynArray::operator-(int Digit)
{
	DynArray Result(size);//Временный обект для хранения результата

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] - Digit;
	}
	return Result;//Возвращаем временный обект
}
//перегрузка оператора умножения для ситуации DynArray*int
DynArray DynArray::operator*(int Digit)
{
	DynArray Result(size);//Временный обект для хранения результата

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] * Digit;
	}
	return Result;//Возвращаем временный обект
}
//перегрузка оператора деления для ситуации DynArray/int
DynArray DynArray::operator/(int Digit)
{
	DynArray Result(size);//Временный обект для хранения результата

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] / Digit;
	}
	return Result;//Возвращаем временный обект
}


//дружественная перегрузка оператора сложения для ситуации int + DynArray
DynArray operator+(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //Временный обект для хранения результата
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit + Massiv.array[i];
	}
	return Temp;//Возвращаем временный обект
}
//дружественная перегрузка оператора вычитания для ситуации int - DynArray
DynArray operator-(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //Временный обект для хранения результата
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit - Massiv.array[i];
	}
	return Temp;//Возвращаем временный обект
}
//дружественная перегрузка оператора умножения для ситуации int * DynArray
DynArray operator*(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //Временный обект для хранения результата
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit * Massiv.array[i];
	}
	return Temp;//Возвращаем временный обект
}
//дружественная перегрузка оператора деления для ситуации int / DynArray
DynArray operator/(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //Временный обект для хранения результата
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit / Massiv.array[i];
	}
	return Temp;//Возвращаем временный обект
}

//дружественная перегрузка операторов:
//перегрузка оператора вывода
ostream& operator<<(ostream& Out, const DynArray& A)
{
	//для дружественной перегрузки							//для глобальной перегрузки
	//прямое обращение к полю size объекта А				//вызов метода Size()
	for (int i = 0; i < A.size; ++i)						//for(int i = 0; i < A.Size(); ++i)
	{														//{
		//прямое обращение к полю array объекта А			//  //вызов перегруженного оператор индексирования для объекта А
		Out << A.array[i] << " ";								//Out << A[i] << " ";
	}														//}
	//Out << endl;											//Out << endl;
	return Out;												//return Out;
}
//перегрузка оператора ввода
istream& operator>>(istream& In, DynArray& A)
{
	//для дружественной перегрузки							//для глобальной перегрузки
	//прямое обращение к полю size объекта А				//вызов метода Size() для объекта А
	for (int i = 0; i < A.size; ++i)						//for(int i = 0; i < A.Size(); ++i)
	{														//{
		cout << "Введите " << i << "-й элемент: ";			//	cout << "Введите " << i << "-й элемент: ";
		//прямое обращение к полю array объекта А			//  //вызов перегруженного оператор индексирования для объекта А
		In >> A.array[i];									//	In >> A[i];
	}														//}
	return In;												//return In;
}

//глобальная перегрузки оператора сложения + (сложение массивов поэлементно)
DynArray operator+(const DynArray& A, const DynArray& B) //A+B
{
	DynArray Temp; //временный пустой объект
	if (B.Size() > A.Size())
	{
		//копируем в Temp объект В бОльшего резмера
		Temp = B; //перегруженный оператор копирующего присваивания
		for (int i = 0; i < A.Size(); ++i)
		{
			Temp[i] += A[i]; //прибавляем значения из меньшего массива А,
			//используя перегруженные операторы индексирования []
		}
	}
	else
	{
		//копируем в Temp объект A бОльшего резмера
		Temp = A; //перегруженный оператор копирующего присваивания
		for (int i = 0; i < B.Size(); ++i)
		{
			Temp[i] += B[i]; //прибавляем значения из меньшего массива B,
			//используя перегруженные операторы индексирования []
		}
	}
	return Temp; //Возвращаем значение временного объекта
}