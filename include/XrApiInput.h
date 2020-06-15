
#ifndef XR_XrApiInput_h
#define XR_XrApiInput_h

#include <stddef.h>
#include <stdint.h>
#include "XrApiConfig.h"
#include "XrApiTypes.h"

/// Describes button input types.
/// For the Gear VR Controller and headset, only the following xrButton types are reported to the
/// application:
///
/// xrButton_Back, xrButton_A, xrButton_Enter
///
/// xrButton_Home, xrButton_VolUp, xrButtonVolDown and xrButton_Back are system buttons that are
/// never reported to applications. xrButton_Back button has system-level handling for long
/// presses, but application-level handling for short-presses. Since a short-press is determined by
/// the time interval between down and up events, the xrButton_Back flag is only set when the back
/// button comes up in less than the short-press time (0.25 seconds). The xrButton_Back flag always
/// signals a short press and will only remain set for a single frame.
typedef enum xrButton_ {
    xrButton_A = 0x00000001, // Set for trigger pulled on the Gear VR and Go Controllers
    xrButton_B = 0x00000002,
    xrButton_RThumb = 0x00000004,
    xrButton_RShoulder = 0x00000008,

    xrButton_X = 0x00000100,
    xrButton_Y = 0x00000200,
    xrButton_LThumb = 0x00000400,
    xrButton_LShoulder = 0x00000800,

    xrButton_Up = 0x00010000,
    xrButton_Down = 0x00020000,
    xrButton_Left = 0x00040000,
    xrButton_Right = 0x00080000,
    xrButton_Enter = 0x00100000, //< Set for touchpad click on the Gear VR and Go Controllers, menu
                                  // button on Left Quest Controller
    xrButton_Back = 0x00200000, //< Back button on the headset or Gear VR Controller (only set when
                                 // a short press comes up)
        xrButton_GripTrigger = 0x04000000, //< grip trigger engaged
        xrButton_Trigger = 0x20000000, //< Index Trigger engaged
        xrButton_Joystick = 0x80000000, //< Click of the Joystick

    xrButton_EnumSize = 0x7fffffff
} xrButton;

/// Describes touch input types.
/// These values map to capacitive touch values and derived pose states
typedef enum xrTouch_ {
    xrTouch_A = 0x00000001, //< The A button has a finger resting on it.
    xrTouch_B = 0x00000002, //< The B button has a finger resting on it.
    xrTouch_X = 0x00000004, //< The X button has a finger resting on it.
    xrTouch_Y = 0x00000008, //< The Y button has a finger resting on it.
    xrTouch_TrackPad = 0x00000010, //< The TrackPad has a finger resting on it.
    xrTouch_Joystick = 0x00000020, //< The Joystick has a finger resting on it.
    xrTouch_IndexTrigger = 0x00000040, //< The Index Trigger has a finger resting on it.
    xrTouch_ThumbUp =
        0x00000100, //< None of A, B, X, Y, or Joystick has a finger/thumb in proximity to it
    xrTouch_IndexPointing = 0x00000200, //< The finger is sufficiently far away from the trigger to
                                         // not be considered in proximity to it.
    xrTouch_BaseState =
        0x00000300, //< No buttons touched or in proximity.  finger pointing and thumb up.
    xrTouch_LThumb = 0x00000400, //< The Left controller Joystick has a finger/thumb resting on it.
    xrTouch_RThumb =
        0x00000800, //< The Right controller Joystick has a finger/thumb resting on it.
    xrTouch_EnumSize
} xrTouch;

/// Specifies which controller is connected; multiple can be connected at once.
typedef enum xrControllerType_ {
    xrControllerType_None = 0,
    xrControllerType_Reserved0 = (1 << 0), //< LTouch in CAPI
    xrControllerType_Reserved1 = (1 << 1), //< RTouch in CAPI
    xrControllerType_TrackedRemote = (1 << 2),
    xrControllerType_Headset = (1 << 3),
    xrControllerType_Gamepad = (1 << 4), //< Xbox in CAPI
    xrControllerType_Hand = (1 << 5),

        xrControllerType_EnumSize = 0x7fffffff
} xrControllerType;

typedef uint32_t xrDeviceID;

typedef enum xrDeviceIdType_ { xrDeviceIdType_Invalid = 0x7fffffff } xrDeviceIdType;

