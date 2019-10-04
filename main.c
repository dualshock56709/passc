
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT argv[1]
#define MIN_ASCII argv[2]
#define MAX_ASCII argv[3]
#define BLACKLIST argv[4]

void usage(unsigned exit_status);
int get_ascii(char *arg, char default_value);
char invalid_char(char ch, char *blacklist);
char random_char(char start, char end, char *blacklist);
void generate_password(char limit, char start, char end,
                      char *password_ptr, char *blacllist);

int main(int argc, char **argv) {
    char limit, start, end, *password;

/*
 * checking if we need to print the
 * help message
 */

    if(LIMIT == "h" || !LIMIT)
    /*
     * if a array hasn't the element of
     * spepcified index it returns a "false"
     * value
     */
        usage(LIMIT? 0 : 1);

/*
 * assignments
 */

    if((limit = atoi(LIMIT)) < 5 || limit > 20)
        usage(1);

    /*
     * allocate some space for the
     * password
     */
    if(!(password = malloc(limit + 1))) {
        puts("inuficcient heap for password lenght");
        return 1;
    }

    password[limit + 1] = 0;

    start = get_ascii(MIN_ASCII, 32);
    end = get_ascii(MAX_ASCII, 126);

    /*
     * sorting the values (higher values in
     * max and lower values in min) with
     * bubble sort
     */
    {
        char temp;
        if(start > end) {
            temp = end;
            end = start;
            start = temp;
        }
    }

    srand(time(NULL));

    generate_password(limit, start, end, password, BLACKLIST);

    printf("%s\n", password);
    return 0;
}

void usage(unsigned exit_status) {
    puts("usage: passc [character limit (5-20)] <min ascii value> <max ascii value> <blacklist>\n"
         "notes:\n"
         "default min ascii value: 32\n"
         "default max ascii value: 126\n"
         "leave a blank string ('' or "") in the arguments os simply let it blank to use the default values\n\n"
         "blacklist is the list of character to ignore; they must be between quotes and entirely compound of characters - not the ascii values\n"
         "(example: passc '' 255 _Aa; passc '' '' abcdefABCDEF)");
    exit(exit_status);
}

/*
 * returns the given ascii value, even if
 * the argument is a character
 */
int get_ascii(char *arg, char default_value) {
    int asciic;

    if(!strlen(arg))
        return default_value;

    /*
     * assigins the first character of arg
     * to asciic if atoi return 0
     */
    if(!(asciic = atoi(arg)))
        asciic = *arg;

    return asciic;
}

/*
 * returns 1 if the ch is not in the character
 * blacklist specified in the command-line
 */
char invalid_char(char ch, char *blacklist) {
    if(!blacklist)
        return 0;

    for(int c = 0; blacklist[c]; c++)
        if(ch == blacklist[c])
            return 1;

    return 0;
}

/*
 * generates a random char with the ascii
 * value between start and end
 */
char random_char(char start, char end, char *blacklist) {
    char new_char;
    register char previous_char;

    do
        new_char = rand() % (end - (start - 1)) + start;
    while(new_char == previous_char ||
        invalid_char(new_char, blacklist) ||
        isspace(new_char) ||
        new_char == 32);
        /*
         * FIXME: it was supposed to this
         * part of code prevent the space
         * character (33, ' ')
         */

    previous_char = new_char;
    return new_char;
}

void generate_password(char limit, char start, char end, char *password_ptr, char *blacklist) {
    for(char c = 0; c < limit; c++)
        password_ptr[c] = random_char(start, end, blacklist);
}
