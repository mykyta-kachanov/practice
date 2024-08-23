/**
* @file source.cpp
* @author Качанов Микита Юрійович 515і2
* @date 22.08.2024
* @brief RGR
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "data.h"
#include "licences.h"
#include "structs.cpp"
#define config "rgr13.cfg"

int main() {
    char filename[255];
    int key[5];
    while (true) {
        if (readConfigFile(filename, key, config) == 0) {
            printf("Error loading config file\n");
            return -1;
        }
        if (checklicense(key) == 0) {
            printf("Error license key not responding\n");
            return -2;
        }
        struct node* head = NULL;
        printf("1. Print all employees"
            "\n2. Add an employee"
            "\n3. Delete an employee"
            "\n4. Modify an employee"
            "\n5. Save data to another file"
            "\n6. Export data to csv file"
            "\n7. Print employees with position and after date"
            "\n8. Print employees with salary greater than"
            "\n9. Edit configuration file"
            "\n-1. Exit"
            "\n: ");
        int choice = 0;
        if(scanf_s("%d", &choice) == 0) {
            printf("incorrect input\n");
            continue;
        }

        while (getchar() != '\n');
        readEmployeeData(filename, &head);

        switch (choice) {
            case 1:
                printEmployees(head);
                break;
            case 2:
                employee e = createEmployeeFromInput();
                addEmployee(&head, e);
                overwriteFile("new_base.dat", head);
                break;
            case 3:
            {
                printf("Enter id of employee: ");
                int id = 0;
                if (scanf_s("%d", &id) == 0) {
                    printf("incorrect input\n");
                    continue;
                }
                employee* foundEmployee = findEmployeeById(head, id);
                deleteEmployee(&head, foundEmployee->id);
                overwriteFile("new_base.dat", head);
            }
                break;
            case 4:
            {
                printf("Enter id of employee: ");
                int id = 0;
                if (scanf_s("%d", &id) == 0) {
                    printf("incorrect input\n");
                    continue;
                }
                employee* foundEmployee = findEmployeeById(head, id);
                printf("Id: %s\n", foundEmployee->id);
                printf("Name: %s\n", foundEmployee->fullname);
                printf("Position: %s\n", foundEmployee->position);
                printf("Joining Date: %d-%d-%d\n", foundEmployee->date[0], foundEmployee->date[1], foundEmployee->date[2]);
                printf("Salary: %.2f\n", foundEmployee->salary);
                int c = 0;
                struct employee newEmployee;
                while (true && c != -1) {
                    printf("\nEnter what you need to change\n");
                    printf("1. Name\n2. Position\n3. Joining date\n4. Salary\n-1. Exit\n: ");
                    if (scanf_s("%d", &c) == 0) {
                        printf("incorrect input\n");
                        continue;
                    }
                    strcpy_s(newEmployee.fullname, foundEmployee->fullname);
                    strcpy_s(newEmployee.position, foundEmployee->position);
                    memcpy(newEmployee.date, foundEmployee->date, sizeof(foundEmployee->date));
                    newEmployee.salary = foundEmployee->salary;
                    while (getchar() != '\n');
                    switch (c) {
                    case 1:
                        printf("\nEnter new name: ");
                        char name[255];
                        fgets(name, 255, stdin);
                        strcpy_s(newEmployee.fullname, name);
                        break;
                    case 2:
                        printf("\nEnter new position: ");
                        char position[255];
                        fgets(position, 255, stdin);
                        strcpy_s(newEmployee.position, position);
                        break;
                    case 3:
                        int date[3];
                        for (int i = 0; i < 3; i++) {
                            printf("date[%d]: ", i);
                            if (scanf_s("%d", &date[i]) == 0) {
                                printf("incorrect input\n");
                                date[i] = 0;
                                continue;
                            }
                        }
                        memcpy(newEmployee.date, date, sizeof(foundEmployee->date));
                        break;
                    case 4: 
                    {
                        double newsalary = 0;
                        printf("\nEnter new salary: ");
                        if (scanf_s("%lf", &newsalary) == 0) {
                            printf("incorrect input\n");
                            continue;
                        }
                        newEmployee.salary = newsalary;
                    }
                        break;
                    case -1:
                        break;
                    default:
                        continue;
                    }
                    modifyEmployee(head, id, newEmployee);
                    saveDataToFile("new_base.dat", head);
                }
                printf("\nNEW EMPLOYEE DATA\n");
                printf("Name: %s\n", newEmployee.fullname);
                printf("Position: %s\n", newEmployee.position);
                printf("Joining Date: %d-%d-%d\n", newEmployee.date[0], newEmployee.date[1], newEmployee.date[2]);
                printf("Salary: %.2f\n", newEmployee.salary);
            }
                break;
            case 5:
                printf("Enter filename for data: ");
                char str[255];
                fgets(str, 255, stdin);
                strtok(str, "\n");
                saveDataToFile(str, head);
                break;
            case 6:
                printf("Enter filename for data: ");
                char csv[255];
                fgets(str, 255, stdin);
                strtok(str, "\n");
                parseToCSVFile(str, head);
                break;
            case 7:
                printf("Enter position: ");
                char pos[255];
                fgets(pos, 255, stdin);
                strtok(pos, "\n");
                printf("Enter date: \n");
                int datee[3];
                for (int i = 0; i < 3; i++) {
                    printf("date[%d]: ", i);
                    if (scanf_s("%d", &datee[i]) == 0) {
                        printf("incorrect input\n");
                        datee[i] = 0;
                        continue;
                    }
                }
                printEmployeesWithPositionAndAfterDate(head, pos, datee);
                break;
            case 8:
                double salaryy;
                printf("Salary: ");
                if (scanf_s("%lf", &salaryy) == 0) {
                    printf("incorrect input\n");
                    continue;
                }
                printEmployeesWithSalaryGreater(head, salaryy);
                break;
            case 9: {
                printf("Config: ");
                displayConfigFile("conf.cfg");
                printf("\n1. Edit database file name\n2. Generate new license key\n-1. Exit\n: ");
                int ch = 0;
                if (scanf_s("%d", &ch) == 0) {
                    printf("incorrect input\n");
                    continue;
                }
                switch (ch) {
                case 1:
                    while (getchar() != '\n');
                    printf("Print new database file name: ");
                    fgets(filename, 255, stdin);
                    strtok(filename, "\n");
                    printf("New file name: %s\n", filename);
                    break;
                case 2:
                    int lic[5];
                    generatelicense(lic);
                    printf("New license key: ");
                    for (int i = 0; i < 5; i++) {
                        printf("%d", lic[i]);
                    }
                    printf("\n");
                    break;
                default:
                    break;
                }
            }
                break;
            case -1:
                exit(0);
                break;
        }
    }
    
    return 0;
}