/// This header starts all xrInputCapabilities structures. It should only hold fields
/// that are common to all input controllers.
typedef struct xrInputCapabilityHeader_ {
    xrControllerType Type;

    /// A unique ID for the input device
    xrDeviceID DeviceID;
} xrInputCapabilityHeader;

/// Specifies capabilites of a controller
/// Note that left and right hand are non-exclusive (a two-handed controller could set both)
typedef enum xrControllerCapabilities_ {
    xrControllerCaps_HasOrientationTracking = 0x00000001,
    xrControllerCaps_HasPositionTracking = 0x00000002,
    xrControllerCaps_LeftHand = 0x00000004, //< Controller is configured for left hand
    xrControllerCaps_RightHand = 0x00000008, //< Controller is configured for right hand

    xrControllerCaps_ModelOculusGo = 0x00000010, //< Controller for Oculus Go devices

        xrControllerCaps_HasAnalogIndexTrigger =
        0x00000040, //< Controller has an analog index trigger vs. a binary one
    xrControllerCaps_HasAnalogGripTrigger =
        0x00000080, //< Controller has an analog grip trigger vs. a binary one
        xrControllerCaps_HasSimpleHapticVibration =
        0x00000200, //< Controller supports simple haptic vibration
    xrControllerCaps_HasBufferedHapticVibration =
        0x00000400, //< Controller supports buffered haptic vibration

    xrControllerCaps_ModelGearVR = 0x00000800, //< Controller is the Gear VR Controller

    xrControllerCaps_HasTrackpad = 0x00001000, //< Controller has a trackpad

    xrControllerCaps_HasJoystick = 0x00002000, //< Controller has a joystick.
    xrControllerCaps_ModelOculusTouch = 0x00004000, //< Oculus Touch Controller For Oculus Quest

    
    xrControllerCaps_EnumSize = 0x7fffffff
} xrControllerCapabilties;

//-----------------------------------------------------------------
// Tracked Remote Capabilities
//-----------------------------------------------------------------

/// Details about the Oculus Remote input device.
typedef struct xrInputTrackedRemoteCapabilities_ {
    xrInputCapabilityHeader Header;

    /// Mask of controller capabilities described by xrControllerCapabilities
    uint32_t ControllerCapabilities;

    /// Mask of button capabilities described by xrButton
    uint32_t ButtonCapabilities;

    /// Maximum coordinates of the Trackpad, bottom right exclusive
    /// For a 300x200 Trackpad, return 299x199
    uint16_t TrackpadMaxX;
    uint16_t TrackpadMaxY;

    /// Size of the Trackpad in mm (millimeters)
    float TrackpadSizeX;
    float TrackpadSizeY;

    /// added in API version 1.1.13.0
    /// Maximum submittable samples for the haptics buffer
    uint32_t HapticSamplesMax;
    /// length in milliseconds of a sample in the haptics buffer.
    uint32_t HapticSampleDurationMS;
    /// added in API version 1.1.15.0
    uint32_t TouchCapabilities;
    uint32_t Reserved4;
    uint32_t Reserved5;
} xrInputTrackedRemoteCapabilities;

/// Capabilities for the Head Mounted Tracking device (i.e. the headset).
/// Note that the GearVR headset firmware always sends relative coordinates
/// with the initial touch position offset by (1280,720). There is no way
/// to get purely raw coordinates from the headset. In addition, these
/// coordinates get adjusted for acceleration resulting in a slow movement
/// from one edge to the other the having a coordinate range of about 300
/// units, while a fast movement from edge to edge may result in a range
/// close to 900 units.
/// This means the headset touchpad needs to be handled differently than
/// the GearVR Controller touchpad.
typedef struct xrInputHeadsetCapabilities_ {
    xrInputCapabilityHeader Header;

    /// Mask of controller capabilities described by xrControllerCapabilities
    uint32_t ControllerCapabilities;

    /// Mask of button capabilities described by xrButton
    uint32_t ButtonCapabilities;

    /// Maximum coordinates of the Trackpad, bottom right exclusive
    /// For a 300x200 Trackpad, return 299x199
    uint16_t TrackpadMaxX;
    uint16_t TrackpadMaxY;

    /// Size of the Trackpad in mm (millimeters)
    float TrackpadSizeX;
    float TrackpadSizeY;
} xrInputHeadsetCapabilities;

