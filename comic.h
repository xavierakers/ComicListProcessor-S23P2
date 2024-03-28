#include<stdio.h>
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>

struct Comic_List{
    struct Comic* list;
    int size;
    int count;
};

struct Comic{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char* cost;
};
void load(char filename[], struct Comic_List *comic_list, int* num);
void initialize_comic(struct Comic* comic, char date[], char code[], char publisher[], char title[], char cost[]);
void initialize_comic_list(struct Comic_List *list);
void expand_comic_list(struct Comic_List *list);
void free_comic_list(struct Comic_List* list);
void read_commands(char input_command_file[], char output_file[], struct Comic_List* Comic_List, struct Comic_List* cart);
void add_comic(struct Comic_List* list, struct Comic* comic);
void buy(FILE* out, struct Comic_List* list, struct Comic_List* cart, int num);
void checkout(FILE* out, struct Comic_List* cart);
void display(FILE* out, struct Comic_List* list);
void save(char filename[], struct Comic_List* list);
void clear(struct Comic_List* list);
void find(FILE* out, struct Comic_List* list, int index);
void remove_comic(FILE* out, struct Comic_List* list, int index);
void free_comic(struct Comic* comic);