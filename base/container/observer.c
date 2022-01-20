#include <errno.h>
#include <stddef.h>

#include "base/container/observer.h"

int observer_register(struct observer_class **nl,
	struct observer_class *n) {
	while ((*nl) != NULL) {
		if (n->priority > (*nl)->priority)
			break;
		nl = &((*nl)->next);
	}
	n->next = *nl;
	*nl = n;
	return 0;
}

int observer_cond_register(struct observer_class **nl,
	struct observer_class *n) {
	while ((*nl) != NULL) {
		if ((*nl) == n) 
			return 0;
		if (n->priority > (*nl)->priority)
			break;
		nl = &((*nl)->next);
	}
	n->next = *nl;
	*nl = n;
	return 0;
}

int observer_unregister(struct observer_class **nl,
	struct observer_class *n) {
	while ((*nl) != NULL) {
		if ((*nl) == n) {
			*nl = n->next;
			return 0;
		}
		nl = &((*nl)->next);
	}
	return -EEXIST;
}

int observer_notify(struct observer_class **nl,
	unsigned long val, void* v) {
	int ret = NOTIFY_DONE;
	struct observer_class *nb, *next_nb;
	nb = *nl;
	while (nb) {
		next_nb = nb->next;
		ret = nb->update(nb, val, v);
		if ((ret & NOTIFY_STOP_MASK) == NOTIFY_STOP_MASK)
			break;
		nb = next_nb;
	}
	return ret;
}