
#ifndef XR_XrApiTypes_h
#define XR_XrApiTypes_h

#include <stdbool.h>
#include <stdint.h>
#include "XrApiConfig.h" // needed for XRAPI_EXPORT

//-----------------------------------------------------------------
// Java
//-----------------------------------------------------------------

#if defined(ANDROID)
#include <jni.h>
#elif defined(__cplusplus)
typedef struct _JNIEnv JNIEnv;
typedef struct _JavaVM JavaVM;
typedef class _jobject* jobject;
#else
typedef const struct JNINativeInterface* JNIEnv;
typedef const struct JNIInvokeInterface* JavaVM;
typedef void* jobject;
#endif

/// Java details about an activity
typedef struct xrJava_ {
    JavaVM* Vm; //< Java Virtual Machine
    JNIEnv* Env; //< Thread specific environment
    jobject ActivityObject; //< Java activity object
} xrJava;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrJava, 12);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrJava, 24);

//-----------------------------------------------------------------
// Basic Types
//-----------------------------------------------------------------

typedef signed int xrResult;

/// xrResult isn't actually an enum type and the the success / failure types are not
/// defined anywhere for GearVR VrApi. This needs to be remedied. For now, I'm defining
/// these here and will try to address this larger issue in a follow-on changeset.
/// errors are < 0, successes are >= 0
/// Except where noted, these match error codes from PC CAPI.
typedef enum xrSuccessResult_ {
    xrSuccess = 0,
    xrSuccess_BoundaryInvalid = 1001,
    xrSuccess_EventUnavailable = 1002,
} xrSuccessResult;

typedef enum xrErrorResult_ {
    xrError_MemoryAllocationFailure = -1000,
    xrError_NotInitialized = -1004,
    xrError_InvalidParameter = -1005,
    xrError_DeviceUnavailable = -1010, //< device is not connected,
                                        // or not connected as input device
    xrError_InvalidOperation = -1015,

    // enums not in CAPI
    xrError_UnsupportedDeviceType = -1050, //< specified device type isn't supported on GearVR
    xrError_NoDevice = -1051, //< specified device ID does not map to any current device
    xrError_NotImplemented = -1052, //< executed an incomplete code path - this should not be
                                     // possible in public releases.

    xrResult_EnumSize = 0x7fffffff
} xrErrorResult;

/// A 2D vector.
typedef struct xrVector2f_ {
    float x, y;
} xrVector2f;

XRAPI_ASSERT_TYPE_SIZE(xrVector2f, 8);

/// A 3D vector.
typedef struct xrVector3f_ {
    float x, y, z;
} xrVector3f;

XRAPI_ASSERT_TYPE_SIZE(xrVector3f, 12);

/// A 4D vector.
typedef struct xrVector4f_ {
    float x, y, z, w;
} xrVector4f;

XRAPI_ASSERT_TYPE_SIZE(xrVector4f, 16);

typedef struct xrVector4s_ {
    int16_t x, y, z, w;
} xrVector4s;

XRAPI_ASSERT_TYPE_SIZE(xrVector4s, 8);

/// Quaternion.
typedef struct xrQuatf_ {
    float x, y, z, w;
} xrQuatf;

XRAPI_ASSERT_TYPE_SIZE(xrQuatf, 16);

/// Row-major 4x4 matrix.
typedef struct xrMatrix4f_ {
    float M[4][4];
} xrMatrix4f;

XRAPI_ASSERT_TYPE_SIZE(xrMatrix4f, 64);

/// Position and orientation together.
typedef struct xrPosef_ {
    xrQuatf Orientation;
    union {
        xrVector3f Position;
        xrVector3f Translation;
    };
} xrPosef;

XRAPI_ASSERT_TYPE_SIZE(xrPosef, 28);

/// A rectangle with 2D size and position.
typedef struct xrRectf_ {
    float x;
    float y;
    float width;
    float height;
} xrRectf;

XRAPI_ASSERT_TYPE_SIZE(xrRectf, 16);

/// True or false.
typedef enum xrBooleanResult_ { XRAPI_FALSE = 0, XRAPI_TRUE = 1 } xrBooleanResult;

/// One of the user's eyes.
typedef enum xrEye_ { XRAPI_EYE_LEFT = 0, XRAPI_EYE_RIGHT = 1, XRAPI_EYE_COUNT = 2 } xrEye;

//-----------------------------------------------------------------
// Structure Types
//-----------------------------------------------------------------

/// Defines a layout for xrInitParms, xrModeParms, or xrFrameParms.
typedef enum xrStructureType_ {
    XRAPI_STRUCTURE_TYPE_INIT_PARMS = 1,
    XRAPI_STRUCTURE_TYPE_MODE_PARMS = 2,
    XRAPI_STRUCTURE_TYPE_FRAME_PARMS = 3,
        XRAPI_STRUCTURE_TYPE_MODE_PARMS_VULKAN = 5,
    } xrStructureType;

//-----------------------------------------------------------------
// System Properties and Status
//-----------------------------------------------------------------

/// A VR-capable device.
typedef enum xrDeviceType_ {
    
    // Standalone Devices
    XRAPI_DEVICE_TYPE_OCULUSGO_START = 64,
    XRAPI_DEVICE_TYPE_OCULUSGO = XRAPI_DEVICE_TYPE_OCULUSGO_START,
    XRAPI_DEVICE_TYPE_MIVR_STANDALONE = XRAPI_DEVICE_TYPE_OCULUSGO_START + 1, //< China-only SKU
    XRAPI_DEVICE_TYPE_OCULUSGO_END = 127,

    XRAPI_DEVICE_TYPE_OCULUSQUEST_START = 256,
        XRAPI_DEVICE_TYPE_OCULUSQUEST = XRAPI_DEVICE_TYPE_OCULUSQUEST_START + 3,
    XRAPI_DEVICE_TYPE_OCULUSQUEST_END = 319,

    
    
    XRAPI_DEVICE_TYPE_UNKNOWN = -1,
} xrDeviceType;

/// A headset, which typically includes optics and tracking hardware, but not necessarily the device
/// itself.
typedef enum xrHeadsetType_ {
    
    // Standalone Headsets
    XRAPI_HEADSET_TYPE_OCULUSGO = 64, //< Oculus Go
    XRAPI_HEADSET_TYPE_MIVR_STANDALONE = 65, //< China-only SKU

    XRAPI_HEADSET_TYPE_OCULUSQUEST = 256,

    
    XRAPI_HEADSET_TYPE_UNKNOWN = -1,
} xrHeadsetType;

/// A geographic region authorized for certain hardware and content.
typedef enum xrDeviceRegion_ {
    XRAPI_DEVICE_REGION_UNSPECIFIED = 0,
    XRAPI_DEVICE_REGION_JAPAN = 1,
    XRAPI_DEVICE_REGION_CHINA = 2,
} xrDeviceRegion;

