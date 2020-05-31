#include"IntColumn.h"

#pragma warning(disable : 4996)

void IntColumn::Free()
{
	for (int  i = 0; i < current; i++)
	{
		delete column[i];
	}
	delete[] column;
}
void IntColumn::FreeName()
{
	delete[] name;
}
void IntColumn::CopyFrom(const IntColumn& other)
{
	current = other.current;
	capacity = other.capacity;
	column = new int*[capacity];
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	for (int i = 0; i < current; i++)
	{	
		if (other.column[i] == nullptr)
			column[i] = nullptr;
		else
		{
			column[i] = new int;
			*column[i] = *other.column[i];
		}
	}
}
IntColumn::IntColumn(const IntColumn& other)
{
	CopyFrom(other);
}
IntColumn& IntColumn::operator=(const IntColumn& other)
{
	if (this != &other)
	{
		Free();
		FreeName();
		CopyFrom(other);
	}
	return *this;
}
void IntColumn::resize()
{
	capacity *= 2;
	int** helper = new int*[capacity];
	for (int i = 0; i < current; i++)
	{
		if (column[i] == nullptr)
			helper[i] = nullptr;
		else
		{
			helper[i] = new int;
			*helper[i] = *column[i];
		}
	}
	Free();
	column = helper;
}
void IntColumn::addValue(const char* str)
{
	if (current == capacity)
		resize();
	if (!strcmp(str, "NULL"))
		column[current] = nullptr;
	else
	{
		column[current] = new int;
		*column[current] = atoi(str);
	}
	current++;
}
void IntColumn::printValue(int row) 
{
	cout << setw(25);
	if (column[row] == nullptr)
		cout << "NULL ";
	else
		cout << *column[row] << " ";
}
int IntColumn::getType()
{
	return 0;
}
const char* IntColumn::getName() const
{
	return name;
}
IntColumn::IntColumn() 
{
	capacity = 4;
	column = new int*[capacity];
	current = 0;
	name = nullptr;
}
IntColumn::~IntColumn()
{
	Free();
	FreeName();
}
void IntColumn::saveToFile(ofstream& oFile)
{
	int type = getType();
	oFile.write((char*)&type, sizeof(int));
	int nameLen = strlen(name) + 1;
	oFile.write((char*)&nameLen, sizeof(int));
	oFile.write(name, sizeof(char) * nameLen);
	oFile.write((char*)&capacity, sizeof(int));
	oFile.write((char*)&current, sizeof(int));
	for (int i = 0; i < current; i++)
	{
		if (column[i] == nullptr)
		{
			bool isNULL = true;
			oFile.write((char*)&isNULL, sizeof(bool));
		}
		else
		{
			bool isNULL = false;
			oFile.write((char*)&isNULL, sizeof(bool));
			oFile.write((char*)column[i], sizeof(int));
		}
	}
}
IntColumn::IntColumn(const char* columnName, int rows)
{
	if (rows)
		capacity = 2 * rows;
	else
		capacity = 4;
	current = rows;
	int nameLen = strlen(columnName) + 1;
	name = new char[nameLen + 1];
	strcpy(name, columnName);
	column = new int* [capacity];
	for (int i = 0; i < current; i++)
	{
		column[i] = nullptr;
	}
}
IntColumn::IntColumn(ifstream& iFile)
{
	int nameLen;
	iFile.read((char*)&nameLen, sizeof(int));
	name = new char[nameLen];
	iFile.read(name, sizeof(char) * nameLen);
	iFile.read((char*)&capacity, sizeof(int));
	iFile.read((char*)&current, sizeof(int));
	column = new int* [capacity];
	for (int i = 0; i < current; i++)
	{
		bool isNULL;
		iFile.read((char*)&isNULL, sizeof(bool));
		if (isNULL)
			column[i] = nullptr;
		else
		{
			column[i] = new int;
			iFile.read((char*)column[i], sizeof(int));
		}
	}
}
void IntColumn::printName()
{
	cout << setw(25);
	cout << name << " ";
}
void IntColumn::deleteRow(int row)
{
	if (row >= current)
		return;
	for (int i = row; i < current; i++)
	{
		delete column[i];
		if (i != current - 1)
		{
			if (column[i + 1] == nullptr)
				column[i] = nullptr;
			else
			{
				column[i] = new int;
				*column[i] = *column[i + 1];
			}
		}	
	}
	current--;
}
bool IntColumn::hasValueAt(int row, const char* value)
{
	if(column[row] != nullptr)
		return (*column[row] == atoi(value));
	return false;
}
void IntColumn::updateValue(int row, const char* value)
{
	delete column[row];
	if (!strcmp(value, "NULL"))
		column[row] = nullptr;
	else
	{
		column[row] = new int;
		*column[row] = atoi(value);
	}
}
void IntColumn::getValueAt(int row, char* str)
{
	if (column[row] == nullptr)
		strcpy(str, "NULL");
	else
	{
		int num = *column[row];
		int digitsNum = DigitsNum(num);
		char result[25];
		int index = 0;
		if (num < 0)
			result[index++] = '-';
		while (digitsNum)
		{
			int digit = num / Power(10, digitsNum - 1) % 10;
			result[index++] = digit + '0';
			digitsNum--;
		}
		result[index] = '\0';
		strcpy(str, result);
	}
 }
int DigitsNum(int num)
{
	int br = 1;
	while (num)
	{
		num /= 10;
		br++;
	}
	if (br > 1)
		br--;
	return br;
}
int Power(int num, int pow)
{
	int result = 1;
	for (int i = 0; i < pow; i++)
	{
		result *= num;
	}
	return result;
}