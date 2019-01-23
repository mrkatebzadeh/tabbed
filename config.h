/* See LICENSE file for copyright and license details. */

/* appearance */
static char font[] = "mono:pixelsize=13:antialias=true:autohint=true";
static const char* selbgcolor   = "#282a36";
static const char* selfgcolor   = "#bd93f9";
static const char* normbgcolor  = "#44475a";
static const char* normfgcolor  = "#ff79c6";
static const char* urgbgcolor   = "#a00000";
static const char* urgfgcolor   = "#ffffff";
static const char before[]      = "<";
static const char after[]       = ">";
static const char titletrim[]   = "...";
static const int  tabwidth      = 200;
static const Bool foreground    = True;
static       Bool urgentswitch  = False;

/*
 * Where to place a new tab when it is opened. When npisrelative is True,
 * then the current position is changed + newposition. If npisrelative
 * is False, then newposition is an absolute position.
 */
static int  newposition   = -1;
static Bool npisrelative  = False;

#define MODKEY ControlMask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY,               XK_t,      spawn,       { 0 } },
	{ MODKEY,               XK_Tab,    rotate,      { .i = +1 } },
	{ MODKEY|ShiftMask,     XK_Tab,    rotate,      { .i = -1 } },
	{ MODKEY,               XK_h,      movetab,     { .i = -1 } },
	{ MODKEY,               XK_l,      movetab,     { .i = +1 } },
};
