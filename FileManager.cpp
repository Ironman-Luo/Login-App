//IMPLEMENTATION FILE (FileManager.h)
//Implement the abstract data type FileManager
//Author: Wei Luo
//Edit history:
// 4.9 Initial Version
#include "FileManager.h"

//Below are positions of features of each record.
const int id = 0;
const int username = 1;
const int password = 2;
const int email = 3;
const int DOB = 4;
const int activation = 5;//Not Used

//Initial read data from database
void FileManager::read_csv() {
	fstream fin;
	fin.open(fileName);
	string line, temp;
	FileManager::num_rows = 0;
	bool empty = true; //check if file is empty
	//get number of rows
	while (getline(fin, line)) {
		FileManager::num_rows++;
	}
	fin.close();

	//read data line by line
	fin.open(fileName);
	vector< vector<string> > result;
	for (int i = 0; i < num_rows; i++) {
		getline(fin, temp);
		if (temp.find_first_not_of(' ') != std::string::npos) empty = false;
		std::vector<std::string> str_vec = split(temp, ",");
		for (int j = 0; j < str_vec.size(); j++) {
			//erase all wierd characters including space
			str_vec[j].erase(std::remove(str_vec[j].begin(), str_vec[j].end(), '\r'), str_vec[j].end());
			str_vec[j].erase(std::remove(str_vec[j].begin(), str_vec[j].end(), '\t'), str_vec[j].end());
			str_vec[j].erase(std::remove(str_vec[j].begin(), str_vec[j].end(), '\n'), str_vec[j].end());
			str_vec[j].erase(std::remove(str_vec[j].begin(), str_vec[j].end(), ' '), str_vec[j].end());
		}
		result.push_back(str_vec);
	}
	fin.close();
	//If file is empty, create a single user called Admin
	if (empty == true) {
		std::vector<string> string_vec = split("0,Admin,password,Admin@bu.edu,9/9/2000,Activated", ",");
		FileManager::data.push_back(string_vec);
		FileManager::num_rows = 1;
	}
	else{
		FileManager::data = result;
	}
	}

//Destructor
FileManager::~FileManager() {
}
//Constructor
FileManager::FileManager(string fileName) {
	FileManager::fileName = fileName;
}

//split a string by token and save it to a vector
vector<string> FileManager::split(string str, string token) {
	vector<string>result;
	while (str.size()) {
		int index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}
//insert new user information and return ID for new user.
int FileManager::new_user_insert(vector<string> input) {
	input.insert(input.begin(), to_string(num_rows + 1));
	data.push_back(input);
	num_rows = data.size();
	return num_rows;
}

//Not used
void FileManager::update_password(string ID, string new_password) {
	for (int i = 0; i < num_rows; i++) {
		if (data[i][id] == ID) {
			data[i][password] = password;
			break;
		}
	}
}
//Not used
void FileManager::update_email(string ID, string new_email) {
	for (int i = 0; i < num_rows; i++) {
		if (data[i][id] == ID) {
			data[i][email] = new_email;
			break;
		}
	}
}

//After destroy window, update the csv file with current data
void FileManager::update_csv() {
	std::ofstream myfile;
	myfile.open("database.csv");
	for (int i = 0; i < FileManager::data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (j != data[i].size() - 1) {
				myfile << data[i][j] << ",";
			}
			else myfile << data[i][j];
		}
		myfile << "\n";
	}
}

//checker for login information. Search login_id in linear time. If information is not correct, return false.
//use a try catch method in order to avoid stoi() function throw exception in login ID is empty case. 
bool FileManager::check_user(string login_id, string login_password) {
	if (FileManager::num_rows == 0) return false;
	int x = 0;
	int y = 0;
	try {
		x = stoi(login_id);
		for (int i = 0; i < FileManager::data.size(); i++) {
			y = stoi(data[i][id]);
			if (x == y) {
				if (data[i][password].compare(login_password) == 0)return true;
				else {
					return false;
				}
			}
		}
	}
	catch (...) { return false; }
	return false;
}

//retrieve password from a given ID. if password is empty, it means ID is not in database.
string FileManager::get_password_from_id(string ID) {
	if (FileManager:: num_rows == 0) return "";
	int x = 0;
	try {
		x = stoi(ID);

		for (int i = 0; i < FileManager::data.size(); i++) {
			int y = stoi(data[i][id]);
			if (x == y) {
				return data[i][username];
			}

		}
	}
	catch (...) { return ""; }
	return "";
}
int FileManager::getNumberOfRows() {
	return num_rows;
}