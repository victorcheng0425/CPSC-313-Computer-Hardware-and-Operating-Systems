#include "catch.hpp"
extern "C"
{
#include "cache.h"
}

#define MAX_SIZE 1024

typedef long array_t[MAX_SIZE * MAX_SIZE];
static cache_t *cache;
static cache_t *cache_solution;

typedef long (*cache_read_func_t)(cache_t *, long *);
typedef long (*sum_func_t)(int, int, cache_read_func_t, cache_t *);

/* Array used for testing. The aligned attribute is used to ensure
 * that array[0] is stored at the start of a cache block, for any
 * block size up to 1024.
 */
array_t __attribute__((aligned(1024))) array;

/*
 * Write data to the array, bypassing the "cache".
 */
void fillArray()
{

    for (int i = 0; i < MAX_SIZE; i++)
    {
        for (int j = 0; j < MAX_SIZE; j++)
        {
            array[i * MAX_SIZE + j] = (i + 1) * (j + 1);
        }
    }
}

long sumA(int rows, int cols, cache_read_func_t read, cache_t *test_cache)
{
    long sum = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            sum += read(test_cache, &array[i * cols + j]);
        }
    }
    return sum;
}

long sumB(int rows, int cols, cache_read_func_t read, cache_t *test_cache)
{
    long sum = 0;

    for (int j = 0; j < cols; j++)
    {
        for (int i = 0; i < rows; i++)
        {
            sum += read(test_cache, &array[i * cols + j]);
        }
    }
    return sum;
}

long sumC(int rows, int cols, cache_read_func_t read, cache_t *test_cache)
{
    long sum = 0;

    for (int j = 0; j < cols; j += 2)
    {
        for (int i = 0; i < rows; i += 2)
        {
            sum += read(test_cache, &array[i * cols + j]);
            sum += read(test_cache, &array[(i + 1) * cols + j]);
            sum += read(test_cache, &array[i * cols + j + 1]);
            sum += read(test_cache, &array[(i + 1) * cols + j + 1]);
        }
    }
    return sum;
}

void test(sum_func_t sum_func)
{
    fillArray();

    cache = cache_new(256, 64, 1, CACHE_REPLACEMENTPOLICY_LRU);
    cache_solution = cache_new_solution(256, 64, 1, CACHE_REPLACEMENTPOLICY_LRU);

    long sum = sum_func(64, 64, cache_read, cache);
    long sum_expected = sum_func(64, 64, cache_read_solution, cache_solution);
    REQUIRE(sum == sum_expected);

    int miss_count = cache_miss_count(cache);
    int miss_count_expected = cache_miss_count_solution(cache_solution);
    REQUIRE(miss_count == miss_count_expected);

    int access_count = cache_access_count(cache);
    int access_count_expected = cache_access_count_solution(cache_solution);
    REQUIRE(access_count == access_count_expected);

    cache_free(cache);
    cache_free_solution(cache_solution);
}

TEST_CASE("sumA", "[weight=1][part=test]")
{
    test(sumA);
}

TEST_CASE("sumB", "[weight=1][part=test]")
{
    test(sumB);
}

TEST_CASE("sumC", "[weight=1][part=test]")
{
    test(sumC);
}