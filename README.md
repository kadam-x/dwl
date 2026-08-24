Personal fork of [dwl](https://codeberg.org/dwl/dwl) 

## Changes on top of upstream
- [bar](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/bar) using
  [slstatus](https://github.com/kadam-x/slstatus)
- [bar-systray](https://codeberg.org/dwl/dwl-patches/src/branch/main/patches/bar-systray)
- [better-float](https://codeberg.org/wochap/dwl/src/branch/v0.6-c/betterfloat/betterfloat-diff.patch) for automatic floating on windows based on rules
- new windows open at the **bottom of the stack** instead of the top
- sway-style move keybinds, per-window float toggle
- idle + exit keybinds
- uses [bemenu](https://github.com/cloudef/bemenu) as dmenucmd and menucmd for
 bemenu-run and my [custom scripts](https://github.com/kadam-x/.dotfiles/tree/main/scripts/.local/bin/scripts)
- launches via [start-dwl script](https://github.com/kadam-x/.dotfiles/blob/main/dwl-start/dwl-start)
