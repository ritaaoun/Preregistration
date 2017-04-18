#pragma once
class Server {
public:
	bool start();

	static Server & getInstance()
	{
		static Server instance; // Guaranteed to be destroyed.
		return instance;	// Instantiated on first use.		
	}
protected:
	bool getDepartments();
	bool getUsers();
	
private:
	Server();
	~Server();
	Server(const Server & other);
	Server & operator=(const Server & rhs);
};