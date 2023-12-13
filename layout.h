/* See LICENSE file for copyright and license details. */

#ifndef LAYOUT_H
#define LAYOUT_H

#include "datatypes.h"

void tile(Monitor *m);
void monocle(Monitor *m);
void bstack(Monitor *m);
void bstackhoriz(Monitor *m);
void deck(Monitor *m);
void fibonacci(Monitor *m, int s);
void spiral(Monitor *m);
void dwindle(Monitor *m);
void grid(Monitor *m);

extern const Layout layouts[];

#endif /* LAYOUT_H */
