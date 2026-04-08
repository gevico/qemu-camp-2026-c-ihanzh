#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 20 位图实现 Bloom 过滤器
 * 需求：m=100 位图，k=3 个哈希函数；插入 "apple"、"banana"，查询示例
 */

typedef struct {
    unsigned char *bits;
    size_t m; /* 位图大小（比特） */
} Bloom;

static Bloom *bloom_create(size_t m) {
    // TODO: 在这里添加你的代码
    Bloom *bf = (Bloom *)malloc(sizeof(Bloom));
    if (bf == NULL) {
        return NULL;
    }
    bf->m = m;
    bf->bits = (unsigned char *)malloc((bf->m + 7) / 8);
    if (bf->bits == NULL) {
        free(bf);
        return NULL;
    }
    memset(bf->bits, 0, (bf->m + 7) / 8);
    return bf;
}

static void bloom_free(Bloom *bf) {
    // TODO: 在这里添加你的代码
    free(bf->bits);
    free(bf);
}

/* 位操作 */
static void set_bit(unsigned char *bm, size_t idx) {
    // TODO: 在这里添加你的代码
    size_t char_idx = (idx >> 3);
    size_t offset = idx - (char_idx << 3);
    unsigned char val = bm[char_idx];
    bm[char_idx] = val | (1 << offset);
}
static int test_bit(const unsigned char *bm, size_t idx) {
    // TODO: 在这里添加你的代码
    size_t char_idx = (idx >> 3);
    size_t offset = idx - (char_idx << 3);
    unsigned char val = bm[char_idx];
    return (val >> offset) & 1;
}

/* 三个简单哈希：sum(c*k) % m */
static size_t hash_k(const char *s, size_t m, int k) {
    // TODO: 在这里添加你的代码
    size_t val = 0;
    for (const char *p = s; *p; p++) {
        val += ((*p) * k) % m;
    }
    return val % m;
}

static void bloom_add(Bloom *bf, const char *s) {
    // TODO: 在这里添加你的代码
    size_t k1 = hash_k(s, bf->m, 1);
    set_bit(bf->bits, k1);
    size_t k2 = hash_k(s, bf->m, 2);
    set_bit(bf->bits, k2);
    size_t k3 = hash_k(s, bf->m, 3);
    set_bit(bf->bits, k3);
}

static int bloom_maybe_contains(Bloom *bf, const char *s) {
    // TODO: 在这里添加你的代码
    size_t k1 = hash_k(s, bf->m, 1);
    if (test_bit(bf->bits, k1) != 1) {
        return 0;
    }
    size_t k2 = hash_k(s, bf->m, 2);
    if (test_bit(bf->bits, k2) != 1) {
        return 0;
    }
    size_t k3 = hash_k(s, bf->m, 3);
    return test_bit(bf->bits, k3);
}

int main(void) {
    const size_t m = 100; /* 位图大小 */
    Bloom *bf = bloom_create(m);
    if (!bf) {
        fprintf(stderr, "bloom create failed\n");
        return 1;
    }

    /* 插入元素："apple"、"banana" */
    bloom_add(bf, "apple");
    bloom_add(bf, "banana");

    /* 查询元素："apple"（应存在）、"orange"（可能存在误判） */
    int apple = bloom_maybe_contains(bf, "apple");
    int grape = bloom_maybe_contains(bf, "grape"); /* 未插入，可能误判 */

    printf("apple exists: %d\n", apple); /* 必须为 1（无假阴性） */
    printf("grape exists: %d\n", grape); /* 允许 0 或 1（可能误判） */

    bloom_free(bf);
    return 0;
}
