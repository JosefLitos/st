/* See LICENSE file for copyright and license details. */

/*
 * appearance
 *
 * font: see http://freedesktop.org/software/fontconfig/fontconfig-user.html
 */
static char *font = "mono:pixelsize=19:antialias=true:autohint=true";
static char *font2[] = {
   "Inconsolata Nerd Font:pixelsize=17:antialias=true:autohint=false",
   "Font Awesome 5 Free Solid:pixelsize=17:antialias=true:autohint=true",
   "JoyPixels:pixelsize=17:antialias=true:autohint=true",
};
static int borderpx = 0;

/*
 * What program is execed by st depends of these precedence rules:
 * 1: program passed with -e
 * 2: utmp option
 * 3: SHELL environment variable
 * 4: value of shell in /etc/passwd
 * 5: value of shell in config.h
 */
static char *shell = "/bin/sh";
char *utmp = NULL;
char *stty_args = "stty raw pass8 nl -echo -iexten -cstopb 38400";

/* identification sequence returned in DA and DECID */
char *vtiden = "\033[?6c";

/* Kerning / character bounding-box multipliers */
static float cwscale = 1;
static float chscale = 0.9;

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
 * interval (in milliseconds) between each successive call to ximspot. This
 * improves terminal performance while not reducing functionality to those
 * whom need XIM support.
 */
int ximspot_update_interval = 2000;

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
 * it#$tabspaces,
 *
 * Secondly make sure your kernel is not expanding tabs. When running `stty
 * -a` »tab0« should appear. You can tell the terminal to not expand tabs by
 *  running following command:
 *
 * stty tabs
 */
unsigned int tabspaces = 2;

/* bg opacity */
float alpha = 0.8;

/* Terminal colors (16 first used in escape sequence) */
static const char *colorname[] = {
	"#101010", "#c82a15", "#669915", "#d8af15", "#1a6ab8", "#9d2088", "#45ac87", "#868380",
	"#4a4846", "#f03522", "#85f022", "#f0e522", "#2798f0", "#d032c5", "#75f0aa", "#f0e8e0",
	[255] = 0,
	/* more colors can be added after 255 to use with DefaultXX */
	"#86e000", /* 256 -> cursor */
	"#555555", /* 257 -> rev cursor*/
	"#101010", /* 258 -> bg */
	"#f0e8e0", /* 259 -> fg */
};

/*
 * Default colors (colorname index)
 * foreground, background, cursor, reverse cursor
 */
unsigned int defaultfg = 259;
unsigned int defaultbg = 258;
unsigned int defaultcs = 256;
unsigned int defaultrcs = 257;

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
 * Default colour and shape of the mouse cursor
 */
static unsigned int mouseshape = XC_xterm;
static unsigned int mousefg = 256;
static unsigned int mousebg = 0;

/*
 * Color used to display font attributes when fontconfig selected a font which
 * doesn't match the ones requested.
 */
static unsigned int defaultattr = 11;

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
   { "font",         STRING,  &font },
   /* { "fontalt0",     STRING,  &font2[0] }, */
   { "color0",       STRING,  &colorname[0] },
   { "color1",       STRING,  &colorname[1] },
   { "color2",       STRING,  &colorname[2] },
   { "color3",       STRING,  &colorname[3] },
   { "color4",       STRING,  &colorname[4] },
   { "color5",       STRING,  &colorname[5] },
   { "color6",       STRING,  &colorname[6] },
   { "color7",       STRING,  &colorname[7] },
   { "color8",       STRING,  &colorname[8] },
   { "color9",       STRING,  &colorname[9] },
   { "color10",      STRING,  &colorname[10] },
   { "color11",      STRING,  &colorname[11] },
   { "color12",      STRING,  &colorname[12] },
   { "color13",      STRING,  &colorname[13] },
   { "color14",      STRING,  &colorname[14] },
   { "color15",      STRING,  &colorname[15] },
   { "background",   STRING,  &colorname[258] },
   { "foreground",   STRING,  &colorname[259] },
   { "cursorColor",  STRING,  &colorname[256] },
   { "termname",     STRING,  &termname },
   { "shell",        STRING,  &shell },
   { "blinktimeout", INTEGER, &blinktimeout },
   { "bellvolume",   INTEGER, &bellvolume },
   { "tabspaces",    INTEGER, &tabspaces },
   { "borderpx",     INTEGER, &borderpx },
   { "cwscale",      FLOAT,   &cwscale },
   { "chscale",      FLOAT,   &chscale },
   { "alpha",        FLOAT,   &alpha },
   { "ximspot_update_interval", INTEGER, &ximspot_update_interval },
};

/*
 * Internal mouse shortcuts.
 * Beware that overloading Button1 will disable the selection.
 */
static MouseShortcut mshortcuts[] = {
   /* button               mask            string */
   { Button4,              XK_NO_MOD,      "\031" },
   { Button5,              XK_NO_MOD,      "\005" },
};

static char *openurlcmd[] = { "/bin/sh", "-c", "st-urlhandler", "externalpipe", NULL };

/* Internal keyboard shortcuts. */
#define MODKEY Mod1Mask
#define TERMMOD (ControlMask|ShiftMask)

MouseKey mkeys[] = {
   /* button      mask            function      argument */
   { Button4,     XK_NO_MOD,      kscrollup,    {.i =  1} },
   { Button5,     XK_NO_MOD,      kscrolldown,  {.i =  1} },
   { Button4,     ControlMask,    kscrollup,    {.i = -1} },
   { Button5,     ControlMask,    kscrolldown,  {.i = -1} },
   { Button4,     TERMMOD,        zoom,         {.f = +1} },
   { Button5,     TERMMOD,        zoom,         {.f = -1} },
   { Button1,     ControlMask,    externalpipe, {.v = openurlcmd } },
};

