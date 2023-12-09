/* See LICENSE file for copyright and license details. */

/* Should I separate config with another config? :3 */

/* Copyright (c) Muhammad Faran Aiki 2023 */

#define LAYOUTS 

#define TRAIN_KEYBOARD_LAYOUT

/* appearance */
static const unsigned int snap      = 32;       /* snap pixel */
static unsigned int borderpx        = 4;        /* border pixel of windows */
static unsigned int gappx           = 16;       /* gap pixel of the window */

static int showbar                  = 1;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";

static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_purple[]      = "#4c115a";

static const char * const used_color[]     = {col_black, col_gray2, col_gray4, col_cyan, col_purple};

static int col_sel = 4;

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_black },
	[SchemeSel]  = { col_gray4, col_black, used_color[4] }, // default is 4
};

/* tagging; why japs? cuz kanji is easier */
static const char *tags[] = { "曲", "捜", "歌", "開", "操", "愛", "録", "描", "電" };

/* layout(s) */
static const float mfact         = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster         = 1;    /* number of clients in master area */
static const int resizehints     = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen  = 1; /* 1 will force focus on the fullscreen window */
static int isattachbelow         = 1; /* 1 means attach at the end [nonmaster, decreasing] */
static int allownextfloating     = 0; /* 1 means focusstack allows next window to be floating */

/* other(s) */
static const Arg startup_tag = { .ui = 1 << 8 };

// Include Layouts
#include "layout.c"