/// The maximum resolution and framerate supported by a video decoder.
typedef enum xrVideoDecoderLimit_ {
    XRAPI_VIDEO_DECODER_LIMIT_4K_30FPS = 0,
    XRAPI_VIDEO_DECODER_LIMIT_4K_60FPS = 1,
} xrVideoDecoderLimit;

/// Emulation mode for applications developed on different devices
/// for determining if running in emulation mode at all test against !=
/// XRAPI_DEVICE_EMULATION_MODE_NONE
typedef enum xrDeviceEmulationMode_ {
    XRAPI_DEVICE_EMULATION_MODE_NONE = 0,
    XRAPI_DEVICE_EMULATION_MODE_GO_ON_QUEST = 1,
} xrDeviceEmulationMode;

/// System configuration properties.
typedef enum xrSystemProperty_ {
    XRAPI_SYS_PROP_DEVICE_TYPE = 0,
    XRAPI_SYS_PROP_MAX_FULLSPEED_FRAMEBUFFER_SAMPLES = 1,
    /// Physical width and height of the display in pixels.
    XRAPI_SYS_PROP_DISPLAY_PIXELS_WIDE = 2,
    XRAPI_SYS_PROP_DISPLAY_PIXELS_HIGH = 3,
    /// Returns the refresh rate of the display in cycles per second.
    XRAPI_SYS_PROP_DISPLAY_REFRESH_RATE = 4,
    /// With a display resolution of 2560x1440, the pixels at the center
    /// of each eye cover about 0.06 degrees of visual arc. To wrap a
    /// full 360 degrees, about 6000 pixels would be needed and about one
    /// quarter of that would be needed for ~90 degrees FOV. As such, Eye
    /// images with a resolution of 1536x1536 result in a good 1:1 mapping
    /// in the center, but they need mip-maps for off center pixels. To
    /// avoid the need for mip-maps and for significantly improved rendering
    /// performance this currently returns a conservative 1024x1024.
    XRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH = 5,
    XRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_HEIGHT = 6,
    /// This is a product of the lens distortion and the screen size,
    /// but there is no truly correct answer.
    /// There is a tradeoff in resolution and coverage.
    /// Too small of an FOV will leave unrendered pixels visible, but too
    /// large wastes resolution or fill rate.  It is unreasonable to
    /// increase it until the corners are completely covered, but we do
    /// want most of the outside edges completely covered.
    /// Applications might choose to render a larger FOV when angular
    /// acceleration is high to reduce black pull in at the edges by
    /// the time warp.
    /// Currently symmetric 90.0 degrees.
    XRAPI_SYS_PROP_SUGGESTED_EYE_FOV_DEGREES_X = 7,
    XRAPI_SYS_PROP_SUGGESTED_EYE_FOV_DEGREES_Y = 8,
    /// Path to the external SD card. On Android-M, this path is dynamic and can
    /// only be determined once the SD card is mounted. Returns an empty string if
    /// device does not support an ext sdcard or if running Android-M and the SD card
    /// is not mounted.
    XRAPI_SYS_PROP_EXT_SDCARD_PATH = 9,
    XRAPI_SYS_PROP_DEVICE_REGION = 10,
    /// Video decoder limit for the device.
    XRAPI_SYS_PROP_VIDEO_DECODER_LIMIT = 11,
    XRAPI_SYS_PROP_HEADSET_TYPE = 12,

    // enum 13 used to be XRAPI_SYS_PROP_BACK_BUTTON_SHORTPRESS_TIME
    // enum 14 used to be XRAPI_SYS_PROP_BACK_BUTTON_DOUBLETAP_TIME

    /// Returns an xrHandedness enum indicating left or right hand.
    XRAPI_SYS_PROP_DOMINANT_HAND = 15,

    /// Returns XRAPI_TRUE if the system supports orientation tracking.
    XRAPI_SYS_PROP_HAS_ORIENTATION_TRACKING = 16,
    /// Returns XRAPI_TRUE if the system supports positional tracking.
    XRAPI_SYS_PROP_HAS_POSITION_TRACKING = 17,

    /// Returns the number of display refresh rates supported by the system.
    XRAPI_SYS_PROP_NUM_SUPPORTED_DISPLAY_REFRESH_RATES = 64,
    /// Returns an array of the supported display refresh rates.
    XRAPI_SYS_PROP_SUPPORTED_DISPLAY_REFRESH_RATES = 65,

    /// Returns the number of swapchain texture formats supported by the system.
    XRAPI_SYS_PROP_NUM_SUPPORTED_SWAPCHAIN_FORMATS = 66,
    /// Returns an array of the supported swapchain formats.
    /// Formats are platform specific. For GLES, this is an array of
    /// GL internal formats.
    XRAPI_SYS_PROP_SUPPORTED_SWAPCHAIN_FORMATS = 67,

    /// Returns XRAPI_TRUE if Multiview rendering support is available for this system,
    /// otherwise XRAPI_FALSE.
    XRAPI_SYS_PROP_MULTIVIEW_AVAILABLE = 128,

    /// Returns XRAPI_TRUE if submission of SRGB Layers is supported for this system,
    /// otherwise XRAPI_FALSE.
    XRAPI_SYS_PROP_SRGB_LAYER_SOURCE_AVAILABLE = 129,

    /// Returns XRAPI_TRUE if on-chip foveated rendering of swapchains is supported
    /// for this system, otherwise XRAPI_FALSE.
    XRAPI_SYS_PROP_FOVEATION_AVAILABLE = 130,
    } xrSystemProperty;

/// Configurable VrApi properties.
typedef enum xrProperty_ {
        XRAPI_FOVEATION_LEVEL = 15, //< Used by apps that want to control swapchain foveation levels.
        XRAPI_REORIENT_HMD_ON_CONTROLLER_RECENTER =
        17, //< Used to determine if a controller recenter should also reorient the headset.
    XRAPI_LATCH_BACK_BUTTON_ENTIRE_FRAME =
        18, //< Used to determine if the 'short press' back button should lasts an entire frame.
    XRAPI_BLOCK_REMOTE_BUTTONS_WHEN_NOT_EMULATING_HMT =
        19, //< Used to not send the remote back button java events to the apps.
    XRAPI_EAT_NATIVE_GAMEPAD_EVENTS =
        20, //< Used to tell the runtime not to eat gamepad events.  If this is false on a native
    // app, the app must be listening for the events.
        XRAPI_ACTIVE_INPUT_DEVICE_ID = 24, //< Used by apps to query which input device is most 'active'
                                       // or primary, a -1 means no active input device
        XRAPI_DEVICE_EMULATION_MODE = 29, //< Used by apps to determine if they are running in an
                                      // emulation mode. Is a xrDeviceEmulationMode value

    XRAPI_DYNAMIC_FOVEATION_ENABLED =
        30, //< Used by apps to enable / disable dynamic foveation adjustments.
} xrProperty;


