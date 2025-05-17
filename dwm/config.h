/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 12;        /* gaps between windows */
static const unsigned int snap      = 0;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "spleen:size=10" };
static const char dmenufont[]       = "spleen:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            0,             1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,             0,           -1 },
};

/* Layout(s) */
static const float mfact     = 0.55; /* Factor of master area size [0.05..0.95]. */
static const int nmaster     = 1;    /* Number of clients in master area. */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals. */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window. */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* Symbol     Arrange function */
	{ "[]=",      tile },    /* First entry is default. */
	{ "><>",      NULL },    /* No layout function means floating behavior. */
	{ "[M]",      monocle },
 	{ "[@]",      spiral },
 	{ "[\\]",      dwindle },
};

/* Key definitions */
/* Modkeys */
#define MODKEY 		Mod1Mask
#define LAYOUTMOD	MODKEY|ControlMask
#define PROMPTMOD	MODKEY|ShiftMask
#define WINDOWMOD	MODKEY
#define TAGMOD		MODKEY
#define MONITORMOD	MODKEY|ShiftMask

/* Keychords */
#define LAYOUTCHORD	{LAYOUTMOD, XK_l}
#define PROMPTCHORD	{PROMPTMOD, XK_p}

/* Tags */
#define TAGKEYS(KEY,TAG)                                                                                               \
       &((Keychord){1, {{MODKEY, KEY}},                                        view,           {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask, KEY}},                            toggleview,     {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ShiftMask, KEY}},                              tag,            {.ui = 1 << TAG} }), \
       &((Keychord){1, {{MODKEY|ControlMask|ShiftMask, KEY}},                  toggletag,      {.ui = 1 << TAG} }),

/* Helper for spawning shell commands in the pre dwm-5.0 fashion. */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Keychord *keychords[] = {
	/* Keychord?    Keys                                             Function        Argument */
	/*						Prompts					*/
	&((Keychord){2, {PROMPTCHORD, {PROMPTMOD, XK_l}},		spawn,          {.v = dmenucmd } }),
	&((Keychord){2, {PROMPTCHORD, {PROMPTMOD, XK_l}},		spawn,          SHCMD("audiodevice_selector.sh") }),
	&((Keychord){2, {PROMPTCHORD, {PROMPTMOD, XK_l}},		spawn,          SHCMD("keyboard.sh") }),
	&((Keychord){2, {PROMPTCHORD, {PROMPTMOD, XK_l}},		spawn,          SHCMD("reader.sh") }),
	&((Keychord){2, {PROMPTCHORD, {PROMPTMOD, XK_l}},		spawn,          SHCMD("shutdown.sh") }),
	/*						Layouts					*/
	&((Keychord){2, {LAYOUTCHORD, {LAYOUTMOD, XK_t}},		setlayout,      {.v = &layouts[0]} }),
	&((Keychord){2, {LAYOUTCHORD, {LAYOUTMOD, XK_f}},		setlayout,      {.v = &layouts[1]} }),
	&((Keychord){2, {LAYOUTCHORD, {LAYOUTMOD, XK_m}},		setlayout,      {.v = &layouts[2]} }),
	&((Keychord){2, {LAYOUTCHORD, {LAYOUTMOD, XK_s}},		setlayout,      {.v = &layouts[3]} }),
	&((Keychord){1, {{MODKEY, XK_space}},				setlayout,      {0} }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_space}},			togglefloating, {0} }),
	/*						Spawn Programs				*/
	&((Keychord){1, {{MODKEY|ShiftMask, XK_Return}},		spawn,          {.v = termcmd } }),
	&((Keychord){2, {{MODKEY, XK_e}, {MODKEY, XK_e}},		spawn,          {.v = termcmd } }),
	&((Keychord){1, {{MODKEY|ShiftMask, XK_l}},			spawn,          SHCMD("slock") }),
	/*						Window Manipulations			*/
	&((Keychord){1, {{WINDOWMOD, XK_j}},				focusstack,     {.i = +1 } }),
	&((Keychord){1, {{WINDOWMOD, XK_k}},				focusstack,     {.i = -1 } }),
	&((Keychord){1, {{WINDOWMOD, XK_i}},				incnmaster,     {.i = +1 } }),
	&((Keychord){1, {{WINDOWMOD, XK_d}},				incnmaster,     {.i = -1 } }),
	&((Keychord){1, {{WINDOWMOD, XK_h}},				setmfact,       {.f = -0.05} }),
	&((Keychord){1, {{WINDOWMOD, XK_l}},				setmfact,       {.f = +0.05} }),
	&((Keychord){1, {{WINDOWMOD, XK_Return}},			zoom,           {0} }),
	&((Keychord){1, {{WINDOWMOD|ShiftMask, XK_c}},			killclient,     {0} }),
	/*						Monitors				*/
	&((Keychord){1, {{MONITORMOD, XK_comma}},			focusmon,       {.i = -1 } }),
	&((Keychord){1, {{MONITORMOD, XK_period}},			focusmon,       {.i = +1 } }),
	&((Keychord){1, {{MONITORMOD, XK_comma}},			tagmon,         {.i = -1 } }),
	&((Keychord){1, {{MONITORMOD, XK_period}},			tagmon,         {.i = +1 } }),
	/*						Tags					*/
	&((Keychord){1, {{TAGMOD, XK_Tab}},				view,           {0} }),
	&((Keychord){1, {{TAGMOD, XK_0}},				view,           {.ui = ~0 } }),
	&((Keychord){1, {{TAGMOD|ShiftMask, XK_0}},			tag,            {.ui = ~0 } }),
	/*						DWM					*/
	&((Keychord){1, {{MODKEY, XK_b}},				togglebar,      {0} }),
	&((Keychord){1, {{MONITORMOD|ShiftMask, XK_q}},			quit,           {0} }),
	/* Mod                          Key                        Tag */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* Button definitions. */
/* Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin. */
static const Button buttons[] = {
	/* Click                Event mask      Button          Function        Argument */
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

