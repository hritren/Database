#include"Column.h"

class IntColumn : public Column 
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
	IntColumn(const IntColumn& other);
	IntColumn& operator=(const IntColumn& other);
	IntColumn();
	IntColumn(ifstream& iFile);
	IntColumn(const char* columnName, int rows);
	~IntColumn();
private:
	int** column;
	int capacity;
	int current;
	char* name;
	void Free();
	void FreeName();
	void CopyFrom(const IntColumn& other);
	void resize();
};
int DigitsNum(int num);
int Power(int num, int pow);