static Shortcut shortcuts[] = {
   /* mask         keysym         function      argument */
   { XK_ANY_MOD,   XK_Break,      sendbreak,    {.i =  0} },
   { ControlMask,  XK_equal,      zoom,         {.f = +1} },
   { ControlMask,  XK_minus,      zoom,         {.f = -1} },
   { TERMMOD,      XK_equal,      kscrollup,    {.i =  1} },
   { TERMMOD,      XK_minus,      kscrolldown,  {.i =  1} },
   { TERMMOD,      XK_Page_Up,    kscrollup,    {.i = -1} },
   { TERMMOD,      XK_Page_Down,  kscrolldown,  {.i = -1} },
   { MODKEY,       XK_equal,      changealpha,  {.f = +0.1} },
   { MODKEY,       XK_minus,      changealpha,  {.f = -0.1} },
   { MODKEY,       XK_c,          clipcopy,     {.i =  0} },
   { MODKEY,       XK_v,          clippaste,    {.i =  0} },
   /* { MODKEY,       XK_Control_L,   iso14755,     {.i =  0} }, */
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
 * crlf value
 * * 0: no value
 * * > 0: crlf mode is enabled
 * * < 0: crlf mode is disabled
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
   XK_m,
   XK_i,
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
 * Override mouse-select while mask is active (when MODE_MOUSE is set).
 * Note that if you want to use ShiftMask with selmasks, set this to an other
 * modifier, set to 0 to not use it.
 */
static uint forceselmod = ShiftMask;

/*
 * This is the huge key array which defines all compatibility to the Linux
 * world. Please decide about changes wisely.
 */
static Key key[] = {
   /* keysym           mask         string      appkey appcursor */
   { XK_ISO_Left_Tab,  ShiftMask,   "\033[Z",   0,    0},
   { XK_F1,            XK_ANY_MOD,  "\033OP" ,  0,    0},
   { XK_F2,            XK_ANY_MOD,  "\033OQ" ,  0,    0},
   { XK_F3,            XK_ANY_MOD,  "\033OR" ,  0,    0},
   { XK_F4,            XK_ANY_MOD,  "\033OS" ,  0,    0},
   { XK_F5,            XK_ANY_MOD,  "\033[15~", 0,    0},
   { XK_F6,            XK_ANY_MOD,  "\033[17~", 0,    0},
   { XK_F7,            XK_ANY_MOD,  "\033[18~", 0,    0},
   { XK_F8,            XK_ANY_MOD,  "\033[19~", 0,    0},
   { XK_F9,            XK_ANY_MOD,  "\033[20~", 0,    0},
   { XK_F10,           XK_ANY_MOD,  "\033[21~", 0,    0},
   { XK_F11,           XK_ANY_MOD,  "\033[23~", 0,    0},
   { XK_F12,           XK_ANY_MOD,  "\033[24~", 0,    0},
   //used my script to generate
   { XK_Tab,         ShiftMask,                      "\033[9;2u",    0,  0},
   { XK_Tab,         Mod1Mask,                       "\033[9;3u",    0,  0},
   { XK_Tab,         Mod1Mask|ShiftMask,             "\033[9;4u",    0,  0},
   { XK_Tab,         ControlMask,                    "\033[9;5u",    0,  0},
   { XK_Tab,         ControlMask|ShiftMask,          "\033[9;6u",    0,  0},
   { XK_Tab,         Mod1Mask|ControlMask,           "\033[9;7u",    0,  0},
   { XK_Tab,         Mod1Mask|ControlMask|ShiftMask, "\033[9;8u",    0,  0},
   { XK_Return,      ShiftMask,                      "\033[13;2u",   0,  0},
   { XK_Return,      Mod1Mask,                       "\033[13;3u",   0,  0},
   { XK_Return,      Mod1Mask|ShiftMask,             "\033[13;4u",   0,  0},
   { XK_Return,      ControlMask,                    "\033[13;5u",   0,  0},
   { XK_Return,      ControlMask|ShiftMask,          "\033[13;6u",   0,  0},
   { XK_Return,      Mod1Mask|ControlMask,           "\033[13;7u",   0,  0},
   { XK_Return,      Mod1Mask|ControlMask|ShiftMask, "\033[13;8u",   0,  0},
   { XK_Pause,       ShiftMask,                      "\033[18;2u",   0,  0},
   { XK_Pause,       Mod1Mask,                       "\033[18;3u",   0,  0},
   { XK_Pause,       Mod1Mask|ShiftMask,             "\033[18;4u",   0,  0},
   { XK_Pause,       ControlMask,                    "\033[18;5u",   0,  0},
   { XK_Pause,       ControlMask|ShiftMask,          "\033[18;6u",   0,  0},
   { XK_Pause,       Mod1Mask|ControlMask,           "\033[18;7u",   0,  0},
   { XK_Pause,       Mod1Mask|ControlMask|ShiftMask, "\033[18;8u",   0,  0},
   { XK_Escape,      ShiftMask,                      "\033[27;2u",   0,  0},
   { XK_Escape,      Mod1Mask,                       "\033[27;3u",   0,  0},
   { XK_Escape,      Mod1Mask|ShiftMask,             "\033[27;4u",   0,  0},
   { XK_Escape,      ControlMask,                    "\033[27;5u",   0,  0},
   { XK_Escape,      ControlMask|ShiftMask,          "\033[27;6u",   0,  0},
   { XK_Escape,      Mod1Mask|ControlMask,           "\033[27;7u",   0,  0},
   { XK_Escape,      Mod1Mask|ControlMask|ShiftMask, "\033[27;8u",   0,  0},
   { XK_space,       ShiftMask,                      "\033[32;2u",   0,  0},
   { XK_space,       Mod1Mask,                       "\033[32;3u",   0,  0},
   { XK_space,       Mod1Mask|ShiftMask,             "\033[32;4u",   0,  0},
   { XK_space,       ControlMask,                    "\033[32;5u",   0,  0},
   { XK_space,       ControlMask|ShiftMask,          "\033[32;6u",   0,  0},
   { XK_space,       Mod1Mask|ControlMask,           "\033[32;7u",   0,  0},
   { XK_space,       Mod1Mask|ControlMask|ShiftMask, "\033[32;8u",   0,  0},
   { XK_Menu,        ShiftMask,                      "\033[103;2u",  0,  0},
   { XK_Menu,        Mod1Mask,                       "\033[103;3u",  0,  0},
   { XK_Menu,        Mod1Mask|ShiftMask,             "\033[103;4u",  0,  0},
   { XK_Menu,        ControlMask,                    "\033[103;5u",  0,  0},
   { XK_Menu,        ControlMask|ShiftMask,          "\033[103;6u",  0,  0},
   { XK_Menu,        Mod1Mask|ControlMask,           "\033[103;7u",  0,  0},
   { XK_Menu,        Mod1Mask|ControlMask|ShiftMask, "\033[103;8u",  0,  0},
   { XK_BackSpace,   XK_NO_MOD,                      "\177",         0,  0},
   { XK_BackSpace,   ShiftMask,                      "\033[127;2u",  0,  0},
   { XK_BackSpace,   Mod1Mask,                       "\033\177",     0,  0},
   { XK_BackSpace,   Mod1Mask|ShiftMask,             "\033[127;4u",  0,  0},
   { XK_BackSpace,   ControlMask,                    "\033[127;5u",  0,  0},
   { XK_BackSpace,   ControlMask|ShiftMask,          "\033[127;6u",  0,  0},
   { XK_BackSpace,   Mod1Mask|ControlMask,           "\033[127;7u",  0,  0},
   { XK_BackSpace,   Mod1Mask|ControlMask|ShiftMask, "\033[127;8u",  0,  0},
   { XK_Up,          XK_NO_MOD,                      "\033OA",       0,  0},
   { XK_Up,          ShiftMask,                      "\033[1;2A",    0,  0},
   { XK_Up,          Mod1Mask,                       "\033[1;3A",    0,  0},
   { XK_Up,          Mod1Mask|ShiftMask,             "\033[1;4A",    0,  0},
   { XK_Up,          ControlMask,                    "\033[1;5A",    0,  0},
   { XK_Up,          ControlMask|ShiftMask,          "\033[1;6A",    0,  0},
   { XK_Up,          Mod1Mask|ControlMask,           "\033[1;7A",    0,  0},
   { XK_Up,          Mod1Mask|ControlMask|ShiftMask, "\033[1;8A",    0,  0},
   { XK_Down,        XK_NO_MOD,                      "\033OB",       0,  0},
   { XK_Down,        ShiftMask,                      "\033[1;2B",    0,  0},
   { XK_Down,        Mod1Mask,                       "\033[1;3B",    0,  0},
   { XK_Down,        Mod1Mask|ShiftMask,             "\033[1;4B",    0,  0},
   { XK_Down,        ControlMask,                    "\033[1;5B",    0,  0},
   { XK_Down,        ControlMask|ShiftMask,          "\033[1;6B",    0,  0},
   { XK_Down,        Mod1Mask|ControlMask,           "\033[1;7B",    0,  0},
   { XK_Down,        Mod1Mask|ControlMask|ShiftMask, "\033[1;8B",    0,  0},
   { XK_Left,        XK_NO_MOD,                      "\033OD",       0,  0},
   { XK_Left,        ShiftMask,                      "\033[1;2D",    0,  0},
   { XK_Left,        Mod1Mask,                       "\033[1;3D",    0,  0},
   { XK_Left,        Mod1Mask|ShiftMask,             "\033[1;4D",    0,  0},
   { XK_Left,        ControlMask,                    "\033[1;5D",    0,  0},
   { XK_Left,        ControlMask|ShiftMask,          "\033[1;6D",    0,  0},
   { XK_Left,        Mod1Mask|ControlMask,           "\033[1;7D",    0,  0},
   { XK_Left,        Mod1Mask|ControlMask|ShiftMask, "\033[1;8D",    0,  0},
   { XK_Right,       XK_NO_MOD,                      "\033OC",       0,  0},
   { XK_Right,       ShiftMask,                      "\033[1;2C",    0,  0},
   { XK_Right,       Mod1Mask,                       "\033[1;3C",    0,  0},
   { XK_Right,       Mod1Mask|ShiftMask,             "\033[1;4C",    0,  0},
   { XK_Right,       ControlMask,                    "\033[1;5C",    0,  0},
   { XK_Right,       ControlMask|ShiftMask,          "\033[1;6C",    0,  0},
   { XK_Right,       Mod1Mask|ControlMask,           "\033[1;7C",    0,  0},
   { XK_Right,       Mod1Mask|ControlMask|ShiftMask, "\033[1;8C",    0,  0},
   { XK_Home,        XK_NO_MOD,                      "\033[1~",      0,  0},
   { XK_Home,        ShiftMask,                      "\033[1;2H",    0,  0},
   { XK_Home,        Mod1Mask,                       "\033[1;3H",    0,  0},
   { XK_Home,        Mod1Mask|ShiftMask,             "\033[1;4H",    0,  0},
   { XK_Home,        ControlMask,                    "\033[1;5H",    0,  0},
   { XK_Home,        ControlMask|ShiftMask,          "\033[1;6H",    0,  0},
   { XK_Home,        Mod1Mask|ControlMask,           "\033[1;7H",    0,  0},
   { XK_Home,        Mod1Mask|ControlMask|ShiftMask, "\033[1;8H",    0,  0},
   { XK_Insert,      XK_NO_MOD,                      "\033[2~",      0,  0},
   { XK_Insert,      ShiftMask,                      "\033[2;2~",   0,  0},
   { XK_Insert,      Mod1Mask,                       "\033[2;3~",   0,  0},
   { XK_Insert,      Mod1Mask|ShiftMask,             "\033[2;4~",   0,  0},
   { XK_Insert,      ControlMask,                    "\033[2;5~",   0,  0},
   { XK_Insert,      ControlMask|ShiftMask,          "\033[2;6~",   0,  0},
   { XK_Insert,      Mod1Mask|ControlMask,           "\033[2;7~",   0,  0},
   { XK_Insert,      Mod1Mask|ControlMask|ShiftMask, "\033[2;8~",   0,  0},
   { XK_Delete,      XK_NO_MOD,                      "\033[3~",      0,  0},
   { XK_Delete,      ShiftMask,                      "\033[3;2~",  0,  0},
   { XK_Delete,      Mod1Mask,                       "\033[3;3~",  0,  0},
   { XK_Delete,      Mod1Mask|ShiftMask,             "\033[3;4~",  0,  0},
   { XK_Delete,      ControlMask,                    "\033[3;5~",  0,  0},
   { XK_Delete,      ControlMask|ShiftMask,          "\033[3;6~",  0,  0},
   { XK_Delete,      Mod1Mask|ControlMask,           "\033[3;7~",  0,  0},
   { XK_Delete,      Mod1Mask|ControlMask|ShiftMask, "\033[3;8~",  0,  0},
   { XK_End,         XK_NO_MOD,                      "\033[4~",      0,  0},
   { XK_End,         ShiftMask,                      "\033[1;2F",    0,  0},
   { XK_End,         Mod1Mask,                       "\033[1;3F",    0,  0},
   { XK_End,         Mod1Mask|ShiftMask,             "\033[1;4F",    0,  0},
   { XK_End,         ControlMask,                    "\033[1;5F",    0,  0},
   { XK_End,         ControlMask|ShiftMask,          "\033[1;6F",    0,  0},
   { XK_End,         Mod1Mask|ControlMask,           "\033[1;7F",    0,  0},
   { XK_End,         Mod1Mask|ControlMask|ShiftMask, "\033[1;8F",    0,  0},
   { XK_Prior,       XK_NO_MOD,                      "\033[5~",      0,  0},
   { XK_Prior,       ShiftMask,                      "\033[5;2~",    0,  0},
   { XK_Prior,       Mod1Mask,                       "\033[5;3~",    0,  0},
   { XK_Prior,       Mod1Mask|ShiftMask,             "\033[5;4~",    0,  0},
   { XK_Prior,       ControlMask,                    "\033[5;5~",    0,  0},
   { XK_Prior,       ControlMask|ShiftMask,          "\033[5;6~",    0,  0},
   { XK_Prior,       Mod1Mask|ControlMask,           "\033[5;7~",    0,  0},
   { XK_Prior,       Mod1Mask|ControlMask|ShiftMask, "\033[5;8~",    0,  0},
   { XK_Next,        XK_NO_MOD,                      "\033[6~",      0,  0},
   { XK_Next,        ShiftMask,                      "\033[6;2~",    0,  0},
   { XK_Next,        Mod1Mask,                       "\033[6;3~",    0,  0},
   { XK_Next,        Mod1Mask|ShiftMask,             "\033[6;4~",    0,  0},
   { XK_Next,        ControlMask,                    "\033[6;5~",    0,  0},
   { XK_Next,        ControlMask|ShiftMask,          "\033[6;6~",    0,  0},
   { XK_Next,        Mod1Mask|ControlMask,           "\033[6;7~",    0,  0},
   { XK_Next,        Mod1Mask|ControlMask|ShiftMask, "\033[6;8~",    0,  0},

   // libtermkey compatible keyboard input
   { XK_i,            ControlMask,                    "\033[105;5u", 0,  0},
   { XK_i,            Mod1Mask|ControlMask,           "\033[105;7u", 0,  0},
   { XK_m,            ControlMask,                    "\033[109;5u", 0,  0},
   { XK_m,            Mod1Mask|ControlMask,           "\033[109;7u", 0,  0},
   { XK_A,            ControlMask|ShiftMask,          "\033[65;6u",  0,  0},
   { XK_B,            ControlMask|ShiftMask,          "\033[66;6u",  0,  0},
   { XK_C,            ControlMask|ShiftMask,          "\033[67;6u",  0,  0},
   { XK_D,            ControlMask|ShiftMask,          "\033[68;6u",  0,  0},
   { XK_E,            ControlMask|ShiftMask,          "\033[69;6u",  0,  0},
   { XK_F,            ControlMask|ShiftMask,          "\033[70;6u",  0,  0},
   { XK_G,            ControlMask|ShiftMask,          "\033[71;6u",  0,  0},
   { XK_H,            ControlMask|ShiftMask,          "\033[72;6u",  0,  0},
   { XK_I,            ControlMask|ShiftMask,          "\033[73;6u",  0,  0},
   { XK_I,            Mod1Mask|ControlMask|ShiftMask, "\033[73;8u",  0,  0},
   { XK_J,            ControlMask|ShiftMask,          "\033[75;6u",  0,  0},
   { XK_K,            ControlMask|ShiftMask,          "\033[74;6u",  0,  0},
   { XK_L,            ControlMask|ShiftMask,          "\033[76;6u",  0,  0},
   { XK_M,            ControlMask|ShiftMask,          "\033[77;6u",  0,  0},
   { XK_M,            Mod1Mask|ControlMask|ShiftMask, "\033[77;8u",  0,  0},
   { XK_N,            ControlMask|ShiftMask,          "\033[78;6u",  0,  0},
   { XK_O,            ControlMask|ShiftMask,          "\033[79;6u",  0,  0},
   { XK_P,            ControlMask|ShiftMask,          "\033[80;6u",  0,  0},
   { XK_Q,            ControlMask|ShiftMask,          "\033[81;6u",  0,  0},
   { XK_R,            ControlMask|ShiftMask,          "\033[82;6u",  0,  0},
   { XK_S,            ControlMask|ShiftMask,          "\033[83;6u",  0,  0},
   { XK_T,            ControlMask|ShiftMask,          "\033[84;6u",  0,  0},
   { XK_U,            ControlMask|ShiftMask,          "\033[85;6u",  0,  0},
   { XK_V,            ControlMask|ShiftMask,          "\033[86;6u",  0,  0},
   { XK_W,            ControlMask|ShiftMask,          "\033[87;6u",  0,  0},
   { XK_X,            ControlMask|ShiftMask,          "\033[88;6u",  0,  0},
   { XK_Y,            ControlMask|ShiftMask,          "\033[89;6u",  0,  0},
   { XK_Z,            ControlMask|ShiftMask,          "\033[90;6u",  0,  0},
   { XK_Z,            ControlMask|ShiftMask,          "\033[90;6u",  0,  0},
   { XK_0,            ControlMask,                    "\033[48;5u",  0,  0},
   { XK_0,            Mod1Mask|ControlMask,           "\033[48;7u",  0,  0},
   { XK_1,            ControlMask,                    "\033[49;5u",  0,  0},
   { XK_1,            Mod1Mask|ControlMask,           "\033[49;7u",  0,  0},
   { XK_2,            ControlMask,                    "\033[50;5u",  0,  0},
   { XK_2,            Mod1Mask|ControlMask,           "\033[50;7u",  0,  0},
   { XK_3,            ControlMask,                    "\033[51;5u",  0,  0},
   { XK_3,            Mod1Mask|ControlMask,           "\033[51;7u",  0,  0},
   { XK_4,            ControlMask,                    "\033[52;5u",  0,  0},
   { XK_4,            Mod1Mask|ControlMask,           "\033[52;7u",  0,  0},
   { XK_5,            ControlMask,                    "\033[53;5u",  0,  0},
   { XK_5,            Mod1Mask|ControlMask,           "\033[53;7u",  0,  0},
   { XK_6,            ControlMask,                    "\033[54;5u",  0,  0},
   { XK_6,            Mod1Mask|ControlMask,           "\033[54;7u",  0,  0},
   { XK_7,            ControlMask,                    "\033[55;5u",  0,  0},
   { XK_7,            Mod1Mask|ControlMask,           "\033[55;7u",  0,  0},
   { XK_8,            ControlMask,                    "\033[56;5u",  0,  0},
   { XK_8,            Mod1Mask|ControlMask,           "\033[56;7u",  0,  0},
   { XK_9,            ControlMask,                    "\033[57;5u",  0,  0},
   { XK_9,            Mod1Mask|ControlMask,           "\033[57;7u",  0,  0},
   { XK_ampersand,    ControlMask,                    "\033[38;5u",  0,  0},
   { XK_ampersand,    ControlMask|ShiftMask,          "\033[38;6u",  0,  0},
   { XK_ampersand,    Mod1Mask,                       "\033[38;3u",  0,  0},
   { XK_ampersand,    Mod1Mask|ControlMask,           "\033[38;7u",  0,  0},
   { XK_ampersand,    Mod1Mask|ControlMask|ShiftMask, "\033[38;8u",  0,  0},
   { XK_ampersand,    Mod1Mask|ShiftMask,             "\033[38;4u",  0,  0},
   { XK_apostrophe,   ControlMask,                    "\033[39;5u",  0,  0},
   { XK_apostrophe,   ControlMask|ShiftMask,          "\033[39;6u",  0,  0},
   { XK_apostrophe,   Mod1Mask,                       "\033[39;3u",  0,  0},
   { XK_apostrophe,   Mod1Mask|ControlMask,           "\033[39;7u",  0,  0},
   { XK_apostrophe,   Mod1Mask|ControlMask|ShiftMask, "\033[39;8u",  0,  0},
   { XK_apostrophe,   Mod1Mask|ShiftMask,             "\033[39;4u",  0,  0},
   { XK_asciicircum,  ControlMask,                    "\033[94;5u",  0,  0},
   { XK_asciicircum,  ControlMask|ShiftMask,          "\033[94;6u",  0,  0},
   { XK_asciicircum,  Mod1Mask,                       "\033[94;3u",  0,  0},
   { XK_asciicircum,  Mod1Mask|ControlMask,           "\033[94;7u",  0,  0},
   { XK_asciicircum,  Mod1Mask|ControlMask|ShiftMask, "\033[94;8u",  0,  0},
   { XK_asciicircum,  Mod1Mask|ShiftMask,             "\033[94;4u",  0,  0},
   { XK_asciitilde,   ControlMask,                    "\033[126;5u", 0,  0},
   { XK_asciitilde,   ControlMask|ShiftMask,          "\033[126;6u", 0,  0},
   { XK_asciitilde,   Mod1Mask,                       "\033[126;3u", 0,  0},
   { XK_asciitilde,   Mod1Mask|ControlMask,           "\033[126;7u", 0,  0},
   { XK_asciitilde,   Mod1Mask|ControlMask|ShiftMask, "\033[126;8u", 0,  0},
   { XK_asciitilde,   Mod1Mask|ShiftMask,             "\033[126;4u", 0,  0},
   { XK_asterisk,     ControlMask,                    "\033[42;5u",  0,  0},
   { XK_asterisk,     ControlMask|ShiftMask,          "\033[42;6u",  0,  0},
   { XK_asterisk,     Mod1Mask,                       "\033[42;3u",  0,  0},
   { XK_asterisk,     Mod1Mask|ControlMask,           "\033[42;7u",  0,  0},
   { XK_asterisk,     Mod1Mask|ControlMask|ShiftMask, "\033[42;8u",  0,  0},
   { XK_asterisk,     Mod1Mask|ShiftMask,             "\033[42;4u",  0,  0},
   { XK_at,           ControlMask,                    "\033[64;5u",  0,  0},
   { XK_at,           ControlMask|ShiftMask,          "\033[64;6u",  0,  0},
   { XK_at,           Mod1Mask,                       "\033[64;3u",  0,  0},
   { XK_at,           Mod1Mask|ControlMask,           "\033[64;7u",  0,  0},
   { XK_at,           Mod1Mask|ControlMask|ShiftMask, "\033[64;8u",  0,  0},
   { XK_at,           Mod1Mask|ShiftMask,             "\033[64;4u",  0,  0},
   { XK_backslash,    ControlMask,                    "\033[92;5u",  0,  0},
   { XK_backslash,    ControlMask|ShiftMask,          "\033[92;6u",  0,  0},
   { XK_backslash,    Mod1Mask,                       "\033[92;3u",  0,  0},
   { XK_backslash,    Mod1Mask|ControlMask,           "\033[92;7u",  0,  0},
   { XK_backslash,    Mod1Mask|ControlMask|ShiftMask, "\033[92;8u",  0,  0},
   { XK_backslash,    Mod1Mask|ShiftMask,             "\033[92;4u",  0,  0},
   { XK_bar,          ControlMask,                    "\033[124;5u", 0,  0},
   { XK_bar,          ControlMask|ShiftMask,          "\033[124;6u", 0,  0},
   { XK_bar,          Mod1Mask,                       "\033[124;3u", 0,  0},
   { XK_bar,          Mod1Mask|ControlMask,           "\033[124;7u", 0,  0},
   { XK_bar,          Mod1Mask|ControlMask|ShiftMask, "\033[124;8u", 0,  0},
   { XK_bar,          Mod1Mask|ShiftMask,             "\033[124;4u", 0,  0},
   { XK_braceleft,    ControlMask,                    "\033[123;5u", 0,  0},
   { XK_braceleft,    ControlMask|ShiftMask,          "\033[123;6u", 0,  0},
   { XK_braceleft,    Mod1Mask,                       "\033[123;3u", 0,  0},
   { XK_braceleft,    Mod1Mask|ControlMask,           "\033[123;7u", 0,  0},
   { XK_braceleft,    Mod1Mask|ControlMask|ShiftMask, "\033[123;8u", 0,  0},
   { XK_braceleft,    Mod1Mask|ShiftMask,             "\033[123;4u", 0,  0},
   { XK_braceright,   ControlMask,                    "\033[125;5u", 0,  0},
   { XK_braceright,   ControlMask|ShiftMask,          "\033[125;6u", 0,  0},
   { XK_braceright,   Mod1Mask,                       "\033[125;3u", 0,  0},
   { XK_braceright,   Mod1Mask|ControlMask,           "\033[125;7u", 0,  0},
   { XK_braceright,   Mod1Mask|ControlMask|ShiftMask, "\033[125;8u", 0,  0},
   { XK_braceright,   Mod1Mask|ShiftMask,             "\033[125;4u", 0,  0},
   { XK_bracketleft,  ControlMask,                    "\033[91;5u",  0,  0},
   { XK_bracketleft,  ControlMask|ShiftMask,          "\033[91;6u",  0,  0},
   { XK_bracketleft,  Mod1Mask,                       "\033[91;3u",  0,  0},
   { XK_bracketleft,  Mod1Mask|ControlMask,           "\033[91;7u",  0,  0},
   { XK_bracketleft,  Mod1Mask|ControlMask|ShiftMask, "\033[91;8u",  0,  0},
   { XK_bracketleft,  Mod1Mask|ShiftMask,             "\033[91;4u",  0,  0},
   { XK_bracketright, ControlMask,                    "\033[93;5u",  0,  0},
   { XK_bracketright, ControlMask|ShiftMask,          "\033[93;6u",  0,  0},
   { XK_bracketright, Mod1Mask,                       "\033[93;3u",  0,  0},
   { XK_bracketright, Mod1Mask|ControlMask,           "\033[93;7u",  0,  0},
   { XK_bracketright, Mod1Mask|ControlMask|ShiftMask, "\033[93;8u",  0,  0},
   { XK_bracketright, Mod1Mask|ShiftMask,             "\033[93;4u",  0,  0},
   { XK_colon,        ControlMask,                    "\033[58;5u",  0,  0},
   { XK_colon,        ControlMask|ShiftMask,          "\033[58;6u",  0,  0},
   { XK_colon,        Mod1Mask,                       "\033[58;3u",  0,  0},
   { XK_colon,        Mod1Mask|ControlMask,           "\033[58;7u",  0,  0},
   { XK_colon,        Mod1Mask|ControlMask|ShiftMask, "\033[58;8u",  0,  0},
   { XK_colon,        Mod1Mask|ShiftMask,             "\033[58;4u",  0,  0},
   { XK_comma,        ControlMask,                    "\033[44;5u",  0,  0},
   { XK_comma,        ControlMask|ShiftMask,          "\033[44;6u",  0,  0},
   { XK_comma,        Mod1Mask,                       "\033[44;3u",  0,  0},
   { XK_comma,        Mod1Mask|ControlMask,           "\033[44;7u",  0,  0},
   { XK_comma,        Mod1Mask|ControlMask|ShiftMask, "\033[44;8u",  0,  0},
   { XK_comma,        Mod1Mask|ShiftMask,             "\033[44;4u",  0,  0},
   { XK_dollar,       ControlMask,                    "\033[36;5u",  0,  0},
   { XK_dollar,       ControlMask|ShiftMask,          "\033[36;6u",  0,  0},
   { XK_dollar,       Mod1Mask,                       "\033[36;3u",  0,  0},
   { XK_dollar,       Mod1Mask|ControlMask,           "\033[36;7u",  0,  0},
   { XK_dollar,       Mod1Mask|ControlMask|ShiftMask, "\033[36;8u",  0,  0},
   { XK_dollar,       Mod1Mask|ShiftMask,             "\033[36;4u",  0,  0},
   { XK_equal,        ControlMask,                    "\033[61;5u",  0,  0},
   { XK_equal,        ControlMask|ShiftMask,          "\033[61;6u",  0,  0},
   { XK_equal,        Mod1Mask,                       "\033[61;3u",  0,  0},
   { XK_equal,        Mod1Mask|ControlMask,           "\033[61;7u",  0,  0},
   { XK_equal,        Mod1Mask|ControlMask|ShiftMask, "\033[61;8u",  0,  0},
   { XK_equal,        Mod1Mask|ShiftMask,             "\033[61;4u",  0,  0},
   { XK_exclam,       ControlMask,                    "\033[33;5u",  0,  0},
   { XK_exclam,       ControlMask|ShiftMask,          "\033[33;6u",  0,  0},
   { XK_exclam,       Mod1Mask,                       "\033[33;3u",  0,  0},
   { XK_exclam,       Mod1Mask|ControlMask,           "\033[33;7u",  0,  0},
   { XK_exclam,       Mod1Mask|ControlMask|ShiftMask, "\033[33;8u",  0,  0},
   { XK_exclam,       Mod1Mask|ShiftMask,             "\033[33;4u",  0,  0},
   { XK_grave,        ControlMask,                    "\033[96;5u",  0,  0},
   { XK_grave,        ControlMask|ShiftMask,          "\033[96;6u",  0,  0},
   { XK_grave,        Mod1Mask,                       "\033[96;3u",  0,  0},
   { XK_grave,        Mod1Mask|ControlMask,           "\033[96;7u",  0,  0},
   { XK_grave,        Mod1Mask|ControlMask|ShiftMask, "\033[96;8u",  0,  0},
   { XK_grave,        Mod1Mask|ShiftMask,             "\033[96;4u",  0,  0},
   { XK_greater,      ControlMask,                    "\033[62;5u",  0,  0},
   { XK_greater,      ControlMask|ShiftMask,          "\033[62;6u",  0,  0},
   { XK_greater,      Mod1Mask,                       "\033[62;3u",  0,  0},
   { XK_greater,      Mod1Mask|ControlMask,           "\033[62;7u",  0,  0},
   { XK_greater,      Mod1Mask|ControlMask|ShiftMask, "\033[62;8u",  0,  0},
   { XK_greater,      Mod1Mask|ShiftMask,             "\033[62;4u",  0,  0},
   { XK_less,         ControlMask,                    "\033[60;5u",  0,  0},
   { XK_less,         ControlMask|ShiftMask,          "\033[60;6u",  0,  0},
   { XK_less,         Mod1Mask,                       "\033[60;3u",  0,  0},
   { XK_less,         Mod1Mask|ControlMask,           "\033[60;7u",  0,  0},
   { XK_less,         Mod1Mask|ControlMask|ShiftMask, "\033[60;8u",  0,  0},
   { XK_less,         Mod1Mask|ShiftMask,             "\033[60;4u",  0,  0},
   { XK_minus,        ControlMask,                    "\033[45;5u",  0,  0},
   { XK_minus,        ControlMask|ShiftMask,          "\033[45;6u",  0,  0},
   { XK_minus,        Mod1Mask,                       "\033[45;3u",  0,  0},
   { XK_minus,        Mod1Mask|ControlMask,           "\033[45;7u",  0,  0},
   { XK_minus,        Mod1Mask|ControlMask|ShiftMask, "\033[45;8u",  0,  0},
   { XK_minus,        Mod1Mask|ShiftMask,             "\033[45;4u",  0,  0},
   { XK_numbersign,   ControlMask,                    "\033[35;5u",  0,  0},
   { XK_numbersign,   ControlMask|ShiftMask,          "\033[35;6u",  0,  0},
   { XK_numbersign,   Mod1Mask,                       "\033[35;3u",  0,  0},
   { XK_numbersign,   Mod1Mask|ControlMask,           "\033[35;7u",  0,  0},
   { XK_numbersign,   Mod1Mask|ControlMask|ShiftMask, "\033[35;8u",  0,  0},
   { XK_numbersign,   Mod1Mask|ShiftMask,             "\033[35;4u",  0,  0},
   { XK_parenleft,    ControlMask,                    "\033[40;5u",  0,  0},
   { XK_parenleft,    ControlMask|ShiftMask,          "\033[40;6u",  0,  0},
   { XK_parenleft,    Mod1Mask,                       "\033[40;3u",  0,  0},
   { XK_parenleft,    Mod1Mask|ControlMask,           "\033[40;7u",  0,  0},
   { XK_parenleft,    Mod1Mask|ControlMask|ShiftMask, "\033[40;8u",  0,  0},
   { XK_parenleft,    Mod1Mask|ShiftMask,             "\033[40;4u",  0,  0},
   { XK_parenright,   ControlMask,                    "\033[41;5u",  0,  0},
   { XK_parenright,   ControlMask|ShiftMask,          "\033[41;6u",  0,  0},
   { XK_parenright,   Mod1Mask,                       "\033[41;3u",  0,  0},
   { XK_parenright,   Mod1Mask|ControlMask,           "\033[41;7u",  0,  0},
   { XK_parenright,   Mod1Mask|ControlMask|ShiftMask, "\033[41;8u",  0,  0},
   { XK_parenright,   Mod1Mask|ShiftMask,             "\033[41;4u",  0,  0},
   { XK_percent,      ControlMask,                    "\033[37;5u",  0,  0},
   { XK_percent,      ControlMask|ShiftMask,          "\033[37;6u",  0,  0},
   { XK_percent,      Mod1Mask,                       "\033[37;3u",  0,  0},
   { XK_percent,      Mod1Mask|ControlMask,           "\033[37;7u",  0,  0},
   { XK_percent,      Mod1Mask|ControlMask|ShiftMask, "\033[37;8u",  0,  0},
   { XK_percent,      Mod1Mask|ShiftMask,             "\033[37;4u",  0,  0},
   { XK_period,       ControlMask,                    "\033[46;5u",  0,  0},
   { XK_period,       ControlMask|ShiftMask,          "\033[46;6u",  0,  0},
   { XK_period,       Mod1Mask|ControlMask,           "\033[46;7u",  0,  0},
   { XK_period,       Mod1Mask|ControlMask|ShiftMask, "\033[46;8u",  0,  0},
   { XK_period,       Mod1Mask|ShiftMask,             "\033[46;4u",  0,  0},
   { XK_plus,         ControlMask,                    "\033[43;5u",  0,  0},
   { XK_plus,         ControlMask|ShiftMask,          "\033[43;6u",  0,  0},
   { XK_plus,         Mod1Mask,                       "\033[43;3u",  0,  0},
   { XK_plus,         Mod1Mask|ControlMask,           "\033[43;7u",  0,  0},
   { XK_plus,         Mod1Mask|ControlMask|ShiftMask, "\033[43;8u",  0,  0},
   { XK_plus,         Mod1Mask|ShiftMask,             "\033[43;4u",  0,  0},
   { XK_question,     ControlMask,                    "\033[63;5u",  0,  0},
   { XK_question,     ControlMask|ShiftMask,          "\033[63;6u",  0,  0},
   { XK_question,     Mod1Mask,                       "\033[63;3u",  0,  0},
   { XK_question,     Mod1Mask|ControlMask,           "\033[63;7u",  0,  0},
   { XK_question,     Mod1Mask|ControlMask|ShiftMask, "\033[63;8u",  0,  0},
   { XK_question,     Mod1Mask|ShiftMask,             "\033[63;4u",  0,  0},
   { XK_quotedbl,     ControlMask,                    "\033[34;5u",  0,  0},
   { XK_quotedbl,     ControlMask|ShiftMask,          "\033[34;6u",  0,  0},
   { XK_quotedbl,     Mod1Mask,                       "\033[34;3u",  0,  0},
   { XK_quotedbl,     Mod1Mask|ControlMask,           "\033[34;7u",  0,  0},
   { XK_quotedbl,     Mod1Mask|ControlMask|ShiftMask, "\033[34;8u",  0,  0},
   { XK_quotedbl,     Mod1Mask|ShiftMask,             "\033[34;4u",  0,  0},
   { XK_semicolon,    ControlMask,                    "\033[59;5u",  0,  0},
   { XK_semicolon,    ControlMask|ShiftMask,          "\033[59;6u",  0,  0},
   { XK_semicolon,    Mod1Mask,                       "\033[59;3u",  0,  0},
   { XK_semicolon,    Mod1Mask|ControlMask,           "\033[59;7u",  0,  0},
   { XK_semicolon,    Mod1Mask|ControlMask|ShiftMask, "\033[59;8u",  0,  0},
   { XK_semicolon,    Mod1Mask|ShiftMask,             "\033[59;4u",  0,  0},
   { XK_slash,        ControlMask|ShiftMask,          "\033[47;6u",  0,  0},
   { XK_slash,        Mod1Mask,                       "\033[47;3u",  0,  0},
   { XK_slash,        Mod1Mask|ControlMask,           "\033[47;7u",  0,  0},
   { XK_slash,        Mod1Mask|ControlMask|ShiftMask, "\033[47;8u",  0,  0},
   { XK_slash,        Mod1Mask|ShiftMask,             "\033[47;4u",  0,  0},
   { XK_underscore,   ControlMask,                    "\033[95;5u",  0,  0},
   { XK_underscore,   ControlMask|ShiftMask,          "\033[95;6u",  0,  0},
   { XK_underscore,   Mod1Mask,                       "\033[95;3u",  0,  0},
   { XK_underscore,   Mod1Mask|ControlMask,           "\033[95;7u",  0,  0},
   { XK_underscore,   Mod1Mask|ControlMask|ShiftMask, "\033[95;8u",  0,  0},
   { XK_underscore,   Mod1Mask|ShiftMask,             "\033[95;4u",  0,  0},
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