/// Specifies left or right handedness.
typedef enum xrHandedness_ {
    XRAPI_HAND_UNKNOWN = 0,
    XRAPI_HAND_LEFT = 1,
    XRAPI_HAND_RIGHT = 2
} xrHandedness;

/// System status bits.
typedef enum xrSystemStatus_ {
    XRAPI_SYS_STATUS_DOCKED = 0, //< Device is docked.
    XRAPI_SYS_STATUS_MOUNTED = 1, //< Device is mounted.
    XRAPI_SYS_STATUS_THROTTLED = 2, //< Device is in powersave mode.

    // enum  3 used to be XRAPI_SYS_STATUS_THROTTLED2.

    // enum  4 used to be XRAPI_SYS_STATUS_THROTTLED_WARNING_LEVEL.

    XRAPI_SYS_STATUS_RENDER_LATENCY_MILLISECONDS =
        5, //< Average time between render tracking sample and scanout.
    XRAPI_SYS_STATUS_TIMEWARP_LATENCY_MILLISECONDS =
        6, //< Average time between timewarp tracking sample and scanout.
    XRAPI_SYS_STATUS_SCANOUT_LATENCY_MILLISECONDS = 7, //< Average time between Vsync and scanout.
    XRAPI_SYS_STATUS_APP_FRAMES_PER_SECOND =
        8, //< Number of frames per second delivered through xrapiSubmitFrame.
    XRAPI_SYS_STATUS_SCREEN_TEARS_PER_SECOND = 9, //< Number of screen tears per second (per eye).
    XRAPI_SYS_STATUS_EARLY_FRAMES_PER_SECOND =
        10, //< Number of frames per second delivered a whole display refresh early.
    XRAPI_SYS_STATUS_STALE_FRAMES_PER_SECOND = 11, //< Number of frames per second delivered late.

    // enum 12 used to be XRAPI_SYS_STATUS_HEADPHONES_PLUGGED_IN

    XRAPI_SYS_STATUS_RECENTER_COUNT = 13, //< Returns the current HMD recenter count. Defaults to 0.
    XRAPI_SYS_STATUS_SYSTEM_UX_ACTIVE = 14, //< Returns XRAPI_TRUE if a system UX layer is active
    XRAPI_SYS_STATUS_USER_RECENTER_COUNT = 15, //< Returns the current HMD recenter count for user
                                               // initiated recenters only. Defaults to 0.

    
    XRAPI_SYS_STATUS_FRONT_BUFFER_PROTECTED =
        128, //< XRAPI_TRUE if the front buffer is allocated in TrustZone memory.
    XRAPI_SYS_STATUS_FRONT_BUFFER_565 = 129, //< XRAPI_TRUE if the front buffer is 16-bit 5:6:5
    XRAPI_SYS_STATUS_FRONT_BUFFER_SRGB =
        130, //< XRAPI_TRUE if the front buffer uses the sRGB color space.

    } xrSystemStatus;

//-----------------------------------------------------------------
// Initialization
//-----------------------------------------------------------------

/// Possible results of initialization.
typedef enum xrInitializeStatus_ {
    XRAPI_INITIALIZE_SUCCESS = 0,
    XRAPI_INITIALIZE_UNKNOWN_ERROR = -1,
    XRAPI_INITIALIZE_PERMISSIONS_ERROR = -2,
    XRAPI_INITIALIZE_ALREADY_INITIALIZED = -3,
    XRAPI_INITIALIZE_SERVICE_CONNECTION_FAILED = -4,
    XRAPI_INITIALIZE_DEVICE_NOT_SUPPORTED = -5,
} xrInitializeStatus;

/// Supported graphics APIs.
typedef enum xrGraphicsAPI_ {
    XRAPI_GRAPHICS_API_TYPE_OPENGL_ES = 0x10000,
    XRAPI_GRAPHICS_API_OPENGL_ES_2 =
        (XRAPI_GRAPHICS_API_TYPE_OPENGL_ES | 0x0200), //< OpenGL ES 2.x context
    XRAPI_GRAPHICS_API_OPENGL_ES_3 =
        (XRAPI_GRAPHICS_API_TYPE_OPENGL_ES | 0x0300), //< OpenGL ES 3.x context

    XRAPI_GRAPHICS_API_TYPE_OPENGL = 0x20000,
    XRAPI_GRAPHICS_API_OPENGL_COMPAT =
        (XRAPI_GRAPHICS_API_TYPE_OPENGL | 0x0100), //< OpenGL Compatibility Profile
    XRAPI_GRAPHICS_API_OPENGL_CORE_3 =
        (XRAPI_GRAPHICS_API_TYPE_OPENGL | 0x0300), //< OpenGL Core Profile 3.x
    XRAPI_GRAPHICS_API_OPENGL_CORE_4 =
        (XRAPI_GRAPHICS_API_TYPE_OPENGL | 0x0400), //< OpenGL Core Profile 4.x

    XRAPI_GRAPHICS_API_TYPE_VULKAN = 0x40000,
    XRAPI_GRAPHICS_API_VULKAN_1 = (XRAPI_GRAPHICS_API_TYPE_VULKAN | 0x0100), //< Vulkan 1.x
} xrGraphicsAPI;

/// Configuration details specified at initialization.
typedef struct xrInitParms_ {
    xrStructureType Type;
    int ProductVersion;
    int MajorVersion;
    int MinorVersion;
    int PatchVersion;
    xrGraphicsAPI GraphicsAPI;
    xrJava Java;
} xrInitParms;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrInitParms, 36);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrInitParms, 48);


//-----------------------------------------------------------------
// VR Mode
//-----------------------------------------------------------------

