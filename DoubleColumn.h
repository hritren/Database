#include"IntColumn.h"

class DoubleColumn : public Column
{
public:
	virtual int getType();
	virtual void addValue(const char* str);
	virtual void printValue(int row);
	virtual void printName();
	virtual const char* getName() const;
	virtual void saveToFile(ofstream& oFile);
	virtual void addEmptyRows(int rowsNum);
	virtual void deleteRow(int row);
	virtual bool hasValueAt(int row, const char* value);
	virtual void updateValue(int row, const char* value);
	virtual void getValueAt(int row, char* str);
	DoubleColumn(const DoubleColumn& other);
	DoubleColumn& operator=(const DoubleColumn& other);
	DoubleColumn();
	~DoubleColumn();
	DoubleColumn(const char* columnName, int rows);
	DoubleColumn(ifstream& iFile);
private:
	double** column;
	int capacity;
	int current;
	char* name;
	void resize();
	void Free();
	void FreeName();
	void CopyFrom(const DoubleColumn& other);
};
