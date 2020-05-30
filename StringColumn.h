#include"DoubleColumn.h"

#pragma warning(disable : 4996)

class StringColumn : public Column 
{
public:
	virtual int getType();
	virtual void addValue(const char* str);
	virtual void printValue(int row);
	virtual void printName();
	virtual void saveToFile(ofstream& oFile);
	virtual void addEmptyRows(int rowsNum);
	virtual const char* getName() const;
	virtual void deleteRow(int row);
	virtual bool hasValueAt(int row, const char* value);
	virtual void updateValue(int row, const char* value);
	virtual void getValueAt(int row, char* str);
	StringColumn(const StringColumn& other);
	StringColumn& operator=(const StringColumn& other);
	StringColumn();
	~StringColumn();
	StringColumn(const char* columnName, int rows);
	StringColumn(ifstream& iFile);
private:
	char** column;
	int current;
	int capacity;
	char* name;
	void resize();
	void Free();
	void FreeName();
	void CopyFrom(const StringColumn& other);
};