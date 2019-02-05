#ifndef NBA_VERSION_HPP
#define NBA_VERSION_HPP

#include <cstdint>

namespace nba
{
    class version final
    {
    private:
        union
        {
            std::uint16_t m_components[4];
            std::uint64_t m_raw;

            static_assert(sizeof(m_components) == sizeof(m_raw),
                          "Sizes of m_compoents and m_raw must match.");
        };

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
    };

    constexpr version::version(std::uint16_t major,
                               std::uint16_t minor,
                               std::uint16_t patch,
                               std::uint16_t tweak) noexcept :
        m_components{major, minor, patch, tweak}
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
        return m_components[MAJOR_INDEX];
    }

    constexpr std::uint16_t version::get_minor() const noexcept
    {
        return m_components[MINOR_INDEX];
    }

    constexpr std::uint16_t version::get_patch() const noexcept
    {
        return m_components[PATCH_INDEX];
    }

    constexpr std::uint16_t version::get_tweak() const noexcept
    {
        return m_components[TWEAK_INDEX];
    }

    void version::set_major(std::uint16_t major) noexcept
    {
        m_components[MAJOR_INDEX] = major;
    }

    void version::set_minor(std::uint16_t minor) noexcept
    {
        m_components[MINOR_INDEX] = minor;
    }

    void version::set_patch(std::uint16_t patch) noexcept
    {
        m_components[PATCH_INDEX] = patch;
    }

    void version::set_tweak(std::uint16_t tweak) noexcept
    {
        m_components[TWEAK_INDEX] = tweak;
    }

    void version::set_raw(std::uint64_t raw) noexcept
    {
        m_raw = raw;
    }

} // namespace nba

#endif