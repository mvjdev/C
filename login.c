
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 3
#define MAX_NAME 10
#define MAX_PASSWD 10

struct user_info 
{
	char user_name[MAX_NAME];
	char user_pass[MAX_PASSWD];
	unsigned user_logged;
};

struct user_db 
{
	char name[MAX_NAME];
	char passwd[MAX_PASSWD];
};

struct user_db users[MAX_USERS] = 
{
	[0].name   = "john",
	[0].passwd = "1234",

	[1].name   = "rabe",
	[1].passwd = "2000",

	[2].name   = "safidy",
	[2].passwd = "3000" 
};


static void list_users (void)
{
	for (unsigned i = 0; i < MAX_USERS; i++)
		printf("user %u  %s\n", i, users[i].name);
}

static struct user_info * user_info_alloc(void)
{
	struct user_info *uinfo = NULL;

	uinfo = (struct user_info *)malloc(sizeof(struct user_info ));
	if (!uinfo)
		return NULL;

	memset(uinfo, 0x0, sizeof(struct user_info));

	return uinfo;

}

static void user_info_check(struct user_info *uinfo)
{

	struct user_db *bdinfo = NULL;

	/* Search for a user in the database */
	for (unsigned i = 0; i < MAX_USERS; i++) {
		if (!strcmp(users[i].name, uinfo->user_name))
		 	bdinfo = &users[i];
	}

	/* No user found, */
	if (!bdinfo)
		return;

	/* Compare the user provided password to the one stored in the database */
	if (!strcmp(bdinfo->passwd, uinfo->user_pass))
		uinfo->user_logged = 1;
}

int main(int argc, char const *argv[])
{
	
	puts("******************WELCOM TO CloudC****************\n");

	puts("Please, Enter your credentials to log in\n");

	struct user_info * uinfo = user_info_alloc();

	if (!uinfo) {
		puts("cannot allocate user info\n");
		return 1;
	}

	printf("Username: ");
	scanf("%s", uinfo->user_name);
	puts("");
	printf("Password: ");
	scanf("%s", uinfo->user_pass);

	user_info_check(uinfo);

	puts("");
	if (uinfo->user_logged) {
		printf("User %s successfully logged in\n", uinfo->user_name);
		free(uinfo);
		return 0;
	}


	puts("\nLOGIN FAILED\n");
	free(uinfo);

	return 0;
}