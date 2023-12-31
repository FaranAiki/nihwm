//* See LICENSE file for copyright and license details.

/* macro definitions for include headers  */

#ifndef NIHWM_H
#define NIHWM_H

#define XK_TECHNICAL
#define XK_PUBLISHING

#include <errno.h>
#include <locale.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <X11/cursorfont.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>
#ifdef XINERAMA
#include <X11/extensions/Xinerama.h>
#endif /* XINERAMA */
#include <X11/Xft/Xft.h>

#include "drw.h"
#include "util.h"

/* macros */
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
#define CLEANMASK(mask)         (mask & ~(numlockmask|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
#define INTERSECT(x,y,w,h,m)    (MAX(0, MIN((x)+(w),(m)->wx+(m)->ww) - MAX((x),(m)->wx)) \
                               * MAX(0, MIN((y)+(h),(m)->wy+(m)->wh) - MAX((y),(m)->wy)))
/* optimize ISVISIBLE! */
#define ISVISIBLE(C)            ((((((C->tags & C->mon->tagset[C->mon->seltags]) && !(C->isoverlay && !showoverlay)) \
                                || (C->isoverlay && showoverlay)) \
                                && (C->isoverlay || (!C->isfloating || floatingvisible))) \
								&& (!C->forceinvisible)))
#define LENGTH(X)               (sizeof X / sizeof *X)
#define MOUSEMASK               (BUTTONMASK|PointerMotionMask)
#define WIDTH(X)                ((X)->w + 2 * (X)->bw + gappx)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw + gappx)
#define TAGMASK                 ((1 << LENGTH(tags)) - 1)
#define TEXTW(X)                (drw_fontset_getwidth(drw, (X)) + lrpad)

#include "datatypes.h"

/* function declarations */
Atom getatomprop(Client *c, Atom prop);
Client *nexttiled(Client *c);
Client *wintoclient(Window w);
Client *findclient(Client *c, int i);
Monitor *createmon(void);
Monitor *dirtomon(int dir);
Monitor *recttomon(int x, int y, int w, int h);
Monitor *wintomon(Window w);

int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact);
int getrootptr(int *x, int *y);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
int sendevent(Client *c, Atom proto);
int updategeom(void);
int xerror(Display *dpy, XErrorEvent *ee);
int xerrordummy(Display *dpy, XErrorEvent *ee);
int xerrorstart(Display *dpy, XErrorEvent *ee);
long getstate(Window w);

void applyrules(Client *c);
void applyfloatingtiling(Client *c);
void arrange(Monitor *m);
void arrangemon(Monitor *m);
void attach(Client *c);
void attachbelow(Client *c);
void attachstack(Client *c);
void buttonpress(XEvent *e);
void checkotherwm(void);
void cleanup(void);
void cleanupmon(Monitor *mon);
void clientmessage(XEvent *e);
void configure(Client *c);
void configurenotify(XEvent *e);
void configurerequest(XEvent *e);
void destroynotify(XEvent *e);
void detach(Client *c);
void detachstack(Client *c);
void drawbar(Monitor *m);
void drawbars(void);
void enternotify(XEvent *e);
void expose(XEvent *e);
void focus(Client *c);
void focusin(XEvent *e);
void focusmon(const Arg *arg);
void focusstack(const Arg *arg);
void grabbuttons(Client *c, int focused);
void grabkeys(void);
void incngappx(const Arg *arg);
void incnmaster(const Arg *arg);
void keypress(XEvent *e);
void killclient(const Arg *arg, const int forced);
void killclientsel(const Arg *arg);
void makeoverlay(const Arg *arg);
void manage(Window w, XWindowAttributes *wa);
void mappingnotify(XEvent *e);
void maprequest(XEvent *e);
void motionnotify(XEvent *e);
void movemouse(const Arg *arg);
void movestack(const Arg *arg);
void pop(Client *);
void propertynotify(XEvent *e);
void quit(const Arg *arg);
void resize(Client *c, int x, int y, int w, int h, int interact);
void resizeclient(Client *c, int x, int y, int w, int h);
void resizemouse(const Arg *arg);
void restack(Monitor *m);
void run(void);
void scan(void);
void sendmon(Client *c, Monitor *m);
void setclientstate(Client *c, long state);
void setfocus(Client *c);
void setfullscreen(Client *c, int fullscreen);
void setlayout(const Arg *arg);
void setmfact(const Arg *arg);
void setnumbdesktops(void);
void setup(void);
void seturgent(Client *c, int urg);
void showhide(Client *c);
void sigchld(int unused);
void sighup(int unused);
void sigterm(int unused);
void spawn(const Arg *arg);
void startapp(void);
void tag(const Arg *arg);
void tagmon(const Arg *arg);
void togglebar(const Arg *arg);
void togglecolorsel(const Arg *arg);
void togglefloating(const Arg *arg);
void toggletag(const Arg *arg);
void toggletopbar(const Arg *arg);
void toggleview(const Arg *arg);
void unfocus(Client *c, int setfocus);
void unmanage(Client *c, int destroyed);
void unmapnotify(XEvent *e);
void updatebarpos(Monitor *m);
void updatebars(void);
void updateclientdesktop(Client *c);
void updateclientlist(void);
void updatecurrentdesktop(void);
void updatenumlockmask(void);
void updatesizehints(Client *c);
void updatestatus(void);
void updatetitle(Client *c);
void updatewindowtype(Client *c);
void updatewmhints(Client *c);
void view(const Arg *arg);
void zoom(const Arg *arg);

#include "layouts.h"

#endif /* NIHWM_H */
