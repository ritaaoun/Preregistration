#include "Server.hpp"
#include <fstream>

int main()
{
	std::ofstream out("Log\\out.txt");
	std::streambuf *coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());

	std::ofstream out2("Log\\out_err.txt");
	std::streambuf *cerrbuf = std::cerr.rdbuf();
	std::cerr.rdbuf(out2.rdbuf());

	Server::getInstance().start();

	std::cout.rdbuf(coutbuf);
	std::cerr.rdbuf(cerrbuf);
}