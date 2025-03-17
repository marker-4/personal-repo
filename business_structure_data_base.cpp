//BUSINESS STRUCTURE Data Base simulation: Ali Haidar + Braeden Marker
#include <iostream>
#include <string>
using namespace std;

const string delimiters = " ,./:;?!";

struct Employee {
    string title; //person attributes
    string frstNme;
    string lstNme;
    string emID;
    int age;
    int salary;
    int yrsServed;
    int numSubords;
    int lvl;

    //Ptrs to immediate subordinates
    Employee* left;
    Employee* right;

    //Constructor
    Employee(string t, string f, string l, string ID, int a, int sal, int yrs) {
        title = t;
        frstNme = f;
        lstNme = l;
        emID = ID;
        age = a;
        salary = sal;
        yrsServed = yrs;
        numSubords = 0;
        left = nullptr;
        right = nullptr;
        lvl = -1;
    }

    Employee(string f, string l, string ID, int a, int sal, int yrs) {
        title = "CEO";
        frstNme = f;
        lstNme = l;
        emID = ID;
        age = a;
        salary = sal;
        yrsServed = yrs;
        numSubords = 0;
        lvl = 0;
    }

};


class Office {
private:
    Employee* root;
    int numEmployees;

public:
    Office() {
        root = nullptr;
        numEmployees = 0;
    }
    
    void treeToArray(Employee* allEmps[], Employee* emp, int& i) {
        if (emp == nullptr) {
            return;
        }
        treeToArray(allEmps, emp->left, i);
        allEmps[i++] = emp;
        treeToArray(allEmps, emp->right, i);
        

    }

    Employee* getJob(string title, Employee* temp) { // if job is in Office, returns job pointer, else returns nullptr
        if (temp == nullptr) { 
            return nullptr;
        }
        
        if (title == "None") { //case where replacing CEO
            return root;
        }

        if (temp->title == title) { 
            return temp;
        }
        
        
        Employee* leftResult = getJob(title, temp->left);
        if (leftResult != nullptr) { 
            return leftResult;
        }
        
        return getJob(title, temp->right); 
    }