/// \note the first two flags use the first two bytes for backwards compatibility on little endian
/// systems.
typedef enum xrModeFlags_ {
        /// When an application moves backwards on the activity stack,
    /// the activity window it returns to is no longer flagged as fullscreen.
    /// As a result, Android will also render the decor view, which wastes a
    /// significant amount of bandwidth.
    /// By setting this flag, the fullscreen flag is reset on the window.
    /// Unfortunately, this causes Android life cycle events that mess up
    /// several NativeActivity codebases like Stratum and UE4, so this
    /// flag should only be set for specific applications.
    /// Use "adb shell dumpsys SurfaceFlinger" to verify
    /// that there is only one HWC next to the FB_TARGET.
    XRAPI_MODE_FLAG_RESET_WINDOW_FULLSCREEN = 0x0000FF00,

    /// The WindowSurface passed in is an ANativeWindow.
    XRAPI_MODE_FLAG_NATIVE_WINDOW = 0x00010000,

    /// Create the front buffer in TrustZone memory to allow protected DRM
    /// content to be rendered to the front buffer. This functionality
    /// requires the WindowSurface to be allocated from TimeWarp, via
    /// specifying the nativeWindow via XRAPI_MODE_FLAG_NATIVE_WINDOW.
    XRAPI_MODE_FLAG_FRONT_BUFFER_PROTECTED = 0x00020000,

    /// Create a 16-bit 5:6:5 front buffer.
    XRAPI_MODE_FLAG_FRONT_BUFFER_565 = 0x00040000,

    /// Create a front buffer using the sRGB color space.
    XRAPI_MODE_FLAG_FRONT_BUFFER_SRGB = 0x00080000,

    /// If set, indicates the OpenGL ES Context was created with EGL_CONTEXT_OPENGL_NO_ERROR_KHR
    /// attribute. The same attribute would be applied when TimeWrap creates the shared context.
    /// More information could be found at:
    /// https://www.khronos.org/registry/EGL/extensions/KHR/EGL_KHR_create_context_no_error.txt
    XRAPI_MODE_FLAG_CREATE_CONTEXT_NO_ERROR = 0x00100000
} xrModeFlags;

/// Configuration details that stay constant between a xrapiEnterVrMode()/xrapiLeaveVrMode() pair.
typedef struct xrModeParms_ {
    xrStructureType Type;

    /// Combination of xrModeFlags flags.
    unsigned int Flags;

    /// The Java VM is needed for the time warp thread to create a Java environment.
    /// A Java environment is needed to access various system services. The thread
    /// that enters VR mode is responsible for attaching and detaching the Java
    /// environment. The Java Activity object is needed to get the windowManager,
    /// packageName, systemService, etc.
    xrJava Java;

    XRAPI_PADDING_32_BIT(4)

    /// Display to use for asynchronous time warp rendering.
    /// Using EGL this is an EGLDisplay.
    unsigned long long Display;

    /// The window surface to use for asynchronous time warp rendering.
    /// Using EGL this can be the EGLSurface created by the application for the ANativeWindow.
    /// This should be the ANativeWIndow itself (requires XRAPI_MODE_FLAG_NATIVE_WINDOW).
    unsigned long long WindowSurface;

    /// The resources from this context will be shared with the asynchronous time warp.
    /// Using EGL this is an EGLContext.
    unsigned long long ShareContext;
} xrModeParms;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrModeParms, 48);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrModeParms, 56);

/// Vulkan-specific mode paramaters.
typedef struct xrModeParmsVulkan_ {
    xrModeParms ModeParms;

    /// For Vulkan, this should be the VkQueue created on the same Device as specified
    /// by xrapiCreateSystemVulkan. An internally created VkFence object will be signaled
    /// by the completion of commands on the queue.
    unsigned long long SynchronizationQueue;
} xrModeParmsVulkan;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrModeParmsVulkan, 56);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrModeParmsVulkan, 64);

/// VR context
/// To allow multiple Android activities that live in the same address space
/// to cooperatively use the VrApi, each activity needs to maintain its own
/// separate contexts for a lot of the video related systems.
typedef struct xrMobile xrMobile;

//-----------------------------------------------------------------
// Tracking
//-----------------------------------------------------------------

/// Full rigid body pose with first and second derivatives.
typedef struct xrRigidBodyPosef_ {
    xrPosef Pose;
    xrVector3f AngularVelocity;
    xrVector3f LinearVelocity;
    xrVector3f AngularAcceleration;
    xrVector3f LinearAcceleration;
    XRAPI_PADDING(4)
    double TimeInSeconds; //< Absolute time of this pose.
    double PredictionInSeconds; //< Seconds this pose was predicted ahead.
} xrRigidBodyPosef;

XRAPI_ASSERT_TYPE_SIZE(xrRigidBodyPosef, 96);

/// Bit flags describing the current status of sensor tracking.
typedef enum xrTrackingStatus_ {
    XRAPI_TRACKING_STATUS_ORIENTATION_TRACKED = 1 << 0, //< Orientation is currently tracked.
    XRAPI_TRACKING_STATUS_POSITION_TRACKED = 1 << 1, //< Position is currently tracked.
    XRAPI_TRACKING_STATUS_ORIENTATION_VALID = 1 << 2, //< Orientation reported is valid.
    XRAPI_TRACKING_STATUS_POSITION_VALID = 1 << 3, //< Position reported is valid.
        XRAPI_TRACKING_STATUS_HMD_CONNECTED = 1 << 7 //< HMD is available & connected.
} xrTrackingStatus;

/// Tracking state at a given absolute time.
typedef struct xrTracking2_ {
    /// Sensor status described by xrTrackingStatus flags.
    unsigned int Status;

    XRAPI_PADDING(4)

    /// Predicted head configuration at the requested absolute time.
    /// The pose describes the head orientation and center eye position.
    xrRigidBodyPosef HeadPose;
    struct {
        xrMatrix4f ProjectionMatrix;
        xrMatrix4f ViewMatrix;
    } Eye[XRAPI_EYE_COUNT];
} xrTracking2;

XRAPI_ASSERT_TYPE_SIZE(xrTracking2, 360);

/// Reports the status and pose of a motion tracker.
typedef struct xrTracking_ {
    /// Sensor status described by xrTrackingStatus flags.
    unsigned int Status;

    XRAPI_PADDING(4)

    /// Predicted head configuration at the requested absolute time.
    /// The pose describes the head orientation and center eye position.
    xrRigidBodyPosef HeadPose;
} xrTracking;

XRAPI_ASSERT_TYPE_SIZE(xrTracking, 104);

/// Specifies a reference frame for motion tracking data.
typedef enum xrTrackingTransform_ {
    XRAPI_TRACKING_TRANSFORM_IDENTITY = 0,
    XRAPI_TRACKING_TRANSFORM_CURRENT = 1,
    XRAPI_TRACKING_TRANSFORM_SYSTEM_CENTER_EYE_LEVEL = 2,
    XRAPI_TRACKING_TRANSFORM_SYSTEM_CENTER_FLOOR_LEVEL = 3,
    } xrTrackingTransform;

typedef enum xrTrackingSpace_ {
    XRAPI_TRACKING_SPACE_LOCAL = 0, // Eye level origin - controlled by system recentering
    XRAPI_TRACKING_SPACE_LOCAL_FLOOR = 1, // Floor level origin - controlled by system recentering
    XRAPI_TRACKING_SPACE_LOCAL_TILTED =
        2, // Tilted pose for "bed mode" - controlled by system recentering
    XRAPI_TRACKING_SPACE_STAGE = 3, // Floor level origin - controlled by Guardian setup
        XRAPI_TRACKING_SPACE_LOCAL_FIXED_YAW = 7, // Position of local space, but yaw stays constant
} xrTrackingSpace;

