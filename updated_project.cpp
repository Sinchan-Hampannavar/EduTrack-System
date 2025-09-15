#include <bits/stdc++.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
using namespace std;

class PortalSystem
{
private:
    string password, email, number, role, date, month, year;
    string loggedInUser;                                                                      // Stores currently logged-in username
    string pass;                                                                              // stores entered password temporarily
    vector<string> defaultSubjects = {"Web Development", "NLP", "Cloud", "Machine Learning"}; // Default subjects

    void waiting(int times = 10)
    {
        for (int i = 0; i < times; i++)
        {
            Sleep(120);
            cout << ".";
        }
        cout << endl;
    }

    string encryption(const string &pw)
    {
        string enc_pass;
        for (size_t i = 0; i < pw.size(); i++)
        {
            enc_pass += to_string((int)pw[i] + 12);
            if (i + 1 < pw.size())
                enc_pass += '-';
        }
        return enc_pass;
    }

    string decrypt(const string &enc_pass)
    {
        stringstream ss(enc_pass);
        string token, result;
        while (getline(ss, token, '-'))
        {
            if (token.empty())
                continue;
            int num = stoi(token) - 12;
            result.push_back((char)num);
        }
        return result;
    }

    bool validMail(const string &email)
    {
        int At = -1, Dot = -1;
        for (int i = 0; i < (int)email.length(); i++)
        {
            if (email[i] == '@')
                At = i;
            else if (email[i] == '.')
            {
                Dot = i;
                break;
            }
        }
        return !(At == -1 || Dot == -1 || Dot - At <= 1 || Dot >= email.length() - 1 || email.length() <= 4);
    }

public:
    void homepage();
    void createAccount();
    void login();
    void studentMenu();
    void teacherMenu();
    void details();
    void changePassword();
    void logout();

    // Marks & Attendance
    void viewMarks();
    void updateMarks();
    void deleteMarks();
    void viewAttendance();
    void manageAttendance();
    void deleteAttendance();
    void searchStudent();
    void generateReport();
};

// -------------------- HOMEPAGE --------------------
void PortalSystem::homepage()
{
    system("cls");
    cout << "\n\t     _________________________________\n";
    cout << "\t    |       WELCOME TO EDUNEST PORTAL   |\n";
    cout << "\t    |___________________________________|\n\n";
    cout << "\t\t1. Create Account\n\t\t2. Login\n\t\t3. Exit\n\t\t-> ";
    int x;
    cin >> x;
    if (x == 1)
        createAccount();
    else if (x == 2)
        login();
    else if (x == 3)
        _exit(0);
    else
    {
        cout << "Invalid option\n";
        Sleep(500);
        homepage();
    }
}

