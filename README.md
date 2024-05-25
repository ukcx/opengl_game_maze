# 3-D Game Development with OpenGL - Monster Chase in a Maze

This project involved the development of a 3-D game using C++ and OpenGL libraries.

## Project Overview
The primary objective was to create an interactive 3-D video game that incorporates various computer graphics principles and techniques. The game was designed to be challenging, fun to play, and included elements of scoring or winning and losing.

## Gameplay
The game, "Monster Chase in a Maze," challenges players to navigate through a maze while avoiding AI-controlled monsters and collecting rewards. The primary objective is to reach the end of the maze quickly without getting hit by the monster's arrows. Players start with 3 lives. Key gameplay elements include:

- **Maze Navigation:** Players start at the entrance of a maze, gradually revealing the maze's layout as they explore. A minimap displays the discovered parts of the maze.
- **AI Monster:** An AI-controlled monster detects the player's presence and launches arrows when aligned. Players can shoot arrows to destroy the monster or its projectiles.
- **Power-ups:** Randomly spawning coins grant power-ups such as extra score, reduced time, and increased speed.
- **Leaderboards:** Players achieving high scores can enter their names on the leaderboard, which displays top scores read from a file.
- **Game Loss Conditions:** Players lose lives if hit by arrows or colliding with the monster directly.

### Some Gameplay Captures:
![Gameplay Screenshot 1](https://github.com/ukcx/opengl_game_maze/assets/80484731/a0241cc8-8a17-48b0-9a16-7a14489ddc13)
![Gameplay Screenshot 2](https://github.com/ukcx/opengl_game_maze/assets/80484731/d52193e1-98a1-4eff-90cb-c56bf589d29f)
![Gameplay Screenshot 3](https://github.com/ukcx/opengl_game_maze/assets/80484731/6eb31f1a-9036-493f-a840-0cb824c903e7)
![Gameplay Screenshot 4](https://github.com/ukcx/opengl_game_maze/assets/80484731/3ec63711-7703-4e5e-9869-48503f938091)

## Implemented Functionalities

### Basic Functionalities
1. **3D Viewing and Objects:**
   - Implemented perspective views with smooth viewpoint changes.
   - Utilized OpenGL for transformation, clipping, and hidden-surface removal.

2. **User Input:**
   - Supported player interaction via keyboard or mouse controls.

3. **Lighting and Smooth Shading:**
   - Employed OpenGL's lighting model for object illumination.
   - Defined normal vectors, materials, and light sources for realism.

4. **Texture Mapping:**
   - Implemented texture mapping for enhanced visual aesthetics.

### Advanced Functionalities
1. **On-screen Control Panel (HUD):**
   - Developed a Heads-Up Display (HUD) with orthographic projection.
   - Displayed game information such as remaining time, player speed, lives, and maze map.
   - Utilized FreeType library for text rendering.

2. **Level of Detail (LOD):**
   - Implemented LOD control to optimize rendering based on object distance.

3. **AI:**
   - AI monster calculates the shortest path to the player using A* search algorithm.
   
4. **Collision Detection:**
   - Enhanced gameplay realism with collision detection between:
     - Player and monster
     - Monster and arrows
     - Arrows and arrows
     - Player and arrows
     - Any moving object with walls
     - Random objects (like trees, other decoratives) that exist in the maze with the moving objects
     - Coins and the player
     - Start and end points with the player to ensure that the player is never outside the maze.
   
5. **Simulated Dynamics:**
   - Implemented physics mechanisms like acceleration, deceleration, and realistic rotation.

## Conclusion
The "Monster Chase in a Maze" project provided hands-on experience in applying computer graphics concepts to create an engaging gaming experience. Leveraging OpenGL and C++, the team successfully implemented advanced functionalities, resulting in an immersive gameplay experience.
