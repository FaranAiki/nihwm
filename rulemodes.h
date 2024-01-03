/* See LICENSE file for copyright and license details. */

#ifndef RULEMODES_H
#define RULEMODES_H

#include "datatypes.h"

#define SSWITCH(V) if (arg->i == -1) V = !V; else V = arg->i & 1

enum { CusNetFocusChange, CusUsingCompositor, CusAttachBelow, CusAllowNextFloating,
	   CusShowOverlay, CusIgnoreMasterFocus, CusNumOfMaster, CusCursorWarp, CusInvisibleWindow,
	   CusBottomRightResizing, CusTagClick, CusKeymode, CusFocusPopup, CusFloatingVisible, CusWindowGap,
	   CusLast,}; /* custom atoms */

enum {
	KeymodeNormal, /* normal behavior */
	KeymodeControl, /* using every key without pressing the Mod button */

}; /* keymodes */ 

extern const Signal signals[];

extern int keymode;

/* this is where all the rulemodes are defined */
extern int allownextfloating;
extern int ignoremasterfocus;
extern int isattachbelow;
extern int iscompositoractive;
extern int iscursorwarp; 
extern int showoverlay;
extern int switchonfocus;
extern int btrresizing;
extern int istagclick;
extern int focuspopup;
extern int floatingvisible;

extern int col_sel;

extern unsigned int snap;
extern /* unsigned */ int borderpx;
extern /* unsigned */ int gappx;

extern int showbar;
extern int topbar;

extern const long stf[2][1];

/* functions for the rulemodes.h */
void initcusatom(void);
void toggleattachbelow(const Arg *arg);
void togglealwaysontop(const Arg *arg);
void toggleallownextfloating(const Arg *arg);
void togglebtrresizing(const Arg *arg);
void togglecompositor(const Arg *arg);
void togglecursorwarp(const Arg *arg);
void toggleswitchonfocus(const Arg *arg);
void toggleoverlay(const Arg *arg);
void toggleignoremasterfocus(const Arg *arg);
void toggletagclick(const Arg *arg);
void togglefocuspopup(const Arg *arg);
void togglefloatingvisible(const Arg *arg);
void toggleforceinvisiblewindow(const Arg *arg);
void toggleallforceinvisible(const Arg *arg);
void killallfloatingwindow(const Arg *arg);
void setupcusatom(void);
int signalhandle(void);

/* functions for signals, nihwmctl */
void settopbar(const Arg *arg);
void setsnap(const Arg *arg);
void setgappx(const Arg *arg);
void setborderpx(const Arg *arg);
void setkeymode(const Arg *arg);
void updatekeymode(void);

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
