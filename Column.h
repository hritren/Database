#include<iostream>
#include<fstream>
#include<cstring>
#include <iomanip>
using namespace std;

//0-int 1-double 2-string

class Column
{
public:
	virtual int getType() = 0;
	virtual void getValueAt(int row, char* str) = 0;
	virtual void printValue(int row) = 0;
	virtual void updateValue(int row, const char* value) = 0;
	virtual void printName() = 0;
	virtual const char* getName() const = 0;
	virtual ~Column() {}
	virtual void addValue(const char* str) = 0;
	virtual void saveToFile(ofstream& oFile) = 0;
	virtual void deleteRow(int row) = 0;
	virtual bool hasValueAt(int row, const char* value) = 0;
};