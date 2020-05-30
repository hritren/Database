#include"Table.h"

class Database
{
public:
	Database();
	Database(const char* name);
	~Database();
	Database(const Database& other);
	Database& operator=(const Database& other);
	void exportTable(const char* name, const char* filename = "");
	void importTable(const char* filename);
	void showtables() const;
	void describe(const char* name) const;
	void createTable(const char* tableName);
	void addColumn(const char* tableName, const char* columnName, int type);
	void print(const char* tableName);
	void insertRow(const char* tableName);
	void select(const char* tableName, int col, const char* value);
	void update(const char* tableName, int colN, const char* searchValue, int targetColN, const char* targetValue);
	void rename(const char* oldName, const char* newName);
	void innerjoin(const char* table1Name, int col1, const char* table2Name, int col2);
	int count(const char* tableName, int col, const char* searchValue);
	void aggregate(const char* tableName, int searchCol, const char* searchValue, int targetCol, const char* operation);
	void save(const char* filename = "");
	void setName(const char* DBname);
	void readFromFile(const char* filename);
	void deleteRows(const char* tableName, int col, const char* value);
private:
	Table* tables;
	int current;
	int capacity;
	int idForNames;
	char* name;
	void resize();
	void Free();
	void CopyFrom(const Database& other);
	void innerJoin(const Table& table1, int col1, const Table& table2, int col2);
};
