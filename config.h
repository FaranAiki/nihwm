/* See LICENSE file for copyright and license details. */

/* Should I separate config with another config? :3 */
/* TODO separate config file */

/* Copyright (c) Muhammad Faran Aiki 2023 */

#ifndef CONFIG_H
	#define CONFIG_H

#define LAYOUTS 

#define TRAIN_KEYBOARD_LAYOUT

/* appearance */
const unsigned int snap      = 32;       /* snap pixel */
/* unsigned */ int borderpx  = 4;        /* border pixel of windows */
/* unsigned */ int gappx     = 16;       /* gap pixel of the window */

int showbar                  = 1;        /* 0 means no bar */
int topbar                   = 1;        /* 0 means bottom bar */

const char *fonts[]          = { "monospace:size=10" };
const char dmenufont[]       = "monospace:size=10";

const char col_black[]       = "#000000";
const char col_gray1[]       = "#222222";
const char col_gray2[]       = "#444444";
const char col_gray3[]       = "#bbbbbb";
const char col_gray4[]       = "#eeeeee";
const char col_cyan[]        = "#005577";
const char col_purple[]      = "#4c115a";

/* define the color when clicking Ctrl-C */
const char * const used_color[]     = {col_black, col_gray2, col_gray4, col_cyan, col_purple};

/* metaconfig */
int col_sel = 4;

const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_black },
	[SchemeSel]  = { col_gray4, col_black, used_color[4] }, // default is 4
};

/* to add your own layout, use the layout.c */
const Layout layouts[] = {
	/* symbol              arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
 	{ "TTT",      bstack },
 	{ "===",      bstackhoriz },
 	{ "GGG",      grid },
 	{ "[D]",      deck },
};

/* tagging; why japs? cuz kanji is easier */
const char *tags[] = { "曲", "捜", "歌", "開", "操", "愛", "録", "描", "電" };

/* layout(s) */
float mfact               = 0.5;  /* factor of master area size [0.05..0.95] */
int nmaster               = 1;    /* number of clients in master area */
int resizehints           = 1;    /* 1 means respect size hints in tiled resizals */
int lockfullscreen        = 1;    /* 1 will force focus on the fullscreen window */

/* other(s) */
const Arg startup_tag = { .ui = 1 << 8 }; /* where do you want the startup to be */

/* include everything */
#include "layout.h"

/* Misc */
#define USEDTERMINAL "kitty"

/* TAGKEYS is the proof that `define` macros are useful, Terry Davis! (RIP THE LEGEND) */
/* key definitions (toggleview and tag is inverted)*/
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ KeyPress, MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ KeyPress, MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* my own key definition */
#define K_printscreen 0x0000ff61

/* helper for spawning shell commands (not recommended )*/
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
const char *shutdowncmd[] = { "nihwmctl", "shutdown" }; 
const char *rebootcmd[] = { "nihwmctl", "reboot" }; // TODO implement this 
const char *roficmd[] = { "rofi", "-show", "drun", "-theme", "nihwm-theme", NULL };

const char *termcmd[]  = { USEDTERMINAL, NULL };
const char *printscr[] = { "flameshot", "gui", NULL };

/* For no apparent reason, fn + button does not work */
const char *decvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%-", NULL };
const char *incvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%+", NULL };

const char *gromitmpxcmd[] = { "gromit-mpx", NULL };
const char *pavucontrolcmd[] = { "pavucontrol", NULL };
const char *mousepadcmd[] = { "mousepad", NULL };

/* Define the startup command (application/optional) */
const char *browsercmd[] = { "chromium", NULL };
const char *rhythmboxcmd[] = { "rhythmbox", NULL };
const char *thunarcmd[] = { "thunar", NULL };
const char *lmms130cmd[] = { "lmms1.3.0", NULL };

/* not in nihwm, my own config KEYBOARDS */
const char *xkbqwerty[] = { "setxkbmap", "us", NULL };
const char *xkbdvorak[] = { "setxkbmap", "us", "-variant", "dvorak", NULL };
const char *xkbcolemak[] = { "setxkbmap", "us", "-variant", "colemak", NULL };
const char *xkbarabic[] = { "setxkbmap", "ara", NULL };
const char *xkbjapanese[] = { "setxkbmap", "jp", NULL };

/* startup */
const char **startup[] = {
	/* command  */
	pavucontrolcmd,
	gromitmpxcmd,
	mousepadcmd,

	termcmd,
	browsercmd,
	rhythmboxcmd,
	thunarcmd,
	lmms130cmd
};

/* this is where the rules are defined */
const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance      title          tags mask     isfloating   monitor    is overlay */
	{  "lmms.real",     "lmms.real",  NULL,          1 << 0,       0,           -1, }, // ergonomic reason
	{  "Audacity",      "audacity",   NULL,          1 << 0,       0,           -1, },
	{  "OpenUtau",      "OpenUtau",   NULL,          1 << 0,       0,           -1, },

	{  "Chromium",      "chromium",   NULL,          1 << 1,       0,           -1, },
	{  "firefox",       "Navigator",  NULL,          1 << 1,       0,           -1, },
	{  "Opera",         "Opera",      NULL,          1 << 1,       0,           -1, },

	{  "Rhythmbox",     "rhythmbox",  NULL,          1 << 2,       1,           -1,        1},

	{  "Thunar",        "thunar",     NULL,          1 << 3,       0,           -1, },

	{  "Zathura",       "org.pwmt.zathura",   NULL,  1 << 4,       0,           -1, },
	{  "Gromit-mpx",    "gromit-mpx",  NULL,         1 << 4,       0,           -1, },
	{  "Pavucontrol",   "pavucontrol",  NULL,        1 << 4,       0,           -1, },

	{  "Whatsapp-for-linux", "whatsapp-for-linux", NULL, 1 << 5,   0,           -1, },
	{  "discord",       "discord",      NULL,        1 << 5,       0,           -1, },
	{  "TelegramDesktop", "telegram-desktop", NULL,  1 << 5,       0,           -1, },

	{  "obs",           "obs",        NULL,          1 << 6,       0,           -1, },
	{  "Olive",         "olive-editor",  NULL,       1 << 6,       0,           -1, },

	{  "krita",         "krita",      NULL,          1 << 7,       0,           -1, },
	{  "Inkscape",  "org.inkscape.Inkscape", NULL,   1 << 7,       0,           -1, },

	{  "kitty",         "kitty",   NULL,             1 << 8,       0,           -1, },
	{  "Alacritty",     "Alacritty",   NULL,         1 << 8,       0,           -1, },
	{  "XTerm",         "xterm",   NULL,             1 << 8,       0,           -1, },

	{  "Mousepad",      "mousepad",   NULL,          0,            1,           -1,        1},
};

