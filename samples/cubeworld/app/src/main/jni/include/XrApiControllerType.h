//
// Created by Weller on 2020/6/11.
//

#ifndef BINDERTEST_CONTROLLERTYPE_H
#define BINDERTEST_CONTROLLERTYPE_H
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Controller connect status
 */
enum XrapiControllerConnectStatus_ {
    XrapiController_Disconnected = 0,
    XrapiController_Scanning = 1,
    XrapiController_Connecting = 2,
    XrapiController_Connected = 3,
    XrapiController_NoRecenter = 4
} XrapiController_ConnectStatus;

/**
 * Controller type
 */
enum XrapiControllerType_ {
    XrapiController_I3VR = 0,
    XrapiController_Nolo_6dof = 1,
    XrapiController_Nolo_3dof = 2
} XrapiController_Type;

/**
 * Controller's handness
 */
enum XrapiControllerHandness_ {
    XrapiController_Right = 0,
    XrapiController_Left = 1,
    XrapiController_Head = 2,
    XrapiController_Handness_Max = 3
} XrapiController_Handness;

/**
 * Key code
 */
enum XrapiControllerKeyCode_ {
    // TouchPad
    XrapiController_Button_Up = 0x00000001,
    XrapiController_Button_Down = 0x00000002,
    XrapiController_Button_Left = 0x00000004,
    XrapiController_Button_Right = 0x00000008,

    // system button
    XrapiController_Button_Enter = 0x00000010,
    XrapiController_Button_Home = 0x00000020,
    XrapiController_Button_Menu = 0x00000040,
    XrapiController_Button_Back = 0x00000080,
    XrapiController_Button_Volume_Up = 0x00000100,
    XrapiController_Button_Volume_Down = 0x00000200,

    // other button
    XrapiController_Button_Grip = 0x00000400,
    XrapiController_Button_Trigger = 0x00000800,

    XrapiController_Button_EnumSize = 0x7fffffff
} XrapiController_KeyCode;

#ifdef __cplusplus
}
#endif

#endif //BINDERTEST_CONTROLLERTYPE_H
