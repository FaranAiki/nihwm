/* See LICENSE file for copyright and license details. */

/* datatypes.h in nihwm.h */
#include "nihwm.h"
#include "rulemodes.h"

extern Display *dpy;
extern Window root; 
extern Atom cusatom[CusLast];
extern Monitor *mons, *selmon; 

extern int colsel;

/* this is where all the rulemodes are defined */
int allownextfloating     = 0;    /* 1 means focusstack allows next window to be floating */
int ignoremasterfocus     = 0;    /* 1 means ignore master in focusstack function, useful for deck */
int isattachbelow         = 1;    /* 1 means attach at the end [nonmaster, decreasing] */
int iscompositoractive    = 1;    /* 1 means compositor (picom, picom-fork, nihcomp) is active */
int iscursorwarp          = 0;    /* 1 means cursor warp i.e. if focusstack, the mouse will warp/move to the current focused client */
int showoverlay           = 0;    /* 1 means show the overlay (Mod-Shift-W windows: at start, Rhythmbox and Mousepad) */
int switchonfocus         = 0;    /* 1 means change to the current window which requests a focus */
int btrresizing           = 1;    /* 1 means the resize (Mod+Mouse) is like in the normal dwm */

/* array */
const long stf[2][1] = {
	{0},
	{1},
}; 

/* constants */
const char *nihwmctl_kill_[]  = {"killall", "nihwmctl", NULL};
const char *nihwmctl_start_[] = {"nihwmctl", "statusbar", NULL};
const char *nihwmctl_compo_kill_[] = {"killall", "picom", NULL};
const char *nihwmctl_compo_start_[] = {"picom", "-b", NULL};

char * const nihwm_reslist[]  = {"nihwm", "-no-startapp", NULL};

// TODO optimize this

/* arg */
const Arg nihwmctl_start = { .v = nihwmctl_start_ };
const Arg nihwmctl_kill = { .v = nihwmctl_kill_ };
const Arg nihwmctl_compo_start = { .v = nihwmctl_compo_start_ };
const Arg nihwmctl_compo_kill = { .v = nihwmctl_compo_kill_ };

void
initcusatom()
{
	cusatom[CusNetFocusChange] = XInternAtom(dpy, "_NIHWM_FOCUS_CHANGE", False);
	cusatom[CusUsingCompositor] = XInternAtom(dpy, "_NIHWM_USING_COMPOSITOR", False);
	cusatom[CusAttachBelow] = XInternAtom(dpy, "_NIHWM_ATTACH_BELOW", False);
	cusatom[CusAllowNextFloating] = XInternAtom(dpy, "_NIHWM_ALLOW_NEXT_FLOATING", False);
	cusatom[CusShowOverlay] = XInternAtom(dpy, "_NIHWM_SHOW_OVERLAY", False);
	cusatom[CusCursorWarp] = XInternAtom(dpy, "_NIHWM_CURSOR_WARP", False);
	cusatom[CusIgnoreMasterFocus] = XInternAtom(dpy, "_NIHWM_IGNORE_MASTER_FOCUS", False); // TODO implement this
	cusatom[CusBottomRightResizing] = XInternAtom(dpy, "_NIHWM_BOTTOM_RIGHT_RESIZING", False); // TODO implement this

	cusatom[CusNumOfMaster] = XInternAtom(dpy, "_NIHWM_NUMBER_OF_MASTER", False);
}

void
setupcusatom()
{
	long numofmaster[] = { selmon->nmaster }; 

	XChangeProperty(dpy, root, cusatom[CusNetFocusChange], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[switchonfocus], 1 );
	XChangeProperty(dpy, root, cusatom[CusUsingCompositor], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[iscompositoractive], 1 );
	XChangeProperty(dpy, root, cusatom[CusAttachBelow], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[isattachbelow], 1 );
	XChangeProperty(dpy, root, cusatom[CusAllowNextFloating], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[allownextfloating], 1 );	
	XChangeProperty(dpy, root, cusatom[CusShowOverlay], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[showoverlay], 1 );	
	XChangeProperty(dpy, root, cusatom[CusIgnoreMasterFocus], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[ignoremasterfocus], 1);
	XChangeProperty(dpy, root, cusatom[CusBottomRightResizing], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[btrresizing], 1);

	XChangeProperty(dpy, root, cusatom[CusNumOfMaster], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) numofmaster, 1);
}

void
toggleallownextfloating(const Arg *arg)
{
	SSWITCH(allownextfloating);

	XChangeProperty(dpy, root, cusatom[CusAllowNextFloating], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[allownextfloating], 1 );	
}

void
toggleattachbelow(const Arg *arg)
{
	SSWITCH(isattachbelow);

	XChangeProperty(dpy, root, cusatom[CusAttachBelow], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[isattachbelow], 1 );	
}

void
toggleswitchonfocus(const Arg *arg)
{
	SSWITCH(switchonfocus);

	XChangeProperty(dpy, root, cusatom[CusNetFocusChange], XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) stf[switchonfocus], 1);
}

void
togglecompositor(const Arg *arg)
{
	SSWITCH(iscompositoractive);

	XChangeProperty(dpy, root, cusatom[CusUsingCompositor], XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) stf[iscompositoractive], 1);

	if (iscompositoractive) {
		spawn(&nihwmctl_compo_start);
	} else {
		spawn(&nihwmctl_compo_kill);
	}
}

void
toggleoverlay(const Arg *arg)
{
	SSWITCH(showoverlay);	
	
	XChangeProperty(dpy, root, cusatom[CusShowOverlay], XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) stf[showoverlay], 1);

	if (showoverlay == 0 && selmon->sel && selmon->sel->isoverlay) {
		unfocus(selmon->sel, 1);
		focus(NULL);
	}

	arrange(selmon);
}


void
toggleignoremasterfocus(const Arg *arg)
{
	SSWITCH(ignoremasterfocus);

	XChangeProperty(dpy, root, cusatom[CusIgnoreMasterFocus], XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) stf[ignoremasterfocus], 1);	
}

void
togglecursorwarp(const Arg *arg)
{
	SSWITCH(iscursorwarp);

	XChangeProperty(dpy, root, cusatom[CusCursorWarp], XA_CARDINAL, 32,
			PropModeReplace, (unsigned char *) stf[iscursorwarp], 1);	
}

void
togglebtrresizing(const Arg *arg)
{
	SSWITCH(btrresizing);
	
	XChangeProperty(dpy, root, cusatom[CusBottomRightResizing], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[btrresizing], 1);
}

