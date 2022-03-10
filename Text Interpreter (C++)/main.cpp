//#include "Value.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include "StackObject.h"
#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char* argv[]) {
	//const char* filename = "interpreter_input.smp";
	FILE* fp = fopen(argv[1], "r");
	if (fp == NULL) {
		cout << "NULL" << endl;
	}
	Memory mem = Memory(fp);
	
	/* Convert smp to int
	FILE* op = fopen("108_test.txt", "w");
	for (int i = 0; i < mem.m_size; i++) {
		fprintf(op, "%d ", (int)mem.memory[i]);
	}
	// End Convert */
	
	StackObject* rstack = new StackObject[mem.m_size];
	int* fpstack = new int[mem.m_size];

	long sp = -1;
	long fpsp = -1;
	long pc = 0;

	unsigned char ByteCode;

	do {
		ByteCode = mem.getMemory(pc++);
		switch ((int)ByteCode) {
		case 132: {// cmpe
			rstack[sp - 1] = rstack[sp - 1] == rstack[sp];
			sp--;
			break; }
		case 136: {// cmplt
			rstack[sp - 1] = rstack[sp - 1] < rstack[sp]; //??? buyiyang
			sp--;
			break; }
		case 140: {// cmpgt
			rstack[sp - 1] = rstack[sp - 1] > rstack[sp];
			sp--;
			break; }
		case 36: {// jmp
			pc = rstack[sp].i;
			sp = sp - 1;
			break; }
		case 40: {// jmpc
			if (rstack[sp - 1].i) pc = rstack[sp].i;
			sp = sp - 2;
			break; }
		case 44: {// call
			fpstack[++fpsp] = (int)(sp - rstack[sp].i - 1); //???
			sp--;
			pc = rstack[sp--].i;
			break; }
		case 48: {// ret
			sp = (int)fpstack[fpsp--];
			pc = rstack[sp--].i;
			break; }
		case 68: {// pushc
			rstack[++sp] = StackObject((char)mem.memory[pc]); //???
			pc += 1;
			break; }
		case 69: {// pushs
			//short s_cpy = (short){ mem.memory[pc + 1], mem.memory[pc + 2] };
			//short* s_cpy = { mem.memory[pc + 1], mem.memory[pc + 2] };
			unsigned char temp[] = {mem.memory[pc], mem.memory[pc + 1]}; //??? why +1 +2
			
			//short s = (short)temp; //???
			short s;
			memcpy(&s, &temp, sizeof(s));

			rstack[++sp] = StackObject(s);
			pc += 2;
			break; }
		case 70: {// pushi
			unsigned char temp70[] = { mem.memory[pc], 
									   mem.memory[pc + 1],
									   mem.memory[pc + 2],
									   mem.memory[pc + 3]};
			//int i = (int)temp; //???
			int i;
			memcpy(&i, &temp70, sizeof(i));

			rstack[++sp] = StackObject(i);

			pc += 4;
			break; }
		case 71: {// pushf
			unsigned char temp71[] = { mem.memory[pc],
									   mem.memory[pc + 1],
									   mem.memory[pc + 2],
									   mem.memory[pc + 3] }; 
			//float f = (float)temp; //???
			float f;
			memcpy(&f, &temp71, sizeof(f));

			rstack[++sp] = StackObject(f);
			pc += 4;
			break; }
		case 72: {// pushvc
			rstack[sp] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 73: {// pushvs
			rstack[sp] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 74: {// pushvi
			rstack[sp] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 75: {// pushvf
			rstack[sp] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 76: {// popm
			sp -= rstack[sp].i + 1;
			break; }
		case 77: {// popa
			for (long i = 1; i <= rstack[sp].i; i++) {
				rstack[fpstack[fpsp] + i] = rstack[sp - rstack[sp].i + i - 1];
			}
			sp = fpstack[fpsp] + rstack[sp].i;
			break; }
		case 80: {// popv
			rstack[fpstack[fpsp] + rstack[sp].i + 1] = rstack[sp - 1]; //???
			sp -= 2;
			break; }
		case 84: {// peekc
			rstack[fpstack[fpsp] + rstack[sp - 1].i + 1] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 85: {// peeks
			rstack[fpstack[fpsp] + rstack[sp - 1].i + 1] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 86: {// peeki
			rstack[fpstack[fpsp] + rstack[sp - 1].i + 1] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 87: {// peekf
			rstack[fpstack[fpsp] + rstack[sp - 1].i + 1] = rstack[fpstack[fpsp] + rstack[sp].i + 1];
			break; }
		case 88: {// pokec
			rstack[fpstack[fpsp] + rstack[sp].i + 1] = rstack[fpstack[fpsp] + rstack[sp - 1].i + 1];
			break; }
		case 89: {// pokes
			rstack[fpstack[fpsp] + rstack[sp].i + 1] = rstack[fpstack[fpsp] + rstack[sp - 1].i + 1];
			break; }
		case 90: {// pokei
			rstack[fpstack[fpsp] + rstack[sp].i + 1] = rstack[fpstack[fpsp] + rstack[sp - 1].i + 1];
			break; }
		case 91: {// pokef
			rstack[fpstack[fpsp] + rstack[sp].i + 1] = rstack[fpstack[fpsp] + rstack[sp - 1].i + 1];
			break; }
		case 94: {{// swp
			StackObject tmp = rstack[sp - 1];
			rstack[sp - 1] = rstack[sp];
			rstack[sp] = tmp;
			break; } }
		case 100: {// add
			rstack[sp - 1] = rstack[sp - 1] + rstack[sp];
			sp--;
			break; }
		case 104: {// sub
			rstack[sp - 1] = rstack[sp - 1] - rstack[sp];
			sp--;
			break; }
		case 108: {// mul
			rstack[sp - 1] = rstack[sp - 1] * rstack[sp];
			sp--;
			break; }
		case 112: {// div
			rstack[sp - 1] = rstack[sp - 1] / rstack[sp];
			sp--;
			break; }
		case 144: {// printc
			rstack[sp--].printObject();
			cout << endl;
			break; }
		case 145: {// prints
			rstack[sp--].printObject();
			cout << endl;
			break; }
		case 146: {// printi
			rstack[sp--].printObject(); //??? if the rstack[sp] is a float and printi is called, what should we do?
			cout << endl;
			break; }
		case 147: {// printf
			rstack[sp--].printObject();
			cout << endl;
			break; }
		case 0: {// halt
			pc--;
			cout << endl;
			cout << "Compile values:" << endl;
			cout << "PC: " << pc << endl;
			cout << "sp: " << sp << endl;

			cout << "rstack: ";
			if (sp == -1) cout << "empty" << endl;
			else {
				for (int i = 0; i < (sp + 1); i++) {
					rstack[i].printObject();
				}
				cout << endl;
			}
			cout << "fpsp: " << fpsp << endl;
			cout << "fpstack: ";
			if (fpsp == -1) cout << "empty" << endl;
			else {
				for (int i = 0; i < (sp + 1); i++) {
					cout << fpstack[i];
				}
				cout << endl;
			}
			break; }
		}

		/*// test
		cout << "PC: " << pc << endl;
		cout << "sp: " << sp << endl;
		cout << "rstack: ";
		if (sp == -1) cout << "empty" << endl;
		else {
			for (int i = 0; i < (sp + 1); i++) {
				rstack[i].printObject();
				cout << " ";
			}
			cout << endl;
		}
		cout << "fpsp: " << fpsp << endl;
		cout << "fpstack: ";
		if (fpsp == -1) cout << "empty\n" << endl;
		else {
			for (int i = 0; i < (sp + 1); i++) {
				cout << (int)fpstack[i];
				cout << " ";
			}
			cout << endl;
			cout << endl;
		}
		*/ // end test

	} while ((int)ByteCode != 0);

	fclose(fp);
	return EXIT_SUCCESS;
}
