#include "sha256_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/sha.h>


void create_objects_directry(const char *objects_path);
void create_commits_directry(const char *commits_path);
void create_head_file(const char *head_path);
void init_repisatory();
void add_file(char *filename);
int sha256_hash(const char *filename, char *output);

void create_objects_directry(const char *objects_path)
{
	// Create Object folder
	if (mkdir(objects_path, 0777) == -1)
	{
		printf("Error creating object folder: %s\n", strerror(errno));
	}
	else
	{
		printf("Object file created at: '%s'\n", objects_path);

	}
}

void create_commits_directry(const char *commits_path)
{
	// Create Commit folder
	if (mkdir(commits_path, 0777) == -1)
	{
		printf("ERROR creating commits folder: %s\n", strerror(errno));
	}
	else
	{
		printf("Commits file created at: '%s'\n", commits_path);
	}
}


void create_head_file(const char *head_path)
{
	FILE *head = fopen(head_path, "w");
	if (head == NULL)
	{
		printf("ERROR creating Head file: %s\n", strerror(errno));
	}
	else
	{
		fprintf(head, "Head\n");
		fclose(head);
	}

	printf("Head Created Successfully\n");
}

void init_repisatory()
{

	// Folders Path
	const char *tgit_path = "./.tgit";
	const char *objects_path = "./.tgit/objects";
	const char *commits_path = "./.tgit/commits";

	// Files Path
	const char *head_path = "./.tgit/HEAD";

	printf("Initializing TinyGit...\n");

	// Create tinyGit folder
	if (mkdir(tgit_path, 0777) == 0)
	{
		printf("Repository Created at '%s' Successfully...\n", tgit_path);

		create_objects_directry(objects_path);
		create_commits_directry(commits_path);
		create_head_file(head_path);

		printf("TinyGit repository Initialized.\n");
	}
	else
	{
		printf("Repository already exist!\n");
	}
}

void add_file(char *filename)
{

	FILE *file = fopen(filename, "r");

	const char *objects_path = "./.tgit/objects/";
	const char *file_path = filename;

	char full_path[256];

	snprintf(full_path, sizeof(full_path), "%s%s", objects_path, file_path);

	FILE *folder_file_path = fopen(full_path, "w");

	if (file == NULL)
	{
		printf("Could not open file : %s\n%s \n",filename, strerror(errno));
		return;		
		
	}
	else if (folder_file_path == NULL)
	{
		printf("Could not write file : %s\n%s \n",full_path, strerror(errno));
		fclose(file);
		return;
	}
	else
	{

		printf("File opened successfully : %s\n", filename);

		printf("\nAdding file: %s", filename);

		printf("\n__________________________________________________________________________________\n");

		int characters;
		while ( (characters = (fgetc(file))) != EOF )
		{
			putchar(characters);
			fputc(characters, folder_file_path);
		}

		printf("\n__________________________________________________________________________________\n");

		fclose(file);
		fclose(folder_file_path);

    //
    // TODO: Remove this While loop this is just for testing purposes. (I don't know how to use debug :P) 
    //

		// Check if the file have added to the Objectes Folder

		folder_file_path = fopen(full_path, "r");
		if(folder_file_path == NULL) 
		{
			printf("Could not open File : %s\n%s\n", full_path, strerror(errno));
  
			return;
		}
		printf("\nCopied file to : %s\n", full_path);

		printf("\nCopied Contents : \n\n");
		int characters2;
		while ( ( characters2 = (fgetc(folder_file_path)) ) != EOF )
		{
			putchar(characters2);
		}
		fclose(folder_file_path);
	}
	
}

int sha256_hash(const char *filename, char *output){
  
  return 1;
}

int main(int argc, char *argv[])
{

	//
	// TODO: REMOVE IT LATER
	// | | |
	// V V V
	printf("Total arguments: %d\n", (argc - 1));
	//
	//
	//

	if (argc < 2)
	{
		printf("Usage: tgit <command>\n");
		return 0;
	}

	// Checks if the argumnet is valid
	if (strcmp(argv[1], "init") == 0)
	{

		init_repisatory();
	}
	else if (strcmp(argv[1], "add") == 0)
	{
		for (int i = 2; i < argc; i++)
		{
			//
			//	TODO: Remove this later
			//	| | |
			//	V V V
			printf( "argc[%d]  : ", i );
			//
			//

			add_file(argv[i]); 
		}
	}
	else
	{
		printf("Unkwnown command: %s\n", argv[1]);
	}
	return 0;
}
