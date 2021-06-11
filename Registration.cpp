#include "Registration.h"
void Registration::resize_users(USERS*& users, int& count) {
    USERS* new_user = new USERS[count * 2];
    for (int i = 0; i < count; i++) {
        new_user[i] = users[i];
    }
    delete[] users;
    users = new_user;
    count *= 2;
}
int Registration::count_users(string name_of_file) {
	ifstream file(name_of_file, ios::app);
    if (!file.is_open())
    {
        std::cout << "Error opening file"<<endl; 
        return -1;
    }
    string line;
    int count_of_users = 0;
    while (!file.eof()) {
        getline(file, line);
        count_of_users++;
    }
    file.close();
    this->all_users_count = count_of_users;
    return all_users_count;
}
void Registration::read_user(const string line, USERS& user) {
   
    string substring_name;
    string substring_email;
    string substring_password;

    int interval_pos = line.find(" ");
    substring_name = line.substr(0, interval_pos);
    user.set_username(substring_name);

    int first_interval_pos = interval_pos;
    interval_pos = line.find(" ", first_interval_pos + 1);
    substring_email = line.substr(first_interval_pos + 1, interval_pos);
    user.set_email(substring_email);

    int second_interval_pos = interval_pos;
    substring_password = line.substr(second_interval_pos + 1);
    user.set_password(substring_password);
}


void Registration::add_user(string name_of_file, USERS& user, USERS*& users, int& all_users_count, int& max_users_count) {
    all_users_count++;
    if (all_users_count >= max_users_count) {
        resize_users(users, max_users_count);
    }
    users[all_users_count - 1] = user;
    ofstream file(name_of_file, ios::app);
    file << user.get_username() << " " << user.get_password() << " " << user.get_email() << endl;
    file.close();
    cout << "Registration complete." << endl;
}

bool Registration::successful_login(const int users_count, const string username, const string password, const USERS* collection_users) {
    int user_index = find_user_index(users_count, username, collection_users);
    if (user_index != -1 || password == collection_users[user_index].get_password()) {
        cout << "Login successful." << endl;
        return true;
    }
    cout << "Username or password is incorrect." << endl;
    return false;
}
int Registration::find_user_index(const int users_count, const string username, const USERS* collection_users) {
    for (int i = 0; i < users_count; i++) {
        if (username==collection_users[i].get_username()) {
            return i;
        }
    }
    return -1;
}
bool Registration::username_is_taken(const int users_count, const string username, const USERS* collection_users) {
    for (int i = 0; i < users_count; i++) {
        if (username == collection_users[i].get_username()) {
            cout << "Username is taken." << endl;
            return true;
        }   
    }
    return false;
}
void Registration::new_password(const int users_count, const string username, USERS* collection_users) {
    /*string input_name;*/
    string input_mail;
    string input_password;
   /* cout << "Enter username: ";*/
  /*  cin >> input_name;*/
    for (int i = 0; i < users_count; i++) {
        if (username == collection_users[i].get_username()) {
            cout << "Username found." << endl;
            cout << endl;
            cout << "Enter email: ";
            cin >> input_mail;
            if (input_mail == collection_users[i].get_email()) {
                cout << "Email is correct." << endl;
                cout << endl;
                cout << "Enter new password: " << endl;
                cin >> input_password;
                collection_users[i].set_password(input_password);
                cout << "New password set." << endl;
                cout << endl;
                return;
            }
            else {
                cout << "Incorrect email." << endl;
                break;
            }
        }
        else {
            cout << "Incorrect username." << endl;
            break;
        }
    }
}
