#ifndef _ROS_HR_2016_controller_h
#define _ROS_HR_2016_controller_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace HR_2016
{

  class controller : public ros::Msg
  {
    public:
      int8_t UP;
      int8_t DOWN;
      int8_t RIGHT;
      int8_t LEFT;
      int8_t MARU;
      int8_t BATSU;
      int8_t SANKAKU;
      int8_t SHIKAKU;
      int8_t R1;
      int8_t R2;
      int8_t R3;
      int8_t L1;
      int8_t L2;
      int8_t L3;
      int8_t SELECT;
      int8_t START;
      int8_t ANALOG;
      float X1;
      float Y1;
      float X2;
      float Y2;

    controller():
      UP(0),
      DOWN(0),
      RIGHT(0),
      LEFT(0),
      MARU(0),
      BATSU(0),
      SANKAKU(0),
      SHIKAKU(0),
      R1(0),
      R2(0),
      R3(0),
      L1(0),
      L2(0),
      L3(0),
      SELECT(0),
      START(0),
      ANALOG(0),
      X1(0),
      Y1(0),
      X2(0),
      Y2(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_UP;
      u_UP.real = this->UP;
      *(outbuffer + offset + 0) = (u_UP.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->UP);
      union {
        int8_t real;
        uint8_t base;
      } u_DOWN;
      u_DOWN.real = this->DOWN;
      *(outbuffer + offset + 0) = (u_DOWN.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->DOWN);
      union {
        int8_t real;
        uint8_t base;
      } u_RIGHT;
      u_RIGHT.real = this->RIGHT;
      *(outbuffer + offset + 0) = (u_RIGHT.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->RIGHT);
      union {
        int8_t real;
        uint8_t base;
      } u_LEFT;
      u_LEFT.real = this->LEFT;
      *(outbuffer + offset + 0) = (u_LEFT.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->LEFT);
      union {
        int8_t real;
        uint8_t base;
      } u_MARU;
      u_MARU.real = this->MARU;
      *(outbuffer + offset + 0) = (u_MARU.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->MARU);
      union {
        int8_t real;
        uint8_t base;
      } u_BATSU;
      u_BATSU.real = this->BATSU;
      *(outbuffer + offset + 0) = (u_BATSU.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->BATSU);
      union {
        int8_t real;
        uint8_t base;
      } u_SANKAKU;
      u_SANKAKU.real = this->SANKAKU;
      *(outbuffer + offset + 0) = (u_SANKAKU.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->SANKAKU);
      union {
        int8_t real;
        uint8_t base;
      } u_SHIKAKU;
      u_SHIKAKU.real = this->SHIKAKU;
      *(outbuffer + offset + 0) = (u_SHIKAKU.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->SHIKAKU);
      union {
        int8_t real;
        uint8_t base;
      } u_R1;
      u_R1.real = this->R1;
      *(outbuffer + offset + 0) = (u_R1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R1);
      union {
        int8_t real;
        uint8_t base;
      } u_R2;
      u_R2.real = this->R2;
      *(outbuffer + offset + 0) = (u_R2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R2);
      union {
        int8_t real;
        uint8_t base;
      } u_R3;
      u_R3.real = this->R3;
      *(outbuffer + offset + 0) = (u_R3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->R3);
      union {
        int8_t real;
        uint8_t base;
      } u_L1;
      u_L1.real = this->L1;
      *(outbuffer + offset + 0) = (u_L1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L1);
      union {
        int8_t real;
        uint8_t base;
      } u_L2;
      u_L2.real = this->L2;
      *(outbuffer + offset + 0) = (u_L2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L2);
      union {
        int8_t real;
        uint8_t base;
      } u_L3;
      u_L3.real = this->L3;
      *(outbuffer + offset + 0) = (u_L3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->L3);
      union {
        int8_t real;
        uint8_t base;
      } u_SELECT;
      u_SELECT.real = this->SELECT;
      *(outbuffer + offset + 0) = (u_SELECT.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->SELECT);
      union {
        int8_t real;
        uint8_t base;
      } u_START;
      u_START.real = this->START;
      *(outbuffer + offset + 0) = (u_START.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->START);
      union {
        int8_t real;
        uint8_t base;
      } u_ANALOG;
      u_ANALOG.real = this->ANALOG;
      *(outbuffer + offset + 0) = (u_ANALOG.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->ANALOG);
      union {
        float real;
        uint32_t base;
      } u_X1;
      u_X1.real = this->X1;
      *(outbuffer + offset + 0) = (u_X1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_X1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_X1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_X1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->X1);
      union {
        float real;
        uint32_t base;
      } u_Y1;
      u_Y1.real = this->Y1;
      *(outbuffer + offset + 0) = (u_Y1.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Y1.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Y1.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Y1.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Y1);
      union {
        float real;
        uint32_t base;
      } u_X2;
      u_X2.real = this->X2;
      *(outbuffer + offset + 0) = (u_X2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_X2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_X2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_X2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->X2);
      union {
        float real;
        uint32_t base;
      } u_Y2;
      u_Y2.real = this->Y2;
      *(outbuffer + offset + 0) = (u_Y2.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Y2.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Y2.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Y2.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Y2);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_UP;
      u_UP.base = 0;
      u_UP.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->UP = u_UP.real;
      offset += sizeof(this->UP);
      union {
        int8_t real;
        uint8_t base;
      } u_DOWN;
      u_DOWN.base = 0;
      u_DOWN.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->DOWN = u_DOWN.real;
      offset += sizeof(this->DOWN);
      union {
        int8_t real;
        uint8_t base;
      } u_RIGHT;
      u_RIGHT.base = 0;
      u_RIGHT.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->RIGHT = u_RIGHT.real;
      offset += sizeof(this->RIGHT);
      union {
        int8_t real;
        uint8_t base;
      } u_LEFT;
      u_LEFT.base = 0;
      u_LEFT.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->LEFT = u_LEFT.real;
      offset += sizeof(this->LEFT);
      union {
        int8_t real;
        uint8_t base;
      } u_MARU;
      u_MARU.base = 0;
      u_MARU.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->MARU = u_MARU.real;
      offset += sizeof(this->MARU);
      union {
        int8_t real;
        uint8_t base;
      } u_BATSU;
      u_BATSU.base = 0;
      u_BATSU.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->BATSU = u_BATSU.real;
      offset += sizeof(this->BATSU);
      union {
        int8_t real;
        uint8_t base;
      } u_SANKAKU;
      u_SANKAKU.base = 0;
      u_SANKAKU.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->SANKAKU = u_SANKAKU.real;
      offset += sizeof(this->SANKAKU);
      union {
        int8_t real;
        uint8_t base;
      } u_SHIKAKU;
      u_SHIKAKU.base = 0;
      u_SHIKAKU.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->SHIKAKU = u_SHIKAKU.real;
      offset += sizeof(this->SHIKAKU);
      union {
        int8_t real;
        uint8_t base;
      } u_R1;
      u_R1.base = 0;
      u_R1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R1 = u_R1.real;
      offset += sizeof(this->R1);
      union {
        int8_t real;
        uint8_t base;
      } u_R2;
      u_R2.base = 0;
      u_R2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R2 = u_R2.real;
      offset += sizeof(this->R2);
      union {
        int8_t real;
        uint8_t base;
      } u_R3;
      u_R3.base = 0;
      u_R3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->R3 = u_R3.real;
      offset += sizeof(this->R3);
      union {
        int8_t real;
        uint8_t base;
      } u_L1;
      u_L1.base = 0;
      u_L1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L1 = u_L1.real;
      offset += sizeof(this->L1);
      union {
        int8_t real;
        uint8_t base;
      } u_L2;
      u_L2.base = 0;
      u_L2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L2 = u_L2.real;
      offset += sizeof(this->L2);
      union {
        int8_t real;
        uint8_t base;
      } u_L3;
      u_L3.base = 0;
      u_L3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->L3 = u_L3.real;
      offset += sizeof(this->L3);
      union {
        int8_t real;
        uint8_t base;
      } u_SELECT;
      u_SELECT.base = 0;
      u_SELECT.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->SELECT = u_SELECT.real;
      offset += sizeof(this->SELECT);
      union {
        int8_t real;
        uint8_t base;
      } u_START;
      u_START.base = 0;
      u_START.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->START = u_START.real;
      offset += sizeof(this->START);
      union {
        int8_t real;
        uint8_t base;
      } u_ANALOG;
      u_ANALOG.base = 0;
      u_ANALOG.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->ANALOG = u_ANALOG.real;
      offset += sizeof(this->ANALOG);
      union {
        float real;
        uint32_t base;
      } u_X1;
      u_X1.base = 0;
      u_X1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_X1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_X1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_X1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->X1 = u_X1.real;
      offset += sizeof(this->X1);
      union {
        float real;
        uint32_t base;
      } u_Y1;
      u_Y1.base = 0;
      u_Y1.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Y1.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Y1.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Y1.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Y1 = u_Y1.real;
      offset += sizeof(this->Y1);
      union {
        float real;
        uint32_t base;
      } u_X2;
      u_X2.base = 0;
      u_X2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_X2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_X2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_X2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->X2 = u_X2.real;
      offset += sizeof(this->X2);
      union {
        float real;
        uint32_t base;
      } u_Y2;
      u_Y2.base = 0;
      u_Y2.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Y2.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Y2.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Y2.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Y2 = u_Y2.real;
      offset += sizeof(this->Y2);
     return offset;
    }

    const char * getType(){ return "HR_2016/controller"; };
    const char * getMD5(){ return "cac089d4f201eae63b638874ceb7ed0d"; };

  };

}
#endif