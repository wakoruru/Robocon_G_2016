#ifndef _ROS_HR_2016_odometry_h
#define _ROS_HR_2016_odometry_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace HR_2016
{

  class odometry : public ros::Msg
  {
    public:
      int16_t x;
      int16_t y;
      int16_t z;
      int16_t w;
      float theta;
      int8_t mode1;
      int8_t mode2;
      int8_t mode3;
      int8_t mode4;

    odometry():
      x(0),
      y(0),
      z(0),
      w(0),
      theta(0),
      mode1(0),
      mode2(0),
      mode3(0),
      mode4(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_x;
      u_x.real = this->x;
      *(outbuffer + offset + 0) = (u_x.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_x.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->x);
      union {
        int16_t real;
        uint16_t base;
      } u_y;
      u_y.real = this->y;
      *(outbuffer + offset + 0) = (u_y.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_y.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->y);
      union {
        int16_t real;
        uint16_t base;
      } u_z;
      u_z.real = this->z;
      *(outbuffer + offset + 0) = (u_z.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_z.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->z);
      union {
        int16_t real;
        uint16_t base;
      } u_w;
      u_w.real = this->w;
      *(outbuffer + offset + 0) = (u_w.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_w.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->w);
      union {
        float real;
        uint32_t base;
      } u_theta;
      u_theta.real = this->theta;
      *(outbuffer + offset + 0) = (u_theta.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_theta.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_theta.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_theta.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->theta);
      union {
        int8_t real;
        uint8_t base;
      } u_mode1;
      u_mode1.real = this->mode1;
      *(outbuffer + offset + 0) = (u_mode1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode1);
      union {
        int8_t real;
        uint8_t base;
      } u_mode2;
      u_mode2.real = this->mode2;
      *(outbuffer + offset + 0) = (u_mode2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode2);
      union {
        int8_t real;
        uint8_t base;
      } u_mode3;
      u_mode3.real = this->mode3;
      *(outbuffer + offset + 0) = (u_mode3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode3);
      union {
        int8_t real;
        uint8_t base;
      } u_mode4;
      u_mode4.real = this->mode4;
      *(outbuffer + offset + 0) = (u_mode4.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode4);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_x;
      u_x.base = 0;
      u_x.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_x.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->x = u_x.real;
      offset += sizeof(this->x);
      union {
        int16_t real;
        uint16_t base;
      } u_y;
      u_y.base = 0;
      u_y.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_y.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->y = u_y.real;
      offset += sizeof(this->y);
      union {
        int16_t real;
        uint16_t base;
      } u_z;
      u_z.base = 0;
      u_z.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_z.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->z = u_z.real;
      offset += sizeof(this->z);
      union {
        int16_t real;
        uint16_t base;
      } u_w;
      u_w.base = 0;
      u_w.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_w.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->w = u_w.real;
      offset += sizeof(this->w);
      union {
        float real;
        uint32_t base;
      } u_theta;
      u_theta.base = 0;
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_theta.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->theta = u_theta.real;
      offset += sizeof(this->theta);
      union {
        int8_t real;
        uint8_t base;
      } u_mode1;
      u_mode1.base = 0;
      u_mode1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode1 = u_mode1.real;
      offset += sizeof(this->mode1);
      union {
        int8_t real;
        uint8_t base;
      } u_mode2;
      u_mode2.base = 0;
      u_mode2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode2 = u_mode2.real;
      offset += sizeof(this->mode2);
      union {
        int8_t real;
        uint8_t base;
      } u_mode3;
      u_mode3.base = 0;
      u_mode3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode3 = u_mode3.real;
      offset += sizeof(this->mode3);
      union {
        int8_t real;
        uint8_t base;
      } u_mode4;
      u_mode4.base = 0;
      u_mode4.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode4 = u_mode4.real;
      offset += sizeof(this->mode4);
     return offset;
    }

    const char * getType(){ return "HR_2016/odometry"; };
    const char * getMD5(){ return "c59f10b62528d62b31e8b179dff91103"; };

  };

}
#endif