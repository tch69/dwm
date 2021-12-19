/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const unsigned int gappx     = 5;
static const unsigned int border    = 8;	/* border pixel of the bar */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Roboto Mono:size=8.8", "fontawesome:size=10" };
static const char bg_norm[]         = "#000000";
static const char fg_norm[]         = "#efefef";
static const char bo_norm[]         = "#000000";
static const char bg_selt[]         = "#3c3fef";
static const char fg_selt[]         = "#efefef";
static const char bo_selt[]         = "#efefef";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg_norm,   bg_norm,   bo_norm  },
	[SchemeSel]  = { fg_selt,   bg_selt,   bo_selt  },
};

/* autostart using 'cool autostart' patch */
static const char *const autostart[] = {
	"ibus-daemon", "-drx", NULL,
	"setbg", NULL,
	"dwmbar", NULL,
/*	"pulseaudio", "--daemon", NULL, */
	NULL
};

/* tagging */
static const char *tags[] = { "A", "Ă", "Â", "B", "C", "D", "Đ", "E", "Ê"};

static const Rule rules[] = {
        /* xprop(1):
         *      WM_CLASS(STRING) = instance, class
         *      WM_NAME(STRING) = title
         */
        /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
        { "Gimp",    NULL,     NULL,           0,         1,          0,                  -1 },
        { "Fceux",    NULL,     NULL,           0,         1,          0,                  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " til ",      tile },    /* first entry is default */
	{ " flt ",      NULL },    /* no layout function means floating behavior */
	{ " mnc ",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define SLCMD(cmd) { .v = (const char*[]){ cmd, NULL } }
/* terminal */
#define TERM "st"
/* screenshot using scrot */
#define SCROT "/usr/bin/scrot -q 100 "
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier			key		function		argument */
	{ MODKEY|ShiftMask,		XK_Return, 	spawn, 			{.v = dmenucmd } },
	{ MODKEY, 			XK_Return, 	spawn, 			{.v = termcmd } },
//	{ MODKEY|ShiftMask,		XK_m, 		spawn, 			SHCMD(TERM " -e ncmpcpp") },
	{ MODKEY|ShiftMask, 		XK_s, 		spawn, 			SHCMD("maim -m 1 --window=root $HOME/Pictures/Screenshots/screenshot-full-$(date +'%d-%m-%y-%H-%M-%S').png") },
	{ MODKEY|ShiftMask, 		XK_f, 		spawn, 			SHCMD("maim -m 1 -B --window=$(xdotool getactivewindow) $HOME/Pictures/Screenshots/screenshot-window-$(date +'%d-%m-%y-%H-%M-%S').png") },
	{ MODKEY|ShiftMask, 		XK_d, 		spawn, 			SHCMD(" maim -m 1 -s $HOME/Pictures/Screenshots/screenshot-selected-$(date +'%d-%m-%y-%H-%M-%S').png") },
	{ MODKEY, 			XK_z, 		spawn, 			SHCMD("ibus engine m17n:vi:telex") },
	{ MODKEY|ShiftMask, 		XK_z, 		spawn, 			SHCMD("ibus engine xkb:us::eng") },
	{ MODKEY|ShiftMask, 		XK_Up,	 	spawn, 			SHCMD("amixer set Master 1+") },
	{ MODKEY|ShiftMask, 		XK_Down, 	spawn, 			SHCMD("amixer set Master 1-") },
	{ MODKEY|ShiftMask, 		XK_l, 		spawn, 			SHCMD(TERM " -e doas shutdown -P now") },
	{ MODKEY, 			XK_b, 		togglebar, 		{0} },
	{ MODKEY, 			XK_space, 	zoom, 			{0} },
	{ MODKEY, 			XK_Tab, 	focusstack, 		{.i = +1 } },
	{ MODKEY, 			XK_i, 		incnmaster, 		{.i = +1 } },
	{ MODKEY, 			XK_d, 		incnmaster, 		{.i = -1 } },
	{ MODKEY, 			XK_h, 		setmfact, 		{.f = -0.05} },
	{ MODKEY, 			XK_l, 		setmfact, 		{.f = +0.05} },
	{ MODKEY, 			XK_x, 		killclient,	 	{0} },
	{ MODKEY, 			XK_t, 		setlayout, 		{.v = &layouts[0]} },
	{ MODKEY, 			XK_f, 		setlayout, 		{.v = &layouts[1]} },
	{ MODKEY, 			XK_m, 		setlayout, 		{.v = &layouts[2]} },
	{ MODKEY|ShiftMask, 		XK_space, 	setlayout, 		{0} },
	{ MODKEY|ShiftMask, 		XK_t, 		togglefloating,		{0} },
	TAGKEYS( 			XK_1, 		0)
	TAGKEYS( 			XK_2, 		1)
	TAGKEYS( 			XK_3, 		2)
	TAGKEYS( 			XK_4, 		3)
	TAGKEYS( 			XK_5, 		4)
	TAGKEYS( 			XK_6, 		5)
	TAGKEYS( 			XK_7, 		6)
	TAGKEYS( 			XK_8, 		7)
	TAGKEYS( 			XK_9, 		8)
	{ MODKEY|ShiftMask, 		XK_q, 		quit, 			{0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click 			event mask 	button 			function 		argument */
	{ ClkLtSymbol, 			0, 		Button1, 		setlayout, 		{0} },
	{ ClkLtSymbol, 			0, 		Button3, 		setlayout, 		{.v = &layouts[2]} },
	{ ClkClientWin, 		MODKEY, 	Button1, 		movemouse,		{0} },
	{ ClkClientWin, 		MODKEY, 	Button2, 		togglefloating, 	{0} },
	{ ClkClientWin, 		MODKEY, 	Button3, 		resizemouse, 		{0} },
	{ ClkTagBar, 			0, 		Button1, 		view, 			{0} },
	{ ClkTagBar, 			0, 		Button3, 		toggleview, 		{0} },
	{ ClkTagBar, 			MODKEY, 	Button1, 		tag, 			{0} },
	{ ClkTagBar, 			MODKEY, 	Button3,		toggletag, 		{0} },
};

