#include "DynArray.h"
//����������� � �����������
DynArray::DynArray(size_t Size) : size{ Size }, array{ new int[size] {} }
{
	if (!array) //�������� ��������� ������
	{
		cout << "������ ��������� ������! ������ ������ ������!" << endl;
		size = 0; //����� ������� ������ ������
	}
	//else cout<<"������ ��� ���� array ������� "<<this<<" ������� �������� � ������������ � ����������!"<<endl; //��� �����
}
//����������� ����������� ��������� ����������� lvalue ������ �� ���������� ����������� ������(Original)
DynArray::DynArray(const DynArray& Original) : size{ Original.size }, array{ new int[size] {} }
{
	if (!array) //�������� ��������� ������
	{
		cout << "������ ��������� ������! ������ ������ ������!" << endl;
		size = 0; //����� ������� ������ ������
	}
	else
	{
		//cout<<"������ ��� ���� array ������� "<<this<<" - ����� ������� "<<&Original
		//	<<" ������� �������� � ������������ �����������!"<<endl; //��� �����
		for (int i = 0; i < size; i++)
		{
			this->array[i] = Original.array[i]; //�������� �������� ��������� �� ���� array ������� Original � ����� ������(� �����) this
		}
	}
}
//���� � ������ ���������� �������� ����������� ������������, �� ��� ����� ������������ � ������������ �����������
//DynArray::DynArray(const DynArray& Original)
//{
//	*this = Original; //������������� �������������� ��������� ����������� ������������
//}

