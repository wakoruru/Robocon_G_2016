#ifndef _ROS_HR_2016_coordinates_h
#define _ROS_HR_2016_coordinates_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace HR_2016
{

  class coordinates : public ros::Msg
  {
    public:
      int16_t x;
      int16_t y;
      int16_t z;
      int16_t xw;
      int16_t yw;
      int16_t zw;

    coordinates():
      x(0),
      y(0),
      z(0),
      xw(0),
      yw(0),
      zw(0)
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
      } u_xw;
      u_xw.real = this->xw;
      *(outbuffer + offset + 0) = (u_xw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_xw.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->xw);
      union {
        int16_t real;
        uint16_t base;
      } u_yw;
      u_yw.real = this->yw;
      *(outbuffer + offset + 0) = (u_yw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yw.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->yw);
      union {
        int16_t real;
        uint16_t base;
      } u_zw;
      u_zw.real = this->zw;
      *(outbuffer + offset + 0) = (u_zw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_zw.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->zw);
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
      } u_xw;
      u_xw.base = 0;
      u_xw.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_xw.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->xw = u_xw.real;
      offset += sizeof(this->xw);
      union {
        int16_t real;
        uint16_t base;
      } u_yw;
      u_yw.base = 0;
      u_yw.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yw.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->yw = u_yw.real;
      offset += sizeof(this->yw);
      union {
        int16_t real;
        uint16_t base;
      } u_zw;
      u_zw.base = 0;
      u_zw.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_zw.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->zw = u_zw.real;
      offset += sizeof(this->zw);
     return offset;
    }

    const char * getType(){ return "HR_2016/coordinates"; };
    const char * getMD5(){ return "07490cd2217ed5a5542c0797c723bac5"; };

  };

}
#endif