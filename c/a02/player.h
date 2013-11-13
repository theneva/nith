#pragma once

#include <stdio.h>
#include <stdlib.h>

/** The player. */
typedef struct
{
    int awakeness_percent;
    int body_temperature_percent;
} Player;

/** Allocates memory for and constructs a new player. */
void construct_player(Player **player, int awakeness_percent, int body_temperature_percent);

/** Prints the player. */
void print_player(Player *player);

/** Increases the awakeness of the player by the given amount. */
void increase_awakeness(Player *player, char amount);

/** Increases the body temperature of the player by the given amount. */
void increase_body_temperature(Player *player, char amount);

/** Displays the user's state, intended for players of the game. */
void display_state(Player *player);
