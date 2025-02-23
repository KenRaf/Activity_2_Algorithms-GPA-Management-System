#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cctype>
#include <unordered_map>
#include <chrono>
#include <thread>

using namespace std;


// Structure for Student
struct Student {
    int id;
    string name;
    string year;
    string semester;
    string section;
    float gpa;
};

// Structure for Feedback
struct Feedback {
    int studentID;
    string message;
    string reply;
};

// Global Vectors
vector<Student> students;
vector<Feedback> feedbacks;

// Function Prototypes
void mainMenu();
void professorPanel();
void studentPanel();
void addStudent();
void viewStudents();
void sortByName();
void sortByGPA();
void binarySearchStudent();
void professorFeedback();
void studentFeedback();
void replyToFeedback();
void validateIntegerInput(int& input, int min, int max);
void validateFloatInput(float& input, float min, float max);
void formatYear(int& year, string& formattedYear);
void formatSemester(int& semester, string& formattedSemester);
string formatName(string name);
bool isValidID(int id, string name);
void clearInputBuffer();
void showLoadingAnimation(int duration);

// Function to display a simple loading animation
void showLoadingAnimation(int duration) {
    const char* loadingChars = "|/-\\";
    int loadingCharsCount = 4;
    for (int i = 0; i < duration; ++i) {
        cout << "\rLoading " << loadingChars[i % loadingCharsCount] << flush;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
    cout << "\r" << string(10, ' ') << "\r"; // Clear the loading animation
}

// Main Menu
void mainMenu() {
    while (true) {
        showLoadingAnimation(6);
        cout << "\n🏫 MAIN MENU 🏫\n";
        cout << "1. Professor Panel\n2. Student Panel\n3. Exit\n";
        int choice;
        validateIntegerInput(choice, 1, 3);

        switch (choice) {
            case 1: professorPanel(); break;
            case 2: studentPanel(); break;
            case 3: exit(0);
        }
    }
}
void replyToFeedback(unordered_map<int, string>& feedbacks);

// Professor Panel
void professorPanel() {
    while (true) {
        showLoadingAnimation(4);
        cout << "\n📚 PROFESSOR PANEL 📚\n";
        cout << "1. Add Student\n2. View Students\n3. Sort by Name\n4. Sort by GPA\n5. Search Student\n6. View Feedback\n7. Reply to Feedback\n8. Back to Main Menu\n";
        int choice;
        validateIntegerInput(choice, 1, 8);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: sortByName(); break;
            case 4: sortByGPA(); break;
            case 5: binarySearchStudent(); break;
            case 6: professorFeedback(); break;
            case 7: replyToFeedback(); break; 
            case 8: return;
        }
    }
}

// Student Panel
void studentPanel() {
    while (true) {
        showLoadingAnimation(4);
        cout << "\n🎓 STUDENT PANEL 🎓\n";
        cout << "1. View GPA\n2. Leave Feedback\n3. View & Reply to Feedback\n4. Back to Main Menu\n";
        int choice;
        validateIntegerInput(choice, 1, 4);

        switch (choice) {
            case 1: viewStudents(); break;
            case 2: studentFeedback(); break;
            case 3: professorFeedback(); break;
            case 4: return;
        }
    }
}

// Add Student
void addStudent() {
    Student s;
    showLoadingAnimation(3);
    cout << "\n📝 ADD STUDENT 📝\n";
    cout << "Enter Student ID (max 6 digits): ";
    validateIntegerInput(s.id, 1, 999999);

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, s.name);
    s.name = formatName(s.name);

    cout << "Enter Year (1-10): ";
    int year;
    validateIntegerInput(year, 1, 10);
    formatYear(year, s.year);

    cout << "Enter Semester (1-3): ";
    int semester;
    validateIntegerInput(semester, 1, 3);
    formatSemester(semester, s.semester);

    cout << "Enter Section: ";
    cin.ignore();
    getline(cin, s.section);

    cout << "Enter GPA (0.0 - 4.0): ";
    validateFloatInput(s.gpa, 0.0, 4.0);

    if (!isValidID(s.id, s.name)) {
        cout << "❌ Error: ID must match an existing name if duplicate.\n";
        return;
    }

    cout << "Adding student...\n";
    showLoadingAnimation(5);
    students.push_back(s);
    cout << "\n✅ Student Added Successfully!\n";
}

// View Students
void viewStudents() {
    cout << "Fetching all students...\n";
    showLoadingAnimation(5);

    if (students.empty()) {
        cout << "❌ No students added yet.\n";
        return;
    }
    cout << "\n========================================================================================\n";
    cout << "📋 All Students 📋:\n";
    for (auto& s : students) {
        cout << "\nID: " << s.id << ", Name: " << s.name << ", Year: " << s.year << ", Semester: " << s.semester << ", Section: " << s.section << ", GPA: " << s.gpa << "\n";
    }
    cout << "\n========================================================================================\n";
}
// Sorting Functions (User-defined)
void sortByName() {
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.name < b.name; });
    cout << "Sorting students by name...\n";
    showLoadingAnimation(2);
    cout << "✅ Students sorted by name.\n";
}
void sortByGPA() {
    sort(students.begin(), students.end(), [](Student a, Student b) { return a.gpa > b.gpa; });
    cout << "Sorting students by GPA...\n";
    showLoadingAnimation(2);
    cout << "✅ Students sorted by GPA.\n";
}

