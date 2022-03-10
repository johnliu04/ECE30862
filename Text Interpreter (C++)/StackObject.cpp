#include "StackObject.h"
#include <iostream>
#include <stdio.h>
using namespace std;

StackObject::StackObject() {}

StackObject::StackObject(char memoryObject) {
	c = memoryObject;
	s = 0;
	i = 0;
	f = 0;
	type = 0;
}

StackObject::StackObject(short memoryObject) {
	c = 0;
	s = memoryObject;
	i = 0;
	f = 0;
	type = 1;
}

StackObject::StackObject(int memoryObject) {
	c = 0;
	s = 0;
	i = memoryObject;
	f = 0;
	type = 2;
}

StackObject::StackObject(float memoryObject) {
	c = 0;
	s = 0;
	i = 0;
	f = memoryObject;
	type = 3;
}

StackObject::~StackObject() {}

char StackObject::getChar() {
	return c;
}

int StackObject::getInt() {
	return i;
}

short StackObject::getShort() {
	return s;
}

float StackObject::getFloat() {
	return f;
}


void StackObject::printObject() {
	switch (type) {
	case 0: cout << (int)c; break;
	case 1: cout << s; break;
	case 2: cout << i; break;
	case 3: cout << f; break;
	}
}


StackObject StackObject::operator==(StackObject& object){
	if (type == object.type) {
		if (type == 0 && c == object.c) return StackObject(int(1));
		else if (type == 1 && s == object.s) return StackObject(int(1));
		else if (type == 2 && i == object.i) return StackObject(int(1));
		else if (type == 3 && f == object.f) return StackObject(int(1));
	}
	return StackObject(int(0));
}

StackObject StackObject::operator<(StackObject& object){
	if (type == object.type) {
		if (type == 0 && c < object.c) return StackObject(int(1));
		else if (type == 1 && s < object.s) return StackObject(int(1));
		else if (type == 2 && i < object.i) return StackObject(int(1));
		else if (type == 3 && f < object.f) return StackObject(int(1));
	}
	return StackObject(int(0));
}

StackObject StackObject::operator>(StackObject& object){
	if (type == object.type) {
		if (type == 0 && c > object.c) return StackObject(int(1));
		else if (type == 1 && s > object.s) return StackObject(int(1));
		else if (type == 2 && i > object.i) return StackObject(int(1));
		else if (type == 3 && f > object.f) return StackObject(int(1));
	}
	return StackObject(int(0));
}

StackObject StackObject::operator+(StackObject& object){
	if (type == object.type) {
		if (type == 0) return StackObject(c + object.c);
		else if (type == 1) return StackObject(s + object.s);
		else if (type == 2) return StackObject(i + object.i);
		else if (type == 3) return StackObject(f + object.f);
	}
	cout << "Unmatched data type while attempting to +" << endl;
	return StackObject(int(0));
}

StackObject StackObject::operator-(StackObject& object){
	if (type == object.type) {
		if (type == 0) return StackObject(c - object.c);
		else if (type == 1) return StackObject(s - object.s);
		else if (type == 2) return StackObject(i - object.i);
		else if (type == 3) return StackObject(f - object.f);
	}
	cout << "Unmatched data type while attempting to -" << endl;
	return StackObject(int(0));
}

StackObject StackObject::operator*(StackObject& object) {
	if (type == object.type) {
		if (type == 0) return StackObject(c * object.c);
		else if (type == 1) return StackObject(s * object.s);
		else if (type == 2) return StackObject(i * object.i);
		else if (type == 3) return StackObject(f * object.f);
	}
	cout << "Unmatched data type while attempting to *" << endl;
	return StackObject(int(0));
}

StackObject StackObject::operator/(StackObject& object) {
	if (type == object.type) {
		if (type == 0) return StackObject(c / object.c);
		else if (type == 1) return StackObject(s / object.s);
		else if (type == 2) return StackObject(i / object.i);
		else if (type == 3) return StackObject(f / object.f);
	}
	cout << "Unmatched data type while attempting to /" << endl;
	return StackObject(int(0));
}