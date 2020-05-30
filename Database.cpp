#include"Database.h"

void Database::Free()
{
	delete[] tables;
	delete[] name;
	current = 0;
}
void Database::CopyFrom(const Database& other)
{
	capacity = other.capacity;
	current = other.current;
	tables = new Table[capacity];
	idForNames = other.idForNames;
	for (int i = 0; i < current; i++)
	{
		tables[i] = other.tables[i];
	}
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}
Database::Database()
{
	capacity = 4;
	current = 0;
	tables = new Table[4];
	idForNames = 0;
	name = new char[8];
	strcpy(name, "No name");
}
Database::~Database()
{
	Free();
}
Database::Database(const Database& other)
{
	CopyFrom(other);
}
Database& Database::operator=(const Database& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
void Database::exportTable(const char* name, const char* filename) 
{
	for (int i = 0; i < current; i++)
	{
		if(!strcmp(name, tables[i].getName()))
			tables[i].saveToFile(filename);
	}
}
void Database::showtables() const
{
	for (int i = 0; i < current; i++)
		cout << tables[i].getName() << endl;
}
void Database::describe(const char* name) const
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(name, tables[i].getName()))
		{
			tables[i].describe();
			break;
		}
	}
}
void Database::importTable(const char* filename)
{
	if (current == capacity)
		resize();

	ifstream iFile(filename, ios::binary);
	int nameLen;
	iFile.read((char*)&nameLen, sizeof(int));
	char* name = new char[nameLen + 1];
	iFile.read(name, sizeof(char) * nameLen);

	for (int i = 0; i < current; i++)
	{
		if (!strcmp(name, tables[i].getName()))
		{
			cout << "A table with the same name already exists!" << endl;
			break;
		}
	}
	iFile.close(); 
	tables[current++].readFromFile(filename);
}
void Database::addColumn(const char* tableName, const char* columnName, int type)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tableName, tables[i].getName()))
		{
			tables[i].addColumn(columnName, type);
			break;
		}
	}
}
void Database::resize()
{
	capacity *= 2;
	Table* helper = new Table[capacity];
	for (int i = 0; i < current; i++)
	{
		helper[i] = tables[i];
	}
	Free();
	tables = helper;
}
void Database::print(const char* tableName)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tables[i].getName(), tableName))
		{
			tables[i].print();
			break;
		}
	}
}
void Database::insertRow(const char* tableName)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tables[i].getName(), tableName))
		{
			tables[i].addRow();
			break;
		}
	}
}
void Database::createTable(const char* tableName)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tables[i].getName(), tableName))
		{
			cout << "A table with this name already exists. The table was not created!" << endl;
			return;
		}
			
	}
	if (current == capacity)
		resize();
	tables[current] = Table(tableName);
	current++;
}
void Database::select(const char* tableName, int col, const char* value)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tableName, tables[i].getName()))
		{
			tables[i].select(col, value);
			break;
		}
	}
}
void Database::update(const char* tableName, int colN, const char* searchValue, int targetColN, const char* targetValue)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tables[i].getName(), tableName))
		{
			tables[i].update(colN, searchValue, targetColN, targetValue);
			break;
		}
	}
}
void Database::innerJoin(const Table& table1, int col1, const Table& table2, int col2)
{
	Table tmp = table1;
	tmp.innerjoin(col1, table2, col2);
	char str[30];
	int id = idForNames++, index = 0;
	do
	{
		str[index++] = id % 10 + '0';
		id /= 10;
	} while (id);
	str[index] = '\0';
	strcat(str, "table");
	tmp.setName(str);
	if (current == capacity)
		resize();
	tables[current] = tmp;
	current++;
	cout << "Name: " << tmp.getName() << endl;
}
void Database::rename(const char* oldName, const char* newName)
{
	bool flag = false;
	for (int i = 0; i < current; i++)
		if (!strcmp(tables[i].getName(), newName))
			flag = true;
	if(!flag)
		for (int i = 0; i < current; i++)
			if (!strcmp(tables[i].getName(), oldName))
			{
				tables[i].setName(newName);
				break;
			}
}
int Database::count(const char* tableName, int col, const char* searchValue)
{
	int br = 0;
	for (int i = 0; i < current; i++)
	{
		br = tables[i].count(col, searchValue);
	}
	return br;
}
void Database::save(const char* filename)
{
	for (int i = 0; i < current; i++)
	{
		char* tableName = new char[strlen(tables[i].getName()) + strlen(name) + 5];
		strcpy(tableName, tables[i].getName());
		strcat(tableName, name);
		strcat(tableName, ".txt");
		tables[i].saveToFile(tableName);
		delete[] tableName;
	}
	ofstream oFile(filename, ios::binary);
	oFile.write((char*)&current, sizeof(int));
	oFile.write((char*)&idForNames, sizeof(int));
	for (int i = 0; i < current; i++)
	{
		char* tableName = new char[strlen(tables[i].getName()) + strlen(name) + 5];
		strcpy(tableName, tables[i].getName());
		int len = strlen(tableName) + 1;
		oFile.write((char*)&len, sizeof(int));
		oFile.write(tableName, sizeof(char) * len);
		strcat(tableName, name);
		strcat(tableName, ".txt");
		len = strlen(tableName) + 1;
		oFile.write((char*)&len, sizeof(int));
		oFile.write(tableName, sizeof(char) * len);
		delete[] tableName;
	}
	oFile.close();
}
void Database::aggregate(const char* tableName, int searchCol, const char* searchValue, int targetCol, const char* operation)
{
	for (int i = 0; i < current; i++)
		if (!strcmp(tables[i].getName(), tableName))
		{
			tables[i].aggregate(searchCol, searchValue, targetCol, operation);
			break;
		}
}
Database::Database(const char* DBname)
{
	capacity = 4;
	current = 0;
	tables = new Table[4];
	idForNames = 0;
	name = new char[strlen(DBname) + 1];
	strcpy(name, DBname);
}
void Database::setName(const char* DBname)
{
	delete[] name;
	name = new char[strlen(DBname) + 1];
	strcpy(name, DBname);
}
void Database::readFromFile(const char* filename)
{
	int curr = 0;
	ifstream iFile(filename, ios::binary);
	iFile.read((char*)&curr, sizeof(int));
	if (curr == 0)
	{
		*this = Database();
		iFile.close();
		return;
	}
	Free();
	name = new char[8];
	strcpy(name, "No name");
	current = curr;
	iFile.read((char*)&idForNames, sizeof(int));
	capacity = 2 * current;
	tables = new Table[capacity];
	for (int i = 0; i < current; i++)
	{
		int len;
		iFile.read((char*)&len, sizeof(int));
		char* tableName = new char[len];
		iFile.read(tableName, sizeof(char) * len);
		iFile.read((char*)&len, sizeof(int));
		char* tableFilename = new char[len];
		iFile.read(tableFilename, sizeof(char) * len);
		tables[i].readFromFile(tableFilename);
		delete[] tableName;
		delete[] tableFilename;
	}
	iFile.close();
}
void Database::innerjoin(const char* table1Name, int col1, const char* table2Name, int col2)
{
	Table t1, t2;
	bool flag1 = false, flag2 = false;
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tables[i].getName(), table1Name))
		{
			t1 = tables[i];
			flag1 = true;
		}
		if (!strcmp(tables[i].getName(), table2Name))
		{
			t2 = tables[i];
			flag2 = true;
		}
	}
	if (flag1 && flag2)
		innerJoin(t1, col1, t2, col2);
}
void Database::deleteRows(const char* tableName, int col, const char* value)
{
	for (int i = 0; i < current; i++)
	{
		if (!strcmp(tableName, tables[i].getName()))
		{
			tables[i].deleteRows(col, value);
			break;
		}
	}
}