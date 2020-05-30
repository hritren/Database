#include"Database.h"

class App
{
public:
	App();
	~App();
	void start();
private:
	Database* DB;
	void Free();
	void CopyFrom(const App& other);
	void save(const char* filename);
	void help();
	void operations(const char* filename);
	void menu(const char* filename);
	void open(const char* filename);
};

