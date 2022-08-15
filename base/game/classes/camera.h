#pragma once
#include "../../utils/vector/vector.h"

class camera
{
private:
    char pad_0001[ 8 ];
    vector m_right;
    vector m_up;
    vector m_forward;
    vector m_translation;

    char pad_0002[ 32 ];
    vector m_viewport;

    char pad_0003[ 108 ];
    vector m_projection1;
    vector m_projection2;
public:
   bool screen_transform( vector world, vector& screen )
   {
       vector temp = world - m_translation;

       temp = {
           temp.x * m_right.x + temp.y * m_right.y + temp.z * m_right.z,
           temp.x * m_up.x + temp.y * m_up.y + temp.z * m_up.z,
           temp.x * m_forward.x + temp.y * m_forward.y + temp.z * m_forward.z
       };

       if( temp.z <= 0.19f )
           return false;

       screen = {
           m_viewport.x * ( 1 + temp.x / m_projection1.x / temp.z ),
           m_viewport.y * ( 1 - temp.y / m_projection2.y / temp.z ),
           temp.z
       };

       return true;
   }
};
