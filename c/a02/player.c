#include "player.h"

void construct_player(Player **player, int awakeness_percent, int body_temperature_percent)
{
    *player = malloc(sizeof(Player));

    (*player)->awakeness_percent = awakeness_percent;
    (*player)->body_temperature_percent = body_temperature_percent;
}

void print_player(Player *player)
{
    printf("Player { awakeness_percent: %d, body_temperature_percent: %d }\n",
        player->awakeness_percent,
        player->body_temperature_percent
    );
}

void increase_awakeness(Player *player, char amount)
{
    player->awakeness_percent += amount;
}

void increase_body_temperature(Player *player, char amount)
{
    player->body_temperature_percent += amount;
}

void display_state(Player *player)
{
    printf("\t\tAwakeness: %d %%\n\t\tBody temperature: %d %%\n", player->awakeness_percent, player->body_temperature_percent);
}
