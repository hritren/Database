#include"DoubleColumn.h"

#pragma warning(disable : 4996)
///This is the class StringColumn. It inheritances the class Column. It is a column with string values
class StringColumn : public Column 
{
public:
	///Virtual finction. Returns 2
	virtual int getType();
	///Virtual finction. Gets the row value of the column
	virtual void getValueAt(int row, char* str);
	///Virtual finction. Prints the row value of the column
	virtual void printValue(int row);
	///Virtual finction. Sets the value of the column's row(paramater) row to value(parameter)
	virtual void updateValue(int row, const char* value);
	///Virtual finction. Prints the name of the column
	virtual void printName();
	///Virtual finction. Gets the name of the column
	virtual const char* getName() const;
	///Virtual finction. Adds a new row with value str(parameter) in column
	virtual void addValue(const char* str);
	///Virtual finction. Saves the column to a file
	virtual void saveToFile(ofstream& oFile);
	///Virtual finction. Deletes the row row(parameter) in column
	virtual void deleteRow(int row);
	///Virtual finction. Returns true if the column has value value(parameter) on the row(parameter) row
	virtual bool hasValueAt(int row, const char* value);
	///Copy constructor
	StringColumn(const StringColumn& other);
	///Operator=
	StringColumn& operator=(const StringColumn& other);
	///Default constructor. Allocates memory, gives default values
	StringColumn();
	///Destructor. Frees allocated memory
	~StringColumn();
	///Constructor with 2 parameters - name and number of rows
	StringColumn(const char* columnName, int rows);
	///Constructor whih reads from a file
	StringColumn(ifstream& iFile);
private:
	///Array of pointers which can be eaiher char or null pointers
	char** column;
	///Number of allocated pointers
	int capacity;
	///This is the number of rows in the column
	int current;
	///This is the name of the column
	char* name;
	///Private function that doubles the capacity of the column
	void resize();
	///Private function that frees the allocated array of pointers
	void Free();
	///Private function that frees the name
	void FreeName();
	///Private function that copies a string column
	void CopyFrom(const StringColumn& other);
};