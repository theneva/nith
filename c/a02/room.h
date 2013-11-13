#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

#define MAX_NEIGHBORING_ROOMS 3
#define CAPACITY_ITEMS 4

/** A room. */
typedef struct Room
{
    char *name;
    
    struct Room **neighboring_rooms;
    int number_of_neighboring_rooms;

    int number_of_items;
    Item **inventory;
} Room;

/** Allocates memory for and constructs a room. */
void construct_room(Room **room, char *name);

/** Adds a neighboring room to the first room. */
void add_neighboring_room(Room *room, Room *neighboring_room);

/** Links two rooms together. */
void link_rooms(Room *a, Room *b);

/** Adds an item to the room. */
void add_item(Room *room, Item *item);

/** Removes an item with the specified name from the desired room if found. */
void remove_item(Room *room, Item *item);

/** Prints a room. */
void print_room(Room *room);
