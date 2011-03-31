/**
 * This application consist of a simple game that we called "Super Fireman Brothers". 
 * This applications uses the XBox Kinect sensor to track the player's moves.
 *
 * Copyright (C) 2011 Alfonso Ros, Ismael Mendonca
 *
 * This file is part of Super Fireman Brothers.
 *
 * Super Fireman Brothers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Super Fireman Brothers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Super Fireman Brothers. Check the txt file "LICENSE",
 * If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 *  @file config.h
 *
 *  @brief Configuration header file.
 *
 *  This file contain the basic configuration for general behavior.
 *
 *  @authors Alfonso Ros e Ismael Mendonça
 */

# ifndef CONFIG_H
# define CONFIG_H

# define MAX_USERS 3
# define MAX_FIREBALLS 100
# define POSE_SIZE 20
# define CONFIDENCE 0.5f
# define NO_LISTENED -1

// crop borders when using image generator.

# define CROPUP       0.08
# define CROPDOWN     0.00
# define CROPLEFT     0.01
# define CROPRIGHT   -0.05

// Pose detection (in degrees)

# define STRAIGHT_RANGE 60

// Listener Types

# define NEUTRAL_TYPE 0
# define ZAMUS_TYPE 1
# define LINQ_TYPE 2

// Pose times

# define Z_POSE_TIME 3.5
# define Z_BUSTER_POSE_TIME 0.0
# define L_POSE_TIME 0.0
# define L_ICEROD_POSE_TIME 0.0

// Zamus and Linq shoots

# define Z_SHOOT_SPEED    1.5
# define Z_SHOOT_MAX_DIST 10000
# define Z_SHOOT_DELAY    2
# define L_SHOOT_SPEED    0.5
# define L_SHOOT_MAX_DIST 10000

// Flame config

# define FLAME_SCALE_FACTOR 1.0

// Game macros.

# define FIRE_LIMIT 3500
# define FLAMES_IN_FIRST_LEVEL 10 / MAX_USERS
# define SPAWN_RATE_FIRST_LEVEL 60 / MAX_USERS
# define SPEED_RATE_FIRST_LEVEL 3.0 / MAX_USERS
# define RISE_SPAWN_RATE 30 / MAX_USERS
# define RISE_SPEED_RATE 10.0 / MAX_USERS
# define RISE_FLAMES_IN_LEVEL 20 / MAX_USERS
# define POINTS_PER_HIT 100

# endif
