/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "mono:pixelsize=19:antialias=true:autohint=true";
/* Spare fonts */
static char *font2[] = {
   "Inconsolata Nerd Font:pixelsize=18:antialias=true:autohint=false",
   "Font Awesome 5 Free Solid:pixelsize=17:antialias=true:autohint=true",
   "JoyPixels:pixelsize=17:antialias=true:autohint=true",
	 "FreeMono:pixelsize=20:antialias=true:autohint=true"
};

static int borderpx = 0;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: scroll and/or utmp
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
/* scroll program: to enable use a string like "scroll" */
char *scroll = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1.0;
static float chscale = 1.0;

/*
 * word delimiter string
 *
 * More advanced example: L" `'\"()[]{}"
 */
wchar_t *worddelimiters = L" ";

/* selection timeouts (in milliseconds) */
static unsigned int doubleclicktimeout = 300;
static unsigned int tripleclicktimeout = 600;

/* alt screens */
int allowaltscreen = 1;

/* allow certain non-interactive (insecure) window operations such as:
   setting the clipboard text */
int allowwindowops = 0;

/*
 * draw latency range in ms - from new content/keypress/etc until drawing.
 * within this range, st draws when content stops arriving (idle). mostly it's
 * near minlatency, but it waits longer for slow updates to avoid partial draw.
 * low minlatency will tear/flicker more, as it can "detect" idle too early.
 */
static double minlatency = 8;
static double maxlatency = 33;

/*
 * blinking timeout (set to 0 to disable blinking) for the terminal blinking
 * attribute.
 */
static unsigned int blinktimeout = 0;

/*
 * thickness of underline and bar cursors
 */
static unsigned int cursorthickness = 2;

/*
 * 1: render most of the lines/blocks characters without using the font for
 *    perfect alignment between cells (U2500 - U259F except dashes/diagonals).
 *    Bold affects lines thickness if boxdraw_bold is not 0. Italic is ignored.
 * 0: disable (render all U25XX glyphs normally from the font).
 */
const int boxdraw = 1;
const int boxdraw_bold = 1;

/* braille (U28XX):  1: render as adjacent "pixels",  0: use font */
const int boxdraw_braille = 1;

/*
 * bell volume. It must be a value between -100 and 100. Use 0 for disabling
 * it
 */
static int bellvolume = 0;

/* default TERM value */
char *termname = "st-256color";

/*
 * spaces per tab
 *
 * When you are changing this value, don't forget to adapt the »it« value in
 * the st.info and appropriately install the st.info in the environment where
 * you use this st version.
 *
 *	it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 *	stty tabs
 */
unsigned int tabspaces = 2;

/* bg opacity */
float alpha = 0.7;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
	"#101010", "#cc2815", "#54a015", "#cfa815", "#3268ad", "#ad30a8", "#32a08d", "#969390",
	"#5a5856", "#f03522", "#77dd22", "#f0e822", "#43a3e0", "#e7909a", "#99a015", "#f0eeea",
	//cyan original: "#32a08d", "#80f0c8"
	[255] = 0,

	/* more colors can be added after 255 to use with DefaultXX */
	"#86e000", /* 256 -> cursor */
	"#505050", /* 257 -> rev cursor*/
	"#f0eeea", /* 258 -> fg */
	"#101010", /* 259 -> bg */
};

/*
 * Default colors (colorname index)
 * foreground, background, cursor, reverse cursor
 */
unsigned int defaultfg = 258;
unsigned int defaultbg = 259;
unsigned int defaultcs = 256;
static unsigned int defaultrcs = 257;

/*
 * Default shape of cursor
 * 2: Block ("█")
 * 4: Underline ("_")
 * 6: Bar ("|")
 * 7: Snowman ("☃")
 */
static unsigned int cursorshape = 6;

/*
 * Default columns and rows numbers
 */

static unsigned int cols = 80;
static unsigned int rows = 24;

/*
 * Default shape of the mouse cursor
 */

static char* mouseshape = "xterm";

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Force mouse select/shortcuts while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forcemousemod = ShiftMask;

static char *openurlcmd[] = { "/bin/sh", "-c", "st-urlhandler", "externalpipe", NULL };

#define MODKEY (ControlMask|Mod1Mask)
#define TERMMOD (ControlMask|ShiftMask)

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
	/* mask                 button   function        argument       release */
	{ XK_ANY_MOD,           Button4, kscrollup,      {.i = 1},      0, /* !alt */ -1 },
	{ XK_ANY_MOD,           Button5, kscrolldown,    {.i = 1},      0, /* !alt */ -1 },
	{ ControlMask,          Button4, kscrollup,      {.i =-1},      0 },
	{ ControlMask,          Button5, kscrolldown,    {.i =-1},      0 },
	{ TERMMOD,              Button4, zoom,           {.f =+1},      0 },
	{ TERMMOD,              Button5, zoom,           {.f =-1},      0 },
	{ XK_ANY_MOD,           Button4, ttysend,        {.s = "\031"} },
	{ XK_ANY_MOD,           Button5, ttysend,        {.s = "\005"} },
	{ ShiftMask,            Button4, ttysend,        {.s = "\033[5;2~"} },
	{ ShiftMask,            Button5, ttysend,        {.s = "\033[6;2~"} },
	{ XK_ANY_MOD,           Button2, clippaste,      {.i = 0},      1 },
  { ControlMask,          Button1, externalpipe,   {.v = openurlcmd } },
};

