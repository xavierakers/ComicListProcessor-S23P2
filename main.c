#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<string.h>
#include "comic.h"
/*“As a Hokie, I will conduct myself with honor and integrity at all times.  I will not lie, cheat, or steal, nor will I accept the actions of those who do.”*/

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "Usage: %s input_commands.txt output.txt\n", argv[0]);
        exit(1);
    }


    struct Comic_List comic_list;
    struct Comic_List cart;

    initialize_comic_list(&comic_list);
    initialize_comic_list(&cart);
    

    read_commands(argv[1], argv[2], &comic_list, &cart);
    free_comic_list(&comic_list);
    free(cart.list);
    //free(comic_list.list);
    //free_comic_list(&cart);

    return 0;
}