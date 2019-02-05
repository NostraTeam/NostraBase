#include "nostra/base/version.hpp"

#include <bitset>
#include <cstdint>
#include <iostream>

// TODO: use proper unit test framework
#define NBA_ASSERT(...)                                                                            \
    if(!(__VA_ARGS__))                                                                             \
    {                                                                                              \
        std::cout << "Assertion failed: '" << (#__VA_ARGS__) << "' in line " << __LINE__ << ".\n"; \
        exit(__LINE__);                                                                            \
    }

#define NBA_TEST_MAJOR_SHIFT_VALUE (16 * 0)
#define NBA_TEST_MINOR_SHIFT_VALUE (16 * 1)
#define NBA_TEST_PATCH_SHIFT_VALUE (16 * 2)
#define NBA_TEST_TWEAK_SHIFT_VALUE (16 * 3)

#define NBA_TEST_SHIFT_MAJOR(major) (std::uint64_t{major} << NBA_TEST_MAJOR_SHIFT_VALUE)
#define NBA_TEST_SHIFT_MINOR(minor) (std::uint64_t{minor} << NBA_TEST_MINOR_SHIFT_VALUE)
#define NBA_TEST_SHIFT_PATCH(patch) (std::uint64_t{patch} << NBA_TEST_PATCH_SHIFT_VALUE)
#define NBA_TEST_SHIFT_TWEAK(tweak) (std::uint64_t{tweak} << NBA_TEST_TWEAK_SHIFT_VALUE)

void test_normal()
{
    // Default constructor
    {
        nba::version version;

        NBA_ASSERT(version.get_raw() == 0);
        NBA_ASSERT(version.get_major() == 0);
        NBA_ASSERT(version.get_minor() == 0);
        NBA_ASSERT(version.get_patch() == 0);
        NBA_ASSERT(version.get_tweak() == 0);
    }

    // Constructor for all components
    {
        nba::version version{1, 2, 3, 4};

        std::uint64_t manual_raw{0};
        manual_raw += std::uint64_t{1} << NBA_TEST_MAJOR_SHIFT_VALUE;
        manual_raw += std::uint64_t{2} << NBA_TEST_MINOR_SHIFT_VALUE;
        manual_raw += std::uint64_t{3} << NBA_TEST_PATCH_SHIFT_VALUE;
        manual_raw += std::uint64_t{4} << NBA_TEST_TWEAK_SHIFT_VALUE;

        NBA_ASSERT(version.get_raw() == manual_raw);
        NBA_ASSERT(version.get_major() == 1);
        NBA_ASSERT(version.get_minor() == 2);
        NBA_ASSERT(version.get_patch() == 3);
        NBA_ASSERT(version.get_tweak() == 4);

        NBA_ASSERT(nba::version{version.get_raw()}.get_raw() == nba::version{1, 2, 3, 4}.get_raw());
    }

    // Raw constructor
    {
        nba::version version{static_cast<std::uint64_t>(1234)};

        NBA_ASSERT(version.get_raw() == 1234);
    }

    // get_masked()
    {
        nba::version version{1, 2, 3, 4};

        std::uint64_t major = version.get_masked(nba::version::mask::MAJOR);
        std::uint64_t minor = version.get_masked(nba::version::mask::MINOR);
        std::uint64_t patch = version.get_masked(nba::version::mask::PATCH);
        std::uint64_t tweak = version.get_masked(nba::version::mask::TWEAK);
        std::uint64_t all   = version.get_masked(nba::version::mask::ALL);

        NBA_ASSERT(major == NBA_TEST_SHIFT_MAJOR(1));
        NBA_ASSERT(minor == NBA_TEST_SHIFT_MINOR(2));
        NBA_ASSERT(patch == NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(tweak == NBA_TEST_SHIFT_TWEAK(4));
        NBA_ASSERT(all == version.get_raw());

        std::uint64_t major_minor = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::MINOR);
        std::uint64_t major_patch = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::PATCH);
        std::uint64_t major_tweak = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::TWEAK);

        NBA_ASSERT(major_minor == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2));
        NBA_ASSERT(major_patch == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(major_tweak == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t minor_patch = version.get_masked(nba::version::mask::MINOR | nba::version::mask::PATCH);
        std::uint64_t minor_tweak = version.get_masked(nba::version::mask::MINOR | nba::version::mask::TWEAK);

        NBA_ASSERT(minor_patch == NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(minor_tweak == NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t patch_tweak = version.get_masked(nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(patch_tweak == NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t major_minor_patch = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::MINOR | nba::version::mask::PATCH);
        std::uint64_t major_patch_tweak = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::PATCH | nba::version::mask::TWEAK);
        std::uint64_t major_minor_tweak = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::MINOR | nba::version::mask::TWEAK);

        NBA_ASSERT(major_minor_patch ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(major_patch_tweak ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));
        NBA_ASSERT(major_minor_tweak ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t minor_patch_tweak = version.get_masked(
            nba::version::mask::MINOR | nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(minor_patch_tweak ==
                   NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t all2 = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::MINOR |
                                                nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(all2 == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3) +
                               NBA_TEST_SHIFT_TWEAK(4));

        // should indirectly be covered by the previous tests, but better safe than sorry...
        NBA_ASSERT(all2 == version.get_masked(nba::version::mask::ALL));
    }

    // set_*()
    {
        nba::version version{1, 2, 3, 4};
        nba::version version2{21, 22, 23, 24};

        version.set_major(11);
        version.set_minor(12);
        version.set_patch(13);
        version.set_tweak(14);

        NBA_ASSERT(version.get_major() == 11);
        NBA_ASSERT(version.get_minor() == 12);
        NBA_ASSERT(version.get_patch() == 13);
        NBA_ASSERT(version.get_tweak() == 14);

        version.set_raw(version2.get_raw());

        NBA_ASSERT(version.get_major() == 21);
        NBA_ASSERT(version.get_minor() == 22);
        NBA_ASSERT(version.get_patch() == 23);
        NBA_ASSERT(version.get_tweak() == 24);
    }
}

void test_constexpr()
{
    // Default constructor
    {
        constexpr nba::version version;

        static_assert(version.get_raw() == 0);
        static_assert(version.get_major() == 0);
        static_assert(version.get_minor() == 0);
        static_assert(version.get_patch() == 0);
        static_assert(version.get_tweak() == 0);
    }

    // Constructor for all components
    {
        nba::version version{1, 2, 3, 4};

        std::uint64_t manual_raw{0};
        manual_raw += std::uint64_t{1} << NBA_TEST_MAJOR_SHIFT_VALUE;
        manual_raw += std::uint64_t{2} << NBA_TEST_MINOR_SHIFT_VALUE;
        manual_raw += std::uint64_t{3} << NBA_TEST_PATCH_SHIFT_VALUE;
        manual_raw += std::uint64_t{4} << NBA_TEST_TWEAK_SHIFT_VALUE;

        NBA_ASSERT(version.get_raw() == manual_raw);
        NBA_ASSERT(version.get_major() == 1);
        NBA_ASSERT(version.get_minor() == 2);
        NBA_ASSERT(version.get_patch() == 3);
        NBA_ASSERT(version.get_tweak() == 4);

        NBA_ASSERT(nba::version{version.get_raw()}.get_raw() == nba::version{1, 2, 3, 4}.get_raw());
    }

    // Raw constructor
    {
        nba::version version{static_cast<std::uint64_t>(1234)};

        NBA_ASSERT(version.get_raw() == 1234);
    }

    // get_masked()
    {
        nba::version version{1, 2, 3, 4};

        std::uint64_t major = version.get_masked(nba::version::mask::MAJOR);
        std::uint64_t minor = version.get_masked(nba::version::mask::MINOR);
        std::uint64_t patch = version.get_masked(nba::version::mask::PATCH);
        std::uint64_t tweak = version.get_masked(nba::version::mask::TWEAK);
        std::uint64_t all   = version.get_masked(nba::version::mask::ALL);

        NBA_ASSERT(major == NBA_TEST_SHIFT_MAJOR(1));
        NBA_ASSERT(minor == NBA_TEST_SHIFT_MINOR(2));
        NBA_ASSERT(patch == NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(tweak == NBA_TEST_SHIFT_TWEAK(4));
        NBA_ASSERT(all == version.get_raw());

        std::uint64_t major_minor = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::MINOR);
        std::uint64_t major_patch = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::PATCH);
        std::uint64_t major_tweak = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::TWEAK);

        NBA_ASSERT(major_minor == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2));
        NBA_ASSERT(major_patch == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(major_tweak == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t minor_patch = version.get_masked(nba::version::mask::MINOR | nba::version::mask::PATCH);
        std::uint64_t minor_tweak = version.get_masked(nba::version::mask::MINOR | nba::version::mask::TWEAK);

        NBA_ASSERT(minor_patch == NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(minor_tweak == NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t patch_tweak = version.get_masked(nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(patch_tweak == NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t major_minor_patch = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::MINOR | nba::version::mask::PATCH);
        std::uint64_t major_patch_tweak = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::PATCH | nba::version::mask::TWEAK);
        std::uint64_t major_minor_tweak = version.get_masked(
            nba::version::mask::MAJOR | nba::version::mask::MINOR | nba::version::mask::TWEAK);

        NBA_ASSERT(major_minor_patch ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3));
        NBA_ASSERT(major_patch_tweak ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));
        NBA_ASSERT(major_minor_tweak ==
                   NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t minor_patch_tweak = version.get_masked(
            nba::version::mask::MINOR | nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(minor_patch_tweak ==
                   NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3) + NBA_TEST_SHIFT_TWEAK(4));

        std::uint64_t all2 = version.get_masked(nba::version::mask::MAJOR | nba::version::mask::MINOR |
                                                nba::version::mask::PATCH | nba::version::mask::TWEAK);

        NBA_ASSERT(all2 == NBA_TEST_SHIFT_MAJOR(1) + NBA_TEST_SHIFT_MINOR(2) + NBA_TEST_SHIFT_PATCH(3) +
                               NBA_TEST_SHIFT_TWEAK(4));

        // should indirectly be covered by the previous tests, but better safe than sorry...
        NBA_ASSERT(all2 == version.get_masked(nba::version::mask::ALL));
    }
}

int main()
{
    test_normal();
    test_constexpr();
}
