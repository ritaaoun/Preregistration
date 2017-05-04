//-*-C++-*-///////////////////////////////////////////////////////////////////
//   Copyright 2004 yuChen Technology.  All Rights Reserved.
//
//   Class: myLog
//   
//   Description: used as a system log file for the simDelta project 
//
//   Name of Designer:  Liyang Yu 
//   Name of Coder:     Liyang Yu 
//   Date:              01/27/04
//
//////////////////////////////////////////////////////////////////////////////

#ifndef myLog_H
#define myLog_H

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

/* 
   the log file has to be accessed from any code
   which includes this header (similiar to cout, cerr, clog, etc..)
*/

class myLog;
extern myLog winLog;

// const string SD_DEFAULT_LOGFILE = "simDelta.log";

const int LOG_WRITE  = ios::out;
const int LOG_APPEND = ios::app;

const int EXIT_MSG_SIZE = 512;
const int MAX_EXIT_CODES = 3;

class myLog : public ofstream
{

public:

   enum logLevels 
   {
      LEVEL_0,       // buffer all log messages
      LEVEL_1,       // buffer Level one, two and three log messages
      LEVEL_2,       // buffer Level two and three log messages
      LEVEL_3,       // buffer Level three log messages
      QUIET_MODE     // do not print out any messages
   };
 
   myLog();
   myLog(const std::string&);
   myLog(const std::string&,enum logLevels);
   virtual ~myLog();

private:

   void initVars();
   void init(const std::string&);
   void init(const std::string&,int);
   void init();

   char* getExecTime();
   void  getExecTime(int*,int*);
   void  openLog(const std::string&,int);
   void  printHeader(int);

private:

	std::string logName;
   enum logLevels logLevel;
   time_t startTime;

};

const enum myLog::logLevels L0 = myLog::LEVEL_0;
const enum myLog::logLevels L1 = myLog::LEVEL_1;
const enum myLog::logLevels L2 = myLog::LEVEL_2;
const enum myLog::logLevels L3 = myLog::LEVEL_3;
const enum myLog::logLevels LQUIET = myLog::QUIET_MODE;

#endif

