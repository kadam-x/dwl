#define COLOR(hex)                                                             \
  {((hex >> 24) & 0xFF) / 255.0f, ((hex >> 16) & 0xFF) / 255.0f,               \
   ((hex >> 8) & 0xFF) / 255.0f, (hex & 0xFF) / 255.0f}

/* appearance */
static const int sloppyfocus = 1;
static const int bypass_surface_visibility = 0;
static const unsigned int borderpx = 3;
static const unsigned int systrayspacing = 2;
static const int showsystray = 1;
static const int showbar = 1;
static const int topbar = 1;
static const char *fonts[] = {"monospace:size=15"};
static const float rootcolor[] = COLOR(0x000000ff);
static const float fullscreen_bg[] = {0.0f, 0.0f, 0.0f, 1.0f};

/* colors */
#define COLOR_MAIN 0x0b2c38ff
#define COLOR_DARK 0x0f0f0fff
#define COLOR_FG 0xbbbbbbff
#define COLOR_BG 0x0c171bff
#define COLOR_URGENT 0x770000ff

static uint32_t colors[][3] = {
    [SchemeNorm] =
        {
            COLOR_FG,
            COLOR_BG,
            COLOR_DARK,
        },
    [SchemeSel] =
        {
            0xffffffff,
            COLOR_MAIN,
            COLOR_MAIN,
        },
    [SchemeUrg] =
        {
            0xffffffff,
            COLOR_BG,
            COLOR_URGENT,
        },
};

/* tagging */
static char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

/* logging */
static int log_level = WLR_ERROR;

static const Rule rules[] = {
    {"Gimp_EXAMPLE", NULL, 0, 1, -1},
    {"firefox_EXAMPLE", NULL, 1 << 8, 0, -1},
    {"yazi", NULL, 0, 1, -1},
};

/* layout(s) */
static const Layout layouts[] = {
    {"[]=", tile},
    {"><>", NULL},
};

/* monitors */
static const MonitorRule monrules[] = {
    {NULL, 0.55f, 1, 1, &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, -1, -1},
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
    .layout = "us,hu",
    .options = "grp:win_space_toggle",
};

static const int repeat_rate = 35;
static const int repeat_delay = 200;

/* Trackpad */
static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 1;
static const int natural_scrolling = 0;
static const int disable_while_typing = 1;
static const int left_handed = 0;
static const int middle_button_emulation = 0;

static const enum libinput_config_scroll_method scroll_method =
    LIBINPUT_CONFIG_SCROLL_2FG;

static const enum libinput_config_click_method click_method =
    LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

static const enum libinput_config_accel_profile accel_profile =
    LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT;

static const double accel_speed = 0.0;

static const enum libinput_config_tap_button_map button_map =
    LIBINPUT_CONFIG_TAP_MAP_LRM;

/* MODKEY */
#define MODKEY WLR_MODIFIER_LOGO

static void tagandview(const Arg *arg) {
  tag(arg);
  view(arg);
}

#define TAGKEYS(KEY, SKEY, TAG)                                                \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | WLR_MODIFIER_SHIFT, SKEY, tag, {.ui = 1 << TAG}}, {            \
    MODKEY | WLR_MODIFIER_CTRL, KEY, tagandview, { .ui = 1 << TAG }            \
  }

#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

#define BEMENU_OPTS                                                            \
  "-l 10 --fn \"monospace 16\" --nb \"#0c171b\" --fb \"#0c171b\" "             \
  "--tb \"#0c171b\" --ab \"#0c171b\" --hb \"#0b2c38\" "                        \
  "--sb \"#0b2c38\" --scb \"#0b2c38\""

/* commands */
static const char *termcmd[] = {"foot", NULL};

static const char *menucmd[] = {
    "sh", "-c", "env BEMENU_OPTS='" BEMENU_OPTS "' bemenu-run", NULL};

static const char *dmenucmd[] = {
    "sh", "-c", "env BEMENU_OPTS='" BEMENU_OPTS "' bemenu-run", NULL};

static const char *yazicmd[] = {"foot", "--app-id", "yazi", "-e", "yazi", NULL};

static const char *pulsemixercmd[] = {"foot", "--app-id",   "pulsemixer",
                                      "-e",   "pulsemixer", NULL};

static const char *hyprpickercmd[] = {"hyprpicker", "-a", NULL};

