/* See LICENSE file for copyright an0od license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static int vertpad            = 3;       /* vertical padding of bar */
static int sidepad            = 3;       /* horizontal padding of bar */

static const char *fonts[]          = { "JetBrains Mono Medium:style=Medium,Regular:size=10", "Font Awesome 6 Pro:style=Solid:pixelsize=11", "Font Awesome 5 Pro:style=Solid:pixelsize=11" };
static const char dmenufont[]       = "JetBrains Mono Medium:style=Medium,Regular:size=10";

static char normbgcolor[]     = "#0A050E";
static char normbordercolor[] = "#668c9a";
static char normfgcolor[]     = "#92c9dd";
static char selfgcolor[]      = "#92c9dd";
static char selbordercolor[]  = "#0759A4";
static char selbgcolor[]      = "#0759A4";

static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor, selbgcolor,  selbordercolor  },
};

static const char *const autostart[] = {
    "dwm_statusbar_wrapper", NULL,
	"sh", "-c", "cmus_wrapper", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "" }; //

static const unsigned int ulinepad	= 8;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

/* Lockfile */
static char lockfile[] = "/tmp/dwm.lock";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */

    /* General */
	{ "Chromium-browser-chromium", "chromium-browser-chromium", NULL, 1, 0, -1 },
	{ "discord",  "discord", NULL, 2, 0, -1 },
	{ NULL, "terminal", NULL, 2, 0, -1},
	{ "Microsoft Teams - Preview", "microsoft teams - preview", NULL, 1 << 4, 0, -1},
	{ "kitty",  "kitty", NULL, 1 << 9, 0, -1 },
	{ NULL, "cmus", NULL, 1 << 3, 0, -1},

    /* Games */
   	{ "Lutris",  "lutris", NULL, 1 << 4, 0, -1 },
	{ "heroic",  "heroic", NULL, 1 << 4, 0, -1 },
	{ "battle.net.exe",  "battle.net.exe", NULL, 1 << 4, 0, -1 },
    { "PolyMC", "polymc", NULL, 1 << 4, 0, -1},
	{ "SevTech Ages", "SevTech Ages", NULL, 1 << 5, 0, -1},
	{ "Minecraft 1.8.9",  "Minecraft 1.8.9", NULL, 1 << 5, 0, -1 },
	{ "Minecraft* 1.17.1",  "Minecraft* 1.17.1", NULL, 1 << 5, 0, -1 },
	{ "Minecraft* 1.18.1",  "Minecraft* 1.18.1", NULL, 1 << 5, 0, -1 },
	{ "overwatch.exe",  "overwatch.exe", NULL, 1 << 5, 0, -1 },
	{ NULL,  NULL, "Wine System Tray", 1 << 4, 0, -1 },
	{ "civilizationvi.exe",  "civilizationvi.exe", NULL, 1 << 5, 0, -1 },
	{ "doomx64vk.exe",  "doomx64vk.exe", NULL, 1 << 5, 0, -1 },
	{ "borderlands3.exe",  "borderlands3.exe", NULL, 1 << 5, 0, -1 },
	{ "Steam",  "Steam", NULL, 1 << 4, 0, -1 },
	{ "steam_app_252950",  "steam_app_252950", NULL, 1 << 5, 0, -1 }, // Rocket League
	{ "steam_app_960090",  "steam_app_960090", NULL, 1 << 5, 0, -1 }, // BTD 6
	{ "steam_app_1276390",  "steam_app_1276390", NULL, 1 << 5, 0, -1 }, // BTDB2
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* custom symbols for nr. of clients in monocle layout */
/* when clients >= LENGTH(monocles), uses the last element */
static const char *monocles[] = { "", "", "", "", "", "", "", "", "", "[9+]" };

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define CTRLKEY XK_Control_L
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY2,                      KEY,      comboview,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY2|ShiftMask,            KEY,      combotag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-hp", "ungoogled,chromium,discord,firefox,kitty,vscodium,nomacs,steam,polymc,flameshot,netflix,mpv,zzz", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *flameshot[] = {"flameshot", "gui", NULL};
static const char *cmusplaypause[] = {"playerctl", "--player=cmus", "play-pause", NULL};
static const char *cmusnext[] = {"playerctl", "--player=cmus", "next", NULL};
static const char *cmusprevious[] = {"playerctl", "--player=cmus", "previous", NULL};
static const char *betterlockscreen[] = {"betterlockscreen", "-l", NULL};
static const char *volup [] = {"pactl", "set-sink-volume", "50", "+5%", NULL};
static const char *voldown[] = {"pactl", "set-sink-volume", "50", "-5%", NULL};
static const char *shutdown[] = {"prompt", "Do you want to shutdown?", "shutdown -h now", NULL};
static const char *lowpower[] = {"prompt", "Do you want to go into low power mode?", "zzz -S", NULL};
//static const char *sleepcmd[] = {"prompt", "Do you want to go sleep?", "zzz", NULL};
static const char *sleepcmdnoprompt[] = {"zzz", NULL};
static const char *hibernate[] = {"prompt", "Do you want to go hibernate?", "ZZZ", NULL};
//static const char *walreload[] = {"walreload", NULL};
//static const char *themereload[] = {"themereload", NULL};


#include "shift-tools.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY2,             		XK_Tab,   shiftview,		{ .i =+1 } },
	{ MODKEY2|ShiftMask,            XK_Tab,   shiftview,		{ .i =-1} },
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_p,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Tab,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Tab,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,		XK_h,      shiftboth,      { .i = -1 }	},
	{ MODKEY|ControlMask,		XK_h,      shiftswaptags,  { .i = -1 }	},
	{ MODKEY|ControlMask,		XK_l,      shiftswaptags,  { .i = +1 }	},
	{ MODKEY|ShiftMask,             XK_l,      shiftboth,      { .i = +1 }	},
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	//{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,		XK_o,	   spawn,	{.v = shutdown} },
	{ MODKEY|ShiftMask,		XK_h,	   spawn,	{.v = hibernate} },
	//{ MODKEY|ShiftMask,		XK_s,	   spawn,	{.v = sleepcmd} },
	{ MODKEY|ShiftMask,		XK_p,	   spawn,	{.v = lowpower} },
	{ 0,		XK_Pause,	   spawn,	{.v = sleepcmdnoprompt} },
	{ MODKEY,             		XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY2,                      XK_space,  setlayout,      {0} },
	{ MODKEY2|ShiftMask,            XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      comboview,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	//{ MODKEY,			XK_F5,     spawn,	   {.v = themereload}},
	{ MODKEY,			XK_F5,     xrdb,	   {.v = NULL} },

	//{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	//{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ 0,				XK_Print,  spawn,	   {.v = flameshot } },
	{ ControlMask|ShiftMask,	XK_x,	   spawn,		{.v = cmusplaypause } },
	{ ControlMask|ShiftMask,	XK_b,	   spawn,		{.v = cmusnext } },
	{ ControlMask|ShiftMask,	XK_n,	   spawn,		{.v = cmusprevious } },
	{ MODKEY,			XK_semicolon,	   spawn,	{.v = betterlockscreen } },
	{ MODKEY,			XK_equal,   spawn,		{.v = volup } },
	{ MODKEY,			XK_minus,   spawn,		{.v = voldown } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

