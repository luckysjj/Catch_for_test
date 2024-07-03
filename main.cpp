#include <chrono>
#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#ifdef __linux__
#include <malloc.h> // For malloc_usable_size
#endif

/* https://x.com/lemire/status/1806429159255580981?t=8bKEufqy3piXd-4PYtIvhw&s=35 

请求大小：malloc 向操作系统请求一个至少 size 字节的内存块。
额外开销：实际分配的内存可能比 size 稍大一些，因为分配器需要一些额外的空间来管理内存块。这个额外的开销取决于具体的内存分配器实现和平台。
对齐：分配的内存块通常是对齐的，以满足系统内存对齐的要求。这可能会导致一些填充（padding）。
*/

TEST_CASE("Simple malloc", "[vector]") {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t size = 0; size < 100; size += 2)
    {
        void* ptr = malloc(size);

        if (ptr == NULL) {
            printf("内存分配失败\n");
        }

        printf("内存分配成功\n");

    #ifdef __linux__
        size_t actual_size = malloc_usable_size(ptr);
        printf("请求大小：%zu, 实际分配大小：%zu\n", size, actual_size);
    #endif

        free(ptr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Test elapsed time: " << elapsed.count() << " ms\n";
}
