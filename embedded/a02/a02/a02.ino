#include <TFT.h>
#include <SPI.h>
#include <SD.h>

#include "a02.h"

// Screen stuff.
TFT screen = TFT(pin_screen_cs, pin_screen_dc, pin_screen_res);
short screen_width, screen_height;

// Game stuff.
byte state;
short score, score_previous, high_score;

// The path to the file containing the high score.
char *file_path = "score.txt";

// Time time at which the current game was started.
long current_game_start_millis = 0;

// Character arrays for each score so they can be printed to the screen.
char score_as_charray[score_charray_length],
score_previous_as_charray[score_charray_length],
high_score_as_charray[score_charray_length];

// Offsets for printing to screen
short score_number_offset;
short score_text_offset;

// Paddle stuff.
short paddle_x;
short paddle_x_previous = -1;
short paddle_y;

// Ball stuff.
short ball_x, ball_y, ball_x_previous, ball_y_previous;

// Bullet stuff.
boolean bullet_exists;
short bullet_x, bullet_y, bullet_y_previous;

// Enemy stuff.
short enemy_x, enemy_y, enemy_x_previous;
byte enemy_width, enemy_height;

/* ARDUINO STUFF. */

void setup()
{
  // Yeah...
  Serial.begin(9600);

  /*
   * Read the high score from the SD card.
   */
  pinMode(pin_sd_cs, OUTPUT);
  if (!SD.begin(pin_sd_cs))
  {
    Serial.println("Failed to initialize the SD card.");
    return;
  }

  // The file containing the high score.
  if (SD.exists(file_path))
  {
    Serial.println("High score file exists. Reading score...");

    File file_high_score = SD.open(file_path); // readonly by default

    // Get the existing high score.
    String high_score_as_string = file_high_score.readStringUntil('\n');

    file_high_score.close();

    high_score_as_string.toCharArray(high_score_as_charray, score_charray_length);
    high_score = atoi(high_score_as_charray);

    Serial.print("High score read: ");
    Serial.println(high_score);

    // Make sure the (first line of the) file is formatted properly. If not, reset it to default value.
    if (high_score == 0)
    {
      update_high_score(default_high_score);
    }
  }
  else
  {
    Serial.println("File did not exist. Creating it with default high score 999...");

    // Default high score.
    update_high_score(default_high_score);
  }

  /**
   * Set up the screen.
   */
  screen.begin();
  screen.background(background_r, background_g, background_b);

  screen_width = screen.width();
  screen_height = screen.height();

  score_text_offset = screen_width - 60;   // magic
  score_number_offset = screen_width - 25; // magic

  set_up_playing();
}

void loop()
{
  // Fairly easy to add more states.
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

/* STATE SET-UPS. */

/**
 * Sets up the playing state.
 */
void set_up_playing()
{
  // Black as the night.
  screen.fillScreen(0);

  // Display the score label.
  screen.setTextSize(1);
  screen.stroke(text_r, text_g, text_b);
  screen.text("score: ", score_text_offset, 0);

  screen.stroke(background_r, background_g, background_b);

  score = 0;
  score_previous = 0;

  String(score).toCharArray(score_as_charray, score_charray_length);
  String(score_previous).toCharArray(score_previous_as_charray, score_charray_length);

  // Dis where it's at, yo.
  paddle_x = (screen_width / 2) - (paddle_x / 2);
  paddle_y = screen_height - (paddle_height * 2);

  reset_bullet();
  refresh_paddle();

  enemy_width = enemy_width_default;
  enemy_height = enemy_height_default;

  reset_enemy();

  current_game_start_millis = millis();

  state = state_playing;
}

/**
 * Sets up the game over state.
 */
void set_up_game_over()
{ 
  // Just plain black.
  screen.fillScreen(0);

  // If the new score is better, update the high score and the file.
  if (score < high_score)
  {
    update_high_score(score);
  }

  String(high_score).toCharArray(high_score_as_charray, 4);

  screen.stroke(text_r, text_g, text_b);

  screen.setTextSize(1);
  screen.text("You : ", 0, 0);
  screen.text(score_as_charray, 35, 0);
  screen.text("High: ", 0, 20);
  screen.text(high_score_as_charray, 35, 20);

  screen.setTextSize(2);

  screen.text("Get ready!", 0, 40);

  state = state_game_over;
}

/* STATE UPDATES. */

/**
 * The playing state.
 */
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
    set_up_game_over();
  }

  update_score();

  // Slow down, son.
  delay(6);
}

/**
 * The game over state.
 */
void update_game_over()
{
  delay(game_over_screen_display_time);

  set_up_playing();
}

/* PLAYER STUFF. */

/**
 * Updates the player.
 */
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

/**
 * Moves the paddle if requested by the user.
 */
