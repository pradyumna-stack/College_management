#include<iostream>
#include<vector>
#include<stdio.h>
#include<cstring>
#include<fstream>
#include<algorithm>
using namespace std;

class student {
public:
    long int reg;
    char name[80], branch[50];

    void input() {
        cout << "\nEnter name: ";
        cin.ignore();
        cin.getline(name, 80);
        cout << "\nEnter roll no: ";
        cin >> reg;
        cin.ignore();
        cout << "\nEnter Branch: ";
        cin.getline(branch, 50);
    }

    void display() {
        system("CLS");
        cout << "\tDisplay Records\n";
        cout << "\nName - " << name;
        cout << "\nReg no. - " << reg;
        cout << "\nBranch - " << branch;
        cout << "\n";
        system("PAUSE");
        system("CLS");
    }

    bool operator==(student a) {
        return (reg == a.reg);
    }
};

vector<student> v;
int search_reg(long int reg, int &i);

void get_file() {
    student x;
    fstream f;
    f.open("College.txt", ios::in);
    if (f) {
        while (f.getline(x.name, 80)) {
            f >> x.reg;
            f.ignore();
            f.getline(x.branch, 50);
            v.push_back(x);
        }
    }
    f.close();
}

void bubblesort() {
    for (int i = 0; i < v.size(); i++)
        for (int j = 0; j < v.size() - i - 1; j++)
            if (v[j].reg > v[j + 1].reg)
                swap(v[j], v[j + 1]);
}

void insert_new() {
    char ch = 'y';
    int ta;
    while (ch == 'y' || ch == 'Y') {
        student x;
        x.input();
        if (search_reg(x.reg, ta) == 0)
            v.push_back(x);
        else
            cout << "\nTHE REGISTRATION NO. ALREADY EXISTS! CANNOT ADD\n";
        cout << "\nPress [Y] to enter more: ";
        cin >> ch;
    }
}

void write_file() {
    bubblesort();
    fstream f;
    f.open("College.txt", ios::out);
    for (int i = 0; i < v.size(); i++) {
        student x = v[i];
        f << x.name << "\n" << x.reg << "\n" << x.branch << "\n";
    }
    f.close();
}

int search_reg(long int reg, int &i) {
    for (i = 0; i < v.size(); i++)
        if (v[i].reg == reg)
            return 1;
    return 0;
}

void search_and_show() {
    int ch, i;
    char name[80], branch[50];
    long int reg;

    cout << "\n1. Search by Reg No.";
    cout << "\n2. Search by Name";
    cout << "\n3. Search by Branch";
    cin >> ch;

    switch (ch) {
        case 1:
            cout << "\nEnter reg no.: ";
            cin >> reg;
            if (search_reg(reg, i) == 1)
                v[i].display();
            else
                cout << "\nRecord NOT FOUND!";
            break;
        case 2:
            cout << "\nEnter name: ";
            cin.ignore();
            cin.getline(name, 80);
            for (i = 0; i < v.size(); i++) {
                if (strcmp(v[i].name, name) == 0)
                    v[i].display();
            }
            break;
        case 3:
            cout << "\nEnter branch: ";
            cin.ignore();
            cin.getline(branch, 50);
            for (i = 0; i < v.size(); i++) {
                if (strcmp(v[i].branch, branch) == 0)
                    v[i].display();
            }
            break;
        default:
            cout << "\nWrong CHOICE!";
    }
}

void show() {
    for (int i = 0; i < v.size(); i++)
        v[i].display();
}

void delete_data() {
    int i;
    long int reg;
    cout << "\nEnter Reg. no.: ";
    cin >> reg;
    if (search_reg(reg, i) == 1) {
        cout << "\nThe following data is being deleted";
        v[i].display();
        v.erase(v.begin() + i);
    }
}

void edit_data() {
    int i;
    long int reg;
    cout << "\nEnter Reg. no.: ";
    cin >> reg;
    if (search_reg(reg, i) == 1) {
        cout << "\nEnter new data:";
        v[i].input();
    }
}

// --- AUTHENTICATION FUNCTION ---
bool login() {
    string uname, pwd;
    cout << "=== Admin Login ===\n";
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pwd;

    if (uname == "admin" && pwd == "admin123") {
        cout << "\nLogin successful!\n";
        return true;
    } else {
        cout << "\nInvalid credentials. Access denied.\n";
        return false;
    }
}

int main() {
    if (!login()) {
        return 0; // Exit if login fails
    }

    int ch;
    char ch1 = 'y';
    get_file();

    while (ch1 == 'y' || ch1 == 'Y') {
        cout << "1. Insert new record\n";
        cout << "2. Show all records\n";
        cout << "3. Search record\n";
        cout << "4. Edit record\n";
        cout << "5. Delete record\n";
        cout << "6. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1: insert_new(); break;
            case 2: show(); break;
            case 3: search_and_show(); break;
            case 4: edit_data(); break;
            case 5: delete_data(); break;
            case 6: ch1 = 'n'; break;
            default: cout << "\nWrong choice"; break;
        }
        write_file();
    }

    return 0;
}
