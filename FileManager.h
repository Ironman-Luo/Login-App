//SPECIFICATION FILE (FileManager.h)
//Declare the abstract data type FileManager
//Author: Wei Luo
//Edit history:
// 4.9 Initial Version
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
#ifndef FILE_H
#define FILE_H

//Main Manager class for our Database system
class FileManager {
public:
	FileManager(string fileName); // Constructor
	~FileManager(); //Destructor
	void read_csv(); // will read data from csv file
	void update_csv(); //will update csv file with private member data
	int new_user_insert(vector<string> input); //function for new user registration 
	void update_password(string ID, string new_password); //Not used but will update_password
	void update_email(string ID, string new_email); //Not used but will update_email
	bool check_user(string login_id, string login_password); //function for login check
	int getNumberOfRows(); //get private member data's size
	string get_password_from_id(string ID); // retrieve password from ID
	vector<string> split(string str, string token); //function used in read_csv
private:
	string fileName;
	int num_rows;
	vector< vector<string> > data; //data storage
};
#endif

