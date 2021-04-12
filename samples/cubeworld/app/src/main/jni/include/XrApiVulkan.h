
#ifndef XR_XrApiVulkan_h
#define XR_XrApiVulkan_h

#include "XrApiConfig.h"
#include "XrApiTypes.h"

#if defined(__cplusplus)
extern "C" {
#endif

// From <vulkan/vulkan.h>:
#if !defined(VK_VERSION_1_0)
#define VK_DEFINE_HANDLE(object) typedef struct object##_T* object;
#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) && !defined(__ILP32__)) || \
    defined(_M_X64) || defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) ||       \
    defined(__powerpc64__)
#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef struct object##_T* object;
#else
#define VK_DEFINE_NON_DISPATCHABLE_HANDLE(object) typedef uint64_t object;
#endif
VK_DEFINE_HANDLE(VkInstance)
VK_DEFINE_HANDLE(VkPhysicalDevice)
VK_DEFINE_HANDLE(VkDevice)
VK_DEFINE_HANDLE(VkQueue)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkImage)
VK_DEFINE_NON_DISPATCHABLE_HANDLE(VkDeviceMemory)
#define VK_NULL_HANDLE 0
#endif

/// Returns a list of strings delimited by a single space identifying Vulkan extensions that must
/// be enabled for the instance in order for the VR runtime to support Vulkan-based applications.
XRAPI_EXPORT xrResult
xrapiGetInstanceExtensionsVulkan(char* extensionNames, uint32_t* extensionNamesSize);

/// Returns a list of strings delimited by a single space identifying Vulkan extensions that must
/// be enabled for the device in order for the VR runtime to support Vulkan-based applications.
XRAPI_EXPORT xrResult
xrapiGetDeviceExtensionsVulkan(char* extensionNames, uint32_t* extensionNamesSize);

/// Initialization parameters unique to Vulkan.
typedef struct xrSystemCreateInfoVulkan_ {
    VkInstance Instance;
    VkPhysicalDevice PhysicalDevice;
    VkDevice Device;
} xrSystemCreateInfoVulkan;

XRAPI_ASSERT_TYPE_SIZE_32_BIT(xrSystemCreateInfoVulkan, 12);
XRAPI_ASSERT_TYPE_SIZE_64_BIT(xrSystemCreateInfoVulkan, 24);

/// Initializes the API for Vulkan support.
/// This is lightweight and does not create any threads.
/// This is called after xrapiInitialize and before texture swapchain creation, or
/// xrapienterVrMode.
XRAPI_EXPORT xrResult xrapiCreateSystemVulkan(xrSystemCreateInfoVulkan* systemInfo);

/// Destroys the API for Vulkan support.
/// This is called before xrapiShutdown.
XRAPI_EXPORT void xrapiDestroySystemVulkan();

/// Get the VkImage at the given index within the chain.
XRAPI_EXPORT VkImage
xrapiGetTextureSwapChainBufferVulkan(xrTextureSwapChain* chain, int index);

/// Get the foveation VkImage and corresponding size at the given index within the chain.
/// In case of failure, this returns a null image handle and zero width and height.
XRAPI_EXPORT xrResult xrapiGetTextureSwapChainBufferFoveationVulkan(
    xrTextureSwapChain* chain,
    int index,
    VkImage* image,
    uint32_t* imageWidth,
    uint32_t* imageHeight);

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // XR_XrApiVulkan_h