    bool isEmpty() {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

    void swap(Employee*& a, Employee*& b) {
        Employee* temp = a;
        a = b;
        b = temp;
    }

    int minSize(string s1, string s2) {
        int sze1 = s1.size();
        int sze2 = s2.size();
        if (sze1 < sze2) {
            return sze1;
        } else {
            return sze2;
        }     
    }

    void rmvDelims(string &str) { //removes delimiters and changes uppercase to lowercase
        int sze = str.size();
        for (int i = 0; i < sze; i++) {
            for (long unsigned int j = 0; j < delimiters.size(); j++) {
                if (64 < str[i] && str[i] < 91) { //controls capitals
                    str[i] += 32;
                }

                if (str[i] == delimiters[j]) {
                    str = str.substr(0, i) + str.substr(i+1);
                    sze--;
                    i--;
                }
            }
        }
    }

    int before(string t1, string t2) { //1 = t1 comes before t2; 0 = t2 comes before t1;

        rmvDelims(t1);
        rmvDelims(t2);

        int minSze = minSize(t1, t2);
        int sze1 = t1.size(), sze2 = t2.size();

        int i = 0;
        while (i < minSze) {
            if (t1[i] < t2[i]) {
                return 1;
            }
            if (t1[i] > t2[i]) {
                return 0;
            }
            i++;
        }

        if (sze2 > sze1) {
            return 1;
        }
        return 0;
    }


    void newPosition(string bossTitle, string t, string f, string l, string ID, int a, int sal, int yrs) { //first added position MUST be CEO

        if (isEmpty()) {
        cout << "Added employee (" << f << ", " << l << ") as the CEO" << endl;
        root = new Employee(f, l, ID, a, sal, yrs);
        numEmployees++;
        return;
        } 

        Employee* newEmp = new Employee(t, f, l, ID, a, sal, yrs);
        Employee* boss = getJob(bossTitle, root);

        if (boss == nullptr) {
            cout << "Can't add employee; No position in office matches Boss Position. \n";
            return;
        }

        if (boss->title == newEmp->title) { //case where replacing CEO
            string choice;
            cout << "Are you sure you want to replace the current CEO? (\"Y\" or \"N\")\n";
            cin >> choice;

            if (choice == "Y") {
                newEmp->left = root->left;
                newEmp->right = root->right;
                delete root;
                root = newEmp;
                cout << "Replacement successful! New CEO is: " << newEmp->frstNme << " " << newEmp->lstNme << endl;
            } else {
                cout << "Cancelled replacement." << endl;
                return;
            }
            
        }
        int bossSubs = boss->numSubords;

        if (bossSubs == 0) {
            boss->left = newEmp;
            boss->numSubords++;
        } else if (bossSubs == 1) {
            boss->right = newEmp;
            boss->numSubords++;
        } else {
            string firstNameToReplace;
            string lastNameToReplace;
            cout << "That boss has 2 subordinates, which one should be replaced? First name: ";
            cin >> firstNameToReplace;
            cout << "Last name: ";
            cin >> lastNameToReplace;
            
            Employee* empToReplace;
            bool replaceLeft; //true means replace boss->left, false means replace boss->right
            if (firstNameToReplace == boss->left->frstNme) {
                if (lastNameToReplace == boss->left->lstNme) {
                    empToReplace = boss->left;
                    replaceLeft = true;
                }
            } else {
                empToReplace = boss->right;
                replaceLeft = false;
            }

            newEmp->left = empToReplace->left;
            newEmp->right = empToReplace->right;

            if (replaceLeft) {
                boss->left = newEmp;
            } else {
                boss->right = newEmp;
            }
            return;
        }
        numEmployees++;
    }

    void searchInt(string type) { 
        Employee* empList[numEmployees];
        int index = 0;
        treeToArray(empList, root, index);

        if (type == "Age") { //start search by Age
            int age;
            cout << "Enter the age you would like to search: ";
            cin >> age;
            Employee* empsWithAge[numEmployees];
            
            int numEmpsWithAge = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->age == age) {
                    empsWithAge[numEmpsWithAge++] = empList[i];
                }
            }

            if (numEmpsWithAge == 0) { //no employees meet criteria
                cout << "No employees found with age " << age << endl;
            } else if (numEmpsWithAge == 1) { //only one employee meets criteria
                string frst = empsWithAge[0]->frstNme;
                string lst = empsWithAge[0]->lstNme;

                cout << "Unique Search; 1 employee found with age " << age << ": " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with age " << age << ": " << endl;
                for (int i = 0; i < numEmpsWithAge - 1; i++) {
                    Employee* curEmp = empsWithAge[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithAge[numEmpsWithAge-1]->frstNme + " " + empsWithAge[numEmpsWithAge-1]->lstNme;
                cout << name;
            }

        } // end sorting by Age
        
        if (type == "Years Served") { //start sorting by Years Served 
            int yrsServed;
            cout << "Enter the Years Served you would like to search: ";
            cin >> yrsServed;
            Employee* empsWithYrsServed[numEmployees];
            
            int numEmpsWithYrsServed = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->yrsServed == yrsServed) {
                    empsWithYrsServed[numEmpsWithYrsServed++] = empList[i];
                }
            }

            if (numEmpsWithYrsServed == 0) { //no employees meet criteria
                cout << "No employees found with " << yrsServed << " years served." << endl;
            } else if (numEmpsWithYrsServed == 1) { //only one employee meets criteria
                string frst = empsWithYrsServed[0]->frstNme;
                string lst = empsWithYrsServed[0]->lstNme;

                cout << "Unique Search; 1 employee found with " << yrsServed << " years served: " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with " << yrsServed << " years served: " << endl;
                for (int i = 0; i < numEmpsWithYrsServed - 1; i++) {
                    Employee* curEmp = empsWithYrsServed[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithYrsServed[numEmpsWithYrsServed-1]->frstNme + " " + empsWithYrsServed[numEmpsWithYrsServed-1]->lstNme;
                cout << name;
            }

        } // End sorting by Years Served
        
    }

    void searchStr(string type) {
        Employee* empList[numEmployees];
        int index = 0;
        treeToArray(empList, root, index);

        if (type == "First Name") { //start sorting by first name
            string frstNme;
            cout << "Enter the first name you would like to search: ";
            cin >> frstNme;

            Employee* empsWithFrstNme[numEmployees];

            int numEmpsWithFrstNme = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->frstNme == frstNme) {
                    empsWithFrstNme[numEmpsWithFrstNme++] = empList[i];
                }
            }

            if (numEmpsWithFrstNme == 0) { //no employees meet criteria
                cout << "No employees found with first name " << frstNme << "." << endl;
            } else if (numEmpsWithFrstNme == 1) { //only one employee meets criteria
                string frst = empsWithFrstNme[0]->frstNme;
                string lst = empsWithFrstNme[0]->lstNme;

                cout << "Unique Search; 1 employee found with first name " << frstNme << ": " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with first name " << frstNme << ": " << endl;
                for (int i = 0; i < numEmpsWithFrstNme - 1; i++) {
                    Employee* curEmp = empsWithFrstNme[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithFrstNme[numEmpsWithFrstNme-1]->frstNme + " " + empsWithFrstNme[numEmpsWithFrstNme-1]->lstNme;
                cout << name;
            }
        } //end searching by first name

        if (type == "Last Name") { //start sorting by last name
            string lstNme;
            cout << "Enter the last name you would like to search: ";
            cin >> lstNme;

            Employee* empsWithLstNme[numEmployees];

            int numEmpsWithLstNme = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->lstNme == lstNme) {
                    empsWithLstNme[numEmpsWithLstNme++] = empList[i];
                }
            }

            if (numEmpsWithLstNme == 0) { //no employees meet criteria
                cout << "No employees found with last name " << lstNme << "." << endl;
            } else if (numEmpsWithLstNme == 1) { //only one employee meets criteria
                string frst = empsWithLstNme[0]->lstNme;
                string lst = empsWithLstNme[0]->lstNme;

                cout << "Unique Search; 1 employee found with last name " << lstNme << ": " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with last name " << lstNme << ": " << endl;
                for (int i = 0; i < numEmpsWithLstNme - 1; i++) {
                    Employee* curEmp = empsWithLstNme[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithLstNme[numEmpsWithLstNme-1]->lstNme + " " + empsWithLstNme[numEmpsWithLstNme-1]->lstNme;
                cout << name;
            }
        } //end searching by last name name

        if (type == "Job Title") { //start searching by job title name
            string title;
            cout << "Enter the job title you would like to search: ";
            cin >> title;

            Employee* empsWithTitle[numEmployees];

            int numEmpsWithTitle = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->title == title) {
                    empsWithTitle[numEmpsWithTitle++] = empList[i];
                }
            }

            if (numEmpsWithTitle == 0) { //no employees meet criteria
                cout << "No employees found with Job Title " << title << "." << endl;
            } else if (numEmpsWithTitle == 1) { //only one employee meets criteria
                string frst = empsWithTitle[0]->title;
                string lst = empsWithTitle[0]->lstNme;

                cout << "Unique Search; 1 employee found with Job title " << title << ": " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with Job title " << title << ": " << endl;
                for (int i = 0; i < numEmpsWithTitle - 1; i++) {
                    Employee* curEmp = empsWithTitle[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithTitle[numEmpsWithTitle-1]->title + " " + empsWithTitle[numEmpsWithTitle-1]->lstNme;
                cout << name;
            }
        } //end searching by Job Title

        if (type == "Employee ID") { //start searching by employee ID
            string emID;
            cout << "Enter the Employee ID you would like to search (EIDXXX): ";
            cin >> emID;

            Employee* empsWithEmID[numEmployees];

            int numEmpsWithEmID = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (empList[i]->emID == emID) {
                    empsWithEmID[numEmpsWithEmID++] = empList[i];
                }
            }

            if (numEmpsWithEmID == 0) { //no employees meet criteria
                cout << "No employees found with Employee ID " << emID << "." << endl;
            } else if (numEmpsWithEmID == 1) { //only one employee meets criteria
                string frst = empsWithEmID[0]->emID;
                string lst = empsWithEmID[0]->lstNme;

                cout << "Unique Search; 1 employee found with Employee ID " << emID << ": " << frst << " " << lst << endl;
            } else { //more than one employee meets criteria
                string name;
                cout << "Multiple Employees found with Employee ID " << emID << ": " << endl;
                for (int i = 0; i < numEmpsWithEmID - 1; i++) {
                    Employee* curEmp = empsWithEmID[i];
                    name = curEmp->frstNme + " " + curEmp->lstNme;
                    cout << name << ", ";
                }
                name = empsWithEmID[numEmpsWithEmID-1]->emID + " " + empsWithEmID[numEmpsWithEmID-1]->lstNme;
                cout << name;
            }
        } //end searching by employee ID

    }