/// Tracked device type id used to simplify interaction checks with Guardian
typedef enum xrTrackedDeviceTypeId_ {
    XRAPI_TRACKED_DEVICE_NONE = -1,
    XRAPI_TRACKED_DEVICE_HMD = 0, //< Headset
    XRAPI_TRACKED_DEVICE_HAND_LEFT = 1, //< Left controller
    XRAPI_TRACKED_DEVICE_HAND_RIGHT = 2, //< Right controller
    XRAPI_NUM_TRACKED_DEVICES = 3,
} xrTrackedDeviceTypeId;

/// Guardian boundary trigger state information based on a given tracked device type
typedef struct xrBoundaryTriggerResult_ {
    /// Closest point on the boundary surface.
    xrVector3f ClosestPoint;

    /// Normal of the closest point on the boundary surface.
    xrVector3f ClosestPointNormal;

    /// Distance to the closest guardian boundary surface.
    float ClosestDistance;

    /// True if the boundary system is being triggered. Note that due to fade in/out effects this
    /// may not exactly match visibility.
    bool IsTriggering;
} xrBoundaryTriggerResult;

XRAPI_ASSERT_TYPE_SIZE(xrBoundaryTriggerResult, 32);


//-----------------------------------------------------------------
// Texture Swap Chain
//-----------------------------------------------------------------

/// A texture type, such as 2D, array, or cubemap.
typedef enum xrTextureType_ {
    XRAPI_TEXTURE_TYPE_2D = 0, //< 2D textures.
        XRAPI_TEXTURE_TYPE_2D_ARRAY = 2, //< Texture array.
    XRAPI_TEXTURE_TYPE_CUBE = 3, //< Cube maps.
    XRAPI_TEXTURE_TYPE_MAX = 4,
    } xrTextureType;

/// A texture format.
/// DEPRECATED in favor of passing platform-specific formats to xrapiCreateTextureSwapChain3.
typedef enum xrTextureFormat_ {
    XRAPI_TEXTURE_FORMAT_NONE = 0,
    XRAPI_TEXTURE_FORMAT_565 = 1,
    XRAPI_TEXTURE_FORMAT_5551 = 2,
    XRAPI_TEXTURE_FORMAT_4444 = 3,
    XRAPI_TEXTURE_FORMAT_8888 = 4,
    XRAPI_TEXTURE_FORMAT_8888_sRGB = 5,
    XRAPI_TEXTURE_FORMAT_RGBA16F = 6,
    XRAPI_TEXTURE_FORMAT_DEPTH_16 = 7,
    XRAPI_TEXTURE_FORMAT_DEPTH_24 = 8,
    XRAPI_TEXTURE_FORMAT_DEPTH_24_STENCIL_8 = 9,
    XRAPI_TEXTURE_FORMAT_RG16 = 10,

    } xrTextureFormat;


/// Built-in convenience swapchains.
typedef enum xrDefaultTextureSwapChain_ {
    XRAPI_DEFAULT_TEXTURE_SWAPCHAIN = 0x1,
    XRAPI_DEFAULT_TEXTURE_SWAPCHAIN_LOADING_ICON = 0x2
} xrDefaultTextureSwapChain;

typedef struct xrTextureSwapChain xrTextureSwapChain;

//-----------------------------------------------------------------
// Frame Submission
//-----------------------------------------------------------------

/// Per-frame configuration options.
typedef enum xrFrameFlags_ {
    // enum 1 << 0 used to be XRAPI_FRAME_FLAG_INHIBIT_SRGB_FRAMEBUFFER. See per-layer
    // flag XRAPI_FRAME_LAYER_FLAG_INHIBIT_SRGB_FRAMEBUFFER.

    /// Flush the warp swap pipeline so the images show up immediately.
    /// This is expensive and should only be used when an immediate transition
    /// is needed like displaying black when resetting the HMD orientation.
    XRAPI_FRAME_FLAG_FLUSH = 1 << 1,
    /// This is the final frame. Do not accept any more frames after this.
    XRAPI_FRAME_FLAG_FINAL = 1 << 2,

    /// enum 1 << 3 used to be XRAPI_FRAME_FLAG_TIMEWARP_DEBUG_GRAPH_SHOW.

    /// enum 1 << 4 used to be XRAPI_FRAME_FLAG_TIMEWARP_DEBUG_GRAPH_FREEZE.

    /// enum 1 << 5 used to be XRAPI_FRAME_FLAG_TIMEWARP_DEBUG_GRAPH_LATENCY_MODE.

    /// Don't show the volume layer when set.
    XRAPI_FRAME_FLAG_INHIBIT_VOLUME_LAYER = 1 << 6,

    /// enum 1 << 7 used to be XRAPI_FRAME_FLAG_SHOW_LAYER_COMPLEXITY.

    /// enum 1 << 8 used to be XRAPI_FRAME_FLAG_SHOW_TEXTURE_DENSITY.

    } xrFrameFlags;

/// Per-frame configuration options that apply to a particular layer.
typedef enum xrFrameLayerFlags_ {
    /// enum 1 << 0 used to be XRAPI_FRAME_LAYER_FLAG_WRITE_ALPHA.

    /// NOTE: On Oculus standalone devices, chromatic aberration correction is enabled
    /// by default.
    /// For non Oculus standalone devices, this must be explicitly enabled by specifying the layer
    /// flag as it is a quality / performance trade off.
    XRAPI_FRAME_LAYER_FLAG_CHROMATIC_ABERRATION_CORRECTION = 1 << 1,
    /// Used for some HUDs, but generally considered bad practice.
    XRAPI_FRAME_LAYER_FLAG_FIXED_TO_VIEW = 1 << 2,
    /// Spin the layer - for loading icons
    XRAPI_FRAME_LAYER_FLAG_SPIN = 1 << 3,
    /// Clip fragments outside the layer's TextureRect
    XRAPI_FRAME_LAYER_FLAG_CLIP_TO_TEXTURE_RECT = 1 << 4,
    
    /// To get gamma correct sRGB filtering of the eye textures, the textures must be
    /// allocated with GL_SRGB8_ALPHA8 format and the window surface must be allocated
    /// with these attributes:
    /// EGL_GL_COLORSPACE_KHR,  EGL_GL_COLORSPACE_SRGB_KHR
    ///
    /// While we can reallocate textures easily enough, we can't change the window
    /// colorspace without relaunching the entire application, so if you want to
    /// be able to toggle between gamma correct and incorrect, you must allocate
    /// the framebuffer as sRGB, then inhibit that processing when using normal
    /// textures.
    ///
    /// If the texture being read isn't an sRGB texture, the conversion
    /// on write must be inhibited or the colors are washed out.
    /// This is necessary for using external images on an sRGB framebuffer.
    XRAPI_FRAME_LAYER_FLAG_INHIBIT_SRGB_FRAMEBUFFER = 1 << 8,

    
    /// Allow Layer to use an expensive filtering mode. Only useful for 2D layers that are high
    /// resolution (e.g. a remote desktop layer), typically double or more the target resolution.
    XRAPI_FRAME_LAYER_FLAG_FILTER_EXPENSIVE = 1 << 19,

    
} xrFrameLayerFlags;

