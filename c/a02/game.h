#pragma once

#include <stdio.h>

#include "lib/boolean.h"
#include "player.h"
#include "room.h"
#include "item.h"

// Needs to be updated whenever a new room is "installed".
// Could use a buffer and a terminating character, but the game is very small.
#define NUMBER_OF_ROOMS 6

void display_options(Room *current_room);