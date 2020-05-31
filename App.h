#include"Database.h"

///This is the class App. It is used for working with databases
class App
{
public:
	///Default constructor. Allocates memory, shows the help menu 
	App();
	///Destructor. Frees allocated memory
	~App();
	///Function that starts the app
	void start();
private:
	///Pointer to a database
	Database* DB;
	///Private function that frees the allocated memory
	void Free();
	///Private function that copies an app;
	void CopyFrom(const App& other);
	///Private function that saves the database
	void save(const char* filename);
	///Private function that displays the help menu
	void help();
	///Private function that displays the operations with a database
	void operations(const char* filename);
	///Private function that opens the menu
	void menu(const char* filename);
	///Private function that reads a database fron a file
	void open(const char* filename);
};

