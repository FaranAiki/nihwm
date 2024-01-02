//* See LICENSE file for copyright and license details.

#ifndef DATATYPES_H
#define DATATYPES_H

#include <X11/Xlib.h>

#define NIH_LOG(X) printf X; fflush(stdout);

/* enums */
enum { CurNormal, CurResize, CurMove, CurLast }; /* cursor */
enum { SchemeNorm, SchemeSel }; /* color schemes */
enum { NetSupported, NetWMName, NetWMState, NetWMCheck,
       NetWMFullscreen, NetActiveWindow, NetWMWindowType, NetWMWindowTypeNotification, NetWMWindowTypeSplash,
	   NetWMWindowTypeDialog, NetClientList, NetNumberOfDesktops, NetWMPID,
	   NetCurrentDesktop, NetWMDesktop, NetCloseWindow, NetWMMoveResize, NetMoveResizeWindow, NetLast }; /* EWMH atoms */
/* enum { ..., CusLast, } */ 
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast }; /* default atoms */
enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} Arg;

typedef struct {
	unsigned int click;
	unsigned int mask;
	unsigned int button;
	void (*func)(const Arg *arg);
	const Arg arg;
	int *disable;
} Button;

typedef struct Monitor Monitor;
typedef struct Client Client;
struct Client {
	char name[256];
	float mina, maxa;
	int x, y, w, h;
	int oldx, oldy, oldw, oldh;
	int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
	int bw, oldbw;
	unsigned int tags;
	int isfixed, iscentered, isfloating, isoverlay, isalwaysontop, isurgent, neverfocus, oldstate, isfullscreen, nfocusonpopup, forceinvisible;
	Client *next;
	Client *snext;
	Monitor *mon;
	Window win;
};

typedef struct {
	int type;
	unsigned int mod;
	KeySym keysym;
	void (*func)(const Arg *);
	const Arg arg;
	int *disable;
} Key;

typedef struct {
	const char *symbol;
	void (*arrange)(Monitor *);
} Layout;

// TODO selmon as array: 1-10 where 10 is when combined
struct Monitor {
	char ltsymbol[16];
	float mfact;
	int nmaster;
	int num;
	int by;               /* bar geometry */
	int mx, my, mw, mh;   /* screen size */
	int wx, wy, ww, wh;   /* window area  */
	unsigned int seltags;
	unsigned int sellt;
	unsigned int tagset[2];
	int showbar;
	int topbar;
	Client *clients;
	Client *sel;
	Client *stack;
	Monitor *next;
	Window barwin;
	const Layout *lt[2];
};

typedef struct {
	const char *instance;
	const char *class;
	const char *title;
	unsigned int tags;
	int isfloating;
	int monitor;
	int isoverlay;
	int nfocusonpopup;
	int iscentered;
} Rule;

typedef struct {
	const char *signal;
	void (*func)(const Arg *);
} Signal;

#endif /* DATATYPES_H */
