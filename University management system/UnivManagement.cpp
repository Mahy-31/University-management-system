#include <iostream>
#include <mysql.h>
#include <mysqlx_error.h>
#include <Windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost"; 
const char* USER = "root"; 
const char* PW = "3112"; 
const char* DB = "univInfo";

class University {
private:
	int Id;
	string Name, Dept;
	float Cgpa;

public:
	University() :Id(0), Name(""), Dept(""), Cgpa(0.0) {}
	
	void setId(int id) {
		Id = id;
	}
	void setName(string name) {
		Name = name;
	}
	void setDept(string dept) {
		Dept = dept;
	}
	void setCgpa(float cgpa) {
		Cgpa = cgpa;
	}

	//getter functions

	int getId() {
		return Id;
	}
	string getName() {
		return Name;
	}
	string getDept() {
		return Dept;
	}
	float getCgpa() {
		return Cgpa;
	}
};

void addStudent(MYSQL* conn, University u) {
	int id;
	string name, dept;
	float cgpa;

	cout << "Enter student Id:"; cin >> id;
	u.setId(id);
	cout << "Enter student name:"; cin >> name;
	u.setName(name);
	cout << "Enter student department:"; cin >> dept;
	u.setDept(dept);
	cout << "Enter student cgpa:"; cin >> cgpa;
	u.setCgpa(cgpa);

	string ins = "INSERT INTO Students(StudentID, Name, Department, Cgpa) VALUES('" + to_string(u.getId()) + "','" + u.getName() + "','" + u.getDept() + "','" + to_string(u.getCgpa()) + "')";
	if (mysql_query(conn, ins.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Data inserted successfully!" << endl;
	}
};

//update function
void updateStudent(MYSQL* conn, University u) {
	int a;
	cout << "1. Department" << endl;
	cout << "2. Cgpa" << endl;
	cout << "which information you wanna update?"; cin >> a;
	int id;
	cout << "Enter Student Id:"; cin >> id;

	if (a == 1) {
		string dept;
		cout << "Enter new department:"; cin >> dept;
		u.setDept(dept);
		string upd1 = "UPDATE Students SET Department = '" + u.getDept() + "' WHERE StudentID = '" + to_string(u.getId()) + "'";
		if (mysql_query(conn, upd1.c_str())) {
			cout << "Error:" << mysql_error(conn) << endl;
		}
		else {
			cout << "Data updated successfully!" << endl;
		}

	}
	else if (a == 2) {
		float cgpa;
		cout << "enter new cgpa:"; cin >> cgpa;
		u.setCgpa(cgpa);
		string upd2 = "UPDATE Students SET Cgpa = '" + to_string(u.getCgpa()) + "' WHERE StudentID = '" + to_string(u.getId()) + "'";
		if (mysql_query(conn, upd2.c_str())) {
			cout << "Error:" << mysql_error(conn) << endl;
		}
		else {
			cout << "Data updated successfully!" << endl;
		}
	}

};

//Search function

void searchStudent(MYSQL* conn) {
	int id;
	cout << "Enter student ID:"; cin >> id;
	stringstream ss;
	ss << id;
	string sId = ss.str();
	string show = "SELECT * FROM Students WHERE StudentID = '" + sId + "'";
	if (mysql_query(conn, show.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			MYSQL_ROW row = mysql_fetch_row(res);
			if (row) {
				int num = mysql_num_fields(res);
				for (int i = 0; i < num; i++) {
					cout << " " << row[i];
				}
			}
			mysql_free_result(res);
		}
	}
	Sleep(3000);
}

//show function
void showRecord(MYSQL* conn) {
	string show = "SELECT * FROM Students";
	if (mysql_query(conn, show.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			int num = mysql_num_fields(res);
			MYSQL_ROW row;
			while (row = mysql_fetch_row(res)) {
				for (int i = 0; i < num; i++) {
					cout << " " << row[i];
				}
			}
		};
	};
	Sleep(5000);

};

//delete function
void deleteStudent(MYSQL* conn) {
	int id;
	cout << "Enter student ID:"; cin >> id;
	stringstream ss;
	ss << id;
	string sId = ss.str();
	string del = "DELETE FROM Students WHERE StudentID = '" + sId + "'";
	if (mysql_query(conn, del.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Data deleted successfully!" << endl;
	}
	Sleep(3000);
}

int main() {

	University u;

	MYSQL* conn;
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Logged in!" << endl;
	}
	Sleep(3000);

	bool exit = false;
	while (!exit) {
		system("cls");
		cout << "UNIVERSITY MANAGEMENT SYSTEM" << endl;
		cout << "-----------------------------" << endl;
		cout << "1. Add student data" << endl;
		cout << "2. Update student data" << endl; 
		cout << "3. Search student data" << endl;
		cout << "4. Show student data" << endl;
		cout << "5. Delete student data" << endl;
		cout << "6.Exit" << endl;
		int n;
		cout << "Enter choice:"; cin >> n;
		if (n == 1) {
			addStudent(conn, u);
		}
		else if (n == 2) {
			updateStudent(conn, u);
		}
		else if (n == 3) {
			searchStudent(conn);
		}
		else if (n == 4) {
			showRecord(conn);
		}
		else if (n == 5) {
			deleteStudent(conn);
		}
		else if (n == 6) {
			exit = true;
			cout << "EXITED!" << endl;
			Sleep(3000);
		}
		else {
			cout << "enter valid option" << endl;
		}
	}

	return 0;
}