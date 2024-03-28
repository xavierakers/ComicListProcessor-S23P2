#include<stdio.h>
#include<math.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>
#include <stdlib.h>
#include "comic.h"

//This function opens and read through the command file
void read_commands(char input_command_file[], char output_file[], struct Comic_List* comic_list, struct Comic_List* cart){
    FILE* in = fopen(input_command_file, "r");
    FILE* out = fopen(output_file, "w");

    //If command file does not exist
    if(in == NULL){
        printf("unable to open file\n");
        return;
    }

    while(!feof(in)){
        char input[11];
        char data[101];
        fscanf(in, "%s", input);
        fgetc(in);


        if(feof(in)){
            break;
        }
        //Checks what the string that follows the command is
        fprintf(out, "Command: %s", input);
        if(strcmp(input, "load") == 0){
            int num = 0;
            fscanf(in, "%s", data);
            fgetc(in);
            load(data, comic_list, &num);
            fprintf(out, " %s\n", data);
            fprintf(out, "\t Number of comics: %d\n", num);
        }

        if(strcmp(input, "buy") == 0){
            fscanf(in, " %s", data);
            fgetc(in);
            fprintf(out, " %s\n", data);
            //Changing the string to an integer
            char *ptr;
            buy(out, comic_list, cart, strtol(data, &ptr, 10));
        }

        if(strcmp(input, "checkout") == 0){
            data[0] = '\0';
            checkout(out, cart);
        }

        if(strcmp(input, "display") == 0){
            data[0] = '\0';
            display(out, comic_list);
        }

        if(strcmp(input, "save") == 0){
            fscanf(in, "%s", data);
            fgetc(in);
            fprintf(out, " %s\n", data);
            save(data, comic_list);
        }

        if(strcmp(input, "clear") == 0){
            data[0] = '\0';
            fprintf(out, "\n");
            clear(comic_list);
        }

        if(strcmp(input, "find") == 0){
            fscanf(in, "%s", data);
            fgetc(in);
            fprintf(out, " %s\n", data);
            int x = strtod(data, NULL);
            find(out, comic_list, x);
        }

        if(strcmp(input, "remove") == 0){
            fscanf(in, "%s", data);
            fgetc(in);
            fprintf(out, " %s\n", data);
            int x = strtod(data, NULL);
            remove_comic(out, comic_list, x);
        }
    }

    fclose(in);
    fclose(out);
}

//Allocates memory for each vairiables in struct Comic and makes it a perfect string from the buffer
void initialize_comic(struct Comic* comic, char date[], char code[], char publisher[], char title[], char cost[]){
    
    comic->date = malloc(strlen(date) + 1);
    strcpy(comic->date, date);

    comic->code = malloc(strlen(code) + 1);
    strcpy(comic->code, code);

    comic->publisher = malloc(strlen(publisher) + 1);
    strcpy(comic->publisher, publisher);
    
    comic->title = malloc(strlen(title) + 1);
    strcpy(comic->title, title);
    
    comic->cost = malloc(strlen(cost) + 1);
    strcpy(comic->cost, cost);
}

//Allocates memory for the list
void initialize_comic_list(struct Comic_List* list){
    list->list = malloc(10 * sizeof(struct Comic));
    list->size = 10;
    list->count = 0;    
}

//Reallocates memory if the list reaches its max size
void expand_comic_list(struct Comic_List* list){
    struct Comic comic;
    list->size = list->size*2;
    list->list = realloc(list->list, list->size*sizeof(comic));
}


//Reads and stores the values in the .csv file
void load(char filename[], struct Comic_List* list, int* num){

    FILE* in = fopen(filename, "r");
    char intro[101];
    fgets(intro, sizeof(intro), in);
    if(in == NULL){
        printf("Error opening file\n");
        return;
    }

    //Buffas
    char date[1000];
    char code[1000];
    char publisher[1000];
    char title[1000];
    char cost[1000];
    int i = 0;

    while(!feof(in)){
        struct Comic comic;
        fscanf(in, "%[^,]", date);
        fgetc(in);
        fscanf(in, "%[^,]", code);
        fgetc(in);
        fscanf(in, "%[^,]", publisher);
        fgetc(in);
        fscanf(in, "%[^,]", title);
        fgetc(in);
        fscanf(in, "%[^\n]", cost);
        fgetc(in);
        //sends buffers
        initialize_comic(&comic, date, code, publisher, title, cost);
        //add comic the comic_list->list
        add_comic(list, &comic);
        i++;
    }
    
    list->count--;
    fclose(in);
    //sends back how many items were in the .csv
    *num = i-1;
}

void add_comic(struct Comic_List* list, struct Comic* comic){
    if(list->count == list->size){
        expand_comic_list(list);
    }
    //sets pointer to the comic
    if(list->count < list->size){
        list->list[list->count] = *comic;
        list->count++;
    }
}

