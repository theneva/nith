#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "player.h"

#define NOTHING -1
#define AWAKENESS 0
#define BODY_TEMPERATURE 1

/** An item. */
typedef struct
{
    char *name;
    char *description;
    char *feedback_on_use;
    // { AWAKENESS/BODY_TEMPERATURE, value to increase percentage by } -- I miss my objects :(
    short effect[2]; // This limits each item to affect either awakeness or body temperatur -- never both.
} Item;

/** Allocates memory for and constructs a new item. */
void construct_item(Item **item, char *name, char *description, char *feedback_on_use, short effect_type, short effect_value);

/** Uses the item on the player. */
void use_item(Item *item, Player *player);

/** Prints the item. */
void print_item(Item *item);