/* Internal keyboard shortcuts. */
static Shortcut shortcuts[] = {
   /* mask         keysym          function      argument */
   { XK_ANY_MOD,   XK_Break,       sendbreak,    {.i =  0} },
   { ControlMask,  XK_equal,       zoom,         {.f = +1} },
   { ControlMask,  XK_minus,       zoom,         {.f = -1} },
   { ControlMask,  XK_0,           zoomreset,    {.f =  0} },
   { TERMMOD,      XK_plus,        kscrollup,    {.i =  1} },
   { TERMMOD,      XK_underscore,  kscrolldown,  {.i =  1} },
   { TERMMOD,      XK_Page_Up,     kscrollup,    {.i = -1} },
   { TERMMOD,      XK_Page_Down,   kscrolldown,  {.i = -1} },
   { Mod1Mask,     XK_equal,       changealpha,  {.f = +0.1} },
   { Mod1Mask,     XK_minus,       changealpha,  {.f = -0.1} },
   { MODKEY,       XK_c,           clipcopy,     {.i =  0} },
   { MODKEY,       XK_v,           clippaste,    {.i =  0} },
	 { MODKEY,       XK_o,           externalpipe, {.v = openurlcmd } },
};

/*
 * Special keys (change & recompile st.info accordingly)
 *
 * Mask value:
 * * Use XK_ANY_MOD to match the key no matter modifiers state
 * * Use XK_NO_MOD to match the key alone (no modifiers)
 * appkey value:
 * * 0: no value
 * * > 0: keypad application mode enabled
 * *   = 2: term.numlock = 1
 * * < 0: keypad application mode disabled
 * appcursor value:
 * * 0: no value
 * * > 0: cursor application mode enabled
 * * < 0: cursor application mode disabled
 *
 * Be careful with the order of the definitions because st searches in
 * this table sequentially, so any XK_ANY_MOD must be in the last
 * position for a key.
 */

/*
 * If you want keys other than the X11 function keys (0xFD00 - 0xFFFF)
 * to be mapped below, add them to this array.
 */
static KeySym mappedkeys[] = {
	XK_space,
	XK_A,
	XK_B,
	XK_C,
	XK_D,
	XK_E,
	XK_F,
	XK_G,
	XK_H,
	XK_I,
	XK_K,
	XK_J,
	XK_L,
	XK_M,
	XK_N,
	XK_O,
	XK_P,
	XK_Q,
	XK_R,
	XK_S,
	XK_T,
	XK_U,
	XK_V,
	XK_W,
	XK_X,
	XK_Y,
	XK_Z,
	XK_0,
	XK_1,
	XK_2,
	XK_3,
	XK_4,
	XK_5,
	XK_6,
	XK_7,
	XK_8,
	XK_9,
	XK_exclam,
	XK_quotedbl,
	XK_numbersign,
	XK_dollar,
	XK_percent,
	XK_ampersand,
	XK_apostrophe,
	XK_parenleft,
	XK_parenright,
	XK_asterisk,
	XK_plus,
	XK_comma,
	XK_minus,
	XK_period,
	XK_slash,
	XK_colon,
	XK_semicolon,
	XK_less,
	XK_equal,
	XK_greater,
	XK_question,
	XK_at,
	XK_bracketleft,
	XK_backslash,
	XK_bracketright,
	XK_asciicircum,
	XK_underscore,
	XK_grave,
	XK_braceleft,
	XK_bar,
	XK_braceright,
	XK_asciitilde,
};

/*
 * State bits to ignore when matching key or button events.  By default,
 * numlock (Mod2Mask) and keyboard layout (XK_SWITCH_MOD) are ignored.
 */