/// Capabilities for an XBox style game pad
typedef struct xrInputGamepadCapabilities_ {
    xrInputCapabilityHeader Header;

    /// Mask of controller capabilities described by xrControllerCapabilities
    uint32_t ControllerCapabilities;

    /// Mask of button capabilities described by xrButton
    uint32_t ButtonCapabilities;

    // Reserved for future use.
    uint64_t Reserved[20];
} xrInputGamepadCapabilities;


/// The buffer data for playing haptics
typedef struct xrHapticBuffer_ {
    /// Start time of the buffer
    double BufferTime;

    /// Number of samples in the buffer;
    uint32_t NumSamples;

    // True if this is the end of the buffers being sent
    bool Terminated;

    uint8_t* HapticBuffer;
} xrHapticBuffer;

/// This header starts all xrInputState structures. It should only hold fields
/// that are common to all input controllers.
typedef struct xrInputStateHeader_ {
    /// Type type of controller
    xrControllerType ControllerType;

    /// System time when the controller state was last updated.
    double TimeInSeconds;
} xrInputStateHeader;

/// xrInputStateTrackedRemote describes the complete input state for the
/// orientation-tracked remote. The TrackpadPosition coordinates returned
/// for the GearVR Controller are in raw, absolute units.
typedef struct xrInputStateTrackedRemote_ {
    xrInputStateHeader Header;

    /// Values for buttons described by xrButton.
    uint32_t Buttons;

    /// Finger contact status for trackpad
    /// true = finger is on trackpad, false = finger is off trackpad
    uint32_t TrackpadStatus;

    /// X and Y coordinates of the Trackpad
    xrVector2f TrackpadPosition;

    /// The percentage of max battery charge remaining.
    uint8_t BatteryPercentRemaining;
    /// Increments every time the remote is recentered. If this changes, the application may need
    /// to adjust its arm model accordingly.
    uint8_t RecenterCount;
    /// Reserved for future use.
    uint16_t Reserved;

    /// added in API version 1.1.13.0
    // Analog values from 0.0 - 1.0 of the pull of the triggers
    float IndexTrigger;
    float GripTrigger;

    /// added in API version 1.1.15.0
    uint32_t Touches;
    uint32_t Reserved5a;
    // Analog values from -1.0 - 1.0
    // The value is set to 0.0 on Joystick, if the magnitude of the vector is < 0.1f
    xrVector2f Joystick;
    // JoystickNoDeadZone does change the raw values of the data.
    xrVector2f JoystickNoDeadZone;

} xrInputStateTrackedRemote;


/// xrInputStateHeadset describes the complete input state for the
/// GearVR headset. The TrackpadPosition coordinates return for the
/// headset are relative coordinates, centered at (1280,720). See the
/// comments on xrInputHeadsetCapabilities for more information.
typedef struct xrInputStateHeadset_ {
    xrInputStateHeader Header;

    /// Values for buttons described by xrButton.
    uint32_t Buttons;

    /// finger contact status for trackpad
    /// true = finger is on trackpad, false = finger is off trackpad
    uint32_t TrackpadStatus;

    /// X and Y coordinates of the Trackpad
    xrVector2f TrackpadPosition;
} xrInputStateHeadset;

/// xrInputStateGamepad describes the input state gamepad input devices
typedef struct xrInputStateGamepad_ {
    xrInputStateHeader Header;

    /// Values for buttons described by xrButton.
    uint32_t Buttons;

    // Analog value from 0.0 - 1.0 of the pull of the Left Trigger
    float LeftTrigger;
    // Analog value from 0.0 - 1.0 of the pull of the Right Trigger
    float RightTrigger;

    /// X and Y coordinates of the Left Joystick, -1.0 - 1.0
    xrVector2f LeftJoystick;
    /// X and Y coordinates of the Right Joystick, -1.0 - 1.0
    xrVector2f RightJoystick;

    // Reserved for future use.
    uint64_t Reserved[20];
} xrInputStateGamepad;


//-----------------------------------------------------------------
// Hand tracking
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Hand capabilities
typedef enum xrHandCapabilities_ {
    xrHandCaps_LeftHand = (1 << 0), // if set, this is the left hand
    xrHandCaps_RightHand = (1 << 1), // if set, this is the right hand
    xrHandCaps_EnumSize = 0x7fffffff
} xrHandCapabilities;

