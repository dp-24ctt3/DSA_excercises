#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct NODE {
	int key;
	NODE* p_next;
};

struct Stack {
	NODE* top;
};

Stack* initializeStack() {
	Stack* st = new Stack;
	st->top = nullptr;
	return st;
}

void push(Stack& s, int key) {
	NODE* newNode = new NODE;
	if (newNode == nullptr) return;
	newNode->key = key;
	newNode->p_next = nullptr;

	if (s.top == nullptr) {
		s.top = newNode;
		return;
	}
    NODE* cur = s.top;
    while (cur->p_next != nullptr){
        cur = cur->p_next;
    }
	cur->p_next = newNode;
	return;
}

int pop(Stack& s) {
	if (!s.top) return NULL;
	int data;

    if (s.top->p_next == nullptr) {
		data = s.top->key;
        delete s.top;
        s.top = nullptr;
		return data;
	}

    NODE* cur = s.top;
    while (cur->p_next->p_next != nullptr){
        cur = cur->p_next;
    }
    data = cur->p_next->key;
    delete cur->p_next;
	cur->p_next = nullptr;
	return data;
}

int size(Stack s) {
	int count = 0;
	NODE* p = s.top;
	while (p != nullptr) {
		count++;
		p = p->p_next;
	}
	return count;
}

bool isEmpty(Stack s) {
	return s.top == nullptr;
}



int main() {
	char* cInput = new char[30];
    bool is_init = false;
    Stack* st;
	ofstream oFile("output.txt", ios::trunc); oFile.close();    // blank output.txt
    oFile.open("output.txt", ios::app);
	ifstream iFile("input.txt");

	while (!iFile.eof()) {
        iFile.getline(cInput, 100);
        if (strcmp(cInput, "init") == 0) {
            st = initializeStack();
            is_init = true;
        }
        else if (!is_init){
            oFile << "Your stack is not intialized";
            oFile.close();
            return 0;
        }
        else if (strcmp(cInput, "pop") == 0) pop(*st);
        else if (cInput[0] == 'p' && cInput[1] == 'u' && cInput[2] == 's' && cInput[3] == 'h' && cInput[4] == ' '){
            // get number from text
            int c, num = 0;
            if (cInput[5] == '-')
                c = 6;
            else
                c = 5;
            while (cInput[c] != '\0'){
                if ('0' <= cInput[c] && cInput[c] <= '9'){
                    num += cInput[c] - 48;
                    num *= 10;
                }
                c++;
            }
            num /= 10;
            if (cInput[5] == '-') num *= -1;    // if is_negative_number
            
            push(*st, num);
        }
        // write queue content
        if (isEmpty(*st)){
            oFile << "EMPTY";
        }
        else{
            NODE* cur = st->top;
            while (cur != nullptr){
                oFile << cur->key;
                if (cur->p_next != nullptr) oFile << ' ';
                cur = cur->p_next;
            }
        }
        if (!iFile.eof()) oFile << endl;
	}
    iFile.close();
    oFile.close();
    cout << "View output in output.txt";
    while (!isEmpty(*st)) pop(*st);
    delete st;

    return 0;
}