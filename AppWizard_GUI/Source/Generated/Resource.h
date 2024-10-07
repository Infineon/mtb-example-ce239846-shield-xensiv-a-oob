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
File        : Resource.h
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#ifndef RESOURCE_H
#define RESOURCE_H

#include "AppWizard.h"

/*********************************************************************
*
*       Text
*/
#define ID_RTEXT_0 0
#define ID_RTEXT_1 1
#define ID_RTEXT_2 2
#define ID_RTEXT_3 3
#define ID_RTEXT_4 4
#define ID_RTEXT_5 5
#define ID_RTEXT_6 6
#define ID_RTEXT_7 7
#define ID_RTEXT_8 8
#define ID_RTEXT_9 9
#define ID_RTEXT_10 10
#define ID_RTEXT_11 11
#define ID_RTEXT_12 12
#define ID_RTEXT_13 13
#define ID_RTEXT_14 14
#define ID_RTEXT_15 15
#define ID_RTEXT_16 16

#define APPW_MANAGE_TEXT APPW_MANAGE_TEXT_EXT
extern GUI_CONST_STORAGE unsigned char acAPPW_Language_0[];

/*********************************************************************
*
*       Fonts
*/
extern GUI_CONST_STORAGE unsigned char acRoboto_16_Normal_EXT_AA4[];
extern GUI_CONST_STORAGE unsigned char acCalibri_14_Normal_EXT_AA4[];
extern GUI_CONST_STORAGE unsigned char acCalibriLight_14_Bold_EXT_AA4[];
extern GUI_CONST_STORAGE unsigned char acCalibriLight_12_Light_EXT_AA4[];

/*********************************************************************
*
*       Images
*/
extern GUI_CONST_STORAGE unsigned char acLOGO_RGB[];
extern GUI_CONST_STORAGE unsigned char acpngwing_com[];
extern GUI_CONST_STORAGE unsigned char acthermometer[];
extern GUI_CONST_STORAGE unsigned char acco2[];
extern GUI_CONST_STORAGE unsigned char acwhite[];
extern GUI_CONST_STORAGE unsigned char acap_arrow[];
extern GUI_CONST_STORAGE unsigned char acdp_arrow[];

/*********************************************************************
*
*       Variables
*/
#define T_DET_Stat (GUI_ID_USER + 2048)
#define P_DET_Stat (GUI_ID_USER + 2049)
#define btn_stat (GUI_ID_USER + 2050)
#define dps_pressure (GUI_ID_USER + 2051)
#define dps_temp (GUI_ID_USER + 2052)

/*********************************************************************
*
*       Screens
*/
#define ID_SCREEN_00 (GUI_ID_USER + 4097)
#define ID_SCREEN_01 (GUI_ID_USER + 4096)
#define ID_SCREEN_02 (GUI_ID_USER + 4104)
#define ID_SCREEN_03 (GUI_ID_USER + 4099)
#define ID_SCREEN_04 (GUI_ID_USER + 4101)
#define ID_SCREEN_05 (GUI_ID_USER + 4102)
#define ID_SCREEN_06 (GUI_ID_USER + 4100)
#define ID_SCREEN_07 (GUI_ID_USER + 4103)

extern APPW_ROOT_INFO ID_SCREEN_00_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_01_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_02_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_03_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_04_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_05_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_06_RootInfo;
extern APPW_ROOT_INFO ID_SCREEN_07_RootInfo;

#define APPW_INITIAL_SCREEN &ID_SCREEN_00_RootInfo

/*********************************************************************
*
*       Project path
*/
#define APPW_PROJECT_PATH "../../../AppWizard_GUI"

#endif  // RESOURCE_H

/*************************** End of file ****************************/
