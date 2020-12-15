//
// Created by Weller on 2020/6/2.
//

#ifndef BINDERTEST_CONTROLLERCLIENT_H
#define BINDERTEST_CONTROLLERCLIENT_H

// Single group data length, There are three groups(Right/Left/Head)
#define XRAPI_CONTROLLER_GROUP_DATA_SIZE         30
#define XRAPI_CONTROLLER_GROUP_COUNT             3
// Single group data index
#define XRAPI_CONTROLLER_INDEX_CONNECT_STATUS    0   // size=1, ConnectStatus
#define XRAPI_CONTROLLER_INDEX_TYPE              1   // size=1, Type
#define XRAPI_CONTROLLER_INDEX_HANDNESS          2   // size=1, Handness
#define XRAPI_CONTROLLER_INDEX_RECENTERED        3   // size=1
#define XRAPI_CONTROLLER_INDEX_BATTERY           4   // size=1
#define XRAPI_CONTROLLER_INDEX_ROTATION          5   // size=4
#define XRAPI_CONTROLLER_INDEX_POSITION          9   // size=3
#define XRAPI_CONTROLLER_INDEX_GATEWAY_POS       12  // size=3
#define XRAPI_CONTROLLER_INDEX_BUTTON_STATE      15  // size=2, KeyCode
#define XRAPI_CONTROLLER_INDEX_TOUCH_STATE       17  // size=1
#define XRAPI_CONTROLLER_INDEX_TOUCH_POS         18  // size=2
#define XRAPI_CONTROLLER_INDEX_TRIGGER_PROCESS   20  // size=1
#define XRAPI_CONTROLLER_INDEX_GRIP_PROCESS      21  // size=1
#define XRAPI_CONTROLLER_INDEX_RESERVED1         22  // size=4
#define XRAPI_CONTROLLER_INDEX_RESERVED2         26  // size=4

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * connect server
 * @return return 0 success
 */
int xrapiController_connect();

/**
 * disconnect server
 * @return return 0 success
 */
int xrapiController_disconnect();

bool xrapiController_isConnected();

/**
 * get controller data
 * @return return 0 success
 */
int xrapiController_getData(float *data, int *len);

#ifdef __cplusplus
}
#endif

#endif //BINDERTEST_CONTROLLERCLIENT_H
