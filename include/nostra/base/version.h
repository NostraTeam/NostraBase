#ifndef NBA_VERSION_H
#define NBA_VERSION_H

#include <stdint.h>

#define NBA_MAKE_VERSION(major, minor, patch, tweak)                                                 \
    ((uint64_t{major} << (16 * 0)) + (uint64_t{minor} << (16 * 1)) + (uint64_t{patch} << (16 * 2)) + \
     (uint64_t{tweak} << (16 * 3)))

#define NBA_INTERNAL_VERSION_GET_COMPONENT(version, index) \
    static_cast<uint16_t>((version & (uint64_t{0xFFFF} << 16 * index)) >> (16 * index))

#define NBA_VERSION_GET_MAJOR(version) NBA_INTERNAL_VERSION_GET_COMPONENT(version, 0)
#define NBA_VERSION_GET_MINOR(version) NBA_INTERNAL_VERSION_GET_COMPONENT(version, 1)
#define NBA_VERSION_GET_PATCH(version) NBA_INTERNAL_VERSION_GET_COMPONENT(version, 2)
#define NBA_VERSION_GET_TWEAK(version) NBA_INTERNAL_VERSION_GET_COMPONENT(version, 3)

#define NBA_VERSION_SET_MAJOR(version, major) (((uint16_t*)(&version))[0] = static_cast<uint16_t>(major))
#define NBA_VERSION_SET_MINOR(version, minor) (((uint16_t*)(&version))[1] = static_cast<uint16_t>(minor))
#define NBA_VERSION_SET_PATCH(version, patch) (((uint16_t*)(&version))[2] = static_cast<uint16_t>(patch))
#define NBA_VERSION_SET_TWEAK(version, tweak) (((uint16_t*)(&version))[3] = static_cast<uint16_t>(tweak))

#endif