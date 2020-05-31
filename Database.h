#include"Table.h"

///This is the class Database. It consists of tables
class Database
{
public:
	///Default constructor. Allocates memory, gives default values
	Database();
	///Constructor with one parameter- name
	Database(const char* name);
	///Destructor. Frees allocated memory
	~Database();
	///Copy constructor
	Database(const Database& other);
	///Operator=
	Database& operator=(const Database& other);
	///Function that saves a tamle with name name(parameter) to a file
	void exportTable(const char* name, const char* filename = "");
	///Function that adds a table to the database from a file
	void importTable(const char* filename);
	///Function that shows all the tables
	void showtables() const;
	///Function that describes the types of the columns in table with name name(parameter)
	void describe(const char* name) const;
	///Function that creates a new table in the database
	void createTable(const char* tableName);
	///Function that adds a column to the table with name tableName(parameter)
	void addColumn(const char* tableName, const char* columnName, int type);
	///Function that prints the table with name tableName(parameter)
	void print(const char* tableName);
	///Function that inserts a new row in the table with name tableName(parameter)
	void insertRow(const char* tableName);
	///Function that prints every row of the table with name tableName(parameter) that has value value(parameter) in column col(parameter)
	void select(const char* tableName, int col, const char* value);
	///Function that sets that value of each row in column targetColN(parameter) to targetValue(parameter) for each row in column colN(parameter) that has searchValue(parameter) in the table with name tableName(parameter)
	void update(const char* tableName, int colN, const char* searchValue, int targetColN, const char* targetValue);
	///Function that renames a table
	void rename(const char* oldName, const char* newName);
	///Function that inner joins two tables a adds the new table to the database
	void innerjoin(const char* table1Name, int col1, const char* table2Name, int col2);
	///Function that returns the count of the rows that have value searchValue(parameter) in column col(parameter) in the table with name tableName(parameter)
	int count(const char* tableName, int col, const char* searchValue);
	///Function that does the operation operation(parameter) on each row in column targetCol(parameter) for each row in column searchCol(parameter) that has searchValue(parameter) in table with name tableName(parameter)
	void aggregate(const char* tableName, int searchCol, const char* searchValue, int targetCol, const char* operation);
	///Function that saves the database to a file
	void save(const char* filename = "");
	///Function that sets the name of the database
	void setName(const char* DBname);
	///Function that reads a database from a file
	void readFromFile(const char* filename);
	///Function that deletes each row in the table with name tableName(parameter) for each row in column col(parameter) that has value value(parameter)
	void deleteRows(const char* tableName, int col, const char* value);
private:
	///Array of tables
	Table* tables;
	///Number of tables in the database
	int current;
	///Number of allocated tables
	int capacity;
	///An identificator which is used for giving a name to an inner joined table
	int idForNames;
	///This is the name of tha database
	char* name;
	///Private function that double the capacity of the database
	void resize();
	///Private function that frees the allocated memory
	void Free();
	///Private function that copies a database
	void CopyFrom(const Database& other);
	///Private function that inner joins two tables
	void innerJoin(const Table& table1, int col1, const Table& table2, int col2);
};
