/* See LICENSE file for copyright and license details. */

/* appearance */
static char font[] = "DejaVu Sans Mono:style=Book:pixelsize=12:antialias=true:autohint=true";
static const char* normbgcolor  = "#101010";
static const char* normfgcolor  = "#800000";
static const char* selbgcolor   = "#101010";
static const char* selfgcolor   = "#ff0000";
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

#define SETPROP(p) { \
        .v = (char *[]){ "/bin/sh", "-c", \
                "prop=\"`xwininfo -children -id $1 | grep '^     0x' |" \
                "sed -e's@^ *\\(0x[0-9a-f]*\\) \"\\([^\"]*\\)\".*@\\1 \\2@' |" \
                "xargs -0 printf %b | dmenu -l 10 -w $1`\" &&" \
                "xprop -id $1 -f $0 8s -set $0 \"$prop\"", \
                p, winid, NULL \
        } \
}

#define MODKEY ControlMask
static Key keys[] = {
	/* modifier             key        function     argument */
	{ MODKEY|ShiftMask,             XK_Return, focusonce,      { 0 } },
	{ MODKEY,                       XK_t,      spawn,          { 0 } },
	{ MODKEY,                       XK_p,      spawn,          SETPROP("_TABBED_SELECT_TAB") },
	{ MODKEY,                       XK_Tab,    rotate,         { .i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    rotate,         { .i = -1 } },
	{ MODKEY,                       XK_h,      movetab,        { .i = -1 } },
	{ MODKEY,                       XK_l,      movetab,        { .i = +1 } },
    { MODKEY,                       XK_F11,    fullscreen,     { 0 } },
};
