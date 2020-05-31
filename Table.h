#include"StringColumn.h"

///This is the class Table. It consists of columns
class Table 
{
public:
	///Default constructor. Allocates memory, gives default values
	Table();
	///Destructor. Frees allocated memory
	~Table();
	///Copy constructor
	Table(const Table& other);
	///Constructor with one parameter - name. Allocates memory
	Table(const char* tableName);
	///Operator=
	Table& operator=(const Table& other);
	///Function that saves the table to a file
	void saveToFile(const char* fileName = "");
	///Function that reads the table from a file
	void readFromFile(const char* fileName);
	///Function that returns the name of the table
	const char* getName() const;
	///Function that describes the column types of the table
	void describe() const;
	///Function that add an empty column to the table
	void addColumn(const char* columnName, int type);
	///Function that prints the table
	void print();
	///Function that adds a row to the table
	void addRow();
	///Function that prints every row of the table that has value value(parameter) in column col(parameter)
	void select(int col, const char* value);
	///Function that deletes the row(parameter) row
	void deleteRow(int row);
	///Function that sets that value of each row in column targetColN(parameter) to targetValue(parameter) for each row in column colN(parameter) that has searchValue(parameter)
	void update(int colN, const char* searchValue, int targetColN, const char* targetValue); 
	///Function that inner joins this table and table2(parameter)
	void innerjoin(int col1, const Table& table2, int col2);
	///Function that sets the name of the table
	void setName(const char* tableName);
	///Function that returns the count of the rows that have value searchValue(parameter) in column col(parameter) 
	int count(int col, const char* searchValue);
	///Function that does the operation operation(parameter) on each row in column targetCol(parameter) for each row in column searchCol(parameter) that has searchValue(parameter)
	void aggregate(int searchCol, const char* searchValue, int targetCol, const char* operation);
	///Function that deletes each row in the table for each row in column col(parameter) that has value value(parameter)
	void deleteRows(int col, const char* value);
private:
	///Private function that frees the allocated memory
	void Free();
	///Private function that copies a table
	void CopyFrom(const Table& other);
	///Array of pointers. Every pointer can be pointing to int/double/string column 
	Column** data;
	///Number of columns in the table
	int current;
	///Number of allocated pointers
	int capacity;
	///Number of rows in the table
	int rows;
	///This is the name of the table
	char* name;
	///Private function that doubles the capacity of the array of pointers
	void resize();
};