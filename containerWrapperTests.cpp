#include <array>
#include <numeric> // std::iota()
#include <gtest/gtest.h>

#if __has_include("../containerWrapper.h")
    #include "../containerWrapper.h"
#elif __has_include("containerWrapper.h")
    #include "containerWrapper.h"
#else
    #error "File 'containerWrapper.h' not found!"
#endif

using namespace std;
using namespace ::testing;


namespace
{
    constexpr size_t N = 100'000;
} // namespace

struct ContainerWrapperTester : ::testing::Test
{
    using value_type = IContainerWrapper::value_type;

    static auto prepareSourceContainer()
    {
        std::array<value_type, N> sourceElements;

        std::iota(sourceElements.begin(), sourceElements.end(), 0);
        return sourceElements;
    }
};

TEST_F(ContainerWrapperTester, constructionLotsOfElementsWithDefaultConstructor)
{
#if IMPLEMENTED_DEFAULT_CONSTRUCTOR == 1
    unique_ptr<ContainerWrapper[]> wrappers(new ContainerWrapper[N]);
    static_cast<void>(wrappers); // to disable warning

    #ifndef DOMJUDGE
    clog << "[INFO] Created " << N << " obects, with size: "
         << (N*sizeof(value_type)/1024) << " kb" << endl;
    #endif // #ifndef DOMJUDGE
#else
    ADD_FAILURE() << "Default constructor not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, constructionFromArray)
{
#if IMPLEMENTED_CONSTRUCTOR_COPYING_FROM_ARRAY == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());
    static_cast<void>(wrapper); // to disable warning
#else
    ADD_FAILURE() << "Constructor, which is copying from array not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, pushBackManyElements)
{
#if IMPLEMENTED_PUSH_BACK == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper;
    for (const auto& element : sourceElements)
    {
        wrapper.push_back(element);
    }
#else
    ADD_FAILURE() << "Method push_back() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, pushFrontManyElements)
{
#if IMPLEMENTED_PUSH_FRONT == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper;
    for (const auto& element : sourceElements)
    {
        wrapper.push_front(element);
    }
#else
    ADD_FAILURE() << "Method push_back() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, insertingInRandomPositionManyElements)
{
#if IMPLEMENTED_INSERT == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper;
    for (const auto& element : sourceElements)
    {
        const size_t position = wrapper.size() > 0 ? rand() % wrapper.size() : 0;
        wrapper.insert(element, position);
    }
#else
    ADD_FAILURE() << "Method insert() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, randomAccess)
{
#if IMPLEMENTED_AT == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    for (size_t i=0; i < N; ++i)
    {
        ASSERT_EQ(sourceElements[i], wrapper.at(i)) << "i = " << i;
    }
#else
    ADD_FAILURE() << "Method at() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, sorting)
{
#if IMPLEMENTED_SORT == 1
    auto sourceElements = prepareSourceContainer();
    decltype(sourceElements) reversedElements;
    std::reverse_copy(begin(sourceElements), end(sourceElements), begin(reversedElements));

    ContainerWrapper wrapper(reversedElements.data(), sourceElements.size());
    wrapper.sort();

    for (size_t i=0; i < N; ++i)
    {
        ASSERT_EQ(sourceElements[i], wrapper.at(i)) << "i = " << i;
    }
#else
    ADD_FAILURE() << "Method sort() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, randomErase)
{
#if IMPLEMENTED_ERASE == 1
    const auto sourceElements = prepareSourceContainer();

    ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    for (size_t i=1; i < N; ++i)
    {
        const size_t erasePosition = wrapper.size() > 0 ? rand() % wrapper.size() : 0;
        wrapper.erase(erasePosition);
        ASSERT_EQ(N - i, wrapper.size()) << "i = " << i;
    }
#else
    ADD_FAILURE() << "Method erase() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, count_expectedAllElementsCounted)
{
#if IMPLEMENTED_COUNT == 1
    const auto sourceElements = prepareSourceContainer();
    const auto expectedCount = std::accumulate(sourceElements.begin(), sourceElements.end(), value_type{});

    const ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    ASSERT_EQ(expectedCount, wrapper.count());
#else
    ADD_FAILURE() << "Method count() not implemented!";
#endif
}

TEST_F(ContainerWrapperTester, findElement)
{
#if IMPLEMENTED_FIND == 1
    const auto sourceElements = prepareSourceContainer();

    const ContainerWrapper wrapper(sourceElements.data(), sourceElements.size());

    const value_type notExistingElement = 2 * N;
    ASSERT_EQ(std::numeric_limits<size_t>::max(), wrapper.find(notExistingElement));

    for (size_t i=0; i < N / 10; ++i)
    {
        const size_t expectedPosition = rand() % sourceElements.size();
        const auto element2Find = sourceElements[expectedPosition];
        ASSERT_EQ(expectedPosition, wrapper.find(element2Find)) << "i = " << i << ", element2Find = " << element2Find;
    }
#else
    ADD_FAILURE() << "Method find() not implemented!";
#endif
}
