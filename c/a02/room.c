#include "room.h"

void construct_room(Room **room, char *name)
{
    *room = malloc(sizeof(Room));

    (*room)->name = name;
    (*room)->number_of_neighboring_rooms = 0;
    (*room)->number_of_items = 0;
    
    (*room)->neighboring_rooms = malloc(sizeof(Room*) * MAX_NEIGHBORING_ROOMS);
    (*room)->inventory = malloc(sizeof(Item*) * CAPACITY_ITEMS);
}

void add_neighboring_room(Room *room, Room *neighboring_room)
{
    room->neighboring_rooms[room->number_of_neighboring_rooms] = neighboring_room;
    room->number_of_neighboring_rooms++;
}

void link_rooms(Room *a, Room *b)
{
    add_neighboring_room(a, b);
    add_neighboring_room(b, a);
}

void add_item(Room *room, Item *item)
{
    room->inventory[room->number_of_items] = item;
    room->number_of_items++;
}

void remove_item(Room *room, Item *item)
{
    int i;
    for (i = 0; i < room->number_of_items; i++)
    {   
        // If there's a match, overwrite and move everything right of the item to the left.
        if (item == room->inventory[i])
        {
            free(room->inventory[i]);

            // Start with the item one to the right. Breaks anyway if rightmost.
            int item_index = i + 1;
            for (; item_index < room->number_of_items; item_index++)
            {
                room->inventory[item_index - 1] = room->inventory[item_index];
            }

            room->number_of_items--;

            break;
        }
    }
}

void print_room(Room *room)
{
    printf("Room: { Name: %s, ", room->name);
    printf("Number of neighboring rooms: %d, ", room->number_of_neighboring_rooms);

    int i;
    for (i = 0; i < room->number_of_neighboring_rooms; i++)
    {
        printf("Neighboring room %d: %s, ", i, room->neighboring_rooms[i]->name);
    }

    printf("Number of items: %d, ", room->number_of_items);
    for (i = 0; i < room->number_of_items; i++)
    {
        print_item(room->inventory[i]);
        printf(", ");
    }

    printf("}\n");
}