typedef enum xrHandStateCapabilities_ {
    xrHandStateCaps_PinchIndex = (1 << 0), // if set, index finger pinch is supported
    xrHandStateCaps_PinchMiddle = (1 << 1), // if set, middle finger pinch is supported
    xrHandStateCaps_PinchRing = (1 << 2), // if set, ring finger pinch is supported
    xrHandStateCaps_PinchPinky = (1 << 3), // if set, pinky finger pinch is supported
    xrHandStateCaps_EnumSize = 0x7fffffff
} xrHandStateCapabilities;

typedef struct xrInputHandCapabilities_ {
    xrInputCapabilityHeader Header;

    // Mask of hand capabilities described by xrHandCapabilities
    uint32_t HandCapabilities;

    // Mask of hand state capabilities described by xrInputHandStateCapabilities
    uint32_t StateCapabilities;
} xrInputHandCapabilities;

typedef enum xrHandTrackingStatus_ {
    xrHandTrackingStatus_Untracked = 0, // not tracked
    xrHandTrackingStatus_Tracked = 1, // tracked
    xrHandTrackingStatus_EnumSize = 0x7fffffff
} xrHandTrackingStatus;

//-----------------------------------------------------------------
// Hand state

typedef enum xrHandFingers_ {
    xrHandFinger_Thumb = 0,
    xrHandFinger_Index = 1,
    xrHandFinger_Middle = 2,
    xrHandFinger_Ring = 3,
    xrHandFinger_Pinky = 4,
    xrHandFinger_Max,
    xrHandFinger_EnumSize = 0x7fffffff
} xrHandFingers;

typedef enum xrHandPinchStrength_ {
    xrHandPinchStrength_Index = 0, // hand is in the index finger pinch state
    xrHandPinchStrength_Middle = 1, // hand is in the middle finger pinch state
    xrHandPinchStrength_Ring = 2, // hand is in the ring finger pinch state
    xrHandPinchStrength_Pinky = 3, // hand is in the pinky finger pinch state
    xrHandPinchStrength_Max = 4,
    xrHandPinchStrength_EnumSize = 0x7fffffff
} xrHandPinchStrength;

typedef int16_t xrVertexIndex;

typedef enum xrHandBone_ {
    xrHandBone_Invalid = -1,
    xrHandBone_WristRoot = 0, // root frame of the hand, where the wrist is located
    xrHandBone_ForearmStub = 1, // frame for user's forearm
    xrHandBone_Thumb0 = 2, // thumb trapezium bone
    xrHandBone_Thumb1 = 3, // thumb metacarpal bone
    xrHandBone_Thumb2 = 4, // thumb proximal phalange bone
    xrHandBone_Thumb3 = 5, // thumb distal phalange bone
    xrHandBone_Index1 = 6, // index proximal phalange bone
    xrHandBone_Index2 = 7, // index intermediate phalange bone
    xrHandBone_Index3 = 8, // index distal phalange bone
    xrHandBone_Middle1 = 9, // middle proximal phalange bone
    xrHandBone_Middle2 = 10, // middle intermediate phalange bone
    xrHandBone_Middle3 = 11, // middle distal phalange bone
    xrHandBone_Ring1 = 12, // ring proximal phalange bone
    xrHandBone_Ring2 = 13, // ring intermediate phalange bone
    xrHandBone_Ring3 = 14, // ring distal phalange bone
    xrHandBone_Pinky0 = 15, // pinky metacarpal bone
    xrHandBone_Pinky1 = 16, // pinky proximal phalange bone
    xrHandBone_Pinky2 = 17, // pinky intermediate phalange bone
    xrHandBone_Pinky3 = 18, // pinky distal phalange bone
        xrHandBone_MaxSkinnable = 19,

    // Bone tips are position only. They are not used for skinning but useful for hit-testing.
    // NOTE: xrHandBone_ThumbTip == xrHandBone_MaxSkinnable since the extended tips need to be
    // contiguous
    xrHandBone_ThumbTip = xrHandBone_MaxSkinnable + 0, // tip of the thumb
    xrHandBone_IndexTip = xrHandBone_MaxSkinnable + 1, // tip of the index finger
    xrHandBone_MiddleTip = xrHandBone_MaxSkinnable + 2, // tip of the middle finger
    xrHandBone_RingTip = xrHandBone_MaxSkinnable + 3, // tip of the ring finger
    xrHandBone_PinkyTip = xrHandBone_MaxSkinnable + 4, // tip of the pinky
    xrHandBone_Max = xrHandBone_MaxSkinnable + 5,
    xrHandBone_EnumSize = 0x7fff
} xrHandBone;
typedef int16_t xrHandBoneIndex;