    void rmvEmp(string title) { //takes Job position and gives an error message if the emp doesn't exist, else removes them and changes tree accordingly
        Employee* empToDelete = getJob(title, root);

        if (empToDelete == nullptr) {
            cout << "No employee found with that Job Title!\n";
        } else if (empToDelete->left == nullptr && empToDelete->right == nullptr && title != "CEO") {
            string bossTitle;
            cout << "What is the boss of this employee's Job Title?\n";
            cin >> bossTitle;
            Employee* boss = getJob(bossTitle, root);
            
            bool left;
            if (boss->left == empToDelete) {
                left = true;
            } else if (boss->right == empToDelete) {
                left = false;
            } else {
                cout << "This boss does not have this employee! Try again.\n";
                return;
            }

            if (left) {
                boss->left == nullptr;
            } else if (!left) {
                boss->right == nullptr;
            }

            delete empToDelete;
        } else {
            string name = empToDelete->frstNme + " " + empToDelete->lstNme;
            empToDelete->age = 0;
            empToDelete->emID = "EMPTY_POSITION";
            empToDelete->frstNme = "EMPTY_POSITION";
            empToDelete->lstNme = "EMPTY_POSITION";
            empToDelete->salary = 0;
            empToDelete->yrsServed = 0;
            cout << "Employee " << name << " has been removed.\n";
        }
    }  

