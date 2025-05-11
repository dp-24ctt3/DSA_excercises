#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};

vector<Company> readCompanyList(string file_name) {
    ifstream iFile(file_name);
    vector<Company> list = {};
    string line;
    // getline(iFile, line);   // decided to keep the 1st line just in case input format changes

    while (getline(iFile, line)) {
        Company newCompany;
        int cur = 0;
        while (cur < line.size() && line[cur] != '|') newCompany.name += line[cur++];
        cur++;
        while (cur < line.size() && line[cur] != '|') newCompany.profit_tax += line[cur++];
        cur++;
        while (cur < line.size()) newCompany.address += line[cur++];      
        list.push_back(newCompany);
    }
    iFile.close();
    return list;
}

long long hashString(string company_name) {
    if (company_name.size() > 20) company_name = company_name.substr(company_name.size() - 21, 20);
    long long hash_value = 0;
    long long pow = 1;
    int cur = 0,
        len = company_name.size();
    while (cur < len) {
        hash_value += company_name[cur] * pow;
        cur++;
        pow *= 31;
    }

    // dont know why but (hash_value %= 2000) sometimes gives negative value
    // this line below forces hash_value to positive, copied from chatGPT
    hash_value = (hash_value % 2000 + 2000) % 2000;
    return hash_value;
}

struct HashTable {
    vector<Company>* hash_table = new vector<Company>[2000];

    void insert(Company company) {
        hash_table[hashString(company.name)].push_back(company);
    }

    Company* Search(string company_name) {
        // trying new way to write for loop
        for (Company &c : hash_table[hashString(company_name)]) {
            if (c.name == company_name) return &c;
        }
        return nullptr;
    }
};

HashTable* createHashTable(vector<Company> list_company) {
    HashTable* newTable = new HashTable;
    for (Company c : list_company) {
        newTable->insert(c);
    }
    return newTable;
}


int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Invalid argument(s)";
        return 0;
    }

    vector<Company> listCompany = readCompanyList(argv[1]);
    HashTable* hashTable = createHashTable(listCompany);

    ifstream iFile(argv[2]);
    ofstream oFile(argv[3]);
    string name;
    while (getline(iFile, name)) {
        Company* tmp = hashTable->Search(name);
        if (tmp) 
            oFile << tmp->name << '|' << tmp->profit_tax << '|' << tmp->address;
        else
            oFile << "Not found";
        if (!iFile.eof()) oFile << endl;
    }
    iFile.close();
    oFile.close();
    return 0;
}