
#ifndef XR_XrApiConfig_h
#define XR_XrApiConfig_h

/*

XRAPI_EXPORT
XRAPI_DEPRECATED

*/

#if defined(_MSC_VER) || defined(__ICL)

#if defined(XRAPI_ENABLE_EXPORT)
#define XRAPI_EXPORT __declspec(dllexport)
#else
#define XRAPI_EXPORT
#endif

#define XRAPI_DEPRECATED(fn) __declspec(deprecated) fn

#else

#if defined(XRAPI_ENABLE_EXPORT)
#define XRAPI_EXPORT __attribute__((__visibility__("default")))
#else
#define XRAPI_EXPORT
#endif

#define XRAPI_DEPRECATED(fn) fn __attribute__((deprecated))

#endif

#if defined(__x86_64__) || defined(__aarch64__) || defined(_WIN64)
#define XRAPI_64_BIT
#else
#define XRAPI_32_BIT
#endif

// clang-format off
/*

XRAPI_STATIC_ASSERT( exp )						// static assert
XRAPI_PADDING( bytes )							// insert bytes of padding
XRAPI_PADDING_32_BIT( bytes )					// insert bytes of padding only when using a 32-bit compiler
XRAPI_PADDING_64_BIT( bytes )					// insert bytes of padding only when using a 64-bit compiler
XRAPI_ASSERT_TYPE_SIZE( type, bytes )			// assert the size of a type
XRAPI_ASSERT_TYPE_SIZE_32_BIT( type, bytes )	// assert the size of a type only when using a 32-bit compiler
XRAPI_ASSERT_TYPE_SIZE_64_BIT( type, bytes )	// assert the size of a type only when using a 64-bit compiler
XRAPI_ALIGN( value, boundary )					// align memory to the given boundary value

*/
// clang-format on

#if defined(__cplusplus) && __cplusplus >= 201103L
#define XRAPI_STATIC_ASSERT(exp) static_assert(exp, #exp)
#endif

#if !defined(XRAPI_STATIC_ASSERT) && defined(__clang__)
#if __has_feature(cxx_static_assert) || __has_extension(cxx_static_assert)
#define XRAPI_STATIC_ASSERT(exp) static_assert(exp)
#endif
#endif

#if !defined(XRAPI_STATIC_ASSERT)
#if defined(__COUNTER__)
#define XRAPI_STATIC_ASSERT(exp) XRAPI_STATIC_ASSERT_ID(exp, __COUNTER__)
#else
#define XRAPI_STATIC_ASSERT(exp) XRAPI_STATIC_ASSERT_ID(exp, __LINE__)
#endif
#define XRAPI_STATIC_ASSERT_ID(exp, id) XRAPI_STATIC_ASSERT_ID_EXPANDED(exp, id)
#define XRAPI_STATIC_ASSERT_ID_EXPANDED(exp, id) typedef char assert_failed_##id[(exp) ? 1 : -1]
#endif

#if defined(__COUNTER__)
#define XRAPI_PADDING(bytes) XRAPI_PADDING_ID(bytes, __COUNTER__)
#else
#define XRAPI_PADDING(bytes) XRAPI_PADDING_ID(bytes, __LINE__)
#endif
#define XRAPI_PADDING_ID(bytes, id) XRAPI_PADDING_ID_EXPANDED(bytes, id)
#define XRAPI_PADDING_ID_EXPANDED(bytes, id) unsigned char dead##id[(bytes)];

#define XRAPI_ASSERT_TYPE_SIZE(type, bytes) XRAPI_STATIC_ASSERT(sizeof(type) == (bytes))

#if defined(XRAPI_64_BIT)
#define XRAPI_PADDING_32_BIT(bytes)
#if defined(__COUNTER__)
#define XRAPI_PADDING_64_BIT(bytes) XRAPI_PADDING_ID(bytes, __COUNTER__)
#else
#define XRAPI_PADDING_64_BIT(bytes) XRAPI_PADDING_ID(bytes, __LINE__)
#endif
#define XRAPI_ASSERT_TYPE_SIZE_32_BIT(type, bytes) XRAPI_STATIC_ASSERT(true)
#define XRAPI_ASSERT_TYPE_SIZE_64_BIT(type, bytes) \
    XRAPI_STATIC_ASSERT(sizeof(type) == (bytes))
#else
#define XRAPI_ASSERT_TYPE_SIZE(type, bytes) XRAPI_STATIC_ASSERT(sizeof(type) == (bytes))
#if defined(__COUNTER__)
#define XRAPI_PADDING_32_BIT(bytes) XRAPI_PADDING_ID(bytes, __COUNTER__)
#else
#define XRAPI_PADDING_32_BIT(bytes) XRAPI_PADDING_ID(bytes, __LINE__)
#endif
#define XRAPI_PADDING_64_BIT(bytes)
#define XRAPI_ASSERT_TYPE_SIZE_32_BIT(type, bytes) \
    XRAPI_STATIC_ASSERT(sizeof(type) == (bytes))
#define XRAPI_ASSERT_TYPE_SIZE_64_BIT(type, bytes) XRAPI_STATIC_ASSERT(true)
#endif

#if !defined(XRAPI_ALIGN)
#define XRAPI_ALIGN(value, boundary) ((value + boundary - 1) & (~(boundary - 1)))
#endif

#endif // !XR_XrApiConfig_h
