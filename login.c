
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
    puts("******************WELCOME TO CloudC****************\n");

    struct user_info *uinfo = user_info_alloc();
    if (!uinfo) {
        puts("Cannot allocate user info\n");
        return 1;
    }

    int attempts = 0; // Compteur d'échecs
    const int max_attempts = 3; // Nombre maximum de tentatives autorisées

    while (attempts < max_attempts) {
        puts("Please, enter your credentials to log in\n");

        printf("Username: ");
        fgets(uinfo->user_name, MAX_NAME, stdin);
        uinfo->user_name[strcspn(uinfo->user_name, "\n")] = '\0'; // Supprimer le '\n'

        printf("Password: ");
        fgets(uinfo->user_pass, MAX_PASSWD, stdin);
        uinfo->user_pass[strcspn(uinfo->user_pass, "\n")] = '\0'; // Supprimer le '\n'

        user_info_check(uinfo);

        if (uinfo->user_logged) {
            printf("User %s successfully logged in\n", uinfo->user_name);
            free(uinfo);
            return 0;
        }

        attempts++;
        printf("Login failed. Attempts remaining: %d\n", max_attempts - attempts);
    }

    puts("Maximum login attempts reached. Account locked.");
    free(uinfo);
    return 1;
}