/* Rule workflow */
// 1 -> Audio Editing    		(LMMS, Utau, Audacity, ...)
// 2 -> Browsing Internet 		(Chromium, Opera, Firefox, ...)
// 3 -> Playing Music     		(Rhythmbox, Clementine, ...)
// 4 -> File Manager      		(Thunar, ...)
// 5 -> System Settings 		(Pavucontrol, Gromit-MPX, Bluez, ...)
// 6 -> Communication or Game	(Whatsapp, Aground, Forager)
// 7 -> Video Editing			(Olive, Kdenlive, OBS, ...)
// 8 -> Drawing Image			(Krita, Inkscape, ...)
// 9 -> Terminal				(Kitty, Alacritty)

/* this is where the keys are defined */
/* TODO implement a system where it is possible to use arrow keys, undescore, .etc */
Key keys[] = {
	/* event type    modifier            key        function        argument            disable */
	{ KeyPress,      MODKEY,             XK_F10,    spawn,          {.v = decvolcmd} },
	{ KeyPress,      MODKEY,             XK_F11,    spawn,          {.v = incvolcmd} },
	{ KeyPress,      0,                  K_printscreen, spawn,      {.v = printscr} },	
	{ KeyPress,      MODKEY,             XK_p,      spawn,          {.v = dmenucmd } },
	{ KeyPress,      MODKEY,             XK_r,      spawn,          {.v = roficmd } }, // Makes it possible to run Windows-downloaded or .desktop file(s): Saya no Uta, FL Studio, xppentablet, ....
	{ KeyPress,      MODKEY|ShiftMask,   XK_Return, spawn,          {.v = termcmd } },

	{ KeyPress,      MODKEY,             XK_b,      togglebar,      {-1} },
	{ KeyPress,      MODKEY|ShiftMask,   XK_b,      toggletopbar,   {-1} },
	
	{ KeyPress,      MODKEY,             XK_j,      focusstack,     {.i = +1 } },
	{ KeyPress,      MODKEY,             XK_k,      focusstack,     {.i = -1 } },
	{ KeyPress,      MODKEY,             XK_i,      incnmaster,     {.i = +1 } },
	{ KeyPress,      MODKEY,             XK_d,      incnmaster,     {.i = -1 } },
	{ KeyPress,      MODKEY,             XK_h,      setmfact,       {.f = -0.015} },
	{ KeyPress,      MODKEY,             XK_l,      setmfact,       {.f = +0.015} },
	{ KeyPress,      MODKEY,             XK_bracketleft,  incngappx, {.i = -2 } },
	{ KeyPress,      MODKEY,             XK_bracketright, incngappx, {.i = +2 } },
	
	{ KeyPress,      MODKEY,             XK_Return, zoom,           {0} },
	{ KeyPress,      MODKEY,             XK_Tab,    view,           {0} },
	{ KeyPress,      MODKEY, 			 XK_q,      killclientsel,  {.i = 0} },
	{ KeyPress,      MODKEY|ShiftMask,   XK_q,      killclientsel,  {.i = 1} },

	{ KeyPress,      MODKEY,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ KeyPress,      MODKEY,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ KeyPress,      MODKEY,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ KeyPress,      MODKEY,             XK_s,      setlayout,      {.v = &layouts[3]} },
	{ KeyPress,      MODKEY,             XK_slash,  setlayout,      {.v = &layouts[4]} },
	{ KeyPress,      MODKEY,             XK_u,      setlayout,      {.v = &layouts[5]} },
	{ KeyPress,      MODKEY,             XK_o,      setlayout,      {.v = &layouts[6]} }, // TODO modify properly
	{ KeyPress,      MODKEY,             XK_g,      setlayout,      {.v = &layouts[7]} },
	{ KeyPress,      MODKEY|ShiftMask,   XK_d,      setlayout,      {.v = &layouts[8]} }, 

	{ KeyPress,      MODKEY,             XK_space,  setlayout,         {0} },
	{ KeyPress,      MODKEY|ShiftMask,   XK_space,  togglefloating,    {0} },
	{ KeyPress,      MODKEY|ControlMask, XK_space,  togglealwaysontop, {0} },
	{ KeyPress,      MODKEY,             XK_0,      view,           {.ui = ~0 } },
	{ KeyPress,      MODKEY|ShiftMask,   XK_0,      tag,            {.ui = ~0 } },
	{ KeyPress,      MODKEY,             XK_comma,  focusmon,       {.i = -1 } },
	{ KeyPress,      MODKEY,             XK_period, focusmon,       {.i = +1 } },
	{ KeyPress,      MODKEY|ShiftMask,   XK_comma,  tagmon,         {.i = -1 } },
	{ KeyPress,      MODKEY|ShiftMask,   XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(         XK_1,               0)
	TAGKEYS(         XK_2,               1)
	TAGKEYS(         XK_3,               2)
	TAGKEYS(         XK_4,               3)
	TAGKEYS(         XK_5,               4)
	TAGKEYS(         XK_6,               5)
	TAGKEYS(         XK_7,               6)
	TAGKEYS(         XK_8,               7)
	TAGKEYS(         XK_9,               8)

	{ KeyPress,      MODKEY|ControlMask,           XK_q,      quit,           {1} },
	{ KeyPress,      MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ KeyPress,      MODKEY|ControlMask|ShiftMask, XK_s,      spawn,          {.v = shutdowncmd} }, // Graceful shutdown
	{ KeyPress,      MODKEY|ControlMask|ShiftMask, XK_r,      spawn,          {.v = rebootcmd} }, // Graceful shutdown

	{ KeyPress,      MODKEY,             XK_c,      togglecolorsel,          {0} }, // color selection
	{ KeyPress,      MODKEY|ControlMask, XK_f,      toggleallownextfloating, {-1} }, // disallow/allow mod+j or mod+k or similar to be focused
	{ KeyPress,      MODKEY|ShiftMask,   XK_c,      togglecompositor,        {-1} }, // use/don't use compositor
	{ KeyPress,      MODKEY|ShiftMask,   XK_f,      toggleswitchonfocus,     {-1} }, // ignore popup focus
	{ KeyPress,      MODKEY|ShiftMask,   XK_a,      toggleattachbelow,       {-1} },
	{ KeyPress,      MODKEY|ShiftMask,   XK_m,      toggleignoremasterfocus, {-1} },

#ifdef TRAIN_KEYBOARD_LAYOUT
	{ KeyPress,      MODKEY,             XK_F1,     spawn,          {.v = xkbqwerty} }, 	
	{ KeyPress,      MODKEY,             XK_F2,     spawn,          {.v = xkbdvorak} }, 	
	{ KeyPress,      MODKEY,             XK_F3,     spawn,          {.v = xkbcolemak} }, 	
	{ KeyPress,      MODKEY,             XK_F4,     spawn,          {.v = xkbarabic} }, 	
	{ KeyPress,      MODKEY,             XK_F5,     spawn,          {.v = xkbjapanese} },

	{ KeyPress,      MODKEY,             XK_w,      toggleoverlay,  {-1} }, // TODO should the overlay be pressed or held?
	{ KeyPress,      MODKEY|ShiftMask,   XK_w,      makeoverlay,    {0} }, 
#endif
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
Button buttons[] = {
	/* click                event mask      button          function        argument           disable */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} }, // TODO disable this
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkWinTitle,          0,              Button4,        focusstack,     {.i = +1 } }, // Scroll up
	{ ClkWinTitle,          0,              Button5,        focusstack,     {.i = -1 } }, // Scroll down
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY,         Button4,        focusstack,     {.i = +1 } }, // Scroll up
	{ ClkClientWin,         MODKEY,         Button5,        focusstack,     {.i = -1 } }, // Scroll down
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      focusstack,     {.i = +1 } },
	{ ClkClientWin,         MODKEY|ShiftMask, Button3,      focusstack,     {.i = -1 } },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	/*{ ClkTagBar,            MODKEY,         Button4,        toggletag,      {0} },
	{ ClkTagBar,            MODKEY,         Button5,        toggletag,      {0} }, Implement scrolling */ 
};

#endif /* CONFIG_H */
