#ifndef BASE_CONTAINER_OBSERVER_H_
#define BASE_CONTAINER_OBSERVER_H_

#include <sys/types.h>
#ifdef __cplusplus
extern "C"{
#endif

struct observer_class;
typedef int (*observer_fn_t)(struct observer_class *, unsigned long, void*);
			
struct observer_class {
	observer_fn_t update;
	struct observer_class  *next;
	int priority;
};

#define NOTIFY_DONE       0x0000		/* Don't care */
#define NOTIFY_OK         0x0001		/* Suits me */
#define NOTIFY_STOP_MASK  0x8000	    /* Don't call further */
#define NOTIFY_BAD        (NOTIFY_STOP_MASK|0x0002) /* Bad/Veto action */
#define NOTIFY_STOP		  (NOTIFY_OK|NOTIFY_STOP_MASK)

int observer_register(struct observer_class **nl, struct observer_class* n);
int observer_cond_register(struct observer_class **nl, 
	struct observer_class* n);
int observer_unregister(struct observer_class **nl,
	struct observer_class *n);
int observer_notify(struct observer_class **nl,
	unsigned long val, void* v);
#ifdef __cplusplus
}
#endif
#endif // BASE_CONTAINER_OBSERVER_H_
