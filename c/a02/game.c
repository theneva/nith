#include "game.h"

int main(int argc, char **argv)
{
    boolean wine_installed = (system("which wine > /dev/null")) == 0 ? true : false;

    if (wine_installed == false)
    {
        // If the player didn't run the game with the argument "force",
        // just give an explanatory message and return.
        if (argc <= 1 || strcmp(argv[1], "force") != 0)
        {
            printf("Please install Wine in order to continue.\n\n\t\t\t\t... or just pass the argument \"force\".\n");
            return -1;
        }
    }

    /**
     * Set everything up.
     */
    Player *player;
    construct_player(&player, 1, 1);

    // Declare, allocate, and partially initialize each room.
    Room *bedroom, *bathroom, *living_room, *kitchen, *outside;
    construct_room(&bedroom, "bedroom");
    construct_room(&bathroom, "bathroom");
    construct_room(&living_room, "living room");
    construct_room(&kitchen, "kitchen");
    construct_room(&outside, "outside");

    // Not really a room, but works as a proof of concept.
    Room *wardrobe;
    construct_room(&wardrobe, "wardrobe");
    link_rooms(bedroom, wardrobe);

    // Link all the rooms together.
    link_rooms(bedroom, bathroom);
    link_rooms(bathroom, living_room);
    link_rooms(living_room, kitchen);

    // outside doesn't need to link back to living room.
    add_neighboring_room(living_room, outside); 
    
    // Stash all the rooms into an array for easier management later.
    Room *rooms[] = { bedroom, wardrobe, bathroom, living_room, kitchen, outside };

    // Items found in the bedroom.
    Item *clothes;
    construct_item(&clothes, "Clothes", "Put on some clothes", "The clothes are cold, but way better than nothing.", BODY_TEMPERATURE, 40);
    add_item(bedroom, clothes);

    // Items found in the wardrobe.
    Item *scarf;
    construct_item(&scarf, "Scarf", "Put on a scarf", "The scarf warms you up nicely.", BODY_TEMPERATURE, 10);
    add_item(wardrobe, scarf);

    // Items found in the bathroom.
    Item *shower;
    construct_item(&shower, "Shower", "Take a shower", "A nice, hot shower heats your body up significantly.", BODY_TEMPERATURE, 50);
    add_item(bathroom, shower);

    Item *aspirin;
    construct_item(&aspirin, "Aspirin", "Take some Aspirin", "The world starts spinning more slowly.", AWAKENESS, 30);
    add_item(bathroom, aspirin);

    // Items found in the living room.
    Item *television;
    construct_item(&television, "Television", "Watch TV", "No time to waste. It doesn't work, anyway.", NOTHING, 0);
    add_item(living_room, television);

    // Items found in the kitchen.
    Item *coffee;
    construct_item(&coffee, "Coffee", "Drink coffee", "The coffee gives your brain a kick.", AWAKENESS, 70);
    add_item(kitchen, coffee);

    /**
     * Game on!
     */
     printf("Last night's party was good, even though the music was terrible.\nYou wake up in your cabin's bedroom, and it's freezing.\nYou have a pretty bad hangover as well.\nYou have to find a way of getting warmed up and fully awake so you can go out skiing.\n");
     printf("You're in terrible condition:\n");
     display_state(player);

    Room *current_room = bedroom;
    for (;;)
    {
        display_options(current_room);

        int selected_option;
        scanf("%d", &selected_option); // Tentative TODO: Validate input.

        // Check that the input is in range
        if (selected_option < 1 || selected_option > current_room->number_of_neighboring_rooms + current_room->number_of_items)
        {
            printf("Let's try that again.\n");
            continue;
        }

        // Items go first, so find out whether the user selected using an item.
        // If they use an item, use that item.
        if (selected_option <= current_room->number_of_items)
        {
            Item *selected_item = current_room->inventory[selected_option - 1];
            
            printf("\n\t");
            use_item(selected_item, player);
            printf("\n");

            remove_item(current_room, selected_item);
            
            display_state(player);
        }
        else // The user selected a room.
        {   
            Room *selected_room = current_room->neighboring_rooms[selected_option - current_room->number_of_items - 1];

            if (selected_room == outside) // The player wants to go outside.
            {
                printf("\t");

                if (player->awakeness_percent >= 100 && player->body_temperature_percent >= 100)
                {
                    printf("You win!\n");
                    if (wine_installed == false) break;                                                                                                                                                                                                                             system("wine ./bin/.s 2> /dev/null"); break;
                }
                else if (player->awakeness_percent >= 100)
                {
                    printf("You're still way too cold!\n");
                }
                else if (player->body_temperature_percent >= 100)
                {
                    printf("You're still so tired, you'd probably fall and break your crazy neck.\n"); // Weak Catcher in the Rye reference, sorry. I'm re-reading it at the moment.
                }
                else
                {
                    printf("You're still in awful condition. Fix yourself up first!\n");
                }

                display_state(player);
            }
            else
            {
                // If they move to any room that's not outside, just update the current room.
                current_room = selected_room;
            }
        }
    }

    /**
     * Game over. Free ALL the things!
     */
    free(player);

    // Free each room's allocated memory.
    // Tentative TODO: This could be solved by looking at each room's next room recursively.
    int room_index;
    for (room_index = 0; room_index < NUMBER_OF_ROOMS; room_index++)
    {
        Room* current_room = rooms[room_index];

        free(current_room->neighboring_rooms);

        // Free each item's allocated memory.
        // If it's not in a room, it shouldn't exist.
        int item_index;
        for (item_index = 0; item_index < current_room->number_of_items; item_index++)
        {
            free(current_room->inventory[item_index]);
        }

        free(current_room->inventory);
        free(current_room);
    }

    return 0;
}

void display_options(Room *current_room)
{
    printf("What do you want to do?\n");
    int counter = 1;
    int i;

    for (i = 0; i < current_room->number_of_items; i++)
    {
        printf("%d) %s\n", counter++, current_room->inventory[i]->description);
    }

    for (i = 0; i < current_room->number_of_neighboring_rooms; i++)
    {
        printf("%d) Go to %s\n", counter++, current_room->neighboring_rooms[i]->name);
    }
}
