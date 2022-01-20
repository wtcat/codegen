#ifndef BASE_BASEDEFS_H_
#define BASE_BASEDEFS_H_

#define _CONTACT(a, b) a##b

#ifndef __externC
#define __externC extern "C"
#endif

#define NOTICE_WARN "Warnning***: "
#define NOTICE_ERR  "Error***: "

#if defined(_MSC_VER) || defined(_WIN32) || defined(_WIN64)
#define __export __declspec(dllexport)
#else
#define __export
#endif

#ifdef __cplusplus
#define STATIC_ASSERT(cond, msg) static_assert(cond, #msg)
#else
#define STATIC_ASSERT(cond, msg) _Static_assert(cond, #msg)
#endif //__cplusplus

#define GENMASK(h, l) \
	(((~0UL) - (1UL << (l)) + 1) & (~0UL >> (BITS_PER_LONG - 1 - (h))))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(array) (sizeof(array) / sizeof((array)[0]))
#endif 

#define CONTAINER_OF(ptr, type, field) \
	((type *)(((char *)(ptr)) - offsetof(type, field)))

#define ROUND_UP(x, align)                                   \
	(((unsigned long)(x) + ((unsigned long)(align) - 1)) & \
	 ~((unsigned long)(align) - 1))

#define ROUND_DOWN(x, align)                                 \
	((unsigned long)(x) & ~((unsigned long)(align) - 1))

#define WB_UP(x) ROUND_UP(x, sizeof(void *))
#define WB_DN(x) ROUND_DOWN(x, sizeof(void *))

#define ceiling_fraction(numerator, divider) \
	(((numerator) + ((divider) - 1)) / (divider))

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef CLAMP
#define CLAMP(val, low, high) (((val) <= (low)) ? (low) : MIN(val, high))
#endif


#define _XXXX1 _YYYY,
#define Z_IS_ENABLED3(ignore_this, val, ...) val
#define Z_IS_ENABLED2(one_or_two_args)       Z_IS_ENABLED3(one_or_two_args 1, 0)
#define Z_IS_ENABLED1(config_macro)          Z_IS_ENABLED2(_XXXX##config_macro)
#define IS_ENABLED(config_macro)             Z_IS_ENABLED1(config_macro)

#endif /* BASE_BASEDEFS_H_ */