//add respective item to the cart
void buy(FILE* out, struct Comic_List* list, struct Comic_List* cart, int num){
    int index = num;
    if(cart->count == cart->size){
        expand_comic_list(cart);
    }
    //checks if index is in range
    if((index < list->count) && (index >= 0)){
        cart->list[cart->count] = list->list[index];
        cart->count++;
        fprintf(out, "Comic #%d added to purchase list\n", num);
        return;
    }
    fprintf(out, "Unable to buy comic #%d\n", num);

}



void checkout(FILE* out, struct Comic_List* cart){
    fprintf(out, "\nComics in Purchase List\n");
    double subtotal = 0.00;
    double tax = 0.00;
    double total = 0.00;


    for(int i = 0; i < cart->count; i++){
        fprintf(out, "Comic Number: %d\n", i+1);
        fprintf(out, "\tDate: %s\n", cart->list[i].date);
        fprintf(out, "\tCode: %s\n", cart->list[i].code);
        fprintf(out, "\tPublisher: %s\n", cart->list[i].publisher);
        fprintf(out, "\tTitle: %s\n", cart->list[i].title);
        fprintf(out, "\tCost: %s\n", cart->list[i].cost);

        //makes sure there is a price and ignore if no price assigned
        if(strcmp(cart->list[i].cost, "AR") != 0){
            //copies the price to a temp variable
            char str[11];
            strcpy(str, cart->list[i].cost);

            //removes the dolla sign
            int len = strlen(str);
            for(int i = 0; i < len; i++){
                str[i] = str[i+1];
            }

            //converts string to a double
            char *ptr;
            double num = strtod(str, &ptr);
            subtotal = subtotal + num;
            //free_comic(&cart->list[i]);
        }
    }

    //ew tax
    tax = subtotal * 0.05;
    total = tax + subtotal;
    
    fprintf(out, "Subtotal: \t$%.2f\n", subtotal);
    fprintf(out, "Tax: \t$%.2f\n", tax);
    fprintf(out, "Total: \t$%.2f\n", total);
    //free_comic_list(cart);

}

void display(FILE* out, struct Comic_List* list){
    fprintf(out, "\n");
    if(list->count == 0){
        fprintf(out, "List is currently empty.\n");
        return;
    }

    for(int i = 0; i < list->count; i++){
        fprintf(out, "Comic Number: %d\n", i+1);
        fprintf(out, "\tDate: %s\n", list->list[i].date);
        fprintf(out, "\tCode: %s\n", list->list[i].code);
        fprintf(out, "\tPublisher: %s\n", list->list[i].publisher);
        fprintf(out, "\tTitle: %s\n", list->list[i].title);
        fprintf(out, "\tCost: %s\n", list->list[i].cost);
    }
}
//saves all items in the list to a new file
void save(char filename[], struct Comic_List* list){
    FILE* out = fopen(filename, "w");
    fprintf(out, "DATE,CODE,PUBLISHER,TITLE,PRICE\n");
    for(int i = 0; i < list->count; i++){
        fprintf(out, "%s,", list->list[i].date);
        fprintf(out, "%s,", list->list[i].code);
        fprintf(out, "%s,", list->list[i].publisher);
        fprintf(out, "%s,", list->list[i].title);
        fprintf(out, "%s", list->list[i].cost);
        fprintf(out, "\n");
    }


    fclose(out);

}

void clear(struct Comic_List* list){
    free_comic_list(list);
    initialize_comic_list(list);
}

void find(FILE* out, struct Comic_List* list, int index){
    //makes sure index is in range
    if((index > list->count-1) || (index < 0)){
        fprintf(out, "There is no comic at index #%d in the list.\n", index);
        return;
    }
    fprintf(out, "\tDate: %s\n", list->list[index].date);
    fprintf(out, "\tCode: %s\n", list->list[index].code);
    fprintf(out, "\tPublisher: %s\n", list->list[index].publisher);
    fprintf(out, "\tTitle: %s\n", list->list[index].title);
    fprintf(out, "\tCost: %s\n", list->list[index].cost);

}

void remove_comic(FILE* out, struct Comic_List* list, int index){
    //makes sure index is in range
    if((index > list->count - 1) || (index < 0)){
        fprintf(out, "Comic at index %d was not removed\n", index);
        return;
    }

    fprintf(out, "Comic at index %d successfully removed\n", index);
    //shifts all items down one to fill gap
    for(int i = index; i < list->count; i++){
        list->list[i] = list->list[i+1];
    }
    free(list->list[list->count].date);
    free(list->list[list->count].code);
    free(list->list[list->count].publisher);
    free(list->list[list->count].title);
    free(list->list[list->count].cost);
    list->count--;
}    

void free_comic(struct Comic* comic){
    free(comic->date);
    free(comic->code);
    free(comic->publisher);
    free(comic->title);
    free(comic->cost);
}

void free_comic_list(struct Comic_List* list){
    
    for(int i = 0; i < list->count; i++){
        free_comic(&list->list[i]);
    }
    free(list->list);
}