// Binary Search (User-defined)
void binarySearchStudent() {
    int id;
    cout << "Enter Student ID: ";
    validateIntegerInput(id, 1, 999999);

    cout << "Searching for student...\n";
    showLoadingAnimation(4);

    for (auto& s : students) {
        if (s.id == id) {
            cout << "\n========================================================================================\n";
            cout << "\nStudent Found!\n";
            cout << "\nID: " << s.id << ", Name: " << s.name << ", Year: " << s.year << ", Semester: " << s.semester << ", Section: " << s.section << ", GPA: " << s.gpa << "\n";
            cout << "\n========================================================================================\n";
            return;
        }
    }
    cout << "❌ Student not found.\n";
}

// Feedback System
void professorFeedback() {
    showLoadingAnimation(3);

    if (feedbacks.empty()) {
        cout << "❌ No feedback available.\n";
        return;
    }

    for (auto& f : feedbacks) {
        cout << "Student ID: " << f.studentID << " - Message: " << f.message;
        if (!f.reply.empty()) {
            cout << " | Reply: " << f.reply;
        }
        cout << "\n";
    }
}


// Leave Feedback
void studentFeedback() {
    int studentID;
    cout << "Enter Student ID: ";
    validateIntegerInput(studentID, 1, 999999);

    showLoadingAnimation(4);

    // Check if student exists
    bool found = false;
    for (auto& s : students) {
        if (s.id == studentID) {
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "❌ Error: Student ID does not exist.\n";
        return;
    }

    Feedback f;
    f.studentID = studentID;

    cout << "Enter Feedback: ";
    cin.ignore();
    getline(cin, f.message);

    feedbacks.push_back(f);
    cout << "Feedback submitted successfully! ✅\n";

    // Debugging: Confirm feedback is stored
    cout << "DEBUG: Feedback stored for ID " << studentID << ": " << f.message << endl;
}


// Reply to Feedback
void replyToFeedback() {
    int studentID;
    cout << "Enter Student ID to reply to: ";
    validateIntegerInput(studentID, 1, 999999);

    showLoadingAnimation(4);

    // Debugging: Show all stored feedback
    cout << "DEBUG: Currently stored feedbacks:\n";
    for (auto& f : feedbacks) {
        cout << "DEBUG: ID: " << f.studentID << " - " << f.message << endl;
    }

    for (auto& f : feedbacks) {
        if (f.studentID == studentID) {
            cout << "Existing Feedback: " << f.message << endl;
            if (!f.reply.empty()) {
                cout << "Current Reply: " << f.reply << endl;
            }

            cout << "Enter your reply: ";
            cin.ignore();
            getline(cin, f.reply);

            cout << "Reply added successfully! ✅\n";
            return;
        }
    }

    cout << "❌ Error: No feedback found for this Student ID.\n";
}



// Helper Functions
void validateIntegerInput(int& input, int min, int max) {
    string userInput;
    while (true) {
        cin >> userInput;

        // Check if input contains non-digit characters
        bool isValid = true;
        for (char c : userInput) {
            if (!isdigit(c)) {
                isValid = false;
                break;
            }
        }

        // Convert to integer if valid
        if (isValid) {
            input = stoi(userInput);
            if (input >= min && input <= max) return;
        }

        // Invalid input, ask again
        cout << "❌ Invalid input. Try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void validateFloatInput(float& input, float min, float max) {
    while (!(cin >> input) || input < min || input > max) {
        cout << "❌ Invalid input. Try again: ";
        cin.clear();
        clearInputBuffer();
    }
}
void formatYear(int& year, string& formattedYear) {
    string suffix = (year == 1) ? "st" : (year == 2) ? "nd" : (year == 3) ? "rd" : "th";
    formattedYear = to_string(year) + suffix;
}
void formatSemester(int& semester, string& formattedSemester) {
    formattedSemester = to_string(semester) + ((semester == 1) ? "st" : (semester == 2) ? "nd" : "rd");
}
string formatName(string name) {
    for (size_t i = 0; i < name.length(); i++)
        name[i] = (i == 0 || name[i - 1] == ' ') ? toupper(name[i]) : tolower(name[i]);
    return name;
}
bool isValidID(int id, string name) {
    for (auto& s : students) {
        if (s.id == id && s.name != name) return false;
    }
    return true;
}
void clearInputBuffer() { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

int main() { 
    mainMenu();
    return 0; 
}
