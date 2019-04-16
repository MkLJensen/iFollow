/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */

#include "Switches.h"

Switches::Switches()
{
}

Switches::~Switches()
{
}

bool Switches::getSwitchStatus(char button) const
{
    if (button == 'P' || button == 'p')
    {
         return PowerSwitch;
    }
    else if (button == 'F' || button == 'f')
    {
        return FollowSwitch;
    }
    return false;
}

void Switches::setSwitchStatus(char button)
{
    if (button == 'P')
    {
         if (PowerSwitch == true)
        {
           PowerSwitch = false;  
        }
        else
         PowerSwitch = true;
    }
    else if (button == 'F')
    {
        if (FollowSwitch == true)
        {
             FollowSwitch = false;
        }
        else
        FollowSwitch = true;
    }
}
