///---User configurable stuff---///
#include <X11/XF86keysym.h>
///---Modifiers---///
#define MOD             XCB_MOD_MASK_4       /* Super/Windows key  or check xmodmap(1) with -pm*/
///--Speed---///
/* Move this many pixels when moving or resizing with keyboard unless the window has hints saying otherwise.
 *0)move step slow   1)move step fast
 *2)mouse slow       3)mouse fast     */
static const uint16_t movements[] = {20,40,15,400};
/* resize by line like in mcwm -- jmbi */
static const bool     resize_by_line          = true;
/* the ratio used when resizing and keeping the aspect */
static const float    resize_keep_aspect_ratio= 1.03;
///---Offsets---///
/*0)offsetx          1)offsety
 *2)maxwidth         3)maxheight */
static const uint8_t offsets[] = {0,0,0,0};
///---Colors---///
/*0)focuscol         1)unfocuscol
 *2)fixedcol         3)unkilcol
 *4)fixedunkilcol    5)outerbordercol
 *6)emptycol         */
static const char *colors[] = {"#B2CCD6","#546E7A","#C3E88D","#F07178","#F78C6C","#263238","#263238"};
/* if this is set to true the inner border and outer borders colors will be swapped */
static const bool inverted_colors = false;
///---Cursor---///
/* default position of the cursor:
 * correct values are:
 * TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, MIDDLE
 * All these are relative to the current window. */
#define CURSOR_POSITION MIDDLE
///---Borders---///
/*0) Outer border size. If you put this negative it will be a square.
 *1) Full borderwidth    2) Magnet border size    
 *3) Resize border size  */
static const uint8_t borders[] = {5, 7, 2, 3};
/* Windows that won't have a border.*/
#define LOOK_INTO "WM_NAME"
static const char *ignore_names[] = {"bar", "xclock"};
///--Menus and Programs---///
static const char *menucmd[]   = { "", NULL };
// static const char *gmrun[]     = { "/usr/bin/gmrun",NULL};
static const char *terminal[]  = { "urxvtc", NULL };
static const char *rofir[]     = {"/home/dillon/Scripts/Rofi.sh", "-r", NULL};
static const char *rofiw[]     = {"/home/dillon/Scripts/Rofi.sh", "-w", NULL};

///--Brightness keys---///
static const char *bri_up[] = {"brightness", "up", NULL};
static const char *bri_down[] = {"brightness", "down", NULL};
///--Volume Keys---///
static const char *vol_up[] = {"volume", "up", NULL};
static const char *vol_down[] = {"volume", "down", NULL};
static const char *vol_mute[] = {"volume", "mute", NULL};
///--Multimedia Keys---///
static const char *media_playpause[] = {"playerctl", "play-pause", NULL};
static const char *media_next[] = {"playerctl", "next", NULL};
static const char *media_prev[] = {"playerctl", "previous", NULL};
///--MPD Keys---///
static const char *mpd_playpause[] = {"mpc", "toggle", NULL};
static const char *mpd_next[] = {"mpc", "next", NULL};
static const char *mpd_prev[] = {"mpc", "prev", NULL};
///--Screenshot Keys---///
static const char *scr_normal[] = {"scr", NULL};
static const char *scr_focused[] = {"scr", "foc", NULL};
static const char *betterlock[] = {"betterlockscreen", "-l", NULL};




static const char *click1[]    = { "xdotool","click", "1", NULL };
static const char *click2[]    = { "xdotool","click", "2", NULL };
static const char *click3[]    = { "xdotool","click", "3", NULL };
///--Custom foo---///
static void halfandcentered(const Arg *arg)
{
	Arg arg2 = {.i=2};
	maxhalf(&arg2);
	Arg arg3 = {.i=0};
	teleport(&arg3);
}
///---Shortcuts---///
/* Check /usr/include/X11/keysymdef.h for the list of all keys
 * 0x000000 is for no modkey
 * For AZERTY keyboards XK_1...0 should be replaced by :
 *      DESKTOPCHANGE(     XK_ampersand,                     0)
 *      DESKTOPCHANGE(     XK_eacute,                        1)
 *      DESKTOPCHANGE(     XK_quotedbl,                      2)
 *      DESKTOPCHANGE(     XK_apostrophe,                    3)
 *      DESKTOPCHANGE(     XK_parenleft,                     4)
 *      DESKTOPCHANGE(     XK_minus,                         5)
 *      DESKTOPCHANGE(     XK_egrave,                        6)
 *      DESKTOPCHANGE(     XK_underscore,                    7)
 *      DESKTOPCHANGE(     XK_ccedilla,                      8)
 *      DESKTOPCHANGE(     XK_agrave,                        9)*
 */