typedef enum xrConfidence_ {
    xrConfidence_LOW = 0x00000000,
    xrConfidence_HIGH = 0x3f800000
} xrConfidence;

/// Unified version struct
typedef enum xrHandVersion_ {
    xrHandVersion_1 = 0xdf000001, /// Current

    
    xrHandVersion_EnumSize = 0x7fffffff
} xrHandVersion;

// xrBoneCapsule
//    _---_
//  -"     "-
// /         \
// |----A----|
// |    |    |
// |    |    |
// |    |-r->|
// |    |    |
// |    |    |
// |----B----|
// \         /
//  -.     .-
//    '---'
typedef struct xrBoneCapsule_ {
    // Index of the bone this capsule is on.
    xrHandBoneIndex BoneIndex;
    // Points at either end of the cylinder inscribed in the capsule. Also the center points for
    // spheres at either end of the capsule. Points A and B in the diagram above.
    xrVector3f Points[2];
    // The radius of the capsule cylinder and of the half-sphere caps on the ends of the capsule.
    float Radius;
} xrBoneCapsule;

typedef enum xrHandConstants_ {
    xrHand_MaxVertices = 3000,
    xrHand_MaxIndices = xrHand_MaxVertices * 6,
    xrHand_MaxFingers = xrHandFinger_Max,
    xrHand_MaxPinchStrengths = xrHandPinchStrength_Max,
    xrHand_MaxSkinnableBones = xrHandBone_MaxSkinnable,
    xrHand_MaxBones = xrHandBone_Max,
    xrHand_MaxCapsules = 19,
        xrHand_EnumSize = 0x7fffffff
} xrHandConstants;

typedef enum xrInputStateHandStatus_ {
    xrInputStateHandStatus_PointerValid =
        (1 << 1), // if this is set the PointerPose and PinchStrength contain valid data, otherwise
                  // they should not be used.
    xrInputStateHandStatus_IndexPinching =
        (1 << 2), // if this is set the pinch gesture for that finger is on
    xrInputStateHandStatus_MiddlePinching =
        (1 << 3), // if this is set the pinch gesture for that finger is on
    xrInputStateHandStatus_RingPinching =
        (1 << 4), // if this is set the pinch gesture for that finger is on
    xrInputStateHandStatus_PinkyPinching =
        (1 << 5), // if this is set the pinch gesture for that finger is on
    xrInputStateHandStatus_SystemGestureProcessing =
        (1 << 6), // if this is set the hand is currently processing a system gesture
    xrInputStateHandStatus_EnumSize = 0x7fffffff
} xrInputStateHandStatus;

// Pass this structure to xrapiGetCurrentInputState() with a device id for a hand to get the
// current, second-order state of the hand.
typedef struct xrInputStateHand_ {
    xrInputStateHeader Header;

    // For each pinch type, indicates how far the fingers are into that pinch state. Range 0.0
    // to 1.0, where 1.0 is fully pinching. Indexable via the xrHandPinchStrength enums.
    float PinchStrength[xrHandPinchStrength_Max];

    // World space position and orientation of the pointer attached to the hand. This describes
    // a pointing ray useful for UI interactions.
    // Note that the pointer pose is not valid unless the xrInputStateHandStatus_PointerValid flag
    // is set in the InputStateStatus field.
    xrPosef PointerPose;

    // Status flags for this hand's input state. Mask of xrInputStateHandStatus flags.
    uint32_t InputStateStatus;
} xrInputStateHand;

//-----------------------------------------------------------------
// Hand pose

// Header for all hand pose structures.
typedef struct xrHandPoseHeader_ {
    // The version number of the Pose structure.
    // When requesting a pose with xrapiGetHandPose this MUST be set to the proper version.
    // If this is not set to a known version, or if the version it is set to is no longer
    // supported for the current SDK, xr_GetHand* functions will return xrError_InvalidParameter.
    xrHandVersion Version;

    /// Reserved for later use
    double Reserved;
} xrHandPoseHeader;

