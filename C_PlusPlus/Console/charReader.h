#ifndef __CHAR_READER_H__
#define __CHAR_READER_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>


class charReader
{
private:
	FILE* m_fp;
	char* m_sStr;


public:
	charReader();
	~charReader(){};

	char next();
	char peek();


};

#endif