    void sortInt(string type) { //sorts all employees by integer attributes
        Employee* empList[numEmployees];
        int index = 0;
        treeToArray(empList, root, index);

        int numEmpsTemp = numEmployees;
        if (type == "Age") { //start sort by age
            bool swapped = true;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    if (empList[i]->age > empList[i + 1]->age) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }
            string name;

            cout << "Employees sorted by Age:\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->frstNme + " " + curEmp->lstNme;
                cout << name << ", Age: " << curEmp->age << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->frstNme + " " + curEmp->lstNme;
            cout << name << ", Age: " << curEmp->age << endl;
        } //end sort by age

        if (type == "Years Served") { //start sort by years served
            bool swapped = true;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    if (empList[i]->yrsServed > empList[i + 1]->yrsServed) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }

            string name;

            cout << "Employees sorted by Years Served:\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->frstNme + " " + curEmp->lstNme;
                cout << name << ", Years Served: " << curEmp->yrsServed << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->frstNme + " " + curEmp->lstNme;
            cout << name << ", Years Served: " << curEmp->yrsServed << endl;
        } //end sort by years served
    }   

    void sortStr(string type) {
        Employee* empList[numEmployees];
        int index = 0;
        treeToArray(empList, root, index);

        int numEmpsTemp = numEmployees;
        if (type == "First Name") { //start sort by First Name
            bool swapped = true;

            string name1;
            string name2;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    name1 = empList[i]->frstNme;
                    name2 = empList[i + 1]->frstNme;
                    
                    if (before(name1, name2) == 0) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }

            string name;

            cout << "Employees sorted by First Name:\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->frstNme;
                cout << name << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->frstNme;
            cout << name << endl;
        } //end sort by First Name

        if (type == "Last Name") { //start sort by Last Name
            bool swapped = true;

            string name1;
            string name2;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    name1 = empList[i]->lstNme;
                    name2 = empList[i + 1]->lstNme;
                    
                    if (before(name1, name2) == 0) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }

            string name;

            cout << "Employees sorted by Last Name:\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->lstNme;
                cout << name << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->lstNme;
            cout << name << endl;
        } //end sort by Last Name

        if (type == "Job Title") { //start sort by Job Title
            bool swapped = true;

            string name1;
            string name2;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    name1 = empList[i]->title;
                    name2 = empList[i + 1]->title;
                    
                    if (before(name1, name2) == 0) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }

            string name;

            cout << "Employees sorted by Job Title (alphabetically) :\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->frstNme + " " + curEmp->lstNme;
                cout << name << ", Job Title: " << curEmp->title << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->frstNme + " " + curEmp->lstNme;
            cout << name << ", Job Title: " << curEmp->title << endl;
        } //end sort by Job Title

        if (type == "Employee ID") { //start sort by Employee ID
            bool swapped = true;

            string name1;
            string name2;
            while (numEmpsTemp >= 1 && swapped) {
                swapped = false;
                for (int i = 0; i < (numEmpsTemp - 1); i++) {
                    name1 = empList[i]->emID;
                    name2 = empList[i + 1]->emID;
                    
                    if (before(name1, name2) == 0) {
                        swap(empList[i], empList[i + 1]);
                        swapped = true;
                    }
                }
                numEmpsTemp--;
            }

            string name;

            cout << "Employees sorted by Employee ID:\n";
            for (int i = 0; i < numEmployees - 1; i++) {
                Employee* curEmp = empList[i];
                name = curEmp->frstNme + " " + curEmp->lstNme;
                cout << name << ", Employee ID: " << curEmp->emID << " - ";
            }
            Employee* curEmp = empList[numEmployees-1];
            name = curEmp->frstNme + " " + curEmp->lstNme;
            cout << name << ", Employee ID: " << curEmp->emID << endl;
        } //end sort by Employee ID
    }

};