static const Key keys[] = {
    {MODKEY, XKB_KEY_a, spawn, {.v = menucmd}},
    {MODKEY, XKB_KEY_Return, spawn, {.v = termcmd}},
    {MODKEY, XKB_KEY_e, spawn, {.v = yazicmd}},
    {MODKEY, XKB_KEY_v, spawn, {.v = pulsemixercmd}},
    {MODKEY, XKB_KEY_u, spawn, {.v = hyprpickercmd}},

    {MODKEY, XKB_KEY_period, spawn,
     SHCMD("env BEMENU_OPTS='" BEMENU_OPTS
           "' bash ~/.local/bin/scripts/emoji-picker.sh")},

    {MODKEY, XKB_KEY_w, spawn,
     SHCMD("env BEMENU_OPTS='" BEMENU_OPTS
           "' bash ~/.local/bin/scripts/wallpaper-picker.sh")},

    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_s, spawn,
     SHCMD("grim -g \"$(slurp)\" - | tee "
           "~/Pictures/Screenshots/screenshot_$(date +%Y%m%d_%H%M%S).png | "
           "wl-copy")},

    {0, XKB_KEY_XF86AudioRaiseVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+")},

    {0, XKB_KEY_XF86AudioLowerVolume, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-")},

    {0, XKB_KEY_XF86AudioMute, spawn,
     SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle")},

    {MODKEY, XKB_KEY_equal, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%+")},

    {MODKEY, XKB_KEY_minus, spawn,
     SHCMD("wpctl set-volume @DEFAULT_AUDIO_SINK@ 5%-")},

    {MODKEY, XKB_KEY_j, focusstack, {.i = +1}},
    {MODKEY, XKB_KEY_k, focusstack, {.i = -1}},

    {MODKEY, XKB_KEY_i, incnmaster, {.i = +1}},
    {MODKEY, XKB_KEY_d, incnmaster, {.i = -1}},

    {MODKEY, XKB_KEY_h, setmfact, {.f = -0.05f}},
    {MODKEY, XKB_KEY_l, setmfact, {.f = +0.05f}},

    {MODKEY, XKB_KEY_Tab, view, {0}},
    {MODKEY, XKB_KEY_q, killclient, {0}},

    {MODKEY, XKB_KEY_f, togglefloating, {0}},
    {MODKEY, XKB_KEY_space, setlayout, {0}},

    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_space, togglefloating, {0}},

    {MODKEY, XKB_KEY_comma, focusmon, {.i = WLR_DIRECTION_LEFT}},
    {MODKEY, XKB_KEY_period, focusmon, {.i = WLR_DIRECTION_RIGHT}},

    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_less,
     tagmon,
     {.i = WLR_DIRECTION_LEFT}},

    {MODKEY | WLR_MODIFIER_SHIFT,
     XKB_KEY_greater,
     tagmon,
     {.i = WLR_DIRECTION_RIGHT}},

    TAGKEYS(XKB_KEY_1, XKB_KEY_exclam, 0),
    TAGKEYS(XKB_KEY_2, XKB_KEY_at, 1),
    TAGKEYS(XKB_KEY_3, XKB_KEY_numbersign, 2),
    TAGKEYS(XKB_KEY_4, XKB_KEY_dollar, 3),
    TAGKEYS(XKB_KEY_5, XKB_KEY_percent, 4),
    TAGKEYS(XKB_KEY_6, XKB_KEY_asciicircum, 5),
    TAGKEYS(XKB_KEY_7, XKB_KEY_ampersand, 6),
    TAGKEYS(XKB_KEY_8, XKB_KEY_asterisk, 7),
    TAGKEYS(XKB_KEY_9, XKB_KEY_parenleft, 8),

    {MODKEY | WLR_MODIFIER_SHIFT, XKB_KEY_q, quit, {0}},

    {WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_Terminate_Server, quit, {0}},

#define CHVT(n)                                                                \
  {                                                                            \
    WLR_MODIFIER_CTRL | WLR_MODIFIER_ALT, XKB_KEY_XF86Switch_VT_##n, chvt, {   \
      .ui = (n)                                                                \
    }                                                                          \
  }

    CHVT(1),
    CHVT(2),
    CHVT(3),
    CHVT(4),
    CHVT(5),
    CHVT(6),
    CHVT(7),
    CHVT(8),
    CHVT(9),
    CHVT(10),
    CHVT(11),
    CHVT(12),
};

static const Button buttons[] = {
    {ClkLtSymbol, 0, BTN_LEFT, setlayout, {.v = &layouts[0]}},
    {ClkLtSymbol, 0, BTN_RIGHT, setlayout, {.v = &layouts[1]}},

    {ClkTitle, 0, BTN_MIDDLE, zoom, {0}},

    {ClkStatus, 0, BTN_MIDDLE, spawn, {.v = termcmd}},

    {ClkClient, MODKEY, BTN_LEFT, moveresize, {.ui = CurMove}},
    {ClkClient, MODKEY, BTN_MIDDLE, togglefloating, {0}},
    {ClkClient, MODKEY, BTN_RIGHT, moveresize, {.ui = CurResize}},

    {ClkTagBar, 0, BTN_LEFT, view, {0}},
    {ClkTagBar, 0, BTN_RIGHT, toggleview, {0}},

    {ClkTagBar, MODKEY, BTN_LEFT, tag, {0}},
    {ClkTagBar, MODKEY, BTN_RIGHT, toggletag, {0}},

    {ClkTray, 0, BTN_LEFT, trayactivate, {0}},
    {ClkTray, 0, BTN_RIGHT, traymenu, {0}},
};
