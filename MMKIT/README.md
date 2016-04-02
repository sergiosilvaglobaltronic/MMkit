# MMKit
Micromouse Kit library
For information on installing libraries, see: http://arduino.cc/en/Guide/Libraries
The MMkit is a library that helps you to program the MMKit
There are several examples:
Basic:
      MoveFoward
      TurnLeft
      TurnRight
      TesteIRSensors
Advanced:
      FloodFillAlgorithm
      RandomNextMove
      RightWallFollow
      
Added cm/s on MoveFoward so if the value used on function is bellow 40cm/s the MMkit assumes that velocity else he assumes the velocity with the following formula (Value/158) cm/s,
also added a new odometry function receives current_cell.theta and move
updates next_theta
current_cell.theta=next_theta
The search speed is optimized for 9 cm/s
