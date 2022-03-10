#pragma once
#ifndef Memory_H
#define Memory_H
#include <iostream>
#include <string>
using namespace std;

class Memory {
public:
	long m_size;
	unsigned char* memory;

	Memory(FILE* fp);
	~Memory();
	//virtual void execute();
	//virtual char getChar();
	//virtual short getShort();
	//virtual int getInt();
	//virtual float getFloat();
	virtual unsigned char getMemory(long sp);
};

#endif