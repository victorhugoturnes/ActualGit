#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <string.h>

#define MAXSIZE 100

struct contacts
{
	char *name;
	char *phone;
};

struct master
{
	FILE *database;					//where to store contacts
	struct contacts *Contacts;		//existing contacts
	struct contacts *newContact;	//new contacts
	int existing;					//existing contacts quantity
	int added;						//newly added contacts quantity
};

int run			(char command, struct master *file);
int readContact(struct contacts *data, FILE *in);
int  CLines		(FILE *stream);

void noEchoRead	(char *command);
void startup	(struct master *file);
void close		(struct master *file);
void create		(struct master *file);
void delete		(struct master *file);
void update		(struct master *file);
void close		(struct master *file);
void load		(struct master *file);
void printer 	(struct master *file, FILE *out);

struct contacts *match(char *del, struct master *file);
struct contacts *search	(struct master *file, char *search);

char *readLine(char *line, FILE *in);


int main()
{
	struct master file;
	char command;

	startup(&file); //set locales and load databases.

	while(1) //TODO UI
	{
		system("cls");
		printf("Select a command:\n1).New Contact\n2).Search\n3).Delete\n4).Edit\n5).Show\n6).Quit\n");
		noEchoRead(&command); // termios eccho off substitute
		if(!run(command, &file)) break;
	}
}

void startup(struct master *file)
{
	setlocale(LC_ALL, ""); //Sets locale to system locale
	//printf("locale is %s\n",setlocale(LC_ALL, ""));

	file->added = 0; //sets amount of newly added contacts to 0
	file->newContact = malloc(sizeof(struct contacts)); //Allocates a single slot for a new contact

	file->database = fopen("contacts.txt", "r"); //opens contanct database
	file->database ? load(file) : (file->existing = 0); // Load database in case it exists, set existing contact amount to 0 in case it doesnt
	fclose(file->database);
}

int run(char command, struct master *file)
{
	char find[MAXSIZE+2];
	switch(command)
	{
		case '1':
			create(file);
			return 1;
		case '2':
			system("cls");
			printf("please input name or phone\n");
			gets(find);
			search(file, find);
			system("pause");
			return 2;
		case '3':
			delete(file);
			return 3;
		case '4':
			update(file);
			return 4;
		case '5':
			system("cls");
			printer(file, stdout);
			system("pause");
			return 5;
		case '6':
			close(file);
			return 0;
	}
}


void noEchoRead(char *command)
{
	*command = getch(); //reads a single character
	while(kbhit()) getch();//erases other characters in buffer to prevent several commandsin a row
}

void create(struct master *file)
{
	file->newContact = realloc(file->newContact, sizeof(struct contacts)*(file->added + 1));//increases new contacts size
	readContact(&file->newContact[file->added], stdin); //read a new contact
	file->added++; //increase new contacts counter.
}

struct contacts *search(struct master *file, char *search)
{
	int i;

	for ( i = 0; i < file->existing; ++i) //searches for new contact in previously existing contacts
	{
		if(strstr(file->Contacts[i].phone, search) || strstr(file->Contacts[i].name, search))
		{
			fprintf(stdout, "%s %s",file->Contacts[i].name, file->Contacts[i].phone );
		}
	}

	for ( i = 0; i < file->added; ++i) //searches for contact in recently added contacts
	{
		if(strstr(file->newContact[i].phone, search) || strstr(file->newContact[i].name, search))
		{
			fprintf(stdout, "%s %s",file->newContact[i].name, file->newContact[i].phone );
		}
	}
}

struct contacts *match(char *del, struct master *file)
{
	int i;

	for ( i = 0; i < file->existing; ++i) //searches for new contact in previously existing contacts
	{
		if(!strcmp(file->Contacts[i].name, del))
		{
			return &file->Contacts[i];
		}
	}

	for ( i = 0; i < file->added; ++i) //searches for contact in recently added contacts
	{
		if(!strcmp(file->newContact[i].name, del))
		{
			return &file->newContact[i];
		}
	}
	return 0;
}

void delete(struct master *file)
{
	struct contacts *Del;
	char delet_this[MAXSIZE+2];
	system("cls");
	printf("Please type a contact to be deleted:\n");
	fgets(delet_this, MAXSIZE, stdin);

	while(!(Del = match(delet_this, file)))
	{
		delet_this[strlen(delet_this)-1] = 0;
		system("cls");
		printf("invalid contact, did you mean:\n");
		search(file, delet_this);
		fgets(delet_this, MAXSIZE, stdin);
	}
//	Del = 
	system("pause");

}

void update(struct master *file)
{
	//TODO
}

void close(struct master *file)
{
	file->database = fopen("contacts.txt", "w");

	printer(file, file->database); //add contacts to database

	fclose(file->database);
}

int readContact(struct contacts *data, FILE *in)
{
	char user;
	in == stdin ? (user = 1) : (user = 0);//checks if reading from user or database

	if(user)
	{
		system("cls");
		printf("Please Enter Contact Name\n");
	}

	data->name = readLine(data->name, in);

	if(user)
	{
		system("cls");
		printf("Please Enter Contact Number\n");
	}

	data->phone = readLine(data->phone, in);
}

char *readLine(char *line, FILE *in)
{
	line = malloc(MAXSIZE*sizeof(char)+2); 				//buffer size
	fgets(line, MAXSIZE, in); 							//reads line
	line = realloc(line, strlen(line)*sizeof(char)); 	//reduce size to needed
	return line;
}

void load (struct master *file)
{
	int i;

	file->existing = CLines(file->database)/2; 								//reads existing amount of contacts by reading database lines

	file->Contacts = malloc(sizeof(struct contacts) * file->existing); 		//allocates memory for contacts

	for (i = 0; i < file->existing; ++i)									//reads them
	{
		file->Contacts[i].name = readLine(file->Contacts[i].name, file->database);
//		printf("name = %s\n", file->Contacts[i].name);
		file->Contacts[i].phone = readLine(file->Contacts[i].phone, file->database);
//		printf("phone = %s\n", file->Contacts[i].phone);
	}
}

void printer (struct master *file, FILE *out)
{
	int i;

	for (int i = 0; i < file->existing; ++i)
	{
//		fprintf(stdout, "%s %s",file->Contacts[i].name, file->Contacts[i].phone );
		fprintf(out, "%s %s",file->Contacts[i].name, file->Contacts[i].phone );
	}

	for (i = 0; i < file->added; ++i)
	{
//		fprintf(stdout, "%s %s",file->newContact[i].name, file->newContact[i].phone );
		fprintf(out, "%s %s",file->newContact[i].name, file->newContact[i].phone );
	}
}

int  CLines		(FILE *stream)
{
	char buffer[MAXSIZE+2];
	int i;

	for (i = 0; !feof(stream); ++i)	fgets(buffer, MAXSIZE, stream); 	//count lines until end of file
	fseek(stream, 0, SEEK_SET);											//reset cursor to start of file

	return i;
}
