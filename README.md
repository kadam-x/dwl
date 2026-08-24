# dwl (personal build)

Personal fork of [dwl](https://codeberg.org/dwl/dwl) — a compact, hackable
Wayland compositor based on wlroots. Upstream lives on Codeberg; this is my
own build hosted on GitHub.

## Changes on top of upstream

- **bar + systray patches** (`patches/bar.patch`, `patches/bar-systray-0.7.patch`)
  statusbar with text rendering and full dbus systray support (`systray/`, `dbus.c`)
- **betterfloat patch** (`patches/betterfloat-diff.patch`)
- new windows open at the **bottom of the stack** instead of the top
- sway-style move keybinds, per-window float toggle
- idle + exit keybinds
- recoloring (compositor colors, bemenu), rules for yazi & pulsemixer

## Building

See upstream README for dependencies; then:

    make
    sudo make install

Configuration is done via `config.h` (copy from `config.def.h`).