// -------------------- CREATE ACCOUNT --------------------
void PortalSystem::createAccount()
{
    system("cls");
    string name;
    cout << "\n\tCREATE ACCOUNT\n";
    cout << "Enter username (no spaces): ";
    cin >> name;
    loggedInUser = name;

    cout << "Role (student/teacher): ";
    cin >> role;
    if (role != "student" && role != "teacher")
        role = "student";

    int d, m, y;
    cout << "DOB (Day Month Year): ";
    cin >> d >> m >> y;
    date = to_string(d);
    month = to_string(m);
    year = to_string(y);

    cout << "Email: ";
    cin >> email;
    while (!validMail(email))
    {
        cout << "Invalid email. Enter again: ";
        cin >> email;
    }

    cout << "Mobile Number: ";
    cin >> number;

    string password;
    char ch;
    cout << "Password: ";
    password = "";
    ch = _getch();
    while (ch != 13)
    {
        password.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    pass = password;
    string enc = encryption(password);

    fstream file("users.txt", ios::app);
    file << name << " " << enc << " " << number << " " << email << " " << date << " " << month << " " << year << " " << role << "\n";
    file.close();

    // -------------------- Pre-fill marks and attendance for new student --------------------
    if (role == "student")
    {
        fstream mfile("marks.txt", ios::app);
        fstream afile("attendance.txt", ios::app);
        for (string &subj : defaultSubjects)
        {
            mfile << name << " " << subj << " " << 0 << "\n"; // 0 marks
            afile << name << " " << subj << " " << 0 << "\n"; // 0% attendance
        }
        mfile.close();
        afile.close();
    }
    // -------------------------------------------------------------------

    cout << "\nAccount Created Successfully.\n";
    system("pause");
    homepage();
}

// -------------------- LOGIN --------------------
void PortalSystem::login()
{
    system("cls");
    cout << "\nLOGIN PAGE\n";
    string name;
    cout << "Username: ";
    cin >> name;

    cout << "Password: ";
    pass = "";
    char ch = _getch();

    while (ch != 13)
    { // Enter key
        if (ch == 8)
        { // Backspace
            if (!pass.empty())
            {
                pass.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pass.push_back(ch);
            cout << '*';
        }
        ch = _getch();
    }

    ifstream file("users.txt");
    if (!file)
    {
        cout << "No users found. Create account first.\n";
        system("pause");
        homepage();
        return;
    }

    string line;
    bool flag = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string f, p_enc, num, mail, dd, mm, yy, r;
        ss >> f >> p_enc >> num >> mail >> dd >> mm >> yy >> r;

        // compare decrypted password
        if (f == name && decrypt(p_enc) == pass)
        {
            loggedInUser = f;
            number = num;
            email = mail;
            date = dd;
            month = mm;
            year = yy;
            role = r;
            flag = true;
            break;
        }
    }
    file.close();

    cout << "Verifying";
    waiting();
    if (flag)
    {
        cout << "Login Successful!\n";
        Sleep(500);
        if (role == "student")
            studentMenu();
        else
            teacherMenu();
    }
    else
    {
        cout << "Invalid credentials\n";
        system("pause");
        homepage();
    }
}

// -------------------- STUDENT MENU --------------------
void PortalSystem::studentMenu()
{
    system("cls");
    cout << "\nWelcome Student: " << loggedInUser << "\n";
    cout << "1. View Marks\n2. View Attendance\n3. Change Password\n4. Account Details\n5. Download Report\n6. Logout\n-> ";
    int opt;
    cin >> opt;
    switch (opt)
    {
    case 1:
        viewMarks();
        break;
    case 2:
        viewAttendance();
        break;
    case 3:
        changePassword();
        break;
    case 4:
        details();
        break;
    case 5:
        generateReport();
        break;
    case 6:
        logout();
        break;
    default:
        studentMenu();
    }
}

// -------------------- TEACHER MENU --------------------
void PortalSystem::teacherMenu()
{
    system("cls");
    cout << "\nWelcome Teacher: " << loggedInUser << "\n";
    cout << "1. Enter/Update Marks\n2. Delete Marks Entry\n3. View All Marks\n";
    cout << "4. Manage Attendance\n5. Delete Attendance Entry\n6. Search Student\n";
    cout << "7. Change Password\n8. Account Details\n9. Generate Class Report\n10. Logout\n-> ";
    int opt;
    cin >> opt;
    switch (opt)
    {
    case 1:
        updateMarks();
        break;
    case 2:
        deleteMarks();
        break;
    case 3:
        viewMarks();
        break;
    case 4:
        manageAttendance();
        break;
    case 5:
        deleteAttendance();
        break;
    case 6:
        searchStudent();
        break;
    case 7:
        changePassword();
        break;
    case 8:
        details();
        break;
    case 9:
        generateReport();
        break;
    case 10:
        logout();
        break;
    default:
        teacherMenu();
    }
}

// -------------------- ACCOUNT FUNCTIONS --------------------
void PortalSystem::details()
{
    system("cls");
    cout << "\nAccount Details\nUsername: " << loggedInUser << "\nEmail: " << email;
    cout << "\nContact: " << number << "\nDOB: " << date << "/" << month << "/" << year;
    cout << "\nRole: " << role << "\nPassword: " << pass << "\n";
    system("pause");
    role == "student" ? studentMenu() : teacherMenu();
}

void PortalSystem::changePassword()
{
    system("cls");
    string oldpass, newpass, conf;
    cout << "Old password: ";
    cin >> oldpass;
    if (oldpass == pass)
    {
        cout << "New password: ";
        cin >> newpass;
        cout << "Confirm new password: ";
        cin >> conf;
        if (newpass == conf)
        {
            fstream file("users.txt", ios::in);
            fstream temp("temp.txt", ios::out);
            string f, p, num, mail, dd, mm, yy, r;
            while (file >> f >> p >> num >> mail >> dd >> mm >> yy >> r)
            {
                if (f == loggedInUser)
                    temp << f << " " << encryption(newpass) << " " << num << " " << mail << " " << dd << " " << mm << " " << yy << " " << r << "\n";
                else
                    temp << f << " " << p << " " << num << " " << mail << " " << dd << " " << mm << " " << yy << " " << r << "\n";
            }
            file.close();
            temp.close();
            remove("users.txt");
            rename("temp.txt", "users.txt");
            cout << "Password changed. Login again.\n";
            system("pause");
            logout();
        }
        else
        {
            cout << "Mismatch. Try again.\n";
            system("pause");
            changePassword();
        }
    }
    else
    {
        cout << "Wrong password. Try again.\n";
        system("pause");
        changePassword();
    }
}

void PortalSystem::logout()
{
    password = email = number = role = date = month = year = pass = "";
    loggedInUser = "";
    cout << "Logging out";
    waiting(6);
    homepage();
}

// -------------------- MARKS --------------------
void PortalSystem::viewMarks()
{
    system("cls");
    fstream file("marks.txt", ios::in);
    if (!file)
    {
        cout << "No marks recorded.\n";
        system("pause");
        role == "student" ? studentMenu() : teacherMenu();
        return;
    }
    string uname, subj;
    int mk;
    bool found = false;
    cout << "---- Marks ----\n";
    while (file >> uname >> subj >> mk)
    {
        if (role == "student" && uname == loggedInUser)
        {
            cout << subj << " : " << mk << "\n";
            found = true;
        }
        else if (role == "teacher")
        {
            cout << uname << " | " << subj << " : " << mk << "\n";
            found = true;
        }
    }
    file.close();
    if (!found)
        cout << "No marks found.\n";
    system("pause");
    role == "student" ? studentMenu() : teacherMenu();
}

void PortalSystem::updateMarks()
{
    string uname, subj;
    int mk;
    cout << "Student username: ";
    cin >> uname;
    cout << "Subject: ";
    cin >> subj;
    cout << "Marks: ";
    cin >> mk;
    fstream file("marks.txt", ios::in);
    vector<tuple<string, string, int>> rows;
    bool updated = false;
    if (file)
    {
        string u, s;
        int m;
        while (file >> u >> s >> m)
        {
            if (u == uname && s == subj)
            {
                rows.emplace_back(u, s, mk);
                updated = true;
            }
            else
                rows.emplace_back(u, s, m);
        }
        file.close();
    }
    if (!updated)
        rows.emplace_back(uname, subj, mk);
    fstream out("marks.txt", ios::out);
    for (auto &t : rows)
        out << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
    out.close();
    cout << (updated ? "Marks updated.\n" : "Marks added.\n");
    system("pause");
    teacherMenu();
}

// -------------------- ATTENDANCE --------------------
void PortalSystem::viewAttendance()
{
    system("cls");
    fstream file("attendance.txt", ios::in);
    if (!file)
    {
        cout << "No attendance recorded.\n";
        system("pause");
        role == "student" ? studentMenu() : teacherMenu();
        return;
    }
    string uname, subj;
    int att;
    bool found = false;
    cout << "---- Attendance ----\n";
    while (file >> uname >> subj >> att)
    {
        if (role == "student" && uname == loggedInUser)
        {
            cout << subj << " : " << att << "%\n";
            found = true;
        }
        else if (role == "teacher")
        {
            cout << uname << " | " << subj << " : " << att << "%\n";
            found = true;
        }
    }
    file.close();
    if (!found)
        cout << "No attendance found.\n";
    system("pause");
    role == "student" ? studentMenu() : teacherMenu();
}

void PortalSystem::manageAttendance()
{
    string uname, subj;
    int att;
    cout << "Student username: ";
    cin >> uname;
    cout << "Subject: ";
    cin >> subj;
    cout << "Attendance %: ";
    cin >> att;
    fstream file("attendance.txt", ios::in);
    vector<tuple<string, string, int>> rows;
    bool updated = false;
    if (file)
    {
        string u, s;
        int a;
        while (file >> u >> s >> a)
        {
            if (u == uname && s == subj)
            {
                rows.emplace_back(u, s, att);
                updated = true;
            }
            else
                rows.emplace_back(u, s, a);
        }
        file.close();
    }
    if (!updated)
        rows.emplace_back(uname, subj, att);
    fstream out("attendance.txt", ios::out);
    for (auto &t : rows)
        out << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << "\n";
    out.close();
    cout << (updated ? "Updated!\n" : "Added!\n");
    system("pause");
    teacherMenu();
}

// -------------------- DELETE --------------------
void PortalSystem::deleteMarks()
{
    string uname, subj;
    cout << "Student username: ";
    cin >> uname;
    cout << "Subject: ";
    cin >> subj;
    fstream file("marks.txt", ios::in);
    if (!file)
    {
        cout << "No marks file.\n";
        system("pause");
        teacherMenu();
        return;
    }
    fstream temp("temp.txt", ios::out);
    string u, s;
    int m;
    bool deleted = false;
    while (file >> u >> s >> m)
    {
        if (u == uname && s == subj)
        {
            deleted = true;
            continue;
        }
        temp << u << " " << s << " " << m << "\n";
    }
    file.close();
    temp.close();
    remove("marks.txt");
    rename("temp.txt", "marks.txt");
    cout << (deleted ? "Deleted.\n" : "No matching entry.\n");
    system("pause");
    teacherMenu();
}

void PortalSystem::deleteAttendance()
{
    string uname, subj;
    cout << "Student username: ";
    cin >> uname;
    cout << "Subject: ";
    cin >> subj;
    fstream file("attendance.txt", ios::in);
    if (!file)
    {
        cout << "No attendance file.\n";
        system("pause");
        teacherMenu();
        return;
    }
    fstream temp("temp.txt", ios::out);
    string u, s;
    int a;
    bool deleted = false;
    while (file >> u >> s >> a)
    {
        if (u == uname && s == subj)
        {
            deleted = true;
            continue;
        }
        temp << u << " " << s << " " << a << "\n";
    }
    file.close();
    temp.close();
    remove("attendance.txt");
    rename("temp.txt", "attendance.txt");
    cout << (deleted ? "Deleted.\n" : "No matching entry.\n");
    system("pause");
    teacherMenu();
}

// -------------------- SEARCH STUDENT --------------------
void PortalSystem::searchStudent()
{
    string uname;
    cout << "Student username: ";
    cin >> uname;
    fstream file("users.txt", ios::in);
    if (!file)
    {
        cout << "No users.\n";
        system("pause");
        teacherMenu();
        return;
    }
    string f, p, num, mail, dd, mm, yy, r;
    bool found = false;
    while (file >> f >> p >> num >> mail >> dd >> mm >> yy >> r)
    {
        if (f == uname)
        {
            cout << "Username: " << f << "\nEmail: " << mail << "\nContact: " << num << "\nDOB: " << dd << "/" << mm << "/" << yy << "\nRole: " << r << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found)
        cout << "No student found.\n";
    system("pause");
    teacherMenu();
}

// -------------------- REPORT --------------------
void PortalSystem::generateReport()
{
    if (role == "student")
    {
        system("cls");
        cout << "\nStudent Report for " << loggedInUser << "\n\n";
        fstream mfile("marks.txt");
        fstream afile("attendance.txt");
        string u, subj;
        int mk, att;
        bool found = false;
        while (mfile >> u >> subj >> mk)
        {
            if (u == loggedInUser)
            {
                cout << subj << " Marks: " << mk << "\n";
                found = true;
            }
        }
        while (afile >> u >> subj >> att)
        {
            if (u == loggedInUser)
            {
                cout << subj << " Attendance: " << att << "%\n";
                found = true;
            }
        }
        mfile.close();
        afile.close();
        if (!found)
            cout << "No records yet.\n";
        system("pause");
        studentMenu();
    }
    else
    {
        ifstream users("users.txt");
        if (!users)
        {
            cout << "No users.\n";
            system("pause");
            teacherMenu();
            return;
        }
        string f, p, num, mail, dd, mm, yy, r;
        vector<string> students;
        while (users >> f >> p >> num >> mail >> dd >> mm >> yy >> r)
            if (r == "student")
                students.push_back(f);
        users.close();

        unordered_map<string, vector<int>> marks_map;
        ifstream mfile("marks.txt");
        string u, subj;
        int mk;
        while (mfile >> u >> subj >> mk)
            marks_map[u].push_back(mk);
        mfile.close();

        unordered_map<string, vector<int>> att_map;
        ifstream afile("attendance.txt");
        int att;
        while (afile >> u >> subj >> att)
            att_map[u].push_back(att);
        afile.close();

        ofstream out("class_report.txt");
        out << "Class Report\n\n";
        for (auto &s : students)
        {
            out << "Student: " << s << "\n";
            if (marks_map.count(s))
            {
                double sum = 0;
                for (int v : marks_map[s])
                    sum += v;
                out << " Avg Marks: " << fixed << setprecision(2) << sum / marks_map[s].size() << "\n";
            }
            else
                out << " Avg Marks: N/A\n";
            if (att_map.count(s))
            {
                double sum = 0;
                for (int v : att_map[s])
                    sum += v;
                out << " Avg Attendance: " << fixed << setprecision(2) << sum / att_map[s].size() << "%\n";
            }
            else
                out << " Avg Attendance: N/A\n";
            out << "\n";
        }
        out.close();
        cout << "Class report saved.\n";
        system("pause");
        teacherMenu();
    }
}

// -------------------- MAIN --------------------
int main()
{
    PortalSystem portal;
    portal.homepage();
    return 0;
}
