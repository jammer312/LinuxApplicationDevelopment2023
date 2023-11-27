#include <stdio.h>
#include <stdint.h>
#include <setjmp.h>

static jmp_buf escape;

static void
test_abort(void)
{
    longjmp(escape, 1);
}

#define BUF_ABORT test_abort
#include "libbuf.h"

#suite All
#tcase Abort
#test abort_test
    if (!setjmp(escape))
        test_abort();

#tcase Basic
#test basic_test
    float *a = 0;
    ck_assert_int_eq(buf_capacity(a), 0);
    ck_assert_int_eq(buf_size(a), 0);
    buf_push(a, 1.3f);
    ck_assert_int_eq(buf_size(a), 1);
    ck_assert_float_eq(a[0], (float)1.3f);
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_nonnull(a);
    buf_free(a);
    ck_assert_ptr_null(a);

#tcase ClearEmpty
#test clear_empty_test
    float *a = 0;
    buf_clear(a);
    ck_assert_int_eq(buf_size(a), 0);
    ck_assert_ptr_null(a);

#tcase Push
#test push_test
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    ck_assert_int_eq(buf_size(ai), 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    ck_assert_int_eq(match, 10000);
    buf_free(ai);

#tcase Grow
#test grow_test
    long *ai = 0;
    buf_grow(ai, 1000);
    ck_assert_int_eq(buf_capacity(ai), 1000);
    ck_assert_int_eq(buf_size(ai), 0);
    buf_trunc(ai, 100);
    ck_assert_int_eq(buf_capacity(ai), 100);
    buf_free(ai);

#tcase Pop
#test pop_test
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    ck_assert_int_eq(buf_size(a), 4);
    ck_assert_float_eq(buf_pop(a), (float)1.4f);
    buf_trunc(a, 3);
    ck_assert_int_eq(buf_size(a), 3);
    ck_assert_float_eq(buf_pop(a), (float)1.3f);
    ck_assert_float_eq(buf_pop(a), (float)1.2f);
    ck_assert_float_eq(buf_pop(a), (float)1.1f);
    ck_assert_int_eq(buf_size(a), 0);
    buf_free(a);

#tcase OOM
#test oom_test
        volatile int aborted = 0;
        int *volatile p = 0;
        if (!setjmp(escape)) {
            size_t max = (PTRDIFF_MAX - sizeof(struct buf)) / sizeof(*p) + 1;
            buf_grow(p, max);
            buf_grow(p, max);
        } else {
            aborted = 1;
        }
        buf_free(p);
        ck_assert_int_eq(aborted, 1);

#tcase overflowInit
#test overflow_init_test
        volatile int aborted = 0;
        int *volatile p = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        ck_assert_int_eq(aborted, 1);

#tcase overflowGrow
#test overflow_grow_test
        volatile int aborted = 0;
        int *volatile p = 0;
        if (!setjmp(escape)) {
            buf_trunc(p, 1); /* force realloc() use next */
            buf_trunc(p, PTRDIFF_MAX);
        } else {
            aborted = 1;
        }
        buf_free(p);
        ck_assert_int_eq(aborted, 1);
