#include "Memory.h"
#include <iostream>
#include <stdio.h>
using namespace std;

long __det_size(FILE* fp);

Memory::Memory(FILE* fp) {
	m_size = __det_size(fp);
	memory = new unsigned char[m_size];
	
	// Build Memory
	unsigned char temp;
	for (long i = 0; i < m_size; i++) {
		fread(&temp, sizeof(temp), 1, fp);
		memory[i] = temp;
	}
}

Memory::~Memory(){
	delete memory;
}

long __det_size(FILE* fp) {
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return size;
}

unsigned char Memory::getMemory(long pc) {
	return memory[pc];
}