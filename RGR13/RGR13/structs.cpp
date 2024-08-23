struct employee {
	int id;
	char fullname[255];
	char position[255];
	int date[3];
	double salary;
};

struct node {
	employee value;
	struct node* next;
};