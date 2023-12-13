#ifndef RULEMODES_H
#define RULEMODES_H

#include "datatypes.h"

/* this is where all the rulemodes are defined */
extern int isattachbelow;
extern int allownextfloating;
extern int switchonfocus;
extern int iscompositoractive;
extern int ignoremasterfocus;
extern int showoverlay;

extern const long stf[2][1];

void initcusatom(void);
void toggleattachbelow(const Arg *arg);
void togglealwaysontop(const Arg *arg);
void toggleallownextfloating(const Arg *arg);
void togglecompositor(const Arg *arg);
void toggleswitchonfocus(const Arg *arg);
void toggleoverlay(const Arg *arg);
void toggleignoremasterfocus(const Arg *arg);
void setupcusatom(void);

/* constants */
extern const char *nihwmctl_kill_[];
extern const char *nihwmctl_start_[];
extern const char *nihwmctl_compo_kill_[];
extern const char *nihwmctl_compo_start_[];
extern char * const nihwm_reslist[];
extern const Arg nihwmctl_start;
extern const Arg nihwmctl_kill;
extern const Arg nihwmctl_compo_start;
extern const Arg nihwmctl_compo_kill;

#endif /* RULEMODES_H */
