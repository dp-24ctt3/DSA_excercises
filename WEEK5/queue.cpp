#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


struct NODE {
	int key;
	NODE* p_next;
};

struct Queue {
	NODE* head;
	NODE* tail;
};

Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = q->tail = nullptr;
	return q;
}

void enqueue(Queue& q, int key) {
	NODE* newNode = new NODE;
	if (!newNode) return;
	newNode->key = key;
	newNode->p_next = nullptr;

	if (q.head == nullptr) {
		q.head = q.tail = newNode;
		return;
	}
    q.tail->p_next = newNode;
	q.tail = newNode;
	return;
}

int dequeue(Queue& q) {
	if (!q.head) return NULL;
    int data = q.head->key;
    NODE* p = q.head;
    q.head = q.head->p_next;
    delete p;
    return data;
}

int size(Queue q) {
	int count = 0;
	NODE* p = q.head;
	while (p != nullptr) {
		count++;
		p = p->p_next;
	}
	return count;
}

bool isEmpty(Queue q) {
	return q.head == nullptr;
}

int main() {
	char* cInput = new char[30];
    bool is_init = false;
    Queue* q;
    ofstream oFile("output.txt", ios::trunc); oFile.close();    // blank output.txt
    oFile.open("output.txt", ios::app);
	ifstream iFile("input.txt");

    while (!iFile.eof()) {
        iFile.getline(cInput, 100);
        if (strcmp(cInput, "init") == 0) {
            q = initializeQueue();
            is_init = true;
        }
        else if (!is_init){
            oFile << "Your queue is not intialized";
            oFile.close();
            return 0;
        }
        else if (strcmp(cInput, "dequeue") == 0) dequeue(*q);
        else if (cInput[0] == 'e' && cInput[1] == 'n' && cInput[2] == 'q' && cInput[3] == 'u' &&
                 cInput[4] == 'e' && cInput[5] == 'u' && cInput[6] == 'e' && cInput[7] == ' ') {
            // get number from text
            int c, num = 0;
            if (cInput[8] == '-')
                c = 9;
            else
                c = 8;
            while (cInput[c] != '\0') {
                if ('0' <= cInput[c] && cInput[c] <= '9') {
                    num += cInput[c] - 48;
                    num *= 10;
                }
                c++;
            }
            num /= 10;
            if (cInput[8] == '-') num *= -1;    // if is_negative_number
            
            enqueue(*q, num);
        }
        // write queue content
        if (isEmpty(*q)) {
            oFile << "EMPTY";
        }
        else {
            NODE* cur = q->head;
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
    while (!isEmpty(*q)) dequeue(*q);
    delete q;

    return 0;
}