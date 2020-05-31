#include"IntColumn.h"

///This is the class DoubleColumn. It inheritances the class Column. It is a column with double values
class DoubleColumn : public Column
{
public:
	///Virtual finction. Returns 1
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
	DoubleColumn(const DoubleColumn& other);
	///Operator=
	DoubleColumn& operator=(const DoubleColumn& other);
	///Default constructor. Allocates memory, gives default values
	DoubleColumn();
	///Destructor. Frees allocated memory
	~DoubleColumn();
	///Constructor with 2 parameters - name and number of rows
	DoubleColumn(const char* columnName, int rows);
	///Constructor whih reads from a file
	DoubleColumn(ifstream& iFile);
private:
	///Array of pointers which can be eaiher double or null pointers
	double** column;
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
	///Private function that copies a double column
	void CopyFrom(const DoubleColumn& other);
};