void move_player()
{
  if (paddle_x != paddle_x_previous)
  {
    refresh_paddle();
  }

  // Can only be one at a time.
  if (stick_is_left())
  {
    move_left();
  }
  else if (stick_is_right())
  {
    move_right();
  } 
}

/**
 * Moves the paddle to the right.
 *
 * TODO: only do math when close to edge.
 */
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

/**
 * Moves the paddle to the left.
 * 
 * TODO: only do math when close to edge.
 */
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

/**
 * Clears the old paddle and draws it in its new position.
 */
void refresh_paddle()
{
  // Fill over previous paddle.
  setBackgroundColor();
  screen.rect(paddle_x_previous, paddle_y, paddle_width, paddle_height);

  setForegroundColor();
  screen.rect(paddle_x, paddle_y, paddle_width, paddle_height);

  paddle_x_previous = paddle_x;
}

/* BULLET STUFF. */

/**
 * Shoots a bullet.
 */
void shoot()
{
  bullet_x = paddle_x + paddle_width / 2 - bullet_width / 2;
  bullet_exists = true;
}

/**
 * Updates the bullet.
 */
void update_bullet()
{
  check_bullet_collision();
  move_bullet();
}

/**
 * Removes the bullet and (possibly) enemy if necessary.
 */
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
    enemy_width -= enemy_width_shrinking;
    enemy_height -= enemy_height_shrinking;
  }
}

/**
 * Moves the bullet.
 */
void move_bullet()
{
  bullet_y -= bullet_speed;
  refresh_bullet();
  bullet_y_previous = bullet_y;
}

/**
 * Refreshes the bullet rectangle by clearing the old one and drawing the new one.
 */
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

/**
 * Resets the bullet to its default position.
 */
void reset_bullet()
{
  bullet_exists = false;
  bullet_y = paddle_y - (bullet_height / 2);
}

/* ENEMY STUFF. */

/**
 * Resets the enemy to its default position.
 */
void reset_enemy()
{
  setBackgroundColor();
  screen.rect(enemy_x, enemy_y, enemy_width, enemy_height);

  enemy_x = 0 - enemy_width;
  enemy_y = screen_upper_limit;  
}

/**
 * Updates the enemy.
 */
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

/**
 * Erases the old enemy rectangle and draws a new one.
 */
void refresh_enemy()
{
  setBackgroundColor();
  screen.rect(enemy_x_previous, enemy_y, enemy_width, enemy_height);

  setForegroundColor();
  screen.rect(enemy_x, enemy_y, enemy_width, enemy_height);
}

/**
 * Returns whether or not the enemy has been hit by a bullet.
 */
boolean enemy_is_hit()
{
  // This compensates for how the bullet moves (bullet speed) pixels at a time. Please don't ask. :(
  return bullet_x >= enemy_x && bullet_x + bullet_width <= enemy_x + enemy_width
    && (bullet_y >= enemy_y || bullet_y - bullet_speed >= enemy_y)
    && (bullet_y + bullet_height <= enemy_y + enemy_height || bullet_y - bullet_speed + bullet_height <= enemy_y + enemy_height);
}

/* SCREEN STUFF. */

/**
 * Updates the fill color of the screen to the background color.
 */
void setBackgroundColor()
{
  screen.fill(background_r, background_g, background_b);
}

/**
 * Updates the fill color of the screen to the foreground color.
 */
void setForegroundColor()
{
  screen.fill(foreground_r, foreground_g, foreground_b);
}

/* INPUT STUFF. */

/**
 * Returns whether the stick is pressed.
 */
boolean stick_is_down()
{
  short joystick_sw = analogRead(pin_joystick_sw);
  return joystick_sw < 10; // hax
}

/**
 * Returns whether the stick is pointed left.
 */
boolean stick_is_left()
{
  short joystick_x = analogRead(pin_joystick_x);
  return joystick_x < 50; // hax
}

/**
 * Returns whether the stick is pointed right.
 */
boolean stick_is_right()
{
  short joystick_x = analogRead(pin_joystick_x);
  return joystick_x > 950; // hax
}

/* SCORE STUFF. */

/**
 * Updates the score and refreshes the score on-screen if necessary.
 */
void update_score()
{
  // Update the score value. Score is as simple as millis() / 100.
  score_previous = score;
  score = (millis() - current_game_start_millis) / 100;

  if (score != score_previous) 
  {
    refresh_score();
  }
}

/**
 * Refreshes the score by clearing the old score from the screen and drawing the new one.
 */
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

/* HIGH SCORE STUFF. */

/**
 * Updates both the file and the high score variable to the new value.
 */
void update_high_score(int new_high_score)
{
  if (SD.exists(file_path))
  {
    SD.remove(file_path);
  }
  
  File file_high_score = SD.open(file_path, FILE_WRITE);
  file_high_score.println(new_high_score);
  
  file_high_score.close();
  
  // Set the variable as well.
  high_score = new_high_score;
}
