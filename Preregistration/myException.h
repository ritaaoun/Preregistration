#ifndef _myException
#define _myException

#include <string>

class myException
{

public:

    // int: error code, string is the concrete error message
	myException(int errCode, const std::string & errMsg);
	~myException() {};

	/*
	   how to handle the exception is done here, so 
	   far, just write the message to screen and log file
	*/
	virtual void response();  
	int getErrCode()    { return errorCode; }
	std::string & getErrMsg() { return errorMsg; }

private:
	void initVars();

private:
	int   errorCode;
	std::string errorMsg;
};

#endif