// Pass this structure to xrapiGetHandPose() to get the pose of the hand at a particular time.
typedef struct xrHandPose_ {
    xrHandPoseHeader Header;

    // Status of tracking for this pose. This is not a bit field, but an exclusive state.
    xrHandTrackingStatus Status;

    // Root pose of the hand in world space. Not to be confused with the root bone's transform.
    // The root bone can still be offset from this by the skeleton's rest pose.
    xrPosef RootPose;

    // Current rotation of each bone.
    xrQuatf BoneRotations[xrHandBone_Max];

    // Time stamp for the pose that was requested in global system time.
    double RequestedTimeStamp;

    // Time stamp of the captured sample that the pose was extrapolated from.
    double SampleTimeStamp;

    // Tracking confidence.
    // This is the amount of confidence that the system has that the entire hand pose is correct.
    xrConfidence HandConfidence;

    // Scale of the hand relative to the original hand model. This value may change at any time
    // based on the size of the hand being tracked. The default is 1.0.
    float HandScale;

    // Per-finger tracking confidence.
    // This is the amount of confidence the system has that the individual finger poses are correct.
    xrConfidence FingerConfidences[xrHandFinger_Max];
} xrHandPose;


XRAPI_EXPORT xrResult xrapiGetHandPose(
    xrMobile* xr,
    const xrDeviceID deviceID,
    const double absTimeInSeconds,
    xrHandPoseHeader* header);

//-----------------------------------------------------------------
// Hand skeleton

// Header for all mesh structures.
typedef struct xrHandSkeletonHeader_ {
    // The version number of the skeleton structure.
    xrHandVersion Version;
} xrHandSkeletonHeader;

typedef struct xrHandSkeleton_V1_ {
    // Version of the mesh structure.
    xrHandSkeletonHeader Header;

    // The number of bones in this skeleton.
    uint32_t NumBones;

    // The number of capsules on this skeleton.
    uint32_t NumCapsules;

    // reserved for future use
    uint32_t Reserved[5];

    // An array of count NumBones transforms for each bone in local (parent) space.
    xrPosef BonePoses[xrHand_MaxBones];

    // An array of count NumBones indicating the parent bone index for each bone.
    xrHandBoneIndex BoneParentIndices[xrHand_MaxBones];

    // An array of count NumCapsules xrHandCapsules. Note that the number of capsules
    // is not necessarily the same as the number of bones.
    xrBoneCapsule Capsules[xrHand_MaxCapsules];
} xrHandSkeleton;


XRAPI_EXPORT xrResult xrapiGetHandSkeleton(
    xrMobile* xr,
    const xrHandedness handedness,
    xrHandSkeletonHeader* header);

//-----------------------------------------------------------------
// Hand mesh

// Header for all mesh structures.
typedef struct xrHandMeshHeader_ {
    // The version number of the mesh structure.
    xrHandVersion Version;
} xrHandMeshHeader;

typedef struct xrHandMesh_V1_ {
    // All mesh structures will start with this header and the version.
    xrHandMeshHeader Header;

    // Number of unique vertices in the mesh.
    uint32_t NumVertices;
    // Number of unique indices in the mesh.
    uint32_t NumIndices;

    // Reserved for future use
    uint32_t Reserved[13];

    // An array of count NumVertices positions for each vertex.
    xrVector3f VertexPositions[xrHand_MaxVertices];
    // An array of count NumIndices of vertex indices specifying triangles that make up the mesh.
    xrVertexIndex Indices[xrHand_MaxIndices];
    // An array of count NumVertices of normals for each vertex.
    xrVector3f VertexNormals[xrHand_MaxVertices];
    // An array of count NumVertices of texture coordinates for each vertex.
    xrVector2f VertexUV0[xrHand_MaxVertices];
    // An array of count NumVertices of blend indices for each of the bones that each vertex is
    // weighted to. Always valid. An index of < 0 means no blend weight.
    xrVector4s BlendIndices[xrHand_MaxVertices];
    // An array of count NumVertices of weights for each of the bones affecting each vertex.
    xrVector4f BlendWeights[xrHand_MaxVertices];
} xrHandMesh;

XRAPI_EXPORT xrResult
xrapiGetHandMesh(xrMobile* xr, const xrHandedness handedness, xrHandMeshHeader* header);

