#include"App.h"

void App::Free()
{
	delete DB;
}
void App::CopyFrom(const App& other)
{
	DB = new Database(*other.DB);
}
App::App()
{
	DB = new Database;
	help();
}
App::~App()
{
	Free();
}
void App::open(const char* filename)
{
	DB->readFromFile(filename);
	cout << "Enter the name of the Database" << endl;
	char name[30];
	cin.getline(name, 30);
	DB->setName(name);
	menu(filename);
}
void App::help()
{
	system("cls");
	cout << "To choose an option enter the number of the option!" << endl;
	cout << "1. Close help" << endl;
	int operation;
	cin >> operation;
	if (operation != 1)
		help();
}
void App::menu(const char* filename)
{
	system("cls");
	cout << "1. Close file" << endl;
	cout << "2. Save" << endl;
	cout << "3. Save As" << endl;
	cout << "4. Help" << endl;
	cout << "5. Operations" << endl;
	cout << "6. Exit" << endl;
	int operation;
	cin >> operation;
	if (operation == 1)
	{
		start();
	}
	if (operation == 2)
	{
		save(filename);
		menu(filename);
	}
	if (operation == 3)
	{
		system("cls");
		cin.ignore();
		char newFilename[30];
		cout << "Enter the name of the file:" << endl;
		cin.getline(newFilename, 30);
		save(newFilename);
		menu(filename);
	}
	if (operation == 4)
	{
		help();
		menu(filename);
	}
	if (operation == 5)
	{
		operations(filename);
	}
}
void App::save(const char* filename)
{
	DB->save(filename);
}
void App::start()
{
	system("cls");
	cout << "1. Open" << endl;
	cout << "2. Exit" << endl;
	int operation;
	cin >> operation;
	if(operation == 1)
	{
		cin.ignore();
		system("cls");
		cout << "Enter the name of the file:" << endl;
		char filename[30];
		cin.getline(filename, 30);
		open(filename);
	}
}
void App::operations(const char* filename)
{
	system("cls");
	cout << "1. Close operations" << endl;
	cout << "2. Import" << endl;
	cout << "3. Showtables" << endl;
	cout << "4. Describe" << endl;
	cout << "5. Print" << endl;
	cout << "6. Create table" << endl;
	cout << "7. Export" << endl;
	cout << "8. Select" << endl;
	cout << "9. Addcolumn" << endl;
	cout << "10. Update" << endl;
	cout << "11. Delete" << endl;
	cout << "12. Insert" << endl;
	cout << "13. Innerjoin" << endl;
	cout << "14. Rename" << endl;
	cout << "15. Count" << endl;
	cout << "16. Aggregate" << endl;
	cout << "17. Exit" << endl;
	int operation;
	cin >> operation;
	if (operation == 1)
	{
		menu(filename);
	}
	if (operation == 2)
	{
		cin.ignore();
		system("cls");
		char importFilename[30];
		cout << "Enter the name of the file" << endl;
		cin.getline(importFilename, 30);
		DB->importTable(importFilename);
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 3)
	{
		system("cls");
		DB->showtables();
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 4)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		DB->describe(tableName);
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 5)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		DB->print(tableName);
		system("cls");
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 6)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		DB->createTable(tableName);
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 7)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char tableFilename[30];
		cout << "Enter the name of the file" << endl;
		cin.getline(tableFilename, 30);
		DB->exportTable(tableName, tableFilename);
		operations(filename);
	}
	if (operation == 8)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char value[30];
		cout << "Enter the value" << endl;
		cin.getline(value, 30);
		int col;
		cout << "Enter the index of the column" << endl;
		cin >> col;
		DB->select(tableName, col, value);
		system("cls");
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 9)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char columnName[30];
		cout << "Enter the name of the column" << endl;
		cin.getline(columnName, 30); 
		int type;
		cout << "Enter the type of the column(0-Integer, 1-Real, 2-String)" << endl;
		cin >> type;
		DB->addColumn(tableName, columnName, type);
		operations(filename);
	}
	if (operation == 10)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char searchValue[30];
		cout << "Enter the search value" << endl;
		cin.getline(searchValue, 30);
		char targetValue[30];
		cout << "Enter the target value" << endl;
		cin.getline(targetValue, 30);
		int sCol, tCol;
		cout << "Enter the index of the search column" << endl;
		cin >> sCol;
		cout << "Enter the index of the target column" << endl;
		cin >> tCol;
		DB->update(tableName, sCol, searchValue, tCol, targetValue);
		operations(filename);
	}
	if (operation == 11)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char value[30];
		cout << "Enter the value" << endl;
		cin.getline(value, 30);
		int col;
		cout << "Enter the index of the column" << endl;
		cin >> col;
		DB->deleteRows(tableName, col, value);
		operations(filename);
	}
	if (operation == 12)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		DB->insertRow(tableName);
		operations(filename);
	}
	if (operation == 13)
	{
		cin.ignore();
		system("cls");
		char table1Name[30];
		cout << "Enter the name of the table1" << endl;
		cin.getline(table1Name, 30);
		int col1, col2;
		cout << "Enter the index of the column1" << endl;
		cin >> col1;
		char table2Name[30];
		cout << "Enter the name of the table2" << endl;
		cin.getline(table2Name, 30);
		cout << "Enter the index of the column2" << endl;
		cin >> col2;
		DB->innerjoin(table1Name, col1, table2Name, col2);
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 14)
	{
		cin.ignore();
		system("cls");
		char oldName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(oldName, 30);
		char newName[30];
		cout << "Enter the new name of the table" << endl;
		cin.getline(newName, 30);
		DB->rename(oldName, newName);
		operations(filename);
	}
	if (operation == 15)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char value[30];
		cout << "Enter the value" << endl;
		cin.getline(value, 30);
		int col;
		cout << "Enter the index of the column" << endl;
		cin >> col;
		cout << DB->count(tableName, col, value);
		cout << "1. Operations" << endl;
		int op;
		cin >> op;
		operations(filename);
	}
	if (operation == 16)
	{
		cin.ignore();
		system("cls");
		char tableName[30];
		cout << "Enter the name of the table" << endl;
		cin.getline(tableName, 30);
		char searchValue[30];
		cout << "Enter the search value" << endl;
		cin.getline(searchValue, 30);
		char operation[30];
		cout << "Enter the operation" << endl;
		cin.getline(operation, 30);
		int sCol, tCol;
		cout << "Enter the index of the search column" << endl;
		cin >> sCol;
		cout << "Enter the index of the target column" << endl;
		cin >> tCol;
		DB->aggregate(tableName, sCol, searchValue, tCol, operation);
		operations(filename);
	}
}