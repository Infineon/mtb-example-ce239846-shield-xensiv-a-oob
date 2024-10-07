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
File        : ID_SCREEN_02.c
Purpose     : Generated file do NOT edit!
---------------------------END-OF-HEADER------------------------------
*/

#include "Resource.h"
#include "ID_SCREEN_02.h"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _aCreate
*/
static APPW_CREATE_ITEM _aCreate[] = {
  { WM_OBJECT_WINDOW_Create,
    ID_SCREEN_02, 0,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_BOX_Create,
    ID_BOX_00, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
      },
      0, 0, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_00, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 9, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      142, 19, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_01, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 0, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 19, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      160, 21, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_IMAGE_Create,
    ID_IMAGE_00, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 32, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 40, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      30, 30, 0, 0, 0, 0
    },
    { 0, 0 }
  },
  { WM_OBJECT_TEXT_Create,
    ID_TEXT_02, ID_SCREEN_02,
    { { { DISPOSE_MODE_REL_PARENT, 67, 0, 0 },
        { DISPOSE_MODE_REL_PARENT, 44, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
        { DISPOSE_MODE_NULL, 0, 0, 0 },
      },
      83, 22, 0, 0, 0, 0
    },
    { 0, 0 }
  },
};

/*********************************************************************
*
*       _aSetup
*/
static GUI_CONST_STORAGE APPW_SETUP_ITEM _aSetup[] = {
  { ID_BOX_00,    APPW_SET_PROP_COLOR,        { ARG_V(GUI_WHITE) } },
  { ID_TEXT_00,   APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_00,   APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_TEXT_00,   APPW_SET_PROP_TEXTID,       { ARG_V(ID_RTEXT_4) } },
  { ID_TEXT_00,   APPW_SET_PROP_FONT,         { ARG_VP(0, acCalibri_14_Normal_EXT_AA4) } },
  { ID_TEXT_01,   APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_01,   APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_HCENTER | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_TEXT_01,   APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_16_Normal_EXT_AA4) } },
  { ID_IMAGE_00,  APPW_SET_PROP_TILE,         { ARG_V(0) } },
  { ID_IMAGE_00,  APPW_SET_PROP_SBITMAP,      { ARG_VP(0, NULL), } },
  { ID_TEXT_02,   APPW_SET_PROP_COLOR,        { ARG_V(GUI_BLACK) } },
  { ID_TEXT_02,   APPW_SET_PROP_ALIGNTEXT,    { ARG_V(GUI_ALIGN_LEFT | GUI_ALIGN_VCENTER),
                                                ARG_V(0),
                                                ARG_V(0) } },
  { ID_TEXT_02,   APPW_SET_PROP_FONT,         { ARG_VP(0, acRoboto_16_Normal_EXT_AA4) } },
};

/*********************************************************************
*
*       Comparison(s)
*/
static APPW_COND_COMP _aComparison_00[] = {
  { { { 0x00001000, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_01[] = {
  { { { 0x00001000, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_02[] = {
  { { { 0x00001000, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_03[] = {
  { { { 0x00001001, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_04[] = {
  { { { 0x00001001, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_05[] = {
  { { { 0x00001001, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_06[] = {
  { { { 0x00001001, 0, ATOM_VARIABLE, 0 }, { 0x00000001, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

static APPW_COND_COMP _aComparison_07[] = {
  { { { 0x00001000, 0, ATOM_VARIABLE, 0 }, { 0x00000000, 0, ATOM_CONSTANT, 0 } }, APPW__CompareIsEqual },
};

/*********************************************************************
*
*       Condition(s)
*/
static GUI_CONST_STORAGE APPW_COND _Condition_00 = { "A", _aComparison_00, GUI_COUNTOF(_aComparison_00) };
static GUI_CONST_STORAGE APPW_COND _Condition_01 = { "A", _aComparison_01, GUI_COUNTOF(_aComparison_01) };
static GUI_CONST_STORAGE APPW_COND _Condition_02 = { "A", _aComparison_02, GUI_COUNTOF(_aComparison_02) };
static GUI_CONST_STORAGE APPW_COND _Condition_03 = { "A", _aComparison_03, GUI_COUNTOF(_aComparison_03) };
static GUI_CONST_STORAGE APPW_COND _Condition_04 = { "A", _aComparison_04, GUI_COUNTOF(_aComparison_04) };
static GUI_CONST_STORAGE APPW_COND _Condition_05 = { "A", _aComparison_05, GUI_COUNTOF(_aComparison_05) };
static GUI_CONST_STORAGE APPW_COND _Condition_06 = { "A", _aComparison_06, GUI_COUNTOF(_aComparison_06) };
static GUI_CONST_STORAGE APPW_COND _Condition_07 = { "A", _aComparison_07, GUI_COUNTOF(_aComparison_07) };

/*********************************************************************
*
*       _aAction
*/
static GUI_CONST_STORAGE APPW_ACTION_ITEM _aAction[] = {
  { T_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_00,  APPW_JOB_SETBITMAP,      ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP_1,
    { ARG_V(0),
      ARG_VP(0, acwhite),
      ARG_V(152),
    }, 0, &_Condition_00
  },
  { T_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_TEXT_02,   APPW_JOB_SETTEXT,        ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_TEXT_02__APPW_JOB_SETTEXT_1,
    { ARG_V(-1),
    }, 0, &_Condition_01
  },
  { T_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_TEXT_01,   APPW_JOB_SETTEXT,        ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_TEXT_01__APPW_JOB_SETTEXT,
    { ARG_V(-1),
    }, 0, &_Condition_02
  },
  { P_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_00,  APPW_JOB_SETBITMAP,      ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP,
    { ARG_V(0),
      ARG_VP(0, acap_arrow),
      ARG_V(385),
    }, 0, &_Condition_03
  },
  { P_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_TEXT_02,   APPW_JOB_SETTEXT,        ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_TEXT_02__APPW_JOB_SETTEXT,
    { ARG_V(-1),
    }, 0, &_Condition_04
  },
  { P_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_TEXT_02,   APPW_JOB_SETTEXT,        ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_TEXT_02__APPW_JOB_SETTEXT_0,
    { ARG_V(-1),
    }, 0, &_Condition_05
  },
  { P_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_IMAGE_00,  APPW_JOB_SETBITMAP,      ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_IMAGE_00__APPW_JOB_SETBITMAP_0,
    { ARG_V(0),
      ARG_VP(0, acdp_arrow),
      ARG_V(392),
    }, 0, &_Condition_06
  },
  { T_DET_Stat,   WM_NOTIFICATION_VALUE_CHANGED,    ID_TEXT_01,   APPW_JOB_SETTEXT,        ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED__ID_TEXT_01__APPW_JOB_SETTEXT_0,
    { ARG_V(-1),
    }, 0, &_Condition_07
  },
  { btn_stat,     WM_NOTIFICATION_VALUE_CHANGED,    0,            APPW_JOB_SHOWSCREEN,     ID_SCREEN_02__WM_NOTIFICATION_VALUE_CHANGED,
    { ARG_V(ID_SCREEN_03),
    }, 0, NULL
  },
};

/*********************************************************************
*
*       Public data
*
**********************************************************************
*/
/*********************************************************************
*
*       ID_SCREEN_02_RootInfo
*/
APPW_ROOT_INFO ID_SCREEN_02_RootInfo = {
  ID_SCREEN_02,
  _aCreate, GUI_COUNTOF(_aCreate),
  _aSetup,  GUI_COUNTOF(_aSetup),
  _aAction, GUI_COUNTOF(_aAction),
  cbID_SCREEN_02,
  0
};

/*************************** End of file ****************************/
