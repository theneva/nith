#include <stdio.h>

#include "boolean.h"

void print_boolean(boolean value)
{
    printf(value == true ? "true" : "false");
}