/// The user's eye (left or right) that can see a layer.
typedef enum xrFrameLayerEye_ {
    XRAPI_FRAME_LAYER_EYE_LEFT = 0,
    XRAPI_FRAME_LAYER_EYE_RIGHT = 1,
    XRAPI_FRAME_LAYER_EYE_MAX = 2
} xrFrameLayerEye;

/// Selects an operation for alpha blending two images.
typedef enum xrFrameLayerBlend_ {
    XRAPI_FRAME_LAYER_BLEND_ZERO = 0,
    XRAPI_FRAME_LAYER_BLEND_ONE = 1,
    XRAPI_FRAME_LAYER_BLEND_SRC_ALPHA = 2,
    /// enum 3 used to be XRAPI_FRAME_LAYER_BLEND_DST_ALPHA.
    /// enum 4 used to be XRAPI_FRAME_LAYER_BLEND_ONE_MINUS_DST_ALPHA.
    XRAPI_FRAME_LAYER_BLEND_ONE_MINUS_SRC_ALPHA = 5
} xrFrameLayerBlend;

/// Extra latency mode pipelines app CPU work a frame ahead of VR composition.
typedef enum xrExtraLatencyMode_ {
    XRAPI_EXTRA_LATENCY_MODE_OFF = 0,
    XRAPI_EXTRA_LATENCY_MODE_ON = 1,
    XRAPI_EXTRA_LATENCY_MODE_DYNAMIC = 2
} xrExtraLatencyMode;

//-------------------------------------
// Legacy monolithic FrameParm submission structures for xrapiSubmitFrame.
//-------------------------------------

/// \deprecated The xrapiSubmitFrame2 path with flexible layer types
/// should be used instead.
typedef enum xrFrameLayerType_ { XRAPI_FRAME_LAYER_TYPE_MAX = 4 } xrFrameLayerType;

/// A compositor layer.
/// \note Any layer textures that are dynamic must be triple buffered.
/// \deprecated The xrapiSubmitFrame2 path with flexible layer types
/// should be used instead.
typedef struct xrFrameLayerTexture_ {
    /// Because OpenGL ES does not support clampToBorder, it is the
    /// application's responsibility to make sure that all mip levels
    /// of the primary eye texture have a black border that will show
    /// up when time warp pushes the texture partially off screen.
    xrTextureSwapChain* ColorTextureSwapChain;

    /// \deprecated The depth texture is optional for positional time warp.
    xrTextureSwapChain* DepthTextureSwapChain;

    /// Index to the texture from the set that should be displayed.
    int TextureSwapChainIndex;

    /// Points on the screen are mapped by a distortion correction
    /// function into ( TanX, TanY, -1, 1 ) vectors that are transformed
    /// by this matrix to get ( S, T, Q, _ ) vectors that are looked
    /// up with texture2dproj() to get texels.
    xrMatrix4f TexCoordsFromTanAngles;

    /// Only texels within this range should be drawn.
    /// This is a sub-rectangle of the [(0,0)-(1,1)] texture coordinate range.
    xrRectf TextureRect;

    XRAPI_PADDING(4)

    /// The tracking state for which ModelViewMatrix is correct.
    /// It is ok to update the orientation for each eye, which
    /// can help minimize black edge pull-in, but the position
    /// must remain the same for both eyes, or the position would
    /// seem to judder "backwards in time" if a frame is dropped.
    xrRigidBodyPosef HeadPose;

            /// \unused parameter.
        unsigned char Pad[8];
        } xrFrameLayerTexture;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrFrameLayerTexture, 200);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrFrameLayerTexture, 208);

/// Per-frame state of a compositor layer.
/// \deprecated The xrapiSubmitFrame2 path with flexible layer types
/// should be used instead.
typedef struct xrFrameLayer_ {
    /// Image used for each eye.
    xrFrameLayerTexture Textures[XRAPI_FRAME_LAYER_EYE_MAX];

    /// Speed and scale of rotation when XRAPI_FRAME_LAYER_FLAG_SPIN is set in xrFrameLayer::Flags
    float SpinSpeed; //< Radians/Second
    float SpinScale;

    /// Color scale for this layer (including alpha)
    float ColorScale;

    /// padding for deprecated variable.
    XRAPI_PADDING(4)

    /// Layer blend function.
    xrFrameLayerBlend SrcBlend;
    xrFrameLayerBlend DstBlend;

    /// Combination of xrFrameLayerFlags flags.
    int Flags;

    /// explicit padding for x86
    XRAPI_PADDING_32_BIT(4)
} xrFrameLayer;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrFrameLayer, 432);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrFrameLayer, 448);

/// Configuration parameters that affect system performance and scheduling behavior.
/// \deprecated The xrapiSubmitFrame2 path with flexible layer types
/// should be used instead.
typedef struct xrPerformanceParms_ {
    /// These are fixed clock levels in the range [0, 3].
    int CpuLevel;
    int GpuLevel;

    /// These threads will get SCHED_FIFO.
    int MainThreadTid;
    int RenderThreadTid;
} xrPerformanceParms;

XRAPI_ASSERT_TYPE_SIZE(xrPerformanceParms, 16);

/// Per-frame details.
/// \deprecated The xrapiSubmitFrame2 path with flexible layer types
/// should be used instead.
typedef struct xrFrameParms_ {
    xrStructureType Type;

    XRAPI_PADDING(4)

    /// Layers composited in the time warp.
    xrFrameLayer Layers[XRAPI_FRAME_LAYER_TYPE_MAX];
    int LayerCount;

    /// Combination of xrFrameFlags flags.
    int Flags;

    /// Application controlled frame index that uniquely identifies this particular frame.
    /// This must be the same frame index that was passed to xrapiGetPredictedDisplayTime()
    /// when synthesis of this frame started.
    long long FrameIndex;

    /// WarpSwap will not return until at least this many V-syncs have
    /// passed since the previous WarpSwap returned.
    /// Setting to 2 will reduce power consumption and may make animation
    /// more regular for applications that can't hold full frame rate.
    int SwapInterval;

    /// Latency Mode.
    xrExtraLatencyMode ExtraLatencyMode;

            /// \unused parameter.
        xrMatrix4f Reserved;
        
            /// \unused parameter.
        void* Reserved1;
        
    /// CPU/GPU performance parameters.
    xrPerformanceParms PerformanceParms;

    /// For handling HMD events and power level state changes.
    xrJava Java;
} xrFrameParms;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrFrameParms, 1856);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrFrameParms, 1936);

