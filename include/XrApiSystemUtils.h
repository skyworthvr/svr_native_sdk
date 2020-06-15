
#ifndef XR_XrApiSystemUtils_h
#define XR_XrApiSystemUtils_h

#include "XrApiConfig.h"
#include "XrApiTypes.h"

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum xrSystemUIType_ {
    // enum 0 used to be XRAPI_SYS_UI_GLOBAL_MENU.

    XRAPI_SYS_UI_CONFIRM_QUIT_MENU = 1, // Display the 'Confirm Quit' Menu.

    XRAPI_SYS_UI_KEYBOARD_MENU = 2, // Display a Keyboard Menu for editing a single string.
    XRAPI_SYS_UI_FILE_DIALOG_MENU =
        3, // Display a Folder Browser Menu for selecting the path to a file or folder.

    } xrSystemUIType;

/// Display a specific System UI.
XRAPI_EXPORT bool xrapiShowSystemUI(const xrJava* java, const xrSystemUIType type);

/// \deprecated Display a specific System UI and pass extra JSON text data.
XRAPI_DEPRECATED(XRAPI_EXPORT bool xrapiShowSystemUIWithExtra(
    const xrJava* java,
    const xrSystemUIType type,
    const char* extraJsonText));


/// Display a Fatal Error Message using the System UI.
XRAPI_EXPORT void xrapiShowFatalError(
    const xrJava* java,
    const char* title,
    const char* message,
    const char* fileName,
    const unsigned int lineNumber);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // XR_XrApiSystemUtils_h
