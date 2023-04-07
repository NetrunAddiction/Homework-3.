#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <>


using namespace std;

const int MAX_NAME_LENGTH = 50;
const int MAX_TESTS = 10;
const int MAX_DATE_LENGTH = 20;

class Gradebook {
    public:
      char studentName[MAX_NAME_LENGTH];
      char testName[MAX_TESTS][MAX_NAME_LENGTH];
      float testScore[MAX_TESTS];
      char testDate[MAX_TESTS][MAX_DATE_LENGTH];
      int numTests;

      void writeToFile(const char* filename, const Gradebook& entry) {
        ofstream file(filename, ios::binary | ios::out | ios::app);
        file.write((char*)&entry, sizeof(Gradebook));
        file.close();
      }

      void readFromFile(const char* filename, Gradebook& entry) {
          ifstream file(filename, ios::binary | ios::in);
          file.read((char*)&entry, sizeof(Gradebook));
          file.close();
      }
      
      void printGradebook(const Gradebook& entry) const {
        cout << "Student Name: " << entry.studentName << endl;
        cout << "Number of Tests: " << entry.numTests << endl;
        for (int i = 0; i < entry.numTests; i++) {
          cout << "Test Name: " << entry.testName[i] << ", Score: " << entry.testScore[i] << ", Date: " << entry.testDate[i] << endl;
        }
      }      
      void modifyGradebook() {
        cout << "Enter new student name: ";
        cin.getline(studentName, MAX_NAME_LENGTH);

        cout << "Enter new number of tests: ";
        cin >> numTests;
        cin.ignore();

        for (int i = 0; i < numTests; i++) {
            cout << "Enter new test name: ";
            cin.getline(testName[i], MAX_NAME_LENGTH);

            cout << "Enter new test score: ";
            cin >> testScore[i];
            cin.ignore();

            cout << "Enter new exam date: ";
            cin.getline(testDate[i], MAX_DATE_LENGTH);
        }
      }
};

class Group{
  public: 
    void printAllGradebooks(const Gradebook& entry) const {
      ifstream file("gradebook.bin", ios::binary | ios::in);

      
      while (file.read((char*)&entry, sizeof(Gradebook))) {
        entry.printGradebook(entry);
        cout << endl;
      }
    
      file.close();
    } 

    void addStudent(){
  
      Gradebook entry;
      
      cout << "Enter student name: ";
      cin.getline(entry.studentName, MAX_NAME_LENGTH);
      
      cout << "Enter number of tests: ";
      cin >> entry.numTests;
      cin.ignore();
      
      for (int i = 0; i < entry.numTests; i++) {
        cout << "Enter test name: ";
        cin.getline(entry.testName[i], MAX_NAME_LENGTH);
      
        cout << "Enter test score: ";
        cin >> entry.testScore[i];
        cin.ignore();
        
        cout << "Enter exam date: ";
        cin.getline(entry.testDate[i], MAX_DATE_LENGTH);
      }
      
      entry.writeToFile("gradebook1.bin", entry);
      
      Gradebook readEntry;
      
      int escapeButton = 0;
      
      while (escapeButton == 0){
        int i = 0;
        
        cout << "Would you like to update the gradebook? (Y/N): ";
        char response;
        cin >> response;
        cin.ignore();
      
        if (response == 'Y' || response == 'y') {
          i++;
          readEntry.modifyGradebook();
          entry.writeToFile(format("gradebook.bin"), readEntry);
        
        }
          
        else{
          
          escapeButton = 1;
       
        }
      
      }
    }
};



int main(){
  Gradebook gb;
  Group gp;
  
  gp.addStudent();
  
  int escapeButtonNewStudent = 0;
  
  while (escapeButtonNewStudent == 0){
    
    cout << "Would you like to add new student? (Y/N): ";
    char response;
    cin >> response;
    cin.ignore();

    if (response == 'Y' || response == 'y'){
      gp.addStudent();
    }
    else{
      
      Gradebook readEntry;
      Group gp;
      gp.printAllGradebooks(readEntry);
      escapeButtonNewStudent = 1;
      
    }
    
  }

  return 0;

}