/* to add your own layout, use the layout.c */
static const Layout layouts[] = {
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

/* Misc */
#define USEDTERMINAL "kitty"

/* TAGKEYS is the proof that `define` macros are useful, Terry Davis! (RIP THE LEGEND) */
/* key definitions (toggleview and tag is inverted)*/
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* my own key definition */
#define K_printscreen 0x0000ff61

/* helper for spawning shell commands (not recommended )*/
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *shutdowncmd[] = { "nihwmctl", "shutdown" }; 
static const char *rebootcmd[] = { "nihwmctl", "reboot" }; // TODO implement this 
static const char *roficmd[] = { "rofi", "-show", "drun", "-theme", "nihwm-theme", NULL };

static const char *termcmd[]  = { USEDTERMINAL, NULL };
static const char *printscr[] = { "flameshot", "gui", NULL };

/* For no apparent reason, fn + button does not work */
static const char *decvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%-", NULL };
static const char *incvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%+", NULL };

static const char *gromitmpxcmd[] = { "gromit-mpx", NULL };
static const char *pavucontrolcmd[] = { "pavucontrol", NULL };

/* Define the startup command (application/optional) */
static const char *browsercmd[] = { "chromium", NULL };
static const char *rhythmboxcmd[] = { "rhythmbox", NULL };
static const char *thunarcmd[] = { "thunar", NULL };
static const char *lmms130cmd[] = { "lmms1.3.0", NULL };

/* not in nihwm, my own config KEYBOARDS */
static const char *xkbqwerty[] = { "setxkbmap", "us", NULL };
static const char *xkbdvorak[] = { "setxkbmap", "us", "-variant", "dvorak", NULL };
static const char *xkbcolemak[] = { "setxkbmap", "us", "-variant", "colemak", NULL };
static const char *xkbarabic[] = { "setxkbmap", "ara", NULL };
static const char *xkbjapanese[] = { "setxkbmap", "jp", NULL };

/* startup */
static const char **startup[] = {
	/* command  */
	pavucontrolcmd,
	gromitmpxcmd,

	termcmd,
	browsercmd,
	rhythmboxcmd,
	thunarcmd,
	lmms130cmd
};

/* this is where the rules are defined */
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance      title          tags mask     isfloating   monitor */
	{  "lmms.real",     "lmms.real" ,    NULL,       1 << 0,       0,           -1}, // ergonomic reason
	{  "Audacity",      "audacity",   NULL,          1 << 0,       0,           -1},
	{  "OpenUtau",      "OpenUtau",   NULL,          1 << 0,       0,           -1},

	{  "Chromium",      "chromium",   NULL,          1 << 1,       0,           -1},
	{  "firefox",       "Navigator",  NULL,          1 << 1,       0,           -1},
	{  "Opera",         "Opera",      NULL,          1 << 1,       0,           -1},

	{  "Rhythmbox",     "rhythmbox",  NULL,          1 << 2,       0,           -1},

	{  "Thunar",        "thunar",     NULL,          1 << 3,       0,           -1},

	{  "Zathura",       "org.pwmt.zathura",   NULL,  1 << 4,       0,           -1},
	{  "Gromit-mpx",    "gromit-mpx",  NULL,         1 << 4,       0,           -1},
	{  "Pavucontrol",   "pavucontrol",  NULL,        1 << 4,       0,           -1},

	{  "Whatsapp-for-linux", "whatsapp-for-linux", NULL, 1 << 5,   0,           -1},
	{  "discord",       "discord",      NULL,        1 << 5,       0,           -1},
	{  "TelegramDesktop", "telegram-desktop", NULL,  1 << 5,       0,           -1},

	{  "obs",           "obs",        NULL,          1 << 6,       0,           -1},
	{  "Olive",         "olive-editor",  NULL,       1 << 6,       0,           -1},

	{  "krita",         "krita",      NULL,          1 << 7,       0,           -1},
	{  "Inkscape",  "org.inkscape.Inkscape", NULL,   1 << 7,       0,           -1},

	{  "kitty",         "kitty",   NULL,             1 << 8,       0,           -1 },
	{  "Alacritty",     "Alacritty",   NULL,         1 << 8,       0,           -1 },
	{  "XTerm",         "xterm",   NULL,             1 << 8,       0,           -1 },

	{  "Mousepad",      "mousepad",   NULL,          0,         1,           -1 },
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
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F10,    spawn,          {.v = decvolcmd} },
	{ MODKEY,                       XK_F11,    spawn,          {.v = incvolcmd} },
	{ 0,                            K_printscreen, spawn,      {.v = printscr} },	
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } }, // Makes it possible to run Windows-downloaded or .desktop file(s): Saya no Uta, FL Studio, xppentablet, ....
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      toggletopbar,   {0} },
	
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.015} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.015} },
	{ MODKEY,                       XK_bracketleft,  incngappx, {.i = -2 } },
	{ MODKEY,                       XK_bracketright, incngappx, {.i = +2 } },
	
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 			            XK_q,      killclientsel,  {.i = 0} },
	{ MODKEY|ShiftMask,             XK_q,      killclientsel,  {.i = 1} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_slash,  setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[6]} }, // TODO modify properly
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[8]} }, 

	{ MODKEY,                       XK_space,  setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,    {0} },
	{ MODKEY|ControlMask,           XK_space,  togglealwaysontop, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ControlMask,           XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_s,      spawn,          {.v = shutdowncmd} }, // Graceful shutdown
	{ MODKEY|ControlMask|ShiftMask, XK_r,      spawn,          {.v = rebootcmd} }, // Graceful shutdown

	{ MODKEY,                       XK_c,      togglecolorsel, {0} }, // color selection
	{ MODKEY|ControlMask,           XK_f,      toggleallownextfloating, {0} }, // disallow/allow mod+j or mod+k or similar to be focused
	{ MODKEY|ShiftMask,             XK_c,      togglecompositor, {0} }, // use/don't use compositor
	{ MODKEY|ShiftMask,             XK_f,      toggleswitchonfocus, {0} }, // ignore popup focus
	{ MODKEY|ShiftMask,             XK_a,      toggleattachbelow, {0} },

#ifdef TRAIN_KEYBOARD_LAYOUT
	{ MODKEY,                       XK_F1,     spawn,          {.v = xkbqwerty}}, 	
	{ MODKEY,                       XK_F2,     spawn,          {.v = xkbdvorak}}, 	
	{ MODKEY,                       XK_F3,     spawn,          {.v = xkbcolemak}}, 	
	{ MODKEY,                       XK_F4,     spawn,          {.v = xkbarabic}}, 	
	{ MODKEY,                       XK_F5,     spawn,          {.v = xkbjapanese}}, 	
#endif
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
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
};
