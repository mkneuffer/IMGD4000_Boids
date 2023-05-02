Matthew Neuffer

Video: https://www.youtube.com/watch?v=Zen6pCkrC-4

Game: User can move target across screen, which the flock will follow. You can move the target left and right across the screen using the arrow buttons.

Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.
Rule 2: Boids try to keep a small distance away from other objects (including other boids).
Rule 3: Boids try to match velocity with near boids.
Rule 4: Boids try to fly toward the target.


When opening the game:
- open the "Flocking_IMGD4000_MatthewNeuffer map.
- compile the code
- open the FlockingGameModeBase_BP and reconnect the Taret_BP to the blueprint slot
- You might need to reconnect the cone shape to the boids actor
- Still in the FlockingGameModeBase_BP, open the viewport, select the Agent Mesh and set the static mesh to GlowCone.