#if defined(__cplusplus)
extern "C" {
#endif

/// Enumerates the input devices connected to the system
/// Start with index=0 and counting up. Stop when xrResult is < 0
///
/// Input: xrMobile, device index, and a capabilities header
/// The capabilities header does not need to have any fields set before calling.
/// Output: capabilitiesHeader with information for that enumeration index
XRAPI_EXPORT xrResult xrapiEnumerateInputDevices(
    xrMobile* xr,
    const uint32_t index,
    xrInputCapabilityHeader* capsHeader);

/// Returns the capabilities of the input device for the corresponding device ID
///
/// Input: xr, pointer to a capabilities structure
/// Output: capabilities will be filled with information for the deviceID
/// Example:
///     The Type field of the capabilitiesHeader must be set when calling this function.
///     Normally the capabilitiesHeader is obtained from the xrapiEnumerateInputDevices API
///     The Type field in the header should match the structure type that is passed.
///
///         xrInputCapabilityHeader capsHeader;
///         if ( xrapiEnumerateInputDevices( xr, deviceIndex, &capsHeader ) >= 0 ) {
///             if ( capsHeader.Type == xrDeviceType_TrackedRemote ) {
///                 xrInputTrackedRemoteCapabilities remoteCaps;
///                 remoteCaps.Header = capsHeader;
///                 xrapiGetInputDeviceCapabilities( xr, &remoteCaps.Header );
XRAPI_EXPORT xrResult
xrapiGetInputDeviceCapabilities(xrMobile* xr, xrInputCapabilityHeader* capsHeader);

/// Sets the vibration level of a haptic device.
/// there should only be one call to xrapiSetHapticVibrationSimple or
/// xrapiSetHapticVibrationBuffer per frame
///  additional calls of either will return xrError_InvalidOperation and have undefined behavior
/// Input: xr, deviceID, intensity: 0.0 - 1.0
XRAPI_EXPORT xrResult
xrapiSetHapticVibrationSimple(xrMobile* xr, const xrDeviceID deviceID, const float intensity);

/// Fills the haptic vibration buffer of a haptic device
/// there should only be one call to xrapiSetHapticVibrationSimple or
/// xrapiSetHapticVibrationBuffer per frame
///  additional calls of either will return xrError_InvalidOperation and have undefined behavior
/// Input: xr, deviceID, pointer to a hapticBuffer with filled in data.
XRAPI_EXPORT xrResult xrapiSetHapticVibrationBuffer(
    xrMobile* xr,
    const xrDeviceID deviceID,
    const xrHapticBuffer* hapticBuffer);


/// Returns the current input state for controllers, without positional tracking info.
///
/// Input: xr, deviceID, pointer to a capabilities structure (with Type field set)
/// Output: Upon return the inputState structure will be set to the device's current input state
/// Example:
///     The Type field of the passed xrInputStateHeader must be set to the type that
///     corresponds to the type of structure being passed.
///     The pointer to the xrInputStateHeader should be a pointer to a Header field in
///     structure matching the value of the Type field.
///
///     xrInputStateTrackedRemote state;
///     state.Header.Type = xrControllerType_TrackedRemote;
///     if ( xrapiGetCurrentInputState( xr, remoteDeviceID, &state.Header ) >= 0 ) {
XRAPI_EXPORT xrResult xrapiGetCurrentInputState(
    xrMobile* xr,
    const xrDeviceID deviceID,
    xrInputStateHeader* inputState);


/// Returns the predicted input state based on the specified absolute system time
/// in seconds. Pass absTime value of 0.0 to request the most recent sensor reading.
/// Input: xr, device ID, prediction time
/// Output: xrTracking structure containing the device's predicted tracking state.
XRAPI_EXPORT xrResult xrapiGetInputTrackingState(
    xrMobile* xr,
    const xrDeviceID deviceID,
    const double absTimeInSeconds,
    xrTracking* tracking);

/// Can be called from any thread while in VR mode. Recenters the tracked remote to the current yaw
/// of the headset. Input: xr, device ID Output: None
XRAPI_DEPRECATED(
    XRAPI_EXPORT void xrapiRecenterInputPose(xrMobile* xr, const xrDeviceID deviceID));

/// Enable or disable emulation for the GearVR Controller.
/// Emulation is false by default.
/// If emulationOn == true, then the back button and touch events on the GearVR Controller will be
/// sent through the Android dispatchKeyEvent and dispatchTouchEvent path as if they were from the
/// headset back button and touchpad. Applications that are intentionally enumerating the controller
/// will likely want to turn emulation off in order to differentiate between controller and headset
/// input events.
XRAPI_EXPORT xrResult xrapiSetRemoteEmulation(xrMobile* xr, const bool emulationOn);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // XR_XrApiInput_h
