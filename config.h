/* See LICENSE file for copyright and license details. */

/* Should I separate config with another config? :3 */

#define LAYOUTS 

// Include Layouts
#include "fibonacci.c"

#define TRAIN_KEYBOARD_LAYOUT

/* appearance */
static const unsigned int snap      = 32;       /* snap pixel */
static unsigned int borderpx        = 8;        /* border pixel of windows */ // not constant
static int showbar                  = 0;        /* 0 means no bar */
static int topbar                   = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_black },
	[SchemeSel]  = { col_gray4, "#050505",  "#101010" },
};

/* tagging; why japs? cuz kanji is easier */
static const char *tags[] = { "電", "捜", "歌", "開", "操", "?", "?", "描", "曲" };

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

// TODO separate layouts to a single file
static const Layout layouts[] = {
	/* symbol              arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",     dwindle },
};

/* Misc */
#define USEDTERMINAL "kitty"

/* TAGKEYS is the proof that `define` macros are useful, Terry Davis! (RIP THE LEGEND) */
/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* my own key definition */
#define PRNSC 0x0000ff61

/* helper for spawning shell commands (not recommended )*/
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *shutdowncmd[] = { "nihwmctl", "shutdown" }; 
static const char *rebootcmd[] = { "nihwmctl", "reboot" }; // TODO implement this 
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", "-theme", "nihwm", NULL };

static const char *termcmd[]  = { USEDTERMINAL, NULL };
static const char *printscr[] = { "flameshot", "gui", NULL };

/* For no apparent reason, fn + button does not work */
static const char *decvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%-", NULL };
static const char *incvolcmd[] = { "amixer", "-D", "pulse", "sset", "Master", "1%+", NULL };

/* Define the startup command (required) */
static const char *statusbarcmd[] = { "nihwmctl", "statusbar",  NULL };
static const char *gromitmpxcmd[] = { "gromit-mpx", NULL };
static const char *pavucontrolcmd[] = { "pavucontrol", NULL };

/* Define the startup command (application/optional) */
static const char *browsercmd[] = { "chromium", NULL };
static const char *rhythmboxcmd[] = { "rhythmbox", NULL };
static const char *thunarcmd[] = { "thunar", NULL };
static const char *lmms130cmd[] = { "lmms1.3.0", NULL };

/* not in nihwm, my own config KEYBOARDS */
static const char *xkbqwerty[] = { "setxkbmap", "us", NULL };
static const char *xkbdvorak[] = { "setxkbmap", "dvorak", NULL };
static const char *xkbcolemak[] = { "setxkbmap", "us", "-variant", "colemak", NULL };
static const char *xkbarabic[] = { "setxkbmap", "ara", NULL };

/* startup */
static const StartApplication startup[] = {
	/* tag       command  */
	{ 1 << 0,	{.v = statusbarcmd} },
	{ 1 << 4,	{.v = pavucontrolcmd} },
	{ 1 << 4,	{.v = gromitmpxcmd} },

	/* optional */
	{ 1 << 0,	{.v = termcmd} },
	{ 1 << 1,	{.v = browsercmd} },
	{ 1 << 2,	{.v = rhythmboxcmd} },
	{ 1 << 3,	{.v = thunarcmd} },
	{ 1 << 8,	{.v = lmms130cmd} },
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance      title          tags mask     isfloating   monitor */
	{  "Chromium",      "chromium",   NULL,          1 << 1,       0,           -1},
	{  "firefox",       "Navigator",  NULL,          1 << 1,       0,           -1},
	{  "Opera",         "Opera",      NULL,          1 << 1,       0,           -1},
	{  "Rhythmbox",     "rhythmbox",  NULL,          1 << 2,       0,           -1},
	{  "Thunar",        "thunar",     NULL,          1 << 3,       0,           -1},
	{  "Zathura",       "org.pwmt.zathura",          NULL,          1 << 4,       0,           -1},
	{  "Gromit-mpx",     "gromit-mpx",  NULL,        1 << 4,       0,           -1},
	{  "Pavucontrol",    "pavucontrol",  NULL,       1 << 4,       0,           -1},
	{  "obs",           "obs",        NULL,          1 << 6,       0,           -1},
	{  "krita",         "krita",      NULL,          1 << 7,       0,           -1},
	{  "Inkscape",      "org.inkscape.Inkscape",     NULL,          1 << 7,       0,           -1},
	{  "lmms.real",     "lmms.real",     NULL,       1 << 8,       0,           -1},
	{  "Mousepad",      "mousepad",   NULL,          0,            1,           -1 }
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_F10,    spawn,          {.v = decvolcmd} },
	{ MODKEY,                       XK_F11,    spawn,          {.v = incvolcmd} },
	{ 0,                            PRNSC,     spawn,          {.v = printscr} },	
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_r,      spawn,          {.v = roficmd } }, // Makes it possible to run Windows-downloaded or .desktop file(s): Saya no Uta, FL Studio, xppentablet, ....
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },

	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_b,      toggletopbar,   {0} },
	{ MODKEY|ShiftMask,             XK_f,      toggleswitchonfocus, {0} }, // switch on focus = 0 means that we ignore if a popup exists, or something similar like that
	
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	/* { MODKEY|ShiftMask,             XK_i,      incnborder,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnborder,     {.i = -1 } }, */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY, 			            XK_q,      killclientsel,  {.i = 0} },
	{ MODKEY|ShiftMask,             XK_q,      killclientsel,  {.i = 1} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_d,      setlayout,      {.v = &layouts[4]} },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
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

	{ MODKEY|ControlMask,           XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },
	{ MODKEY|ControlMask|ShiftMask, XK_s,      spawn,          {.v = shutdowncmd} }, // Graceful shutdown
	{ MODKEY|ControlMask|ShiftMask, XK_r,      spawn,          {.v = rebootcmd} }, // Graceful shutdown
#ifdef TRAIN_KEYBOARD_LAYOUT
	{ MODKEY,                       XK_F1,     spawn,          {.v = xkbqwerty}}, 	
	{ MODKEY,                       XK_F2,     spawn,          {.v = xkbdvorak}}, 	
	{ MODKEY,                       XK_F3,     spawn,          {.v = xkbcolemak}}, 	
	{ MODKEY,                       XK_F4,     spawn,          {.v = xkbarabic}}, 	
#endif
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
