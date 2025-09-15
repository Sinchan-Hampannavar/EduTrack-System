# EduTrack

EduTrack is a **student and course management system** built with C++ that implements **Object-Oriented Programming (OOP) concepts**. It allows students and teachers to **manage courses, marks, and attendance efficiently** through a secure login system.

---

## Features

### User Management
- **Create Account:** Students and teachers can register with email, contact number, DOB, and password.  
- **Login/Logout:** Secure login system with password encryption.  
- **Role-Based Access Control (RBAC):** Students and teachers have separate menus and functionalities.  

### Student Features
- **View Marks:** Check marks for all subjects.  
- **View Attendance:** See attendance percentages per subject.  
- **Generate Report:** Download personal report of marks and attendance.  
- **Change Password:** Securely update account password.  
- **Account Details:** View personal information including email, contact, and DOB.  

### Teacher Features
- **Add/Update Marks:** Enter or modify marks for students.  
- **Delete Marks Entry:** Remove incorrect marks entries.  
- **Manage Attendance:** Add or update student attendance.  
- **Delete Attendance Entry:** Remove attendance records if needed.  
- **Search Student:** Look up student details by username.  
- **Generate Class Report:** Create a report summarizing average marks and attendance for the class.  

### Security
- **Password Encryption & Decryption:** Protects user passwords in storage.  
- **Email Validation:** Ensures correct email format during registration.  
- **Role-Based Access Control (RBAC):** Restricts menu options and actions based on user role (student/teacher).  

---

### File-Based Storage
User, marks, and attendance data are stored in text files:  
- `users.txt` – stores registered user information.  
- `marks.txt` – stores marks for students.  
- `attendance.txt` – stores attendance records.  
- `class_report.txt` – auto-generated class report (teacher functionality).  

---

## Tech Stack
- **Language:** C++  
- **Libraries:** `<iostream>`, `<fstream>`, `<vector>`, `<string>`, `<sstream>`, `<windows.h>`, `<conio.h>`

## Screenshots

### Homepage
![Homepage](images/homepage.png)

### Student Menu
![Student Menu](images/student_menu.png)

### Teacher Menu
![Teacher Menu](images/teacher_menu.png)

