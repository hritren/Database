#include"DoubleColumn.h"

#pragma warning(disable : 4996)

void DoubleColumn::Free()
{
	for (int i = 0; i < current; i++)
	{
		delete column[i];
	}
	delete[] column;
}
void DoubleColumn::FreeName()
{
	delete[] name;
}
void DoubleColumn::CopyFrom(const DoubleColumn& other)
{
	current = other.current;
	capacity = other.capacity;
	column = new double* [capacity];
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	for (int i = 0; i < current; i++)
	{
		if (other.column[i] == nullptr)
			column[i] = nullptr;
		else
		{
			column[i] = new double;
			*column[i] = *other.column[i];
		}
	}
}
DoubleColumn::DoubleColumn(const DoubleColumn& other)
{
	CopyFrom(other);
}
DoubleColumn& DoubleColumn::operator=(const DoubleColumn& other)
{
	if (this != &other)
	{
		Free();
		FreeName();
		CopyFrom(other);
	}
	return *this;
}
void DoubleColumn::addValue(const char* str)
{
	if (current == capacity)
		resize();
	if (!strcmp(str, "NULL"))
		column[current] = nullptr;
	else
	{
		column[current] = new double;
		*column[current] = atof(str);
	}
	current++;
}
void DoubleColumn::printValue(int row)
{
	cout << setw(25);
	if (column[row] == nullptr)
		cout << "NULL ";
	else
		cout << *column[row] << " ";
}
int DoubleColumn::getType()
{
	return 1;
}
DoubleColumn::DoubleColumn()
{
	capacity = 4;
	column = new double* [capacity];
	current = 0;
	name = nullptr;
	
}
DoubleColumn::~DoubleColumn()
{
	Free();
	FreeName();
}
void DoubleColumn::saveToFile(ofstream& oFile)
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
			oFile.write((char*)column[i], sizeof(double));
		}
	}
}
void DoubleColumn::addEmptyRows(int rowsNum)
{

}
void DoubleColumn::resize()
{
	capacity *= 2;
	double** helper = new double* [capacity];
	for (int i = 0; i < current; i++)
	{
		if (column[i] == nullptr)
			helper[i] = nullptr;
		else
		{
			helper[i] = new double;
			*helper[i] = *column[i];
		}
	}
	Free();
	column = helper;
}
DoubleColumn::DoubleColumn(const char* columnName, int rows)
{
	if (rows)
		capacity = 2 * rows;
	else
		capacity = 4;
	current = rows;
	int nameLen = strlen(columnName) + 1;
	name = new char[nameLen + 1];
	strcpy(name, columnName);
	column = new double* [capacity];
	for (int i = 0; i < current; i++)
	{
		column[i] = nullptr;
	}
}
DoubleColumn::DoubleColumn(ifstream& iFile)
{
	int nameLen;
	iFile.read((char*)&nameLen, sizeof(int));
	name = new char[nameLen];
	iFile.read(name, sizeof(char) * nameLen);
	iFile.read((char*)&capacity, sizeof(int));
	iFile.read((char*)&current, sizeof(int));
	column = new double* [capacity];
	for (int i = 0; i < current; i++)
	{
		bool isNULL;
		iFile.read((char*)&isNULL, sizeof(bool));
		if (isNULL)
			column[i] = nullptr;
		else
		{
			column[i] = new double;
			iFile.read((char*)column[i], sizeof(double));
		}
	}
}
void DoubleColumn::printName()
{
	cout << setw(25);
	cout << name << " ";
}
const char* DoubleColumn::getName() const
{
	return name;

}
void DoubleColumn::deleteRow(int row)
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
				column[i] = new double;
				*column[i] = *column[i + 1];
			}
		}
	}
	current--;
}
bool DoubleColumn::hasValueAt(int row, const char* value)
{
	if(column[row] != nullptr)
		return (*column[row] == atof(value));
	return false;
}
void DoubleColumn::updateValue(int row, const char* value)
{
	delete column[row];
	if (!strcmp(value, "NULL"))
		column[row] = nullptr;
	else
	{
		column[row] = new double;
		*column[row] = atof(value);
	}
}
void DoubleColumn::getValueAt(int row, char* str)
{
	if (column[row] == nullptr)
		strcpy(str, "NULL");
	else
	{
		double num = *column[row];
		int intNum = num;
		int digitsNum = DigitsNum(intNum);
		char result[25];
		int index = 0;
		if (num < 0)
			result[index++] = '-';
		while (digitsNum)
		{
			int digit = intNum / Power(10, digitsNum - 1) % 10;
			result[index++] = digit + '0';
			digitsNum--;
		}
		num = num - double(intNum);
		if (num > 0)
		{
			num *= 100;
			intNum = num;
			digitsNum = 2;
			result[index++] = '.';
			while (digitsNum)
			{
				int digit = intNum / Power(10, digitsNum - 1) % 10;
				result[index++] = digit + '0';
				digitsNum--;
			}
		}
		result[index] = '\0';
		strcpy(str, result);
	}
}