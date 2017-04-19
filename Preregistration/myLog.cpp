#include "myLog.h"
#define _CRT_SECURE_NO_WARNINGS

const enum myLog::logLevels DEFAULT_LOG_LEVEL = myLog::LEVEL_1;

myLog::myLog()
{
   initVars();
   init();
} 

myLog::myLog(const string& fileName)
{
    initVars();
    init(fileName);
}

myLog::myLog(const string& fileName,enum logLevels levelIn)
{
    initVars();
    logLevel = levelIn;
    init(fileName);
}

myLog::~myLog()
{
   if ( logLevel<QUIET_MODE )
   {
      clear(ios::goodbit);
      *this << endl;
      printHeader(1);    // add ending time to log file
   }
   close();
}

void myLog::init(const string& fileName)
{
   if ( (fileName.c_str())[0] )
      openLog(fileName,LOG_WRITE);
   else
      openLog("syslog.log",LOG_WRITE);
}

void myLog::init(const string& fileName, int mode)
{
   if ( (fileName.c_str())[0] )
      openLog(fileName,mode);
   else
      openLog("syslog.log", mode);
}

void myLog::init()
{
   openLog("syslog.log",LOG_WRITE);
}

void myLog::openLog(const string& fileName, int mode)
{
   if (logLevel < QUIET_MODE)
   {
      open(fileName.c_str(),mode);
      
      // fail() returns a null zero when operation fails   
      // rc = (*this).fail();
    
      if ( fail() == 0 )
      {
         logName = fileName;
         printHeader(0);         // insert start time into top of log file
      }
      else
      {
         cout << "ERROR: Log file " << fileName.c_str() 
              << " could not be opened for write access." << endl;
         logLevel = QUIET_MODE;
      }
   }
   else
   {
      cout << "Logging disabled (QUIET_MODE set)" << endl;
   }
}

void myLog::initVars()
{
   time(&startTime);
   logLevel = DEFAULT_LOG_LEVEL;
}

void myLog::printHeader(int theEnd)
{
   if ( logLevel < QUIET_MODE )
   {
      clear(ios::goodbit);



      char cur_time[9];
      char cur_date[9];



      char line_1[61];
      sprintf_s(line_1,"A yuChen Technology Development Work Log File");

      char line_2[61];
      sprintf_s(line_2,"DATE: %s - %s%30s",cur_date,cur_time,logName.c_str());

      *this << line_1 << endl;
      *this << line_2 << endl << endl;

      if (theEnd) *this << getExecTime() << endl;
   }
        
} 

void myLog::getExecTime(int* min, int* sec)
{
   time_t endTime;
   time(&endTime);
   *min = (int)((endTime - startTime)/60);
   *sec = (int)((endTime - startTime)%60);
} 

char* myLog::getExecTime()
{
    int min = 0;
    int sec = 0;
    getExecTime(&min, &sec);
    static char execTime[128];
    sprintf_s(execTime, "Execution time: %d minutes %d seconds", min, sec);
    return execTime;
}
