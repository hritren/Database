#include"Table.h"

Table::Table()
{
	name = new char[8];
	strcpy(name, "No name");
	current = 0;
	capacity = 4;
	data = new Column* [capacity];
	rows = 0;
}
void Table::Free()
{
	for (int i = 0; i < current; i++)
	{
		delete data[i];
	}
	delete[] data;
	delete[] name;
}
void Table::CopyFrom(const Table& other)
{
	current = other.current;
	capacity = other.capacity;
	rows = other.rows;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	data = new Column* [capacity];
	for (int i = 0; i < current; i++)
	{
		if (other.data[i]->getType() == 0)
			data[i] = new IntColumn(*((IntColumn*)other.data[i]));
		if (other.data[i]->getType() == 1)
			data[i] = new DoubleColumn(*((DoubleColumn*)other.data[i]));
		if (other.data[i]->getType() == 2)
			data[i] = new StringColumn(*((StringColumn*)other.data[i]));
	}
}
Table::~Table()
{
	Free();
}
Table::Table(const Table& other)
{
	CopyFrom(other);
}
Table& Table::operator=(const Table& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
void Table::saveToFile(const char* fileName)
{
	ofstream oFile(fileName, ios::binary);
	int nameLen = strlen(name) + 1;
	oFile.write((char*)&nameLen, sizeof(int));
	oFile.write(name, sizeof(char) * nameLen);
	oFile.write((char*)&current, sizeof(int));
	oFile.write((char*)&capacity, sizeof(int));
	oFile.write((char*)&rows, sizeof(int));
	for (int i = 0; i < current; i++)
	{
		data[i]->saveToFile(oFile);
	}
	oFile.close();
}
const char* Table::getName() const
{
	return name;
}
void Table::describe() const
{
	for (int i = 0; i < current; i++)
	{
		if (data[i]->getType() == 0)
			cout << "Integer ";
		if (data[i]->getType() == 1)
			cout << "Real ";
		if (data[i]->getType() == 2)
			cout << "String ";
	}
	cout << endl;
}
void Table::addColumn(const char* columnName, int type)
{
	if (current == capacity)
		resize();
	if (type == 0)
		data[current] = new IntColumn(columnName, rows);
	if (type == 1)
		data[current] = new DoubleColumn(columnName, rows);
	if (type == 2)
		data[current] = new StringColumn(columnName, rows);
	current++;
}
void Table::readFromFile(const char* filename)
{
	Free();
	ifstream iFile(filename, ios::binary);
	int nameLen;
	iFile.read((char*)&nameLen, sizeof(int));
	name = new char[nameLen];
	iFile.read(name, sizeof(char) * nameLen);
	iFile.read((char*)&current, sizeof(int));
	iFile.read((char*)&capacity, sizeof(int));
	iFile.read((char*)&rows, sizeof(int));
	data = new Column* [capacity];
	for (int i = 0; i < current; i++)
	{
		int type;
		iFile.read((char*)&type, sizeof(int));
		if (type == 0)
			data[i] = new IntColumn(iFile);
		if (type == 1)
			data[i] = new DoubleColumn(iFile);
		if (type == 2)
			data[i] = new StringColumn(iFile);
	}
	iFile.close();
}
void Table::resize()
{
	capacity *= 2;
	Column** helper = new Column* [capacity];
	for (int i = 0; i < current; i++)
	{
		helper[i] = data[i];
	}
	delete[] data;
	data = helper;
}
void Table::print()
{
	int page = 0;
	bool isOpened = true;
	while (isOpened)
	{
		system("cls");
		for (int i = 0; i < 10; i++)
		{
			if (i + page * 10 >= rows)
				break;
			if (i == 0)
			{
				for (int j = 0; j < current; j++)
				{
					data[j]->printName();
				}
				cout << endl;
			}
			for (int j = 0; j < current; j++)
			{
				data[j]->printValue(i + page * 10);
			}
			cout << endl;
		}
		cout << "Next/Previous/Close" << endl;
		char str[10];
		cin.getline(str, 10);
		if (!strcmp(str, "Close"))
			isOpened = false;
		if (!strcmp(str, "Next"))
		{
			if (page < rows / 10)
				page++;
		}
		if (!strcmp(str, "Previous"))
		{
			if (page > 0)
				page--;
		}
	}
}
void Table::addRow()
{
	for (int i = 0; i < current; i++)
	{
		char str[30];
		cout << "Enter " << data[i]->getName() << endl;
		cin.getline(str, 30);
		data[i]->addValue(str);
	}
	rows++;
}
Table::Table(const char* tableName)
{
	capacity = 4;
	current = 0;
	rows = 0;
	data = new Column * [capacity];
	name = new char[strlen(tableName) + 1];
	strcpy(name, tableName);
}
void Table::select(int col, const char* value)
{
	Table tmp = *this;
	for (int i = rows - 1; i >= 0; i--)
	{
		if (!tmp.data[col]->hasValueAt(i, value))
			tmp.deleteRow(i);
	}
	tmp.print();
}
void Table::deleteRow(int row)
{
	for (int i = 0; i < current; i++)
	{
		data[i]->deleteRow(row);
	}
	rows--;
}
void Table::update(int colN, const char* searchValue, int targetColN, const char* targetValue)
{
	for (int i = 0; i < rows; i++)
	{
		if (data[colN]->hasValueAt(i, searchValue))
			data[targetColN]->updateValue(i, targetValue);
	}
}
void Table::innerjoin(int col1, const Table& table2, int col2)
{
	int oldcurrent = current;
	for (int i = 0; i < table2.current; i++)
	{
		if (i != col2)
		{
			addColumn(table2.data[i]->getName(), table2.data[i]->getType());
		}
	}
	for (int i = 0; i < table2.rows; i++)
	{
		char value2[30];
		table2.data[col2]->getValueAt(i, value2);
		for (int j = 0; j < rows; j++)
		{
			char value1[30];
			data[col1]->getValueAt(j, value1);
			if (!strcmp(value1, value2))
			{
				for (int k = oldcurrent; k < current; k++)
				{
					for (int l = 0; l < table2.current; l++)
					{
						if (!strcmp(data[k]->getName(), table2.data[l]->getName()))
						{
							char str[30];
							table2.data[l]->getValueAt(i, str);
							data[k]->updateValue(j, str);
							break;
						}	
					}
				}
			}
		}
	}
	for (int i = rows - 1; i >= 0; i--)
	{
		bool flag = false;
		for (int j = 0; j < table2.rows; j++)
		{
			char str[30];
			table2.data[col2]->getValueAt(j, str);
			if (data[col1]->hasValueAt(i, str))
			{
				flag = true;
				break;
			}
		}
		if (!flag)
			deleteRow(i);
	}
}
void Table::setName(const char* tableName)
{
	delete[] name;
	name = new char[strlen(tableName) + 1];
	strcpy(name, tableName);
}
int Table::count(int col, const char* searchValue)
{
	int br = 0;
	for (int i = 0; i < rows; i++)
	{
		if (data[col]->hasValueAt(i, searchValue))
			br++;
	}
	return br;
}
void Table::aggregate(int searchCol, const char* searchValue, int targetCol, const char* operation)
{
	if (data[searchCol]->getType() == 2 || data[targetCol]->getType() == 2)
	{
		cout << "Not numerical column" << endl;
		return;
	}
	bool flag = false;
	if (!strcmp(operation, "sum"))
	{
		double sum = 0;
		for (int i = 0; i < rows; i++)
		{
			if (data[searchCol]->hasValueAt(i, searchValue))
			{
				char str[30];
				data[targetCol]->getValueAt(i, str);
				double num = 0;
				if (data[targetCol]->getType() == 0)
					num = atoi(str);
				else
					num = atof(str);
				sum += num;
				flag = true;
			}
		}
		if (flag)
			cout << "The sum is: " << sum << endl;
		else
			cout << "There is no such value in the column" << endl;
	}
	if (!strcmp(operation, "product"))
	{
		double product = 1;
		for (int i = 0; i < rows; i++)
		{
			if (data[searchCol]->hasValueAt(i, searchValue))
			{
				char str[30];
				data[targetCol]->getValueAt(i, str);
				double num = 0;
				if (data[targetCol]->getType() == 0)
					num = atoi(str);
				else
					num = atof(str);
				product *= num;
				flag = true;
			}
		}
		if(flag)
			cout << "The product is: " << product << endl;
		else
			cout << "There is no such value in the column" << endl;
	}
	if (!strcmp(operation, "minimum"))
	{
		double minn = INT_MAX;
		for (int i = 0; i < rows; i++)
		{
			if (data[searchCol]->hasValueAt(i, searchValue))
			{
				char str[30];
				data[targetCol]->getValueAt(i, str);
				double num = 0;
				if (data[targetCol]->getType() == 0)
					num = atoi(str);
				else
					num = atof(str);
				if (minn > num)
					minn = num;
				flag = true;
			}
		}
		if(flag)
			cout << "The minimum is: " << minn << endl;
		else
			cout << "There is no such value in the column" << endl;
	}
	if (!strcmp(operation, "maximum"))
	{
		double maxx = -INT_MAX;
		for (int i = 0; i < rows; i++)
		{
			if (data[searchCol]->hasValueAt(i, searchValue))
			{
				char str[30];
				data[targetCol]->getValueAt(i, str);
				double num = 0;
				if (data[targetCol]->getType() == 0)
					num = atoi(str);
				else
					num = atof(str);
				if (maxx < num)
					maxx = num;
				flag = true;
			}
		}
		if(flag)
			cout << "The maximum is: " << maxx << endl;
		else
			cout << "There is no such value in the column" << endl;
	}
}
void Table::deleteRows(int col, const char* value)
{
	for (int i = rows - 1; i >= 0; i--)
	{
		if (data[col]->hasValueAt(i, value))
			deleteRow(i);
	}
}