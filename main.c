#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800
#define TITLE "Balls and their admirers"
#define BALL_COUNT 20
#define FPS 60
#define VEL_MAX 5
#define RADIUS_MAX 20
#define RADIUS_MIN 10


Color COLORS[] = {
    LIGHTGRAY, GRAY,   DARKGRAY, YELLOW,     GOLD,      ORANGE,  PINK,
    RED,       MAROON, GREEN,    LIME,       DARKGREEN, SKYBLUE, BLUE,
    DARKBLUE,  PURPLE, VIOLET,   DARKPURPLE, BEIGE,     BROWN,   DARKBROWN,
};

// Definition of Ball

typedef struct Ball {
  float posx;
  float posy;
  float velx;
  float vely;
  float radius;
  Color color;
  struct Ball *follows; /* Pointer to another ball */
} Ball;

Ball balls[BALL_COUNT];

// Initializes a ball with random values
Ball *init_ball_random(Ball *p) {
  // Randomly initialize state and properties
  p->posx = rand() % WIDTH;
  p->posy = rand() % HEIGHT;
  p->velx = ((rand() % (2 * VEL_MAX)) - VEL_MAX);
  p->vely = ((rand() % (2 * VEL_MAX)) - VEL_MAX);
  p->radius = (RADIUS_MIN + rand() % (RADIUS_MAX - RADIUS_MIN + 1));
  p->color = COLORS[rand() % (sizeof(COLORS) / sizeof(Color))];

  // Find a leading ball other than the initialized ball itself.
  Ball *leader;

  leader = &balls[rand() % BALL_COUNT];

  p->follows = leader;
  return p;
}

// Initialize all `balls`
void init_balls_random() {
  for (size_t count = 0; count < BALL_COUNT; count++) {
    Ball initball;
    init_ball_random(&initball);
    balls[count] = initball;
  }
}

Ball *draw_ball(Ball *p) {
  DrawCircle(p->posx, p->posy, p->radius, p->color);
  return p;
}

// Updates the positions of balls according to their velocities
Ball *update_pos(Ball *p) {
  p->posx = fmodf(WIDTH + p->posx + p->velx, WIDTH); /* Måtte ændre */
  p->posy = fmodf(HEIGHT + p->posy + p->vely, HEIGHT);
  return p;
}

// Updates the velocity of a ball so that it follows the leading ball
Ball *update_vel_for_following(Ball *p) {
  int errx = p->follows->posx - p->posx;
  int erry = p->follows->posy - p->posy;
  p->velx = errx > 0 ? 1 : -1;
  p->vely = erry > 0 ? 1 : -1;
  return p;
}

// Update all elements
void update_elements() {
  for (size_t i = 0; i < BALL_COUNT; ++i) { /* changed to BALL_COUNT and defined top */
    draw_ball(update_pos(update_vel_for_following(&balls[i])));
  }
}

int main() {
  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  init_balls_random();

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();
    update_elements();
    ClearBackground(RAYWHITE);
    EndDrawing();
  }
}