static uint ignoremod = Mod2Mask|XK_SWITCH_MOD;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
	/* keysym           mask            string           appkey appcursor */
	{ XK_ISO_Left_Tab,  ShiftMask,      "\033[Z",        0,    0},
	{ XK_F1,            XK_NO_MOD,      "\033OP" ,       0,    0},
	{ XK_F1, /* F13 */  ShiftMask,      "\033[1;2P",     0,    0},
	{ XK_F1, /* F25 */  ControlMask,    "\033[1;5P",     0,    0},
	{ XK_F2,            XK_NO_MOD,      "\033OQ" ,       0,    0},
	{ XK_F2, /* F14 */  ShiftMask,      "\033[1;2Q",     0,    0},
	{ XK_F2, /* F26 */  ControlMask,    "\033[1;5Q",     0,    0},
	{ XK_F3,            XK_NO_MOD,      "\033OR" ,       0,    0},
	{ XK_F3, /* F15 */  ShiftMask,      "\033[1;2R",     0,    0},
	{ XK_F3, /* F27 */  ControlMask,    "\033[1;5R",     0,    0},
	{ XK_F4,            XK_NO_MOD,      "\033OS" ,       0,    0},
	{ XK_F4, /* F16 */  ShiftMask,      "\033[1;2S",     0,    0},
	{ XK_F4, /* F28 */  ControlMask,    "\033[1;5S",     0,    0},
	{ XK_F5,            XK_NO_MOD,      "\033[15~",      0,    0},
	{ XK_F5, /* F17 */  ShiftMask,      "\033[15;2~",    0,    0},
	{ XK_F5, /* F29 */  ControlMask,    "\033[15;5~",    0,    0},
	{ XK_F6,            XK_NO_MOD,      "\033[17~",      0,    0},
	{ XK_F6, /* F18 */  ShiftMask,      "\033[17;2~",    0,    0},
	{ XK_F6, /* F30 */  ControlMask,    "\033[17;5~",    0,    0},
	{ XK_F7,            XK_NO_MOD,      "\033[18~",      0,    0},
	{ XK_F7, /* F19 */  ShiftMask,      "\033[18;2~",    0,    0},
	{ XK_F7, /* F31 */  ControlMask,    "\033[18;5~",    0,    0},
	{ XK_F8,            XK_NO_MOD,      "\033[19~",      0,    0},
	{ XK_F8, /* F20 */  ShiftMask,      "\033[19;2~",    0,    0},
	{ XK_F8, /* F32 */  ControlMask,    "\033[19;5~",    0,    0},
	{ XK_F9,            XK_NO_MOD,      "\033[20~",      0,    0},
	{ XK_F9, /* F21 */  ShiftMask,      "\033[20;2~",    0,    0},
	{ XK_F9, /* F33 */  ControlMask,    "\033[20;5~",    0,    0},
	{ XK_F10,           XK_NO_MOD,      "\033[21~",      0,    0},
	{ XK_F10, /* F22 */ ShiftMask,      "\033[21;2~",    0,    0},
	{ XK_F10, /* F34 */ ControlMask,    "\033[21;5~",    0,    0},
	{ XK_F11,           XK_NO_MOD,      "\033[23~",      0,    0},
	{ XK_F11, /* F23 */ ShiftMask,      "\033[23;2~",    0,    0},
	{ XK_F11, /* F35 */ ControlMask,    "\033[23;5~",    0,    0},
	{ XK_F12,           XK_NO_MOD,      "\033[24~",      0,    0},
	{ XK_F12, /* F24 */ ShiftMask,      "\033[24;2~",    0,    0},
	{ XK_F12, /* F36 */ ControlMask,    "\033[24;5~",    0,    0},
	//used my script to generate
	{ XK_Tab,         Mod1Mask,              "\033[9;3u",   0,  0},
	{ XK_Tab,         ControlMask,           "\033[9;5u",   0,  0},
	{ XK_Tab,         ControlMask|Mod1Mask,  "\033[9;7u",   0,  0},
	{ XK_Return,      ShiftMask,             "\033[13;2u",  0,  0},
	{ XK_Return,      Mod1Mask,              "\033[13;3u",  0,  0},
	{ XK_Return,      Mod1Mask|ShiftMask,    "\033[13;4u",  0,  0},
	{ XK_Return,      ControlMask,           "\033[13;5u",  0,  0},
	{ XK_Return,      ControlMask|ShiftMask, "\033[13;6u",  0,  0},
	{ XK_Return,      ControlMask|Mod1Mask,  "\033[13;7u",  0,  0},
	{ XK_Pause,       ShiftMask,             "\033[18;2u",  0,  0},
	{ XK_Pause,       Mod1Mask,              "\033[18;3u",  0,  0},
	{ XK_Pause,       Mod1Mask|ShiftMask,    "\033[18;4u",  0,  0},
	{ XK_Pause,       ControlMask,           "\033[18;5u",  0,  0},
	{ XK_Pause,       ControlMask|ShiftMask, "\033[18;6u",  0,  0},
	{ XK_Pause,       ControlMask|Mod1Mask,  "\033[18;7u",  0,  0},
	{ XK_Escape,      ShiftMask,             "\033[27;2u",  0,  0},
	{ XK_Escape,      Mod1Mask,              "\033[27;3u",  0,  0},
	{ XK_Escape,      Mod1Mask|ShiftMask,    "\033[27;4u",  0,  0},
	{ XK_Escape,      ControlMask,           "\033[27;5u",  0,  0},
	{ XK_Escape,      ControlMask|ShiftMask, "\033[27;6u",  0,  0},
	{ XK_Escape,      ControlMask|Mod1Mask,  "\033[27;7u",  0,  0},
	{ XK_space,       ShiftMask,             "\033[32;2u",  0,  0},
	{ XK_space,       Mod1Mask,              "\033[32;3u",  0,  0},
	{ XK_space,       Mod1Mask|ShiftMask,    "\033[32;4u",  0,  0},
	{ XK_space,       ControlMask,           "\033[32;5u",  0,  0},
	{ XK_space,       ControlMask|ShiftMask, "\033[32;6u",  0,  0},
	{ XK_space,       ControlMask|Mod1Mask,  "\033[32;7u",  0,  0},
	{ XK_Menu,        ShiftMask,             "\033[103;2u", 0,  0},
	{ XK_Menu,        Mod1Mask,              "\033[103;3u", 0,  0},
	{ XK_Menu,        Mod1Mask|ShiftMask,    "\033[103;4u", 0,  0},
	{ XK_Menu,        ControlMask,           "\033[103;5u", 0,  0},
	{ XK_Menu,        ControlMask|ShiftMask, "\033[103;6u", 0,  0},
	{ XK_Menu,        ControlMask|Mod1Mask,  "\033[103;7u", 0,  0},
	{ XK_BackSpace,   XK_NO_MOD,             "\177",        0,  0},
	{ XK_BackSpace,   ShiftMask,             "\033[127;2u", 0,  0},
	{ XK_BackSpace,   Mod1Mask,              "\033\177",    0,  0},
	{ XK_BackSpace,   Mod1Mask|ShiftMask,    "\033[127;4u", 0,  0},
	{ XK_BackSpace,   ControlMask,           "\033[127;5u", 0,  0},
	{ XK_BackSpace,   ControlMask|ShiftMask, "\033[127;6u", 0,  0},
	{ XK_BackSpace,   ControlMask|Mod1Mask,  "\033[127;7u", 0,  0},
	{ XK_Up,          XK_NO_MOD,             "\033OA",      0,  0},
	{ XK_Up,          ShiftMask,             "\033[1;2A",   0,  0},
	{ XK_Up,          Mod1Mask,              "\033[1;3A",   0,  0},
	{ XK_Up,          Mod1Mask|ShiftMask,    "\033[1;4A",   0,  0},
	{ XK_Up,          ControlMask,           "\033[1;5A",   0,  0},
	{ XK_Up,          ControlMask|ShiftMask, "\033[1;6A",   0,  0},
	{ XK_Up,          ControlMask|Mod1Mask,  "\033[1;7A",   0,  0},
	{ XK_Down,        XK_NO_MOD,             "\033OB",      0,  0},
	{ XK_Down,        ShiftMask,             "\033[1;2B",   0,  0},
	{ XK_Down,        Mod1Mask,              "\033[1;3B",   0,  0},
	{ XK_Down,        Mod1Mask|ShiftMask,    "\033[1;4B",   0,  0},
	{ XK_Down,        ControlMask,           "\033[1;5B",   0,  0},
	{ XK_Down,        ControlMask|ShiftMask, "\033[1;6B",   0,  0},
	{ XK_Down,        ControlMask|Mod1Mask,  "\033[1;7B",   0,  0},
	{ XK_Left,        XK_NO_MOD,             "\033OD",      0,  0},
	{ XK_Left,        ShiftMask,             "\033[1;2D",   0,  0},
	{ XK_Left,        Mod1Mask,              "\033[1;3D",   0,  0},
	{ XK_Left,        Mod1Mask|ShiftMask,    "\033[1;4D",   0,  0},
	{ XK_Left,        ControlMask,           "\033[1;5D",   0,  0},
	{ XK_Left,        ControlMask|ShiftMask, "\033[1;6D",   0,  0},
	{ XK_Left,        ControlMask|Mod1Mask,  "\033[1;7D",   0,  0},
	{ XK_Right,       XK_NO_MOD,             "\033OC",      0,  0},
	{ XK_Right,       ShiftMask,             "\033[1;2C",   0,  0},
	{ XK_Right,       Mod1Mask,              "\033[1;3C",   0,  0},
	{ XK_Right,       Mod1Mask|ShiftMask,    "\033[1;4C",   0,  0},
	{ XK_Right,       ControlMask,           "\033[1;5C",   0,  0},
	{ XK_Right,       ControlMask|ShiftMask, "\033[1;6C",   0,  0},
	{ XK_Right,       ControlMask|Mod1Mask,  "\033[1;7C",   0,  0},
	{ XK_Home,        XK_NO_MOD,             "\033[1~",     0,  0},
	{ XK_Home,        ShiftMask,             "\033[1;2H",   0,  0},
	{ XK_Home,        Mod1Mask,              "\033[1;3H",   0,  0},
	{ XK_Home,        Mod1Mask|ShiftMask,    "\033[1;4H",   0,  0},
	{ XK_Home,        ControlMask,           "\033[1;5H",   0,  0},
	{ XK_Home,        ControlMask|ShiftMask, "\033[1;6H",   0,  0},
	{ XK_Home,        ControlMask|Mod1Mask,  "\033[1;7H",   0,  0},
	{ XK_End,         XK_NO_MOD,             "\033[4~",     0,  0},
	{ XK_End,         ShiftMask,             "\033[1;2F",   0,  0},
	{ XK_End,         Mod1Mask,              "\033[1;3F",   0,  0},
	{ XK_End,         Mod1Mask|ShiftMask,    "\033[1;4F",   0,  0},
	{ XK_End,         ControlMask,           "\033[1;5F",   0,  0},
	{ XK_End,         ControlMask|ShiftMask, "\033[1;6F",   0,  0},
	{ XK_End,         ControlMask|Mod1Mask,  "\033[1;7F",   0,  0},
	{ XK_Insert,      XK_NO_MOD,             "\033[2~",     0,  0},
	{ XK_Insert,      ShiftMask,             "\033[2;2~",   0,  0},
	{ XK_Insert,      Mod1Mask,              "\033[2;3~",   0,  0},
	{ XK_Insert,      Mod1Mask|ShiftMask,    "\033[2;4~",   0,  0},
	{ XK_Insert,      ControlMask,           "\033[2;5~",   0,  0},
	{ XK_Insert,      ControlMask|ShiftMask, "\033[2;6~",   0,  0},
	{ XK_Insert,      ControlMask|Mod1Mask,  "\033[2;7~",   0,  0},
	{ XK_Delete,      XK_NO_MOD,             "\033[3~",     0,  0},
	{ XK_Delete,      ShiftMask,             "\033[3;2~",   0,  0},
	{ XK_Delete,      Mod1Mask,              "\033[3;3~",   0,  0},
	{ XK_Delete,      Mod1Mask|ShiftMask,    "\033[3;4~",   0,  0},
	{ XK_Delete,      ControlMask,           "\033[3;6~",   0,  0},
	{ XK_Delete,      ControlMask|ShiftMask, "\033[3;5~",   0,  0},
	{ XK_Delete,      ControlMask|Mod1Mask,  "\033[3;7~",   0,  0},
	{ XK_Prior,       XK_NO_MOD,             "\033[5~",     0,  0},
	{ XK_Prior,       ShiftMask,             "\033[5;2~",   0,  0},
	{ XK_Prior,       Mod1Mask,              "\033[5;3~",   0,  0},
	{ XK_Prior,       Mod1Mask|ShiftMask,    "\033[5;4~",   0,  0},
	{ XK_Prior,       ControlMask,           "\033[5;5~",   0,  0},
	{ XK_Prior,       ControlMask|ShiftMask, "\033[5;6~",   0,  0},
	{ XK_Prior,       ControlMask|Mod1Mask,  "\033[5;7~",   0,  0},
	{ XK_Next,        XK_NO_MOD,             "\033[6~",     0,  0},
	{ XK_Next,        ShiftMask,             "\033[6;2~",   0,  0},
	{ XK_Next,        Mod1Mask,              "\033[6;3~",   0,  0},
	{ XK_Next,        Mod1Mask|ShiftMask,    "\033[6;4~",   0,  0},
	{ XK_Next,        ControlMask,           "\033[6;5~",   0,  0},
	{ XK_Next,        ControlMask|ShiftMask, "\033[6;6~",   0,  0},
	{ XK_Next,        ControlMask|Mod1Mask,  "\033[6;7~",   0,  0},

	// libtermkey compatible keyboard input
	{ XK_i,           ControlMask,           "\033[105;5u", 0,  0},
	{ XK_i,           ControlMask|Mod1Mask,  "\033[105;7u", 0,  0},
	{ XK_m,           ControlMask,           "\033[109;5u", 0,  0},
	{ XK_m,           ControlMask|Mod1Mask,  "\033[109;7u", 0,  0},
	{ XK_A,           ControlMask|ShiftMask, "\033[65;6u",  0,  0},
	{ XK_B,           ControlMask|ShiftMask, "\033[66;6u",  0,  0},
	{ XK_C,           ControlMask|ShiftMask, "\033[67;6u",  0,  0},
	{ XK_D,           ControlMask|ShiftMask, "\033[68;6u",  0,  0},
	{ XK_E,           ControlMask|ShiftMask, "\033[69;6u",  0,  0},
	{ XK_F,           ControlMask|ShiftMask, "\033[70;6u",  0,  0},
	{ XK_G,           ControlMask|ShiftMask, "\033[71;6u",  0,  0},
	{ XK_H,           ControlMask|ShiftMask, "\033[72;6u",  0,  0},
	{ XK_I,           ControlMask|ShiftMask, "\033[73;6u",  0,  0},
	{ XK_J,           ControlMask|ShiftMask, "\033[75;6u",  0,  0},
	{ XK_K,           ControlMask|ShiftMask, "\033[74;6u",  0,  0},
	{ XK_L,           ControlMask|ShiftMask, "\033[76;6u",  0,  0},
	{ XK_M,           ControlMask|ShiftMask, "\033[77;6u",  0,  0},
	{ XK_N,           ControlMask|ShiftMask, "\033[78;6u",  0,  0},
	{ XK_O,           ControlMask|ShiftMask, "\033[79;6u",  0,  0},
	{ XK_P,           ControlMask|ShiftMask, "\033[80;6u",  0,  0},
	{ XK_Q,           ControlMask|ShiftMask, "\033[81;6u",  0,  0},
	{ XK_R,           ControlMask|ShiftMask, "\033[82;6u",  0,  0},
	{ XK_S,           ControlMask|ShiftMask, "\033[83;6u",  0,  0},
	{ XK_T,           ControlMask|ShiftMask, "\033[84;6u",  0,  0},
	{ XK_U,           ControlMask|ShiftMask, "\033[85;6u",  0,  0},
	{ XK_V,           ControlMask|ShiftMask, "\033[86;6u",  0,  0},
	{ XK_W,           ControlMask|ShiftMask, "\033[87;6u",  0,  0},
	{ XK_X,           ControlMask|ShiftMask, "\033[88;6u",  0,  0},
	{ XK_Y,           ControlMask|ShiftMask, "\033[89;6u",  0,  0},
	{ XK_Z,           ControlMask|ShiftMask, "\033[90;6u",  0,  0},
	{ XK_0,           ControlMask,           "\033[48;5u",  0,  0},
	{ XK_0,           ControlMask|Mod1Mask,  "\033[48;7u",  0,  0},
	{ XK_1,           ControlMask,           "\033[49;5u",  0,  0},
	{ XK_1,           ControlMask|Mod1Mask,  "\033[49;7u",  0,  0},
	{ XK_2,           ControlMask,           "\033[50;5u",  0,  0},
	{ XK_2,           ControlMask|Mod1Mask,  "\033[50;7u",  0,  0},
	{ XK_3,           ControlMask,           "\033[51;5u",  0,  0},
	{ XK_3,           ControlMask|Mod1Mask,  "\033[51;7u",  0,  0},
	{ XK_4,           ControlMask,           "\033[52;5u",  0,  0},
	{ XK_4,           ControlMask|Mod1Mask,  "\033[52;7u",  0,  0},
	{ XK_5,           ControlMask,           "\033[53;5u",  0,  0},
	{ XK_5,           ControlMask|Mod1Mask,  "\033[53;7u",  0,  0},
	{ XK_6,           ControlMask,           "\033[54;5u",  0,  0},
	{ XK_6,           ControlMask|Mod1Mask,  "\033[54;7u",  0,  0},
	{ XK_7,           ControlMask,           "\033[55;5u",  0,  0},
	{ XK_7,           ControlMask|Mod1Mask,  "\033[55;7u",  0,  0},
	{ XK_8,           ControlMask,           "\033[56;5u",  0,  0},
	{ XK_8,           ControlMask|Mod1Mask,  "\033[56;7u",  0,  0},
	{ XK_9,           ControlMask,           "\033[57;5u",  0,  0},
	{ XK_9,           ControlMask|Mod1Mask,  "\033[57;7u",  0,  0},
	{ XK_ampersand,   Mod1Mask,              "\033[38;3u",  0,  0},
	{ XK_ampersand,   Mod1Mask|ShiftMask,    "\033[38;4u",  0,  0},
	{ XK_ampersand,   ControlMask,           "\033[38;5u",  0,  0},
	{ XK_ampersand,   ControlMask|ShiftMask, "\033[38;6u",  0,  0},
	{ XK_ampersand,   ControlMask|Mod1Mask,  "\033[38;7u",  0,  0},
	{ XK_apostrophe,  Mod1Mask,              "\033[39;3u",  0,  0},
	{ XK_apostrophe,  Mod1Mask|ShiftMask,    "\033[39;4u",  0,  0},
	{ XK_apostrophe,  ControlMask,           "\033[39;5u",  0,  0},
	{ XK_apostrophe,  ControlMask|ShiftMask, "\033[39;6u",  0,  0},
	{ XK_apostrophe,  ControlMask|Mod1Mask,  "\033[39;7u",  0,  0},
	{ XK_asciicircum, Mod1Mask,              "\033[94;3u",  0,  0},
	{ XK_asciicircum, Mod1Mask|ShiftMask,    "\033[94;4u",  0,  0},
	{ XK_asciicircum, ControlMask,           "\033[94;5u",  0,  0},
	{ XK_asciicircum, ControlMask|ShiftMask, "\033[94;6u",  0,  0},
	{ XK_asciicircum, ControlMask|Mod1Mask,  "\033[94;7u",  0,  0},
	{ XK_asciitilde,  Mod1Mask,              "\033[126;3u", 0,  0},
	{ XK_asciitilde,  Mod1Mask|ShiftMask,    "\033[126;4u", 0,  0},
	{ XK_asciitilde,  ControlMask,           "\033[126;5u", 0,  0},
	{ XK_asciitilde,  ControlMask|ShiftMask, "\033[126;6u", 0,  0},
	{ XK_asciitilde,  ControlMask|Mod1Mask,  "\033[126;7u", 0,  0},
	{ XK_asterisk,    Mod1Mask,              "\033[42;3u",  0,  0},
	{ XK_asterisk,    Mod1Mask|ShiftMask,    "\033[42;4u",  0,  0},
	{ XK_asterisk,    ControlMask,           "\033[42;5u",  0,  0},
	{ XK_asterisk,    ControlMask|ShiftMask, "\033[42;6u",  0,  0},
	{ XK_asterisk,    ControlMask|Mod1Mask,  "\033[42;7u",  0,  0},
	{ XK_at,          Mod1Mask,              "\033[64;3u",  0,  0},
	{ XK_at,          Mod1Mask|ShiftMask,    "\033[64;4u",  0,  0},
	{ XK_at,          ControlMask,           "\033[64;5u",  0,  0},
	{ XK_at,          ControlMask|ShiftMask, "\033[64;6u",  0,  0},
	{ XK_at,          ControlMask|Mod1Mask,  "\033[64;7u",  0,  0},
	{ XK_backslash,   Mod1Mask,              "\033[92;3u",  0,  0},
	{ XK_backslash,   Mod1Mask|ShiftMask,    "\033[92;4u",  0,  0},
	{ XK_backslash,   ControlMask,           "\033[92;5u",  0,  0},
	{ XK_backslash,   ControlMask|ShiftMask, "\033[92;6u",  0,  0},
	{ XK_backslash,   ControlMask|Mod1Mask,  "\033[92;7u",  0,  0},
	{ XK_bar,         Mod1Mask,              "\033[124;3u", 0,  0},
	{ XK_bar,         Mod1Mask|ShiftMask,    "\033[124;4u", 0,  0},
	{ XK_bar,         ControlMask,           "\033[124;5u", 0,  0},
	{ XK_bar,         ControlMask|ShiftMask, "\033[124;6u", 0,  0},
	{ XK_bar,         ControlMask|Mod1Mask,  "\033[124;7u", 0,  0},
	{ XK_braceleft,   Mod1Mask,              "\033[123;3u", 0,  0},
	{ XK_braceleft,   Mod1Mask|ShiftMask,    "\033[123;4u", 0,  0},
	{ XK_braceleft,   ControlMask,           "\033[123;5u", 0,  0},
	{ XK_braceleft,   ControlMask|ShiftMask, "\033[123;6u", 0,  0},
	{ XK_braceleft,   ControlMask|Mod1Mask,  "\033[123;7u", 0,  0},
	{ XK_braceright,  Mod1Mask,              "\033[125;3u", 0,  0},
	{ XK_braceright,  Mod1Mask|ShiftMask,    "\033[125;4u", 0,  0},
	{ XK_braceright,  ControlMask,           "\033[125;5u", 0,  0},
	{ XK_braceright,  ControlMask|ShiftMask, "\033[125;6u", 0,  0},
	{ XK_braceright,  ControlMask|Mod1Mask,  "\033[125;7u", 0,  0},
	{ XK_bracketleft, Mod1Mask,              "\033[91;3u",  0,  0},
	{ XK_bracketleft, Mod1Mask|ShiftMask,    "\033[91;4u",  0,  0},
	{ XK_bracketleft, ControlMask,           "\033[91;5u",  0,  0},
	{ XK_bracketleft, ControlMask|ShiftMask, "\033[91;6u",  0,  0},
	{ XK_bracketleft, ControlMask|Mod1Mask,  "\033[91;7u",  0,  0},
	{ XK_bracketright,Mod1Mask,              "\033[93;3u",  0,  0},
	{ XK_bracketright,Mod1Mask|ShiftMask,    "\033[93;4u",  0,  0},
	{ XK_bracketright,ControlMask,           "\033[93;5u",  0,  0},
	{ XK_bracketright,ControlMask|ShiftMask, "\033[93;6u",  0,  0},
	{ XK_bracketright,ControlMask|Mod1Mask,  "\033[93;7u",  0,  0},
	{ XK_colon,       Mod1Mask,              "\033[58;3u",  0,  0},
	{ XK_colon,       Mod1Mask|ShiftMask,    "\033[58;4u",  0,  0},
	{ XK_colon,       ControlMask,           "\033[58;5u",  0,  0},
	{ XK_colon,       ControlMask|ShiftMask, "\033[58;6u",  0,  0},
	{ XK_colon,       ControlMask|Mod1Mask,  "\033[58;7u",  0,  0},
	{ XK_comma,       Mod1Mask,              "\033[44;3u",  0,  0},
	{ XK_comma,       Mod1Mask|ShiftMask,    "\033[44;4u",  0,  0},
	{ XK_comma,       ControlMask,           "\033[44;5u",  0,  0},
	{ XK_comma,       ControlMask|ShiftMask, "\033[44;6u",  0,  0},
	{ XK_comma,       ControlMask|Mod1Mask,  "\033[44;7u",  0,  0},
	{ XK_dollar,      Mod1Mask,              "\033[36;3u",  0,  0},
	{ XK_dollar,      Mod1Mask|ShiftMask,    "\033[36;4u",  0,  0},
	{ XK_dollar,      ControlMask,           "\033[36;5u",  0,  0},
	{ XK_dollar,      ControlMask|ShiftMask, "\033[36;6u",  0,  0},
	{ XK_dollar,      ControlMask|Mod1Mask,  "\033[36;7u",  0,  0},
	{ XK_equal,       Mod1Mask,              "\033[61;3u",  0,  0},
	{ XK_equal,       Mod1Mask|ShiftMask,    "\033[61;4u",  0,  0},
	{ XK_equal,       ControlMask,           "\033[61;5u",  0,  0},
	{ XK_equal,       ControlMask|ShiftMask, "\033[61;6u",  0,  0},
	{ XK_equal,       ControlMask|Mod1Mask,  "\033[61;7u",  0,  0},
	{ XK_exclam,      Mod1Mask,              "\033[33;3u",  0,  0},
	{ XK_exclam,      Mod1Mask|ShiftMask,    "\033[33;4u",  0,  0},
	{ XK_exclam,      ControlMask,           "\033[33;5u",  0,  0},
	{ XK_exclam,      ControlMask|ShiftMask, "\033[33;6u",  0,  0},
	{ XK_exclam,      ControlMask|Mod1Mask,  "\033[33;7u",  0,  0},
	{ XK_grave,       Mod1Mask,              "\033[96;3u",  0,  0},
	{ XK_grave,       Mod1Mask|ShiftMask,    "\033[96;4u",  0,  0},
	{ XK_grave,       ControlMask,           "\033[96;5u",  0,  0},
	{ XK_grave,       ControlMask|ShiftMask, "\033[96;6u",  0,  0},
	{ XK_grave,       ControlMask|Mod1Mask,  "\033[96;7u",  0,  0},
	{ XK_greater,     Mod1Mask,              "\033[62;3u",  0,  0},
	{ XK_greater,     Mod1Mask|ShiftMask,    "\033[62;4u",  0,  0},
	{ XK_greater,     ControlMask,           "\033[62;5u",  0,  0},
	{ XK_greater,     ControlMask|ShiftMask, "\033[62;6u",  0,  0},
	{ XK_greater,     ControlMask|Mod1Mask,  "\033[62;7u",  0,  0},
	{ XK_less,        Mod1Mask,              "\033[60;3u",  0,  0},
	{ XK_less,        Mod1Mask|ShiftMask,    "\033[60;4u",  0,  0},
	{ XK_less,        ControlMask,           "\033[60;5u",  0,  0},
	{ XK_less,        ControlMask|ShiftMask, "\033[60;6u",  0,  0},
	{ XK_less,        ControlMask|Mod1Mask,  "\033[60;7u",  0,  0},
	{ XK_minus,       Mod1Mask,              "\033[45;3u",  0,  0},
	{ XK_minus,       Mod1Mask|ShiftMask,    "\033[45;4u",  0,  0},
	{ XK_minus,       ControlMask,           "\033[45;5u",  0,  0},
	{ XK_minus,       ControlMask|ShiftMask, "\033[45;6u",  0,  0},
	{ XK_minus,       ControlMask|Mod1Mask,  "\033[45;7u",  0,  0},
	{ XK_numbersign,  Mod1Mask,              "\033[35;3u",  0,  0},
	{ XK_numbersign,  Mod1Mask|ShiftMask,    "\033[35;4u",  0,  0},
	{ XK_numbersign,  ControlMask,           "\033[35;5u",  0,  0},
	{ XK_numbersign,  ControlMask|ShiftMask, "\033[35;6u",  0,  0},
	{ XK_numbersign,  ControlMask|Mod1Mask,  "\033[35;7u",  0,  0},
	{ XK_parenleft,   Mod1Mask,              "\033[40;3u",  0,  0},
	{ XK_parenleft,   Mod1Mask|ShiftMask,    "\033[40;4u",  0,  0},
	{ XK_parenleft,   ControlMask,           "\033[40;5u",  0,  0},
	{ XK_parenleft,   ControlMask|ShiftMask, "\033[40;6u",  0,  0},
	{ XK_parenleft,   ControlMask|Mod1Mask,  "\033[40;7u",  0,  0},
	{ XK_parenright,  Mod1Mask,              "\033[41;3u",  0,  0},
	{ XK_parenright,  Mod1Mask|ShiftMask,    "\033[41;4u",  0,  0},
	{ XK_parenright,  ControlMask,           "\033[41;5u",  0,  0},
	{ XK_parenright,  ControlMask|ShiftMask, "\033[41;6u",  0,  0},
	{ XK_parenright,  ControlMask|Mod1Mask,  "\033[41;7u",  0,  0},
	{ XK_percent,     Mod1Mask,              "\033[37;3u",  0,  0},
	{ XK_percent,     Mod1Mask|ShiftMask,    "\033[37;4u",  0,  0},
	{ XK_percent,     ControlMask,           "\033[37;5u",  0,  0},
	{ XK_percent,     ControlMask|ShiftMask, "\033[37;6u",  0,  0},
	{ XK_percent,     ControlMask|Mod1Mask,  "\033[37;7u",  0,  0},
	{ XK_period,      Mod1Mask|ShiftMask,    "\033[46;4u",  0,  0},
	{ XK_period,      ControlMask,           "\033[46;5u",  0,  0},
	{ XK_period,      ControlMask|ShiftMask, "\033[46;6u",  0,  0},
	{ XK_period,      ControlMask|Mod1Mask,  "\033[46;7u",  0,  0},
	{ XK_plus,        Mod1Mask,              "\033[43;3u",  0,  0},
	{ XK_plus,        Mod1Mask|ShiftMask,    "\033[43;4u",  0,  0},
	{ XK_plus,        ControlMask,           "\033[43;5u",  0,  0},
	{ XK_plus,        ControlMask|ShiftMask, "\033[43;6u",  0,  0},
	{ XK_plus,        ControlMask|Mod1Mask,  "\033[43;7u",  0,  0},
	{ XK_question,    Mod1Mask,              "\033[63;3u",  0,  0},
	{ XK_question,    Mod1Mask|ShiftMask,    "\033[63;4u",  0,  0},
	{ XK_question,    ControlMask,           "\033[63;5u",  0,  0},
	{ XK_question,    ControlMask|ShiftMask, "\033[63;6u",  0,  0},
	{ XK_question,    ControlMask|Mod1Mask,  "\033[63;7u",  0,  0},
	{ XK_quotedbl,    Mod1Mask,              "\033[34;3u",  0,  0},
	{ XK_quotedbl,    Mod1Mask|ShiftMask,    "\033[34;4u",  0,  0},
	{ XK_quotedbl,    ControlMask,           "\033[34;5u",  0,  0},
	{ XK_quotedbl,    ControlMask|ShiftMask, "\033[34;6u",  0,  0},
	{ XK_quotedbl,    ControlMask|Mod1Mask,  "\033[34;7u",  0,  0},
	{ XK_semicolon,   Mod1Mask,              "\033[59;3u",  0,  0},
	{ XK_semicolon,   Mod1Mask|ShiftMask,    "\033[59;4u",  0,  0},
	{ XK_semicolon,   ControlMask,           "\033[59;5u",  0,  0},
	{ XK_semicolon,   ControlMask|ShiftMask, "\033[59;6u",  0,  0},
	{ XK_semicolon,   ControlMask|Mod1Mask,  "\033[59;7u",  0,  0},
	{ XK_slash,       Mod1Mask,              "\033[47;3u",  0,  0},
	{ XK_slash,       Mod1Mask|ShiftMask,    "\033[47;4u",  0,  0},
	{ XK_slash,       ControlMask,           "\033[47;5u",  0,  0},
	{ XK_slash,       ControlMask|ShiftMask, "\033[47;6u",  0,  0},
	{ XK_slash,       ControlMask|Mod1Mask,  "\033[47;7u",  0,  0},
	{ XK_underscore,  Mod1Mask,              "\033[95;3u",  0,  0},
	{ XK_underscore,  Mod1Mask|ShiftMask,    "\033[95;4u",  0,  0},
	{ XK_underscore,  ControlMask,           "\033[95;5u",  0,  0},
	{ XK_underscore,  ControlMask|ShiftMask, "\033[95;6u",  0,  0},
	{ XK_underscore,  ControlMask|Mod1Mask,  "\033[95;7u",  0,  0},
};

