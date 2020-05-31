#include"StringColumn.h"

#pragma warning(disable : 4996)

int StringColumn::getType()
{ 
	return 2; 
}
void StringColumn::addValue(const char* str)
{
	if (current == capacity)
		resize();
	if (!strcmp(str, "NULL"))
		column[current] = nullptr;
	else
	{
		column[current] = new char[strlen(str) + 1];
		strcpy(column[current], str);
	}
	current++;
}
void StringColumn::printValue(int row)
{
	cout << setw(25);
	if (column[row] == nullptr)
		cout << "NULL ";
	else
		cout << column[row] << " ";
}
void StringColumn::Free()
{
	for (int i = 0; i < current; i++)
	{
		delete[] column[i];
	}
	delete[] column;
}
void StringColumn::FreeName()
{
	delete[] name;
}
void StringColumn::CopyFrom(const StringColumn& other)
{
	capacity = other.capacity;
	current = other.current;
	column = new char* [capacity];
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	for (int i = 0; i < current; i++)
	{
		if (other.column[i] != nullptr)
		{
			column[i] = new char[strlen(other.column[i]) + 1];
			strcpy(column[i], other.column[i]);
		}
		else
			column[i] = nullptr;
	}
}
StringColumn::StringColumn() 
{
	capacity = 4;
	column = new char* [capacity];
	current = 0;
	name = nullptr;
}
StringColumn::~StringColumn()
{
	Free();
	FreeName();
}
StringColumn::StringColumn(const StringColumn& other)
{
	CopyFrom(other);
}
StringColumn& StringColumn::operator=(const StringColumn& other)
{
	if (this != &other)
	{
		Free();
		FreeName();
		CopyFrom(other);
	}
	return *this;
}
void StringColumn::saveToFile(ofstream& oFile)
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
			int len = strlen(column[i]) + 1;
			oFile.write((char*)&len, sizeof(int));
			oFile.write(column[i], sizeof(char) * len);
		}
	}
}
void StringColumn::resize()
{
	capacity *= 2;
	char** helper = new char* [capacity];
	for (int i = 0; i < current; i++)
	{
		if (column[i] == nullptr)
			helper[i] = nullptr;
		else
		{
			int len = strlen(column[i]);
			helper[i] = new char[len + 1];
			strcpy(helper[i], column[i]);
		}
	}
	Free();
	column = helper;
}
StringColumn::StringColumn(const char* columnName, int rows)
{
	if (rows)
		capacity = 2 * rows;
	else
		capacity = 4;
	current = rows;
	int nameLen = strlen(columnName) + 1;
	name = new char[nameLen + 1];
	strcpy(name, columnName);
	column = new char* [capacity];
	for (int i = 0; i < current; i++)
	{
		column[i] = nullptr;
	}
}
StringColumn::StringColumn(ifstream& iFile)
{
	int nameLen;
	iFile.read((char*)&nameLen, sizeof(int));
	name = new char[nameLen];
	iFile.read(name, sizeof(char) * nameLen);
	iFile.read((char*)&capacity, sizeof(int));
	iFile.read((char*)&current, sizeof(int));
	column = new char* [capacity];
	for (int i = 0; i < current; i++)
	{
		bool isNULL;
		iFile.read((char*)&isNULL, sizeof(bool));
		if (isNULL)
			column[i] = nullptr;
		else
		{
			int len;
			iFile.read((char*)&len, sizeof(int));
			column[i] = new char[len];
			iFile.read((char*)column[i], sizeof(char) * len);
		}
	}
}
void StringColumn::printName()
{
	cout << setw(25);
	cout << name << " ";
}
const char* StringColumn::getName() const
{
	return name;
}
void StringColumn::deleteRow(int row)
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
				column[i] = new char[strlen(column[i + 1]) + 1];
				strcpy(column[i], column[i + 1]);
			}
		}
	}
	current--;
}
bool StringColumn::hasValueAt(int row, const char* value)
{
	if(column[row] != nullptr)
		return (!strcmp(column[row], value));
	return false;
}
void StringColumn::updateValue(int row, const char* value)
{
	delete column[row];
	if (!strcmp(value, "NULL"))
		column[row] = nullptr;
	else
	{
		column[row] = new char[1 + strlen(value)];
		strcpy(column[row], value);
	}
}
void StringColumn::getValueAt(int row, char* str)
{
	if (column[row] == nullptr)
		strcpy(str, "NULL");
	else
		strcpy(str, column[row]);
}