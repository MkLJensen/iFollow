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

/***************************************************
* Used to get state of switch 
* @param button letter - P or F
* @return <1 if on, 0 if off>
****************************************************/
bool Switches::getSwitchStatus(char button) const
{
    if (button == 'P' || button == 'p')
    {
         return PowerSwitch;
    }
    else if ((button == 'F' || button == 'f') && PowerSwitch == true)
    {
        return FollowSwitch;
    }
    return false;
}

/***************************************************
* Used to set state of switch 
* @param button letter - P or F
* @return none
****************************************************/
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
