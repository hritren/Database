#include<iostream>
#include<fstream>
#include<cstring>
#include <iomanip>
using namespace std;

//0-int 1-double 2-string

///This is the class Column. It is an abstract class which has only pure vurtual functions
class Column
{
public:
	///Pure virtual finction. Returns 0/1/2 depending on the type column
	virtual int getType() = 0;
	///Pure virtual finction. Gets the row value of the column
	virtual void getValueAt(int row, char* str) = 0;
	///Pure virtual finction. Prints the row value of the column
	virtual void printValue(int row) = 0;
	///Pure virtual finction. Sets the value of the column's row(paramater) row to value(parameter)
	virtual void updateValue(int row, const char* value) = 0;
	///Pure virtual finction. Prints the name of the column
	virtual void printName() = 0;
	///Pure virtual finction. Gets the name of the column
	virtual const char* getName() const = 0;
	///Virtual destructor
	virtual ~Column() {}
	///Pure virtual finction. Adds a new row with value str(parameter) in column
	virtual void addValue(const char* str) = 0;
	///Pure virtual finction. Saves the column to a file
	virtual void saveToFile(ofstream& oFile) = 0;
	///Pure virtual finction. Deletes the row row(parameter) in column
	virtual void deleteRow(int row) = 0;
	///Pure virtual finction. Returns true if the column has value value(parameter) on the row(parameter) row
	virtual bool hasValueAt(int row, const char* value) = 0;
};