//����������� ����������� rvalue ������ � �������� ��������� ��������� ��������� ���������� rvalue ������ ������ DynArray
DynArray::DynArray(DynArray&& rVal) : size{ rVal.size }, array{ rVal.array } //��������� ����� ������, ���������� � ��������(��������� ���������� �������)
//�� ������ rVal � ����� ���������� ����������� ������
{
	//�������� ����� �������� ������� � ���������(���������� �����������) ������� � "��������" ���
	rVal.array = nullptr;
	rVal.size = (size_t)0;
	//cout<<"�������� ����������� ����������� ��� ������� "<<this<<". ������ "<<&rVal<<" ��� ���������!"<<endl;//��� �����!
}
//����������� ��������� �������������
//������������� - ����� ����� ������������ � �����������
DynArray::DynArray(const initializer_list<int>& list) : DynArray(list.size())
{
	int i = 0;
	//range-base ����
	for (int element : list) //for (auto element : list)
		//������ auto ����� ���������� ��� ������, �������������� �����������
	{
		array[i] = element; //element - ����� � ������� �� ������ ���� ����� ���������� ��������
		//�� ������� list ������ initializer_list<int> � ������� �� ���������� ������������
		i++;
	}
	//cout << "�������� ����������� ��������� ������������� ��� ������� " << this << endl; //��� �����
}
//����������
DynArray::~DynArray()
{
	if (array) //���� ������ �� "������"
	{
		delete[] array; //������������ ������, ���������� ��� ���� array
		array = nullptr;
		size = 0;
		//cout << "������ ��� ���� array ������� " << this << " ������� �����������!" << endl; //��� �����
	}
	//����� ���� ���� ��������� ���������� ��� ������ ������ ���������� ��� ��� "���������"
	//else cout<<"������ ��� ���� array ������� "<<this<<" ��� ���� �����������!"<<endl; //��� �����
}
//�������:
//����� ���������� ������� ���������� ������� �� ���������� �� ���������� �����
void DynArray::Randomize(int Begin, int End)
{
	//����� ���������� ��������� ����� � main
	//���� ������ ������, �� ����� ��������� ������, �������� ������ � ���������
	for (int i = 0; i < size; i++)
	{
		//�������� ���� Begin>End
		array[i] = (Begin < End) ? rand() % (End + 1 - Begin) + Begin : rand() % (Begin + 1 - End) + End;
	}
}
//����� ��������� ������� ������� ������ ������� ������ DynArray
void DynArray::ReSize(size_t NewSize)
{
	if (this->size == NewSize)return; //���� ������� ������ � ����� ������ ���������
	int* temp = new int[NewSize] {}; //�������� ������ ��� �������� ���� ������ int ����� ���-���
	if (!temp)//�������� ��������� ������!
	{
		cout << "������ ��������� ������! ������ ������� �� ����� �������!" << endl;
		return; //����� �� �������� ������
	}
	if (this->size != 0) //if(size!=0)  //if(size)
	{
		for (int i = 0; i < NewSize; i++) //�������� �������� �� ���� array �������� ������� � ����� ������
		{
			if (i < size)temp[i] = array[i]; //���� ��� ���� �������� � ������� �������
			else break; //����� ����� �� ����� ����������� ��������� �� ���� array �������� ������� � ����� ������
		}
		delete[] array; //����������� ������ ������ ���� array
	}
	size = NewSize; //�������� ������ �������� �������
	array = temp; //�������� � ���� array �������� ������� ����� ����� ������ ������� �������
}
//�������:
//����� ��������� �������� ������� �������(���-�� ���������)
size_t DynArray::Size() const
{
	return size;
}
//���������� ������ ���������� �������
void DynArray::Sort()
{
	bool Type = 0;
	cout << R"(
�������� ��� ������������� ������:
0 - �� �������� � ��������(�� ����������� ��������)
1 - �� �������� � ��������(�� �������� ��������)
)";
	cin >> Type;
	cout << endl;
	for (int i = 0; i < size - 1; i++)// i - ������ ���������� �� ������������� ���������
	{
		// ������� Array[i+1] - ��������� �������, ������� ���������� �������� �� ������ ����� �� 0 �� i+1
		int tmp = array[i + 1];// �������� � ���������� ��� ������
		int j = i;// �������, �������� �� ����� ������������� �����
		if (Type)//�� ���. � ����. (�� ����������� ��������)
		{
			while (j >= 0 && array[j] < tmp)// ���� ������� �� ����� �� ������ ������� � ������� �� �������������� ������� ������ tmp 
				// ���� �� ������� �����
			{
				array[j + 1] = array[j];// �������� ������� ������
				j--;
			}
			array[j + 1] = tmp;// ����� ������� ��������, ����� �������� ����� �������� �������
		}
		else//�� ����. � ���. (�� �������� ��������)
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


//���������� ���������� ��� ������� ������:
//���������� ��������� �������������� []
int& DynArray::operator[](int index)
{
	//�������� ������ �� ������� �������
	while (index < 0 || index >= size)
	{
		cout << "����� �� ������� �������! ������� ������: " << endl;
		cin >> index;
		/*return array[0];
		delete[] array;
		exit(3);
		this->~DynArray();
		exit(3);*/
	}
	return array[index]; //���������� ������ �� ������� � ��������� ��������
}
//����������� ���������� ��������� �������������� []
const int DynArray::operator[](int index) const
{
	bool Error = (index >= 0 && index < size); //������� ����������� �������
	if (!Error)this->~DynArray(); //���� ����� �� ������� ������� ����������� ������
	assert(Error && "����� �� ������� �������!"); //��������� ����� ������� � ������� �����
	return array[index]; //���������� �������� �������� � ��������� ��������
}
//���������� ��������� ����������� ������������
DynArray& DynArray::operator=(const DynArray& Original) //*this=Original
{
	//Original = Original;
	if (this != &Original) //���� �� ���� � ��� �� ������
	{
		if (this->size != Original.size) //���� �� ����� ������� �������� ������ �������� this � Original
		{
			delete[] this->array; //����������� ������ ������ ���� array �������� ������� this
			this->array = nullptr; //�������� ���������
			this->size = Original.size; //�������� ����� ������ �� ����������� ������� Original
			if (this->size) //���� �����(����������) ������ �� �������, �������� ������ ������� �������
			{
				array = new int[size] {}; //this->array = new int[this->size]{};
				if (!array)
				{
					cout << "������ ��������� ������!" << endl;
					size = 0; //����� ��������� ������� ������ ������
				}
			}
		}
		for (int i = 0; i < size; ++i)
		{
			this->array[i] = Original.array[i]; //������� �������� �� ����������� ������� Original � ������� ������ this
		}
	}
	//cout<<"�������� ����������� ������������ �� ������� "<<&Original<<" � ������ "<<this<<endl; //��� �����
	return *this;//���������� ������ �� ������ ��� �������� ��������� ��������
}
//���������� ��������� ������������� ������������ = 
DynArray& DynArray::operator=(DynArray&& rVal)
{
	//rVal = move(rVal);
	if (this != &rVal) //���� ��� �� ���� � ��� �� ������
	{
		delete[] array; //delete[] this->array; //���-��������� ������ ������ ���� array �������� �������
		array = rVal.array; //this->array = rVal.array; //�������� ����� ������ �� �������������� �������, ������������ �� rvalue ������ rVal � ������� this 
		size = rVal.size; //this->size = rVal.size; //�������� ����� ������ �� �������������� �������, ������������ �� rvalue ������ rVal � ������� this 
		//"��������" ������������� ������,  ����������� �� rvalue ������ rVal
		rVal.array = nullptr;
		rVal.size = 0;
	}
	//cout << "�������� ������������� ������������ �� ������� " << &rVal << " � ������ " << this << endl; //��� �����
	return *this;//���������� ������ �� ������ ��� �������� ��������� ��������
}
//���������� ��������� �������� �� ��������� ==
bool DynArray::operator==(const DynArray& A) const //*this==A
{
	if (this->size != A.size) //���� ������� �� �����
		return false;
	for (int i = 0; i < size; ++i)
	{
		//��� ������ ������� �������� ��������
		if (array[i] != A.array[i]) //if(this->array[i]!=A.array[i])
			return false;
	}
	return true; //������� �����
}
//���������� ��������� �������� �� ��������� !=
bool DynArray::operator!=(const DynArray& A) const
{
	return !(*this == A); //�������� ��������� �������������� ��������� �������� �� ��������� ==
	//�������� ������� - �������������� ��������� *this � ������������� � ��� ������� �
}
//���������� ���������� ������ � ������������ �������
void* DynArray::operator new(size_t Size)
{
	//this; //��������� new � delete - �����������
	void* Pointer = malloc(Size); //������� ��������� ������
	//int* A = (int*)malloc(sizeof(int)); //��������� ������ ��� ���� ���������� � ����� �	

	if (!Pointer)
	{
		cout << "������ ��������� ������!" << endl;
		//exit(3);
		//�������� ����������
	}
	//else cout << "\n������ ������� ��������!" << endl; //��� �����
	return Pointer;
	//return malloc(Size);
}
void DynArray::operator delete(void* Pointer)
{
	if (Pointer)
	{
		//Pointer = realloc(Pointer, sizeof(int));
		//������� ������������ ������ ������ � ��������� ����� ������ ������� �������
		free(Pointer); //������� ������������ ������ �� ����� �
		//cout << "������ ���� ������� �����������!" << endl; //��� �����
	}
	//else cout<<"������ ��� ���� �����������!"<<endl; //��� �����
}
void* DynArray::operator new[](size_t Size)
{
	//this; //��������� new � delete - �����������
	void* Pointer = malloc(Size); //������� ��������� ������
	//int* Array = (int*)malloc(Size*sizeof(int)); //��������� ������ ��� ������ ���������� � ����� �	

	if (!Pointer)
	{
		cout << "������ ��������� ������!" << endl;
		//exit(3);
		//�������� ����������
	}
	//else cout << "\n������ ������� ��������!" << endl; //��� �����
	return Pointer;
	//return malloc(Size);
}
void DynArray::operator delete[](void* Pointer)
{
	if (Pointer)
	{
		//Pointer = realloc(Pointer, NewSize * sizeof(int));
		//������� ������������ ������ ������ � ��������� ����� ������ ������� ������� ��� ������
		free(Pointer); //������� ������������ ������ �� ����� �
		//cout << "������ ���� ������� �����������!" << endl; //��� �����
	}
	//else cout << "������ ��� ���� �����������!" << endl; //��� �����
}

//���������� ��������� �������� ��� �������� DynArray+int
DynArray DynArray::operator+(int Digit)
{
	DynArray Result(size);//��������� ����� ��� �������� ����������

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] + Digit;
	}
	return Result;//���������� ��������� �����
}
//���������� ��������� ��������� ��� �������� DynArray-int
DynArray DynArray::operator-(int Digit)
{
	DynArray Result(size);//��������� ����� ��� �������� ����������

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] - Digit;
	}
	return Result;//���������� ��������� �����
}
//���������� ��������� ��������� ��� �������� DynArray*int
DynArray DynArray::operator*(int Digit)
{
	DynArray Result(size);//��������� ����� ��� �������� ����������

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] * Digit;
	}
	return Result;//���������� ��������� �����
}
//���������� ��������� ������� ��� �������� DynArray/int
DynArray DynArray::operator/(int Digit)
{
	DynArray Result(size);//��������� ����� ��� �������� ����������

	for (int i = 0; i < size; ++i)
	{
		Result.array[i] = array[i] / Digit;
	}
	return Result;//���������� ��������� �����
}


//������������� ���������� ��������� �������� ��� �������� int + DynArray
DynArray operator+(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //��������� ����� ��� �������� ����������
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit + Massiv.array[i];
	}
	return Temp;//���������� ��������� �����
}
//������������� ���������� ��������� ��������� ��� �������� int - DynArray
DynArray operator-(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //��������� ����� ��� �������� ����������
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit - Massiv.array[i];
	}
	return Temp;//���������� ��������� �����
}
//������������� ���������� ��������� ��������� ��� �������� int * DynArray
DynArray operator*(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //��������� ����� ��� �������� ����������
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit * Massiv.array[i];
	}
	return Temp;//���������� ��������� �����
}
//������������� ���������� ��������� ������� ��� �������� int / DynArray
DynArray operator/(int Digit, const DynArray& Massiv)
{
	DynArray Temp(Massiv.size); //��������� ����� ��� �������� ����������
	for (int i = 0; i < Massiv.size; ++i)
	{
		Temp[i] = Digit / Massiv.array[i];
	}
	return Temp;//���������� ��������� �����
}

//������������� ���������� ����������:
//���������� ��������� ������
ostream& operator<<(ostream& Out, const DynArray& A)
{
	//��� ������������� ����������							//��� ���������� ����������
	//������ ��������� � ���� size ������� �				//����� ������ Size()
	for (int i = 0; i < A.size; ++i)						//for(int i = 0; i < A.Size(); ++i)
	{														//{
		//������ ��������� � ���� array ������� �			//  //����� �������������� �������� �������������� ��� ������� �
		Out << A.array[i] << " ";								//Out << A[i] << " ";
	}														//}
	//Out << endl;											//Out << endl;
	return Out;												//return Out;
}
//���������� ��������� �����
istream& operator>>(istream& In, DynArray& A)
{
	//��� ������������� ����������							//��� ���������� ����������
	//������ ��������� � ���� size ������� �				//����� ������ Size() ��� ������� �
	for (int i = 0; i < A.size; ++i)						//for(int i = 0; i < A.Size(); ++i)
	{														//{
		cout << "������� " << i << "-� �������: ";			//	cout << "������� " << i << "-� �������: ";
		//������ ��������� � ���� array ������� �			//  //����� �������������� �������� �������������� ��� ������� �
		In >> A.array[i];									//	In >> A[i];
	}														//}
	return In;												//return In;
}

//���������� ���������� ��������� �������� + (�������� �������� �����������)
DynArray operator+(const DynArray& A, const DynArray& B) //A+B
{
	DynArray Temp; //��������� ������ ������
	if (B.Size() > A.Size())
	{
		//�������� � Temp ������ � �������� �������
		Temp = B; //������������� �������� ����������� ������������
		for (int i = 0; i < A.Size(); ++i)
		{
			Temp[i] += A[i]; //���������� �������� �� �������� ������� �,
			//��������� ������������� ��������� �������������� []
		}
	}
	else
	{
		//�������� � Temp ������ A �������� �������
		Temp = A; //������������� �������� ����������� ������������
		for (int i = 0; i < B.Size(); ++i)
		{
			Temp[i] += B[i]; //���������� �������� �� �������� ������� B,
			//��������� ������������� ��������� �������������� []
		}
	}
	return Temp; //���������� �������� ���������� �������
}