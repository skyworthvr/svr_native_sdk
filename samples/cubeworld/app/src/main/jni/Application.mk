# Common build settings for all VR apps
BUILDTYPE := Debug
# This needs to be defined to get the right header directories for egl / etc
APP_PLATFORM := android-26

APP_ABI := armeabi-v7a arm64-v8a

# Statically link the GNU STL. This may not be safe for multi-so libraries but
# we don't know of any problems yet.
APP_STL := c++_static

# Make sure every shared lib includes a .note.gnu.build-id header, for crash reporting
APP_LDFLAGS := -Wl,--build-id

# Define the directories for $(import-module, ...) to look in
ROOT_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
NDK_MODULE_PATH := $(ROOT_DIR)

# Explicitly use GCC 4.8 as our toolchain. This is the 32-bit default as of
# r10d but versions as far back as r9d have 4.8. The previous default, 4.6, is
# deprecated as of r10c.
NDK_TOOLCHAIN_VERSION := clang
#NDK_TOOLCHAIN_VERSION := 4.9

APP_OPTIM := debug
