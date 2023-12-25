/* See LICENSE file for copyright and license details. */

/* datatypes.h in nihwm.h */
#include "nihwm.h"
#include "rulemodes.h"

extern Display *dpy;
extern Window root; 
extern Atom cusatom[CusLast];
extern Monitor *mons, *selmon; 

const Signal signals[] = {
	/* signum               function */
	{ "focusstack",         focusstack },
	{ "mfact",              setmfact },
	{ "bar",                togglebar },
	{ "barpos",             settopbar },
	{ "nmaster",            incnmaster },
	{ "floating",           togglefloating },
	{ "focusmon",           focusmon },
	{ "tagmon",             tagmon },
	{ "zoom",               zoom },
	{ "view",               view },
	// { "viewall",            viewall },
	// { "viewex",             viewex },
	{ "toggleview",         view },
	// { "toggleviewex",       toggleviewex },
	{ "tag",                tag },
	// { "tagall",             tagall },
	// { "tagex",              tagex },
	{ "toggletag",          tag },
	// { "toggletagex",    toggletagex },
	{ "killclient",         killclientsel },
	{ "quit",               quit },
	{ "layout",             setlayout },
	// { "setlayoutex",    setlayoutex },

	{ "snap",               setsnap },	
	{ "gap",                setgappx },	
	{ "gappx",              setgappx },	
	{ "border",             setborderpx },	
	{ "borderpx",            setborderpx },	

	{ "allownextfloating",  toggleallownextfloating },	
	{ "compositor",         togglecompositor },
	{ "cursorwrap",         togglecursorwarp },
	{ "attachbelow",        toggleattachbelow },
	{ "ignoremasterfocus",  toggleignoremasterfocus },
	{ "overlay",            toggleoverlay },
	{ "switchonfocus",      toggleswitchonfocus },
	{ "btrresizing",        togglebtrresizing },
	{ "btr",                togglebtrresizing },
	{ "tagclick",           togglebtrresizing },
};


int keymode = KeymodeNormal; 

/* this is where all the rulemodes are defined */
int allownextfloating     = 0;    /* 1 means focusstack allows next window to be floating */
int ignoremasterfocus     = 0;    /* 1 means ignore master in focusstack function, useful for deck */
int isattachbelow         = 1;    /* 1 means attach at the end [nonmaster, decreasing] */
int iscompositoractive    = 1;    /* 1 means compositor (picom, picom-fork, nihcomp) is active */
int iscursorwarp          = 0;    /* 1 means cursor warp i.e. if focusstack, the mouse will warp/move to the current focused client */
int showoverlay           = 0;    /* 1 means show the overlay (Mod-Shift-W windows: at start, Rhythmbox and Mousepad) */
int switchonfocus         = 0;    /* 1 means change to the current window which requests a focus */
int btrresizing           = 1;    /* 1 means the resize (Mod+Mouse) is like in the normal dwm */
int istagclick            = 0;    /* 1 means tag click is possible  */

/* appearance */
unsigned int snap            = 32;       /* snap pixel */
/* unsigned */ int borderpx  = 4;        /* border pixel of windows */
/* unsigned */ int gappx     = 16;       /* gap pixel of the window */

int showbar                  = 1;        /* 0 means no bar */
int topbar                   = 1;        /* 0 means bottom bar */

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
updatekeymode()
{
	/* do something */
}

void
settopbar(const Arg *arg)
{
	SSWITCH(topbar);	
}

void
setsnap(const Arg *arg)
{
	snap = MAX(arg->i, 2);	
}

void 
setgappx(const Arg *arg)
{
	gappx = MAX(arg->i, 2); // TODO fix this so that we can set this to 0
	arrange(selmon);
}

// TODO implement this correctly
void
setborderpx(const Arg *arg)
{
	borderpx = MAX(arg->i, 2);
	arrange(selmon);
}

void
setkeymode(const Arg *arg)
{
	if (!arg || arg->i == -1) {
		keymode = 0;
		return;
	}

	keymode = arg->i;
	updatekeymode();
}

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
	cusatom[CusBottomRightResizing] = XInternAtom(dpy, "_NIHWM_BOTTOM_RIGHT_RESIZING", False); // TODO properly implement this
	cusatom[CusTagClick] = XInternAtom(dpy, "_NIHWM_TAG_CLICK", False); 

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
	XChangeProperty(dpy, root, cusatom[CusTagClick], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[istagclick], 1);

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

void
toggletagclick(const Arg *arg)
{
	SSWITCH(istagclick);
	
	XChangeProperty(dpy, root, cusatom[CusTagClick], XA_CARDINAL, 32,
		PropModeReplace, (unsigned char *) stf[istagclick], 1);
}

// copy from dwmc and modified
int
signalhandle()
{
	char fsignal[256], paramsignal[256];
	char indicator[8] = "signal:";
	char str_sig[256];
	char param[64];
	int i, len_str_sig, n, paramn;
	size_t len_fsignal, len_indicator = strlen(indicator);
	Arg arg; arg.v = 0;

	if (gettextprop(root, XA_WM_NAME, fsignal, sizeof(fsignal))) {
		len_fsignal = strlen(fsignal);

		if (len_indicator > len_fsignal ? 0 : !strncmp(indicator, fsignal, len_indicator)) {

			paramn = sscanf(fsignal+len_indicator, "%s%n%s%n", str_sig, &len_str_sig, param, &n);

			if (paramn == 1) arg = (Arg) {0};
			else if (paramn > 2) return 1;
			else if (!strncmp(param, "i", n - len_str_sig) || !strncmp(param, "int", len_str_sig))
				sscanf(fsignal + len_indicator + n, "%i", &(arg.i));
			else if (!strncmp(param, "ui", n - len_str_sig) || !strncmp(param, "unsigned", len_str_sig))
				sscanf(fsignal + len_indicator + n, "%u", &(arg.ui));
			else if (!strncmp(param, "f", n - len_str_sig) || !strncmp(param, "float", len_str_sig))
				sscanf(fsignal + len_indicator + n, "%f", &(arg.f));
			else if (!strncmp(param, "s", n - len_str_sig) || !strncmp(param, "string", len_str_sig)) {
				sscanf(fsignal + len_indicator + n, "%s", paramsignal);
				arg.v = paramsignal;
			}
			else return 0;

			
			for (i = 0; i < LENGTH(signals); i++)
				if (!strncmp(str_sig, signals[i].signal, len_str_sig) && signals[i].func)	
					signals[i].func(&arg);

			return 1;
		}
	}

	return 0;
}