#define DESKTOPCHANGE(K,N) \
{  MOD ,             K,              changeworkspace, {.i=N}}, \
{  MOD |SHIFT,       K,              sendtoworkspace, {.i=N}},
static key keys[] = {
    /* modifier           key            function           argument */
    // Focus to next/previous window
    {  MOD ,              XK_Tab,        focusnext,         {.i=0}},
    {  MOD |SHIFT,        XK_Tab,        focusnext,         {.i=1}},
    // Kill a window
    {  MOD ,              XK_q,          deletewin,         {.i=0}},
    // Resize a window
    {  MOD |SHIFT,        XK_k,          resizestep,        {.i=2}},
    {  MOD |SHIFT,        XK_j,          resizestep,        {.i=1}},
    {  MOD |SHIFT,        XK_l,          resizestep,        {.i=3}},
    {  MOD |SHIFT,        XK_h,          resizestep,        {.i=0}},
    // Resize a window slower
    {  MOD |SHIFT|CONTROL,XK_k,          resizestep,        {.i=6}},
    {  MOD |SHIFT|CONTROL,XK_j,          resizestep,        {.i=5}},
    {  MOD |SHIFT|CONTROL,XK_l,          resizestep,        {.i=7}},
    {  MOD |SHIFT|CONTROL,XK_h,          resizestep,        {.i=4}},
    // Move a window
    {  MOD ,              XK_k,          movestep,          {.i=2}},
    {  MOD ,              XK_j,          movestep,          {.i=1}},
    {  MOD ,              XK_l,          movestep,          {.i=3}},
    {  MOD ,              XK_h,          movestep,          {.i=0}},
    // Move a window slower
    {  MOD |CONTROL,      XK_k,          movestep,          {.i=6}},
    {  MOD |CONTROL,      XK_j,          movestep,          {.i=5}},
    {  MOD |CONTROL,      XK_l,          movestep,          {.i=7}},
    {  MOD |CONTROL,      XK_h,          movestep,          {.i=4}},
    // Teleport the window to an area of the screen.
    // Center:
    {  MOD ,              XK_g,          teleport,          {.i=0}},
    // Center y:
    {  MOD |SHIFT,        XK_g,          teleport,          {.i=3}},
    // Center x:
    {  MOD |CONTROL,      XK_g,          teleport,          {.i=-3}},
    // Top left:
    {  MOD ,              XK_y,          teleport,          {.i=2}},
    // Top right:
    {  MOD ,              XK_u,          teleport,          {.i=-2}},
    // Bottom left:
    {  MOD ,              XK_b,          teleport,          {.i=1}},
    // Bottom right:
    {  MOD ,              XK_n,          teleport,          {.i=-1}},
    // Resize while keeping the window aspect
    {  MOD ,              XK_Home,       resizestep_aspect, {.i=0}},
    {  MOD ,              XK_End,        resizestep_aspect, {.i=1}},
    // Full screen window without borders
    {  MOD ,              XK_x,         maximize,          {.i=0}},
    //Full screen window without borders overiding offsets
    {  MOD |SHIFT ,       XK_x,          maximize,          {.i=1}},
    // Maximize vertically
    {  MOD ,              XK_m,          maxvert_hor,       {.i=1}},
    // Maximize horizontally
    {  MOD |SHIFT,        XK_m,          maxvert_hor,       {.i=0}},
    // Maximize and move
    // vertically left
    {  MOD |SHIFT,        XK_y,          maxhalf,           {.i=2}},
    // vertically right
    {  MOD |SHIFT,        XK_u,          maxhalf,           {.i=1}},
    // horizontally left
    {  MOD |SHIFT,        XK_b,          maxhalf,           {.i=-1}},
    // horizontally right
    {  MOD |SHIFT,        XK_n,          maxhalf,           {.i=-2}},
    //fold half vertically
    {  MOD |SHIFT|CONTROL,XK_y,          maxhalf,           {.i=4}},
    //fold half horizontally
    {  MOD |SHIFT|CONTROL,XK_b,          maxhalf,           {.i=-4}},
    //unfold vertically
    {  MOD |SHIFT|CONTROL,XK_u,          maxhalf,           {.i=3}},
    //unfold horizontally
    {  MOD |SHIFT|CONTROL,XK_n,          maxhalf,           {.i=-3}},
    // Next/Previous screen
    {  MOD ,              XK_comma,      changescreen,      {.i=1}},
    {  MOD ,              XK_period,     changescreen,      {.i=0}},
    // Raise or lower a window
    {  MOD ,              XK_r,          raiseorlower,      {.i=0}},
    // Next/Previous workspace
    {  MOD ,              XK_v,          nextworkspace,     {.i=0}},
    {  MOD ,              XK_c,          prevworkspace,     {.i=0}},
    // Move to Next/Previous workspace
    {  MOD |SHIFT ,       XK_v,          sendtonextworkspace,{.i=0}},
    {  MOD |SHIFT ,       XK_c,          sendtoprevworkspace,{.i=0}},
    // Iconify the window
    {  MOD ,              XK_i,          hide,              {.i=0}},
    // Make the window unkillable
    {  MOD ,              XK_a,          unkillable,        {.i=0}},
    // Make the window appear always on top
    {  MOD,               XK_t,          always_on_top,     {.i=0}},
    // Make the window stay on all workspaces
    {  MOD ,              XK_f,          fix,               {.i=0}},
    // Move the cursor
    {  MOD ,              XK_Up,         cursor_move,       {.i=4}},
    {  MOD ,              XK_Down,       cursor_move,       {.i=5}},
    {  MOD ,              XK_Right,      cursor_move,       {.i=6}},
    {  MOD ,              XK_Left,       cursor_move,       {.i=7}},
    // Move the cursor faster
    {  MOD |SHIFT,        XK_Up,         cursor_move,       {.i=0}},
    {  MOD |SHIFT,        XK_Down,       cursor_move,       {.i=1}},
    {  MOD |SHIFT,        XK_Right,      cursor_move,       {.i=2}},
    {  MOD |SHIFT,        XK_Left,       cursor_move,       {.i=3}},
    // Start programs
    {  MOD ,              XK_Return,     start,             {.com = terminal}},
    {  MOD ,              XK_i,          start,             {.com = rofiw}},
    {  MOD ,              XK_d,          start,             {.com = rofir}},
    
    
    
    // Lockscreen
    {  MOD |SHIFT,        XK_p,          start,             {.com = betterlock} },
    // Brightness Keys
    {  0 ,                XF86XK_MonBrightnessUp,         start,             {.com = bri_up} },
    {  0 ,                XF86XK_MonBrightnessDown,       start,             {.com = bri_down} },
    // Volume Keys
    {  0 ,                XF86XK_AudioMute,               start,             {.com = vol_mute} },
    {  0 ,                XF86XK_AudioLowerVolume,        start,             {.com = vol_down} },
    {  0 ,                XF86XK_AudioRaiseVolume,        start,             {.com = vol_up} },
    // Media Keys
    {  0 ,                XF86XK_AudioPlay,               start,             {.com = media_playpause} },
    {  0 ,                XF86XK_AudioPrev,               start,             {.com = media_prev} },
    {  0 ,                XF86XK_AudioNext,               start,             {.com = media_next} },
    // Mpd Media Keys
    {  SHIFT ,            XF86XK_AudioPlay,               start,             {.com = mpd_playpause} },
    {  SHIFT ,            XF86XK_AudioPrev,               start,             {.com = mpd_prev} },
    {  SHIFT ,            XF86XK_AudioNext,               start,             {.com = mpd_next} },
    // Screenshot
    {  0 ,                XK_Print,                       start,             {.com = scr_normal} },
    { MOD ,               XK_Print,                       start,             {.com = scr_focused} },



    // {  MOD ,              XK_w,          start,             {.com = menucmd}},
    // {  MOD |SHIFT,        XK_w,          start,             {.com = gmrun}},
    // Exit or restart 2bwm
    {  MOD |CONTROL,      XK_q,          twobwm_exit,         {.i=0}},
    {  MOD |CONTROL,      XK_r,          twobwm_restart,      {.i=0}},
    {  MOD ,              XK_space,      halfandcentered,    {.i=0}},
    // Fake clicks using xdotool
    {  MOD |CONTROL,      XK_Up,         start,             {.com = click1}},
    {  MOD |CONTROL,      XK_Down,       start,             {.com = click2}},
    {  MOD |CONTROL,      XK_Right,      start,             {.com = click3}},
    // Change current workspace
       DESKTOPCHANGE(     XK_1,                             0)
       DESKTOPCHANGE(     XK_2,                             1)
       DESKTOPCHANGE(     XK_3,                             2)
       DESKTOPCHANGE(     XK_4,                             3)
       DESKTOPCHANGE(     XK_5,                             4)
       DESKTOPCHANGE(     XK_6,                             5)
       DESKTOPCHANGE(     XK_7,                             6)
       DESKTOPCHANGE(     XK_8,                             7)
       DESKTOPCHANGE(     XK_9,                             8)
       DESKTOPCHANGE(     XK_0,                             9)
};
static Button buttons[] = {
    {  MOD        ,XCB_BUTTON_INDEX_1,     mousemotion,   {.i=TWOBWM_MOVE}},
    {  MOD        ,XCB_BUTTON_INDEX_3,     mousemotion,   {.i=TWOBWM_RESIZE}},
    {  MOD|CONTROL,XCB_BUTTON_INDEX_3,     start,         {.com = menucmd}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_1,     changeworkspace, {.i=0}},
    {  MOD|SHIFT,  XCB_BUTTON_INDEX_3,     changeworkspace, {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_1,     changescreen,    {.i=1}},
    {  MOD|ALT,    XCB_BUTTON_INDEX_3,     changescreen,    {.i=0}}
};
