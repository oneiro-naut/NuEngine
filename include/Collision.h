#ifndef COLLISION_H
#define COLLISION_H

struct collision_flags {
  unsigned short no_collision : 1;
  unsigned short all_solid : 1;
  unsigned short left_out : 1;
  unsigned short right_out : 1;
  unsigned short up_out : 1;
  unsigned short down_out : 1;
  unsigned short left_in : 1;
  unsigned short right_in : 1;
  unsigned short up_in : 1;
  unsigned short down_in : 1;
  unsigned short : 0;
};

#endif