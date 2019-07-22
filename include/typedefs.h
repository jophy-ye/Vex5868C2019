#ifndef _TYPE_DEFS_H_
#define _TYPE_DEFS_H_

/**
 * Some typedefs for this project
 */

/**
 * GameStatus_t type. Set to different value when the robot is at different state
 */
enum GameStatus_t
{ Initialize, Autonomous, DriverControl };

/**
 * The starting position of autonomous. They are:
 * BlueFront, RedFront, BlueBack, RedBack, Skills
 */
enum AutonPos_t
{ BlueFront, RedFront, BlueBack, RedBack, Skills };

#endif