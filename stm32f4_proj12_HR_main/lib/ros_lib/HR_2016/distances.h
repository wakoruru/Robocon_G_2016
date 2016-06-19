#ifndef _ROS_HR_2016_distances_h
#define _ROS_HR_2016_distances_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace HR_2016
{

  class distances : public ros::Msg
  {
    public:
      float dist_x;
      float dist_y;

    distances():
      dist_x(0),
      dist_y(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dist_x;
      u_dist_x.real = this->dist_x;
      *(outbuffer + offset + 0) = (u_dist_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dist_x.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dist_x.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dist_x.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dist_x);
      union {
        float real;
        uint32_t base;
      } u_dist_y;
      u_dist_y.real = this->dist_y;
      *(outbuffer + offset + 0) = (u_dist_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dist_y.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dist_y.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dist_y.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dist_y);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_dist_x;
      u_dist_x.base = 0;
      u_dist_x.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dist_x.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dist_x.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dist_x.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dist_x = u_dist_x.real;
      offset += sizeof(this->dist_x);
      union {
        float real;
        uint32_t base;
      } u_dist_y;
      u_dist_y.base = 0;
      u_dist_y.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dist_y.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dist_y.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dist_y.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dist_y = u_dist_y.real;
      offset += sizeof(this->dist_y);
     return offset;
    }

    const char * getType(){ return "HR_2016/distances"; };
    const char * getMD5(){ return "85963607e68f57c227de1b608a39b6d1"; };

  };

}
#endif