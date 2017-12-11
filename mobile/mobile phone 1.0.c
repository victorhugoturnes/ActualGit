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
	FILE *database;
	FILE *metadata;
	struct contacts *Contacts;
	struct contacts *newContact;
	int contNum;
	int added;
	int *order;
};

int run			(char command, struct master *file);
void noEchoRead	(char *command);

void startup	(struct master *file);
void close		(struct master *file);
void create		(struct master *file);
void delete		(struct master *file);
void update		(struct master *file);
void printAll	(struct master *file);
void close		(struct master *file);
void load		(struct master *file);
void fillMeta	(struct master *file, FILE *out);
void fillDB 	(struct master *file, FILE *out);
int loadMetadata(struct master *file);
int loadDatabase(struct master *file);


struct contacts *search		(struct master *file, int del);
int readContact(struct contacts *data, FILE *in);
char *readNumber(char *number, FILE *in);
char *readName	(char *name, FILE *in);


int main()
{
	struct master file;
	char command;

	startup(&file);

	while(1) //TODO GUI
	{
		system("cls");
		printf("Selecione um comando:\n1).Novo Contanto\n2).Pesquisar\n3).Excluir contanto\n4).Editar\n5).Exibir\n6).Sair\n");
		noEchoRead(&command); // termios eccho off?
//		printf("command is = %c\n", command );

		if(!run(command, &file)) break;
	}
}

void startup(struct master *file)
{
	setlocale(LC_ALL, "");
	file->added = 0;
	file->newContact = malloc(sizeof(struct contacts));
	file->metadata = fopen("metadata.txt", "r+");
	file->database = fopen("contacts.txt", "r+");
	if(!file->metadata || !file->database)
	{
		file->metadata = fopen("metadata.txt", "w+");
		file->database = fopen("contacts.txt", "w+");
		file->contNum = 0;
		fillMeta(file, file->metadata);
	}else
	{
		load(file);
	}
	//printf("locale is %s\n",setlocale(LC_ALL, ""));
}

int run(char command, struct master *file)
{
	switch(command)
	{
		case '1':
			create(file);
			return 1;
		case '2':
			search(file, 0);
			return 2;
		case '3':
			delete(file);
			return 3;
		case '4':
			update(file);
			return 4;
		case '5':
			printAll(file);
			return 5;
		case '6':
			close(file);
			return 0;
	}
}


void noEchoRead(char *command)
{
	*command = getch();
	while(kbhit()) getch();
}

void create(struct master *file)
{
	file->newContact = realloc(file->newContact, sizeof(struct contacts)*(file->added + file->added/2 + 1));
	readContact(&file->newContact[file->added], stdin);
	file->added++;
}

struct contacts *search(struct master *file, int del)
{
	char search[MAXSIZE];
	int i;

	system("cls");
	printf("please input name or phone\n");
	gets(search);

	for ( i = 0; i < file->contNum; ++i)
	{
//		printf("%s%s%s\n",search,file->Contacts[i].phone, file->Contacts[i].name  );
		if(strstr(file->Contacts[i].phone, search) || strstr(file->Contacts[i].name, search))
		{
//			printf("found something\n");
			fprintf(stdout, "%s %s",file->Contacts[i].name, file->Contacts[i].phone );
			if(del) return &file->Contacts[i];
		}
//		printf("for 1, a%d b%d\n", a, b);
	}

	for ( i = 0; i < file->added; ++i)
	{
//		printf("for 2\n");
		if(strstr(file->newContact[i].phone, search) || strstr(file->newContact[i].name, search))
		{
//			printf("found something2\n");
			fprintf(stdout, "%s %s",file->newContact[i].name, file->newContact[i].phone );
			if(del) return &file->Contacts[i];
		}
	}
	system("pause");
}

void delete(struct master *file)
{
	struct contacts *delet_this = NULL;
	char confirm;

	printf("Please select a contact to be deleted\n");
	if(delet_this = search(file, 1))
	{
		printf("Are you sure you wish to delete %s\n1).Yes\n2).No\n", delet_this->name );
		confirm = getch();
//		if(confirm == '1') remove(delet_this);
	}else
	{
		printf("invalid contact\n");
	}
}
/*
void remove(struct contacts *cont)
{

}
*/
void update(struct master *file)
{
}

void printAll(struct master *file)
{
	system("cls");
	fillDB(file, stdout);
	system("pause");
}

void close(struct master *file)
{
	fillDB(file, file->database);
	fillMeta(file, file->metadata);

	fclose(file->database);
	fclose(file->metadata);
}

int readContact(struct contacts *data, FILE *in)
{
	char user;
	in == stdin ? (user = 1) : (user = 0);
	if(user)
	{
		system("cls");
		printf("Please Enter Contact Name\n");
	}
	data->name = readName(data->name, in);
	if(user)
	{
		system("cls");
		printf("Please Enter Contact Number\n");
	}
	data->phone = readNumber(data->phone, in);
}

char *readName(char *name, FILE *in)
{
	name = malloc(MAXSIZE*sizeof(char));

	fgets(name, MAXSIZE, in);

	name = realloc(name, strlen(name)*sizeof(char));

	return name;
}

char *readNumber(char *number, FILE *in)
{
	number = malloc(MAXSIZE*sizeof(char));

	fgets(number, MAXSIZE, in);

	number = realloc(number, strlen(number)*sizeof(char));

	return number;
}

void load (struct master *file)
{
	loadMetadata(file);
	loadDatabase(file);
}

int loadMetadata(struct master *file)
{
	int i;

	fscanf(file->metadata, "%*s %d [^\n]%*c", &file->contNum);

	for (int i = 0; i < file->contNum; ++i)
	{
//		fscanf(file->metadata, " %d", &file->order[i]);
	}
}

int loadDatabase(struct master *file)
{
	printf("called\n");
	int i;

	file->Contacts = malloc(sizeof(struct contacts) * file->contNum);

	for (i = 0; i < file->contNum; ++i)
	{
		file->Contacts[i].name = readName(file->Contacts[i].name, file->database);
		printf("name = %s\n", file->Contacts[i].name);
		file->Contacts[i].phone = readNumber(file->Contacts[i].phone, file->database);
		printf("phone = %s\n", file->Contacts[i].phone);
	}
}


void fillMeta	(struct master *file, FILE *out)
{
	fclose(file->metadata);
	file->metadata = fopen("metadata.txt", "w+");

	int i;

	fprintf(out, "contacts= %d\nalphabetic order =  ", file->added + file->contNum);

	for (i = 0; i < file->contNum + file->added; ++i)
	{
//		fprintf(out, "%d ",file->order );
	}
}

void fillDB (struct master *file, FILE *out)
{
	fclose(file->database);
	file->database = fopen("contacts.txt", "w");

	int i;
	for (int i = 0; i < file->contNum; ++i)
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