//-------------------------------------
// Flexible Layer Type structures for xrapiSubmitFrame2.
//-------------------------------------

enum { xrMaxLayerCount = 16 };

/// A layer type.
typedef enum xrLayerType2_ {
    XRAPI_LAYER_TYPE_PROJECTION2 = 1,
        XRAPI_LAYER_TYPE_CYLINDER2 = 3,
    XRAPI_LAYER_TYPE_CUBE2 = 4,
    XRAPI_LAYER_TYPE_EQUIRECT2 = 5,
    XRAPI_LAYER_TYPE_LOADING_ICON2 = 6,
    XRAPI_LAYER_TYPE_FISHEYE2 = 7,
} xrLayerType2;

/// Properties shared by any type of layer.
typedef struct xrLayerHeader2_ {
    xrLayerType2 Type;
    uint32_t Flags;

    xrVector4f ColorScale;
    xrFrameLayerBlend SrcBlend;
    xrFrameLayerBlend DstBlend;
            /// \unused parameter.
        void* Reserved;
        } xrLayerHeader2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerHeader2, 36);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerHeader2, 40);

/// xrLayerProjection2 provides support for a typical world view layer.
/// \note Any layer textures that are dynamic must be triple buffered.
typedef struct xrLayerProjection2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_PROJECTION2.
    xrLayerHeader2 Header;
    XRAPI_PADDING_32_BIT(4)

    xrRigidBodyPosef HeadPose;

    struct {
        xrTextureSwapChain* ColorSwapChain;
        int SwapChainIndex;
        xrMatrix4f TexCoordsFromTanAngles;
        xrRectf TextureRect;
    } Textures[XRAPI_FRAME_LAYER_EYE_MAX];
} xrLayerProjection2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerProjection2, 312);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerProjection2, 328);

/// xrLayerCylinder2 provides support for a single 2D texture projected onto a cylinder shape.
///
/// For Cylinder, the vertex coordinates will be transformed as if the texture type was CUBE.
/// Additionally, the interpolated vec3 will be remapped to vec2 by a direction-to-hemicyl mapping.
/// This mapping is currently hard-coded to 180 degrees around and 60 degrees vertical FOV.
///
/// After the mapping to 2D, an optional textureMatrix is applied. In the monoscopic case, the
/// matrix will typically be the identity matrix (ie no scale, bias). In the stereo case, when the
/// image source comes from a single image, the transform is necessary to map the [0.0,1.0] output
/// to a different (sub)rect.
///
/// Regardless of how the textureMatrix transforms the vec2 output of the equirect transform, each
/// TextureRect clamps the resulting texture coordinates so that no coordinates are beyond the
/// specified extents. No guarantees are made about whether fragments will be shaded outside the
/// rect, so it is important that the subrect have a transparent border.
///
typedef struct xrLayerCylinder2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_CYLINDER2.
    xrLayerHeader2 Header;
    XRAPI_PADDING_32_BIT(4)

    xrRigidBodyPosef HeadPose;

    struct {
        /// Texture type used to create the swapchain must be a 2D target (XRAPI_TEXTURE_TYPE_2D_*).
        xrTextureSwapChain* ColorSwapChain;
        int SwapChainIndex;
        xrMatrix4f TexCoordsFromTanAngles;
        xrRectf TextureRect;
        /// \note textureMatrix is set up like the following:
        ///	sx,  0, tx, 0
        ///	0,  sy, ty, 0
        ///	0,   0,  1, 0
        ///	0,   0,  0, 1
        /// since we do not need z coord for mapping to 2d texture.
        xrMatrix4f TextureMatrix;
    } Textures[XRAPI_FRAME_LAYER_EYE_MAX];
} xrLayerCylinder2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerCylinder2, 440);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerCylinder2, 456);

/// xrLayerCube2 provides support for a single timewarped cubemap at infinity
/// with optional Offset vector (provided in normalized [-1.0,1.0] space).
///
/// Cube maps are an omni-directional layer source that are directly supported
/// by the graphics hardware. The nature of the cube map definition results in
/// higher resolution (in pixels per solid angle) at the corners and edges of
/// the cube and lower resolution at the center of each face. While the cube map
/// does have variability in sample density, the variability is spread symmetrically
/// around the sphere.
///
/// Sometimes it is valuable to have an omni-directional format that has a
/// directional bias where quality and sample density is better in a particular
/// direction or over a particular region. If we changed the cube map sampling
///
/// from:
///   color = texture( cubeLayerSampler, direction );
/// to:
///   color = texture( cubeLayerSampler, normalize( direction ) + offset );
///
/// we can provide a remapping of the cube map sample distribution such that
/// samples in the "offset" direction map to a smaller region of the cube map
/// (and are thus higher resolution).
///
/// A normal high resolution cube map can be resampled using the inverse of this
/// mapping to retain high resolution for one direction while signficantly reducing
/// the required size of the cube map.
///
typedef struct xrLayerCube2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_CUBE2.
    xrLayerHeader2 Header;
    XRAPI_PADDING_32_BIT(4)

    xrRigidBodyPosef HeadPose;
    xrMatrix4f TexCoordsFromTanAngles;

    xrVector3f Offset;

    struct {
        /// Texture type used to create the swapchain must be a cube target
        /// (XRAPI_TEXTURE_TYPE_CUBE).
        xrTextureSwapChain* ColorSwapChain;
        int SwapChainIndex;
    } Textures[XRAPI_FRAME_LAYER_EYE_MAX];
#ifdef __i386__
    uint32_t Padding;
#endif
} xrLayerCube2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerCube2, 232);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerCube2, 248);

