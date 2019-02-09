#ifndef NBA_VERSION_HPP
#define NBA_VERSION_HPP

#include "nostra/base/version.h"

#include <cstdint>

namespace nba
{
    class version final
    {
    private:
        std::uint64_t m_raw;

        using mask_underlying_type = std::uint64_t;

        constexpr static std::size_t MAJOR_INDEX = 0;
        constexpr static std::size_t MINOR_INDEX = 1;
        constexpr static std::size_t PATCH_INDEX = 2;
        constexpr static std::size_t TWEAK_INDEX = 3;

    public:
        struct mask
        {
            enum enum_type : mask_underlying_type
            {
                MAJOR = mask_underlying_type{0xFFFF} << 16 * MAJOR_INDEX,
                MINOR = mask_underlying_type{0xFFFF} << 16 * MINOR_INDEX,
                PATCH = mask_underlying_type{0xFFFF} << 16 * PATCH_INDEX,
                TWEAK = mask_underlying_type{0xFFFF} << 16 * TWEAK_INDEX,
                ALL   = MAJOR | MINOR | PATCH | TWEAK
            };
        };

        constexpr explicit version(std::uint16_t major = 0,
                                   std::uint16_t minor = 0,
                                   std::uint16_t patch = 0,
                                   std::uint16_t tweak = 0) noexcept;
        constexpr version(std::uint64_t raw) noexcept;

        constexpr std::uint64_t get_raw() const noexcept;
        constexpr std::uint64_t get_masked(mask_underlying_type m) const noexcept;

        constexpr std::uint16_t get_major() const noexcept;
        constexpr std::uint16_t get_minor() const noexcept;
        constexpr std::uint16_t get_patch() const noexcept;
        constexpr std::uint16_t get_tweak() const noexcept;

        inline void set_major(std::uint16_t major) noexcept;
        inline void set_minor(std::uint16_t minor) noexcept;
        inline void set_patch(std::uint16_t patch) noexcept;
        inline void set_tweak(std::uint16_t tweak) noexcept;
        inline void set_raw(std::uint64_t raw) noexcept;

        constexpr version operator+(const version& other) const;
        inline version& operator+=(const version& other);

        constexpr version operator-(const version& other) const;
        inline version& operator-=(const version& other);

        constexpr bool operator==(const version& other) const;
        constexpr bool operator!=(const version& other) const;

        constexpr bool operator<(const version& other) const;
        constexpr bool operator>(const version& other) const;

        constexpr bool operator<=(const version& other) const;
        constexpr bool operator>=(const version& other) const;
    };

    constexpr version::version(std::uint16_t major,
                               std::uint16_t minor,
                               std::uint16_t patch,
                               std::uint16_t tweak) noexcept :
        m_raw{NBA_MAKE_VERSION(major, minor, patch, tweak)}
    {}

    constexpr version::version(std::uint64_t raw) noexcept : m_raw{raw}
    {}

    constexpr std::uint64_t version::get_raw() const noexcept
    {
        return m_raw;
    }

    constexpr std::uint64_t version::get_masked(mask_underlying_type m) const noexcept
    {
        return get_raw() & static_cast<std::uint64_t>(m);
    }

    constexpr std::uint16_t version::get_major() const noexcept
    {
        return NBA_VERSION_GET_MAJOR(m_raw);
    }

    constexpr std::uint16_t version::get_minor() const noexcept
    {
        return NBA_VERSION_GET_MINOR(m_raw);
    }

    constexpr std::uint16_t version::get_patch() const noexcept
    {
        return NBA_VERSION_GET_PATCH(m_raw);
    }

    constexpr std::uint16_t version::get_tweak() const noexcept
    {
        return NBA_VERSION_GET_TWEAK(m_raw);
    }

    void version::set_major(std::uint16_t major) noexcept
    {
        NBA_VERSION_SET_MAJOR(m_raw, major);
    }

    void version::set_minor(std::uint16_t minor) noexcept
    {
        NBA_VERSION_SET_MINOR(m_raw, minor);
    }

    void version::set_patch(std::uint16_t patch) noexcept
    {
        NBA_VERSION_SET_PATCH(m_raw, patch);
    }

    void version::set_tweak(std::uint16_t tweak) noexcept
    {
        NBA_VERSION_SET_TWEAK(m_raw, tweak);
    }

    void version::set_raw(std::uint64_t raw) noexcept
    {
        m_raw = raw;
    }

    constexpr version version::operator+(const version& other) const
    {
        return version{get_major() + other.get_major(), get_minor() + other.get_minor(),
                       get_patch() + other.get_patch(), get_tweak() + other.get_tweak()};
    }

    version& version::operator+=(const version& other)
    {
        set_major(get_major() + other.get_major());
        set_minor(get_minor() + other.get_minor());
        set_patch(get_patch() + other.get_patch());
        set_tweak(get_tweak() + other.get_tweak());

        return *this;
    }

    constexpr version version::operator-(const version& other) const
    {
        return version{get_major() - other.get_major(), get_minor() - other.get_minor(),
                       get_patch() - other.get_patch(), get_tweak() - other.get_tweak()};
    }

    version& version::operator-=(const version& other)
    {
        set_major(get_major() - other.get_major());
        set_minor(get_minor() - other.get_minor());
        set_patch(get_patch() - other.get_patch());
        set_tweak(get_tweak() - other.get_tweak());

        return *this;
    }

    constexpr bool version::operator==(const version& other) const
    {
        return get_raw() == other.get_raw();
    }

    constexpr bool version::operator!=(const version& other) const
    {
        return get_raw() != other.get_raw();
    }

    constexpr bool version::operator<(const version& other) const
    {
        return get_raw() < other.get_raw();
    }

    constexpr bool version::operator>(const version& other) const
    {
        return get_raw() > other.get_raw();
    }

    constexpr bool version::operator<=(const version& other) const
    {
        return get_raw() <= other.get_raw();
    }

    constexpr bool version::operator>=(const version& other) const
    {
        return get_raw() >= other.get_raw();
    }

} // namespace nba

#endif