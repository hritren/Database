#include"StringColumn.h"


class Table 
{
public:
	Table();
	~Table();
	Table(const Table& other);
	Table(const char* tableName);
	Table& operator=(const Table& other);
	void saveToFile(const char* fileName = "");
	void readFromFile(const char* fileName);
	const char* getName() const;
	void describe() const;
	void addColumn(const char* columnName, int type);
	void print();
	void addRow();
	void select(int col, const char* value);
	void deleteRow(int row);
	void update(int colN, const char* searchValue, int targetColN, const char* targetValue);
	void innerjoin(int col1, const Table& table2, int col2);
	void setName(const char* tableName);
	int count(int col, const char* searchValue);
	void aggregate(int searchCol, const char* searchValue, int targetCol, const char* operation);
	void deleteRows(int col, const char* value);
private:
	void Free();
	void CopyFrom(const Table& other);
	Column** data;
	int current;
	int capacity;
	int rows;
	char* name;
	void resize();
};