/// xrLayerEquirect2 provides support for a single Equirectangular texture at infinity.
///
/// For Equirectangular, the vertex coordinates will be transformed as if the texture type was CUBE,
/// and in the fragment shader, the interpolated vec3 will be remapped to vec2 by a
/// direction-to-equirect mapping.
///
/// After the mapping to 2D, an optional textureMatrix is applied. In the monoscopic case, the
/// matrix will typically be the identity matrix (ie no scale, bias). In the stereo case, when the
/// image source come from a single image, the transform is necessary to map the [0.0,1.0] output to
/// a different (sub)rect.
///
/// Regardless of how the textureMatrix transforms the vec2 output of the equirect transform, each
/// TextureRect clamps the resulting texture coordinates so that no coordinates are beyond the
/// specified extents. No guarantees are made about whether fragments will be shaded outside the
/// rect, so it is important that the subrect have a transparent border.
///
typedef struct xrLayerEquirect2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_EQUIRECT2.
    xrLayerHeader2 Header;
    XRAPI_PADDING_32_BIT(4)

    xrRigidBodyPosef HeadPose;
    xrMatrix4f TexCoordsFromTanAngles;

    struct {
        /// Texture type used to create the swapchain must be a 2D target (XRAPI_TEXTURE_TYPE_2D_*).
        xrTextureSwapChain* ColorSwapChain;
        int SwapChainIndex;
        xrRectf TextureRect;
        /// \note textureMatrix is set up like the following:
        ///	sx,  0, tx, 0
        ///	0,  sy, ty, 0
        ///	0,   0,  1, 0
        ///	0,   0,  0, 1
        /// since we do not need z coord for mapping to 2d texture.
        xrMatrix4f TextureMatrix;
    } Textures[XRAPI_FRAME_LAYER_EYE_MAX];
} xrLayerEquirect2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerEquirect2, 376);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerEquirect2, 392);

/// xrLayerLoadingIcon2 provides support for a monoscopic spinning layer.
///
typedef struct xrLayerLoadingIcon2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_LOADING_ICON2.
    xrLayerHeader2 Header;

    float SpinSpeed; //< radians per second
    float SpinScale;

    /// Only monoscopic texture supported for spinning layer.
    xrTextureSwapChain* ColorSwapChain;
    int SwapChainIndex;
} xrLayerLoadingIcon2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerLoadingIcon2, 52);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerLoadingIcon2, 64);

/// An "equiangular fisheye" or "f-theta" lens can be used to capture photos or video
/// of around 180 degrees without stitching.
///
/// The cameras probably aren't exactly vertical, so a transformation may need to be applied
/// before performing the fisheye calculation.
/// A stereo fisheye camera rig will usually have slight misalignments between the two
/// cameras, so they need independent transformations.
///
/// Once in lens space, the ray is transformed into an ideal fisheye projection, where the
/// 180 degree hemisphere is mapped to a -1 to 1 2D space.
///
/// From there it can be mapped into actual texture coordinates, possibly two to an image for
/// stereo.
///
typedef struct xrLayerFishEye2_ {
    /// Header.Type must be XRAPI_LAYER_TYPE_FISHEYE2.
    xrLayerHeader2 Header;
    XRAPI_PADDING_32_BIT(4)

    xrRigidBodyPosef HeadPose;

    struct {
        xrTextureSwapChain* ColorSwapChain;
        int SwapChainIndex;
        xrMatrix4f LensFromTanAngles; //< transforms a tanAngle ray into lens space
        xrRectf TextureRect; //< packed stereo images will need to clamp at the mid border
        xrMatrix4f TextureMatrix; //< transform from a -1 to 1 ideal fisheye to the texture
        xrVector4f Distortion; //< Not currently used.
    } Textures[XRAPI_FRAME_LAYER_EYE_MAX];
} xrLayerFishEye2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrLayerFishEye2, 472);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrLayerFishEye2, 488);

/// Union that combines xrLayer types in a way that allows them
/// to be used in a polymorphic way.
typedef union xrLayer_Union2_ {
    xrLayerHeader2 Header;
    xrLayerProjection2 Projection;
    xrLayerCylinder2 Cylinder;
    xrLayerCube2 Cube;
    xrLayerEquirect2 Equirect;
    xrLayerLoadingIcon2 LoadingIcon;
    xrLayerFishEye2 FishEye;
} xrLayer_Union2;

/// Parameters for frame submission.
typedef struct xrSubmitFrameDescription2_ {
    uint32_t Flags;
    uint32_t SwapInterval;
    uint64_t FrameIndex;
    double DisplayTime;
            /// \unused parameter.
        unsigned char Pad[8];
            uint32_t LayerCount;
    const xrLayerHeader2* const* Layers;
} xrSubmitFrameDescription2;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrSubmitFrameDescription2, 40);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrSubmitFrameDescription2, 48);

//-----------------------------------------------------------------
// Performance
//-----------------------------------------------------------------

/// Identifies a VR-related application thread.
typedef enum xrPerfThreadType_ {
    XRAPI_PERF_THREAD_TYPE_MAIN = 0,
    XRAPI_PERF_THREAD_TYPE_RENDERER = 1,
} xrPerfThreadType;


//-----------------------------------------------------------------
// Events
//-----------------------------------------------------------------

typedef enum xrEventType_ {
    // No event. This is returned if no events are pending.
    XRAPI_EVENT_NONE = 0,
    // Events were lost due to event queue overflow.
    XRAPI_EVENT_DATA_LOST = 1,
    // The application's frames are visible to the user.
    XRAPI_EVENT_VISIBILITY_GAINED = 2,
    // The application's frames are no longer visible to the user.
    XRAPI_EVENT_VISIBILITY_LOST = 3,
    // The current activity is in the foreground and has input focus.
    XRAPI_EVENT_FOCUS_GAINED = 4,
    // The current activity is in the background (but possibly still visible) and has lost input
    // focus.
    XRAPI_EVENT_FOCUS_LOST = 5,
    } xrEventType;


typedef struct xrEventHeader_ {
    xrEventType EventType;
} xrEventHeader;

// Event structure for XRAPI_EVENT_DATA_LOST
typedef struct xrEventDataLost_ {
    xrEventHeader EventHeader;
} xrEventDataLost;

// Event structure for XRAPI_EVENT_VISIBILITY_GAINED
typedef struct xrEventVisibilityGained_ {
    xrEventHeader EventHeader;
} xrEventVisibilityGained;

// Event structure for XRAPI_EVENT_VISIBILITY_LOST
typedef struct xrEventVisibilityLost_ {
    xrEventHeader EventHeader;
} xrEventVisibilityLost;

// Event structure for XRAPI_EVENT_FOCUS_GAINED
typedef struct xrEventFocusGained_ {
    xrEventHeader EventHeader;
} xrEventFocusGained;

// Event structure for XRAPI_EVENT_FOCUS_LOST
typedef struct xrEventFocusLost_ {
    xrEventHeader EventHeader;
} xrEventFocusLost;


typedef struct xrEventDataBuffer_ {
    xrEventHeader EventHeader;
    unsigned char EventData[4000];
} xrEventDataBuffer;

#define XRAPI_LARGEST_EVENT_TYPE xrEventDataBuffer

typedef enum xrEventSize_ { XRAPI_MAX_EVENT_SIZE = sizeof(XRAPI_LARGEST_EVENT_TYPE) } xrEventSize;

#endif // XR_XrApiTypes_h
