/*********************************************************************
*                     SEGGER Microcontroller GmbH                    *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2024  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************
----------------------------------------------------------------------
File        : ID_SCREEN_01.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef ID_SCREEN_01_H
#define ID_SCREEN_01_H

#include "AppWizard.h"

/*********************************************************************
*
*       Objects
*/
#define ID_BOX_00   (GUI_ID_USER + 1)
#define ID_TEXT_00  (GUI_ID_USER + 2)
#define ID_TEXT_01  (GUI_ID_USER + 3)
#define ID_TIMER_00 (GUI_ID_USER + 4)

/*********************************************************************
*
*       Slots
*/
void ID_SCREEN_01__WM_NOTIFICATION_VALUE_CHANGED(APPW_ACTION_ITEM * pAction, WM_HWIN hScreen, WM_MESSAGE * pMsg, int * pResult);

/*********************************************************************
*
*       Callback
*/
void cbID_SCREEN_01(WM_MESSAGE * pMsg);

#endif  // ID_SCREEN_01_H

/*************************** End of file ****************************/
