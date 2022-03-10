#ifndef StackObject_H
#define StackObject_H
#include <iostream>
#include <string>
//#include "MemoryObject.h"
using namespace std;

class StackObject {
public:
	char c;
	short s;
	int i;
	float f;

	// char(0), short(1), int(2), float(3)
	int type; 

	StackObject();
	StackObject(char memoryObject);
	StackObject(short memoryObject);
	StackObject(int memoryObject);
	StackObject(float memoryObject);
	~StackObject();
	virtual char getChar();
	virtual int getInt();
	virtual short getShort();
	virtual float getFloat();
	virtual void printObject();

	StackObject operator==(StackObject& object);
	StackObject operator<(StackObject& object);
	StackObject operator>(StackObject& object);
	StackObject operator+(StackObject& object);
	StackObject operator-(StackObject& object);
	StackObject operator*(StackObject& object);
	StackObject operator/(StackObject& object);
};

#endif
