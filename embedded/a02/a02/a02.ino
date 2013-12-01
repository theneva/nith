#include <TFT.h>
#include <SPI.h>

#include "a02.h"

// Screen stuff.
TFT screen = TFT(pin_screen_cs, pin_screen_dc, pin_screen_res);
short screen_width, screen_height;

// Game stuff.
int state;
int score, score_previous, high_score;
char score_as_charray[score_charray_length], score_previous_as_charray[score_charray_length];
short score_number_offset;

// Paddle stuff.
short paddle_x = (screen_width / 2) - (paddle_x / 2);
short paddle_x_previous = -1;
short paddle_y;

// Ball stuff.
short ball_x, ball_y, ball_x_previous, ball_y_previous;

// Bullet stuff.
boolean bullet_exists;
short bullet_x, bullet_y, bullet_y_previous;

// Enemy stuff.
short enemy_x, enemy_y, enemy_x_previous;
byte enemy_width = 40, enemy_height = 40;

void setup()
{
  Serial.begin(9600);

  // Set up the screen.
  screen.begin();
  screen.background(background_r, background_g, background_b);

  screen_width = screen.width();
  screen_height = screen.height();

  score_number_offset = screen_width - 25;

  // Display the score label.
  screen.setTextSize(1);
  screen.stroke(text_r, text_g, text_b);
  screen.text("score: ", screen_width - 60, 0);

  screen.stroke(background_r, background_g, background_b);

  // Dis where it's at, yo.
  paddle_y = screen_height - (paddle_height * 2);

  reset_bullet();
  refresh_paddle();

  reset_enemy();

  state = state_playing;
}

void loop()
{
  switch (state)
  {
  case state_playing: 
    update_playing(); 
    break;
  case state_game_over: 
    update_game_over(); 
    break;
  default: 
    exit(-1);
  }
}

// ======================================================================

void update_playing()
{
  update_player();  

  update_enemy();

  if (bullet_exists)
  {
    update_bullet();
  }

  if (enemy_width <= 0 || enemy_height <= 0)
  {
    set_game_over();
  }

  update_score();

  // Slow down, son.
  delay(6);
}

void update_player()
{
  move_player();
  if (stick_is_down())
  {
    if (!bullet_exists)
    {
      shoot();
    }
  }
}

void update_score()
{
  // Update the score value.
  score_previous = score;
  score = millis() / 1000;

  if (score != score_previous) 
  {
    refresh_score();
  }
}

void refresh_score()
{
  // Get a text representation of both scores.
  String(score_previous).toCharArray(score_previous_as_charray, score_charray_length);
  String(score).toCharArray(score_as_charray, score_charray_length);

  // Erase the previous score.
  screen.stroke(background_r, background_g, background_b);
  screen.text(score_previous_as_charray, score_number_offset, 0);

  // Display the new score.
  screen.stroke(text_r, text_g, text_b);

  screen.text(score_as_charray, score_number_offset, 0);

  // Reset the borders to the foreground color.
  screen.stroke(background_r, background_g, background_b);  
}

void update_game_over()
{

}

// ========================================================================

void move_player()
{
  if (paddle_x != paddle_x_previous)
  {
    refresh_paddle();
  }

  // Can only be one at a time. Sorry.
  if (stick_is_left())
  {
    move_left();
  }
  else if (stick_is_right())
  {
    move_right();
  } 
}

boolean stick_is_down()
{
  short joystick_sw = analogRead(pin_joystick_sw);
  return joystick_sw < 10; // hax
}

boolean stick_is_left()
{
  short joystick_x = analogRead(pin_joystick_x);
  return joystick_x < 50; // hax
}

boolean stick_is_right()
{
  short joystick_x = analogRead(pin_joystick_x);
  return joystick_x > 950; // hax
}

// TODO: only do math when close to edge.
void move_right()
{ 
  if (paddle_x + paddle_width - (paddle_width / 2) + bullet_width < screen_width)
  {
    paddle_x += paddle_speed;
  }
  else
  {
    paddle_x = -(paddle_width / 2);
  }
}

// TODO: only do math when close to edge.
void move_left()
{
  if (paddle_x + (paddle_width / 2) - bullet_width > 0)
  {
    paddle_x -= paddle_speed;
  }
  else
  {
    paddle_x = screen_width - paddle_width / 2;
  }
}

void setBackgroundColor()
{
  screen.fill(background_r, background_g, background_b);
}

void setForegroundColor()
{
  screen.fill(foreground_r, foreground_g, foreground_b);
}

void refresh_paddle()
{
  // Fill over previous paddle.
  setBackgroundColor();
  screen.rect(paddle_x_previous, paddle_y, paddle_width, paddle_height);

  setForegroundColor();
  screen.rect(paddle_x, paddle_y, paddle_width, paddle_height);

  paddle_x_previous = paddle_x;
}

void shoot()
{
  bullet_x = paddle_x + paddle_width / 2 - bullet_width / 2;
  bullet_exists = true;
}

void update_bullet()
{
  check_bullet_collision();
  move_bullet();
}

void check_bullet_collision()
{
  if (bullet_y < screen_upper_limit)
  {
    reset_bullet();
  }
  else if (enemy_is_hit())
  {
    reset_bullet();
    reset_enemy();
    enemy_width -= 5;
    enemy_height -= 5;
  }
}

void move_bullet()
{
  bullet_y -= bullet_speed;
  refresh_bullet();
  bullet_y_previous = bullet_y;
}

void refresh_bullet()
{
  // Erase the existing bullet.
  setBackgroundColor();
  screen.rect(bullet_x, bullet_y_previous, bullet_width, bullet_height);

  if (!bullet_exists) return;

  // Draw the new bullet.
  setForegroundColor();
  screen.rect(bullet_x, bullet_y, bullet_width, bullet_height);
}

void reset_bullet()
{
  bullet_exists = false;
  bullet_y = paddle_y - (bullet_height / 2);
}

void reset_enemy()
{
  setBackgroundColor();
  screen.rect(enemy_x, enemy_y, enemy_width, enemy_height);

  enemy_x = 0 - enemy_width;
  enemy_y = screen_upper_limit;  
}

void update_enemy()
{
  enemy_x += enemy_speed;

  refresh_enemy();

  if (enemy_x > screen_width)
  {
    reset_enemy();
  }

  enemy_x_previous = enemy_x;
}

void refresh_enemy()
{
  setBackgroundColor();
  screen.rect(enemy_x_previous, enemy_y, enemy_width, enemy_height);

  setForegroundColor();
  screen.rect(enemy_x, enemy_y, enemy_width, enemy_height);
}

boolean enemy_is_hit()
{
  // This compensates for how the bullet moves (bullet speed) pixels at a time. Please don't ask. :(
  return bullet_x >= enemy_x && bullet_x + bullet_width <= enemy_x + enemy_width
    && (bullet_y >= enemy_y || bullet_y - bullet_speed >= enemy_y)
    && (bullet_y + bullet_height <= enemy_y + enemy_height || bullet_y - bullet_speed + bullet_height <= enemy_y + enemy_height);
}

void set_game_over()
{
  state = state_game_over;
}


