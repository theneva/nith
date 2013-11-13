#include "item.h"

void construct_item(Item **item, char *name, char *description, char *feedback_on_use, short effect_type, short effect_value)
{
    *item = malloc(sizeof(Item));

    // Won't need to type (*item) four times
    Item *i = *item;

    i->name = name;
    i->description = description;
    i->feedback_on_use = feedback_on_use;
    
    // 0 = type, 1 = value
    i->effect[0] = effect_type;
    i->effect[1] = effect_value;
}

void use_item(Item *item, Player *player)
{
    printf("%s\n", item->feedback_on_use);

    short effect = item->effect[1];

    switch (item->effect[0])
    {
        case AWAKENESS          : player->awakeness_percent += effect;          break;
        case BODY_TEMPERATURE   : player->body_temperature_percent += effect;   break;
        case NOTHING            :
        default                 : return;
    }
}

void print_item(Item *item)
{
    printf("Item { name: %s, description: %s, feedback on use: %s, effect: { %s, %d} }",
        item->name,
        item->description,
        item->feedback_on_use,
        item->effect[0] == AWAKENESS ? "awakeness" : "body_temperature",
        item->effect[1]
    );
}