# balls_and_their_admirers

The program creates BALL_COUNT balls. Each ball gets random properties: Position within the window, velocity in both x and y directions, radius and color. Each ball also picks another random ball from the group to “follow.” This is stored as a pointer: p->follows.
During each frame, every ball calculates the direction of its leader (the ball it follows). Adjusts its velocity slightly toward that leader. Updates its position.
