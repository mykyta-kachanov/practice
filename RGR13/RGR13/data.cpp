#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.cpp"

void addEmployee(struct node** head, struct employee newEmployee) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->value = newEmployee;
	newNode->next = *head;
	int id = 0;
	if(newNode->next != NULL)
		id = newNode->next->value.id + 1;
	newNode->value.id = id;
	*head = newNode;
}

struct employee createEmployeeFromInput() {
	struct employee emp;
	printf("Enter full name: ");
	fgets(emp.fullname, sizeof(emp.fullname), stdin);
	emp.fullname[strcspn(emp.fullname, "\n")] = '\0'; //del last symbol
	printf("Enter position: ");
	fgets(emp.position, sizeof(emp.position), stdin);
	emp.position[strcspn(emp.position, "\n")] = '\0';
	printf("Enter joining date (DD MM YYYY): ");
	scanf_s("%d %d %d", &emp.date[0], &emp.date[1], &emp.date[2]);
	printf("Enter salary: ");
	scanf_s("%lf", &emp.salary);
	getchar();
	return emp;
}

void deleteEmployee(struct node** head, int id) {
	struct node* temp = *head, * prev = NULL;

	while (temp != NULL && temp->value.id == id) {
		prev = temp;
		temp = temp->next;
	}

	if (temp == NULL) return;

	if (prev == NULL) {
		*head = temp->next;
	}
	else {
		prev->next = temp->next;
	}

	free(temp);
}

void printEmployees(struct node* head) {
	struct node* temp = head;

	while (temp != NULL) {
		printf("Id: %d\n", temp->value.id);
		printf("Full Name: %s\n", temp->value.fullname);
		printf("Position: %s\n", temp->value.position);
		printf("Date: %02d/%02d/%04d\n", temp->value.date[0], temp->value.date[1], temp->value.date[2]);
		printf("Salary: %.2f\n", temp->value.salary);
		printf("---------------------\n");
		temp = temp->next;
	}
}

struct employee* findEmployeeByName(struct node* head, char* name) {
	struct node* current = head;

	while (current != NULL) {
		strtok(name, "\n");
		if (strcmp(current->value.fullname, name) == 0) {
			return &current->value;
		}
		current = current->next;
	}

	return NULL;
}

struct employee* findEmployeeById(struct node* head, int id) {
	struct node* current = head;

	while (current != NULL) {
		if (current->value.id == id) {
			return &current->value;
		}
		current = current->next;
	}

	return NULL;
}


void modifyEmployee(struct node* head, int id, struct employee newEmployee) {
	struct node* temp = head;

	while (temp != NULL) {
		if (temp->value.id == id) {
			temp->value = newEmployee;
			return;
		}
		temp = temp->next;
	}
}

void createNewDataFile(const char* filename) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to create new data file");
		exit(EXIT_FAILURE);
	}

	fclose(file);
}

void readEmployeeData(const char* filename, struct node** head) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Unable to open employee data file\nCreating new file new_base.dat\n");
		createNewDataFile("new_base.dat");
		file = fopen("new_base.dat", "r");
	}
	int id = 0;
	struct employee emp;
	while (fscanf(file, "%254[^,],%254[^,],%d,%d,%d,%lf\n", emp.fullname, emp.position, &emp.date[0], &emp.date[1], &emp.date[2], &emp.salary) == 6) {
		emp.id = id;
		addEmployee(head, emp);
		id++;
	}

	fclose(file);
}

void saveDataToFile(const char* filename, struct node* head) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to open file for writing");
		exit(EXIT_FAILURE);
	}

	struct node* temp = head;
	while (temp != NULL) {
		strtok(temp->value.fullname, "\n");
		strtok(temp->value.position, "\n");
		fprintf(file, "%s,%s,%d,%d,%d,%.2f\n",
			temp->value.fullname,
			temp->value.position,
			temp->value.date[0], temp->value.date[1], temp->value.date[2],
			temp->value.salary);
		temp = temp->next;
	}

	fclose(file);
}

void overwriteFile(const char* filename, struct node* head) {
	FILE* file = fopen(filename, "w+");
	if (file == NULL) {
		perror("Unable to open file for writing");
		exit(EXIT_FAILURE);
	}

	struct node* temp = head;
	while (temp != NULL) {
		fprintf(file, "%s,%s,%d,%d,%d,%.2f\n",
			temp->value.fullname,
			temp->value.position,
			temp->value.date[0], temp->value.date[1], temp->value.date[2],
			temp->value.salary);
		temp = temp->next;
	}

	fclose(file);
}

void printEmployeesWithSalaryGreater(struct node * head, double salary) {
	struct node* temp = head;

	while (temp != NULL) {
		if (temp->value.salary < salary) {
			temp = temp->next;
			continue;
		}
		printf("Id: %d\n", temp->value.id);
		printf("Full Name: %s\n", temp->value.fullname);
		printf("Position: %s\n", temp->value.position);
		printf("Date: %02d/%02d/%04d\n", temp->value.date[0], temp->value.date[1], temp->value.date[2]);
		printf("Salary: %.2f\n", temp->value.salary);
		printf("---------------------\n");
		temp = temp->next;
	}
}

int greaterFirstDate(int date1[], int date2[]) {
	if (date1[2] > date2[2])
		return 1;
	if (date1[1] > date2[1] && date1[2] > date2[2])
		return 1;
	if (date1[0] > date2[0] && date1[2] > date2[2])
		return 1;
	if (date1[0] > date2[0] && date1[1] > date2[1] && date1[2] > date2[2])
		return 1;
	return 0;
}

void printEmployeesWithPositionAndAfterDate(struct node* head, const char* position, int date[3]) {
	struct node* temp = head;

	while (temp != NULL) {
		if (strcmp(temp->value.position, position) != 0 || greaterFirstDate(temp->value.date, date) == 0) {
			temp = temp->next;
			continue;
		}
		printf("Id: %d\n", temp->value.id);
		printf("Full Name: %s\n", temp->value.fullname);
		printf("Position: %s\n", temp->value.position);
		printf("Date: %02d/%02d/%04d\n", temp->value.date[0], temp->value.date[1], temp->value.date[2]);
		printf("Salary: %.2f\n", temp->value.salary);
		printf("---------------------\n");
		temp = temp->next;
	}
}

void parseToCSVFile(const char* filename, struct node* head) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("Unable to open file for writing");
		exit(EXIT_FAILURE);
	}

	struct node* temp = head;
	while (temp != NULL) {
		fprintf(file, "%s,%s,%d,%d,%d,%.2f\n",
			temp->value.fullname,
			temp->value.position,
			temp->value.date[0], temp->value.date[1], temp->value.date[2],
			temp->value.salary);
		temp = temp->next;
	}

	fclose(file);
}