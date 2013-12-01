#pragma once

// Screen stuff.
#define pin_screen_cs 10
#define pin_screen_dc 9
#define pin_screen_res 8

#define pin_sd_cs 4

#define pin_joystick_x A3 
#define pin_joystick_y A4
#define pin_joystick_sw A5

#define screen_upper_limit 13

// Colors.
#define foreground_r 0
#define foreground_g 255
#define foreground_b 0

#define background_r 0
#define background_g 0
#define background_b 0

#define text_r 255
#define text_g 0
#define text_b 0

// Game stuff.
#define game_over_screen_display_time 3000

#define state_playing 0
#define state_game_over 1

// Score stuff.
#define score_charray_length 4

// Paddle stuff.
#define paddle_width 20
#define paddle_height 5
#define paddle_speed 5

// Bullet stuff.
#define bullet_width 4
#define bullet_height 4
#define bullet_speed 5

// Enemy stuff.
#define enemy_speed 2
#define enemy_width_default 40
#define enemy_height_default 40

