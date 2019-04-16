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
#ifndef SWITCHES_H_
#define SWITCHES_H_
#define true 1
#define false 0

#ifdef __cplusplus
extern "C"
{
#endif
#include "project.h"
#ifdef __cplusplus
}
#endif

class Switches 
{
public:
   Switches();
   ~Switches();      
   bool getSwitchStatus(char button) const;
   void setSwitchStatus(char button);

private:
   bool PowerSwitch = false;
   //bool PowerSwitchPressed = false;
   bool FollowSwitch = false;
   //bool FollowSwitchPressed = false;
    
};

#endif