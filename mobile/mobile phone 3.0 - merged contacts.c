#include <conio.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAXSIZE 100

struct contacts
{
	char *name;
	char *phone;
};

struct master
{
	FILE *database;					//where to store contacts
	struct contacts **contact;		//array of existing contacts pointers
	int existing;					//existing contacts quantity
	int max;						//max contacts before needing realloc
};

int CLines		(FILE *stream);
int getUser		(struct master *file);
int run			(struct master *file, char command);
int match 		(struct master *file, char *del);
int readContact	(struct contacts *data, FILE *in);


void noEchoRead	(char *command);
void startup	(struct master *file);
void close		(struct master *file);
void create		(struct master *file);
void delete		(struct master *file);
void update		(struct master *file);
void load		(struct master *file);
void searchPrint(struct master *file, char *search, FILE *stream);

char *readLine(char *line, FILE *in);

int main()
{
	struct master file;
	char command = '0';

	startup(&file); //set locales and load databases.

	do
	{
		system("cls");
		printf("Select a command:\n1).New Contact\n2).Search\n3).Delete\n4).Edit\n5).Show\n6).Quit\n");
		noEchoRead(&command); // termios eccho off substitute
	} while(run(&file, command));
}

void startup(struct master *file)
{
	setlocale(LC_ALL, ""); //Sets locale to system locale
	//printf("locale is %s\n",setlocale(LC_ALL, ""));


	file->database = fopen("contacts.txt", "r"); //opens contanct database
	if(file->database)
	{
		load(file); //load contact info from DB
		fclose(file->database);
	}else
 	 {
		file->contact = malloc(sizeof(struct contacts*)*2);	//allocates 2 starting pointers
		file->existing = 0;	//declare nothing exists
		file->max = 2;	//declares 2 things can exist
	 }
}

int run(struct master *file, char command)
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
			searchPrint(file, find, stdout);
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
			searchPrint(file, "", stdout);
			system("pause");
			return 5;
		case '6':
			close(file);
			return 0;
		default :
			return 1;
	}
}


void noEchoRead(char *command)
{
	*command = getch(); //reads a single character
	while(kbhit()) getch();//erases other characters in buffer to prevent several commandsin a row
}

void create(struct master *file)
{
	if(file->existing == file->max) //checks for free slots
	{
		file->max *= 1.5; //increases max slots if necessary
		file->contact = realloc(file->contact, sizeof(struct contacts*) * (file->max)); //allocate said slots
	}

	file->contact[file->existing] = malloc(sizeof(struct contacts)); //allocates new contact memory and pointer
	readContact(file->contact[file->existing], stdin); 				//read a new contact
	file->existing++; 											//increase contacts counter.
}

void searchPrint(struct master *file, char *search, FILE *stream)
{
	int i;

	for ( i = 0; i < file->existing; ++i) //searches for new contact in previously existing contacts
	{
		if(strstr(file->contact[i]->phone, search) || strstr(file->contact[i]->name, search)) //if the name or phone contains searched term
		{
			fprintf(stream, "%s %s",file->contact[i]->name, file->contact[i]->phone ); //print it stream
		}
	}
}

int match(struct master *file, char *string)
{
	int i;
	for ( i = 0; i < file->existing; ++i) //runs through all existing contacts
	{
		if(!strcmp(file->contact[i]->name, string))	return i; //returns matching string position if found
	}
	return -1; //error code for string not found
}

void delete(struct master *file) //spaghetti
{
	int del;

	system("cls");
	if(file->existing)											//checks if users exist
	{
		printf("Please type a contact to be deleted:\n");
		searchPrint(file, "", stdout);							//prints all contacts

		del = getUser(file);									//match a selected contact

		printf("deleting\n");

		file->existing--;										//declares 1 thing less exists
		free(file->contact[del]);								//make the ghost go away
		file->contact[del] = file->contact[file->existing]; 	//change the ghost thing to the one that doesnt exist

		printf("Sucessfully deleted\n");					//maybe, probably, hopefully
	}else
	 {
	 	printf("no contacts to be deleted\n");
	 }

	system("pause");
}

int getUser(struct master *file)
{
	char user[MAXSIZE+2];
	int index = -1;

	fgets(user, MAXSIZE, stdin);					//gets contact name

	while((index = match(file, user)) ==-1)			//check existance
	{
		//once you're here you're forced to select something because I'm too lazy to make a escape action
		user[strlen(user)-1] = 0;			//removes \n from string

		system("cls");
		printf("invalid contact, did you mean:\n");		//offers suggestions

		searchPrint(file, user, stdout);			//search possibly related contacts

		fgets(user, MAXSIZE, stdin);				//gets contact name
	}
	return index;
}

void update(struct master *file)
{
	//TODO
}

void close(struct master *file)
{
	file->database = fopen("contacts.txt", "w");

	searchPrint(file, "", file->database); //add contacts to database

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

	file->contact = malloc(sizeof(struct contacts*) * file->existing*2+2);				//allocates memory for contacts and expansions

	file->max = file->existing*2+2;														//set current expansion limit

	for (i = 0; i < file->existing; ++i)												//reads them
	{
		file->contact[i] = malloc(sizeof(struct contacts)); 							//allocates memory to store contact info
		file->contact[i]->name = readLine(file->contact[i]->name, file->database);		//loads names from database
		file->contact[i]->phone = readLine(file->contact[i]->phone, file->database); 	//loads phones from database
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