/*
 * Selection types' masks.
 * Use the same masks as usual.
 * Button1Mask is always unset, to make masks match between ButtonPress.
 * ButtonRelease and MotionNotify.
 * If no match is found, regular selection is used.
 */
static uint selmasks[] = {
	[SEL_RECTANGULAR] = Mod1Mask,
};

/*
 * Printable characters in ASCII, used to estimate the advance width
 * of single wide characters.
 */
static char ascii_printable[] =
	" !\"#$%&'()*+,-./0123456789:;<=>?"
	"@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_"
	"`abcdefghijklmnopqrstuvwxyz{|}~";

/**
 * Undercurl style. Set UNDERCURL_STYLE to one of the available styles.
 *
 * Curly: Dunno how to draw it *shrug*
 *  _   _   _   _
 * ( ) ( ) ( ) ( )
 *	 (_) (_) (_) (_)
 *
 * Spiky:
 * /\  /\   /\	/\
 *   \/  \/	  \/
 *
 * Capped:
 *	_     _     _
 * / \   / \   / \
 *    \_/   \_/
 */
// Available styles
#define UNDERCURL_CURLY 0
#define UNDERCURL_SPIKY 1
#define UNDERCURL_CAPPED 2
// Active style
#define UNDERCURL_STYLE UNDERCURL_SPIKY
