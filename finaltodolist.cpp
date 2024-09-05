#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct todolist {
    int id; 
    string task;
};

int ID = 0;

void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main() {
    system("cls");
    while (true) {
        banner();
        cout << "\n\t1. Add Task";
        cout << "\n\t2. Show Task";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";

        int choice;
        cout << "\n\t  Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                showTask();
                break;
            case 3:
                searchTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                updateTask();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }
    return 0;
}

void banner() {
    cout << "______________________" << endl;
    cout << "\t      MY TO DO      " << endl;
    cout << "______________________" << endl;
}

void addTask() {
    system("cls");
    banner();
    todolist todo;

    cout << "Enter New Task: ";
    cin.ignore();
    getline(cin, todo.task);
    char save;
    cout << "Save? (y/n): ";
    cin >> save;
    if (save == 'y') {
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << ID << endl;
        fout << todo.task << endl;
        fout.close();

        char more;
        cout << "Add more Task? (y/n): ";
        cin >> more;

        if (more == 'y') {
            addTask();
        } else {
            system("cls");
            cout << "Added Successfully!" << endl;
        }
    }
    system("cls");
}

void showTask() {
    system("cls");
    banner();
    todolist todo;
    ifstream fin;
    fin.open("todo.txt");
    cout << "Tasks:" << endl;

    while (fin >> todo.id) {
        fin.ignore();
        getline(fin, todo.task);
        if (!todo.task.empty()) {
            cout << "\t" << todo.id << " : " << todo.task << endl;
        } else {
            cout << "\t Empty!" << endl;
        }
    }
    fin.close();
    char exit;
    cout << "Exit? (y/n): ";
    cin >> exit;
    if (exit != 'y') {
        showTask();
    }
    system("cls");
}

int searchTask() {
    system("cls");
    banner();
    int id;
    cout << "Enter task id: ";
    cin >> id;
    todolist todo;
    ifstream fin("todo.txt");

    while (fin >> todo.id) {
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id == id) {
            system("cls");
            cout << "\t " << todo.id << ": " << todo.task << endl;
            fin.close();
            return id;
        }
    }
    fin.close();
    cout << "Task not found." << endl;
    return 0;
}

void deleteTask() {
    system("cls");
    int id = searchTask();
    if (id != 0) {
        char del;
        cout << "\n\t Delete? (y/n): ";
        cin >> del;
        if (del == 'y') {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;

            while (fin >> todo.id) {
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id) {
                    tempFile << index << endl;
                    tempFile << todo.task << endl;
                    index++;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "\n\t Deleted Successfully!" << endl;
        }
    }
}

void updateTask() {
    system("cls");
    int id = searchTask();
    if (id != 0) {
        char upd;
        cout << "\n\t Update? (y/n): ";
        cin >> upd;
        if (upd == 'y') {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;

            while (fin >> todo.id) {
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id == id) {
                    cout << "Enter new task: ";
                    cin.ignore();
                    getline(cin, todo.task);
                }
                tempFile << index << endl;
                tempFile << todo.task << endl;
                index++;
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            system("cls");
            cout << "\n\t Updated Successfully!" << endl;
        }
    }
}
