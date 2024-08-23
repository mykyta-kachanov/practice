#pragma once
struct employee createEmployeeFromInput();
void deleteEmployee(struct node** head, int id);
void printEmployees(struct node* head);
void modifyEmployee(struct node* head, int id, struct employee newEmployee);
void createNewDataFile(const char* filename);
void readEmployeeData(const char* filename, struct node** head);
void saveDataToFile(const char* filename, struct node* head);
struct employee* findEmployeeByName(struct node* head, char* name);
struct employee* findEmployeeById(struct node* head, int id);
void overwriteFile(const char* filename, struct node* head);
void addEmployee(struct node** head, struct employee newEmployee);
void printEmployeesWithPositionAndAfterDate(struct node* head, const char* position, int date[3]);
int greaterFirstDate(int date1[], int date2[]);
void printEmployeesWithSalaryGreater(struct node* head, double salary);
void parseToCSVFile(const char* filename, struct node* head);