int main() {

    Office office;

    string title; //person attributes
    string frstNme;
    string lstNme;
    string emID;
    int age;
    int salary;
    int yrsServed;

    string bossTitle;
    string type;


    int option;
    do {
        cout << endl;
        cout << "===== Operation Menu: Enter 0 to exit ======" << endl;
        cout << "1. newEmp(): Add new employee to Office" << endl;
        cout << "2. Search(int)(): Search by Age or Years Served" << endl;
        cout << "3. Search(string)(): Search by First name, Last name, Job Title, or Employee ID" << endl;
        cout << "4. Sort(int)(): Displays all employees sorted by Age or Years Served" << endl;
        cout << "5. Sort(string): Displays all employees sorted by First name, Last name, Job Title, or Employee ID" << endl;
        cout << "6. rmvEmp(): Remove an employee and leave an empty position to be filled in its place." << endl;
        cout << "0. Exit" << endl;

        cin >> option;

        switch (option) {
        case 0:
            break;
        case 1:
            cout << "Enter Job Position of new employee's BOSS (\"None\" if adding CEO): " << endl;
            cin.ignore();
            getline(cin, bossTitle);
            cout << "Enter Job Position of new employee: " << endl;
            getline(cin, title);
            cout << "Enter First Name of new employee: " << endl;
            getline(cin, frstNme);
            cout << "Enter the Last Name of new employee: " << endl;
            getline(cin, lstNme);
            cout << "Enter the Employee ID of new employee: " << endl;
            getline(cin, emID);
            cout << "Enter the Age of new employee: " << endl;
            cin >> age;
            cout << "Enter the Salary of new employee: " << endl;
            cin >> salary;
            cout << "Enter the number of Years Served of new employee: " << endl;
            cin >> yrsServed;
            office.newPosition(bossTitle, title, frstNme, lstNme, emID, age, salary, yrsServed);
            break;
        case 2:
            cout << "Enter the category would you like to search by (\"Age\" or \"Years Served\"): "<< endl;
            cin.ignore();
            getline(cin, type);
            office.searchInt(type);
            break;
        case 3:
            cout << "Enter the category would you like to search by (\"First Name\", \"Last Name\", \"Job Title\", or \"Employee ID\"): "<< endl;
            cin.ignore();
            getline(cin, type);
            office.searchStr(type);
            break;
        case 4:
            cout << "Enter the category you would like to sort by (\"Age\" or \"Years Served\"): " << endl;
            cin.ignore();
            getline(cin, type);
            office.sortInt(type);
            break;
        case 5:
            cout << "Enter the category you would like to sort by (\"First Name\", \"Last Name\", \"Job Title\", or \"Employee ID\") " << endl;
            cin.ignore();
            getline(cin, type);
            office.sortStr(type);
            break;
        case 6:
            cout << "Enter the Job Title of the employee you would like to remove. " << endl;
            cin.ignore();
            cin >> title;
            office.rmvEmp(title);
        default:
            cout << "Please enter a valid option: " << endl;
        }
    } while (option != 0);

    return 0;
}
