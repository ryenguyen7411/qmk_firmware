# Ryenguyen7411 Atreus Keymap

This is a custom keymap for the Keyboardio Atreus optimized for:
- **Programming workflow** (Vim integration, coding shortcuts)
- **macOS productivity** (Cmd key workflows, window management)
- **Mouse-free computing** (trackpad/mouse control via keyboard)

## How This Keymap Works

This keymap uses **layers** - think of them as different keyboard modes you can switch between:
- **BASE**: Your normal typing layer
- **MOUSE** (FN1): Mouse control and window management
- **NUMBERS** (FN2): Numbers, symbols, and punctuation
- **VIM** (FN3): Vim editor commands and shortcuts
- **FUNCTION** (FN4): Function keys and media controls

### Key Behaviors
- **Tap vs Hold**: Many keys do different things when tapped vs held down
- **Layer Access**: Hold layer keys (FN1-FN4) to temporarily access that layer
- **Tap Dance**: Some keys change behavior when double-tapped
- **Key Overrides**: Holding modifiers (Cmd/Ctrl) changes what certain keys do

---

## BASE LAYOUT

.-----------------------------,           .-----------------------------.
|  Q  |  W  |  E  |  R  |  T  |           |  Y  |  U  |  I  |  O  |  P  |
|-----------------------------|           |-----------------------------|
|  A  |  S  |  D  |  F  |  G  |           |  H  |  J  |  K  |  L  | FN4 |
|-----------------------------------------------------------------------|
|Shift|  Z  |  X  |  C  |  V  |     |MOUSE|  B  |  N  |  M  |     |Ctrl |
|-----------------------------------------------------------------------|
|Ctrl |     | Alt | Cmd |xxxxx| FN2 | FN1 | FN3 |  ◀  |  ▼  |  ▲  |  ▶  |
'-----------------------------------------------------------------------'

- Shift Tap = ESC
- Right Ctrl Tap = ESC
- **FN1,2,3 Tap** = Space
- **FN4 Tap** = Enter
- **MOUSE Tap** = Enable mouse layer
    > Shift/Ctrl + MOUSE = Disable mouse layer
    - xxxxx: Key is dead :(

---

## MOUSE LAYER (FN1)
*Hold FN1 or tap MOUSE key to access*

.-----------------------------.           .-----------------------------.
|     |SlowM|     |     |Clk ◀|           |Clk ▶|Dock |Lang | Del | <-- |
|-----------------------------|           |-----------------------------|
| Cmd |MSc ◀|MSc ▼|MSc ▲|MSc ▶|           | M ◀ | M ▼ | M ▲ | M ▶ |     |
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |Scr01|Peek |Win ◀|Win ▶|Scr02|
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'

### Mouse & Window Controls:
- **SlowM**: Slow mouse mode
- **MSc ◀/▼/▲/▶**: Mouse scroll direction
- **M ◀/▼/▲/▶**: Mouse movement
- **Clk ◀/▶**: Mouse click left/right
- **Dock**: Show/hide dock (Ctrl+F3)
- **Lang**: Switch input language (Ctrl+Space)

### Window Management:
- **Scr01**: Move window to left screen (Ctrl+Shift+[)
- **Scr02**: Move window to right screen (Ctrl+Shift+])
- **Win ◀/▶ (Ctrl ◀/▶)**: Window control shortcuts
- **Peek**: Mission Control/window overview

*Requires BetterTouchTool for screen movement shortcuts*

---

## NUMBERS LAYER (FN2)
*Hold FN2 to access*

.-----------------------------.           .-----------------------------.
|  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  |
|-----------------------------|           |-----------------------------|
| Cmd |Shift| Alt |  ~  | Tab |           |  -  |  =  |  ;  |  '  |  \  |
|-----------------------------------------------------------------------|
|     |     |     |     |     |VI11 |     | 〚  |  ,  |  .  |  /  |  〛 |
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'

Numbers 1-0 on top row, with common symbols and modifiers positioned for easy programming workflows.

### Vim Commands:
- **VI11**: Vim Save (ESC + <leader> + w)

---

## VIM LAYER (FN3)
*Hold FN3 to access*

.-----------------------------.           .-----------------------------.
|     |     |VI07 |VI08 |     |           |VI05 |     |VI10 |     |     |
|-----------------------------|           |-----------------------------|
|     |     |     |     |VI09 |           |     |VI03 |VI06 |VI02 |VI01 |
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |VI04 |     |     |     |PASTE|
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'

### Vim Commands (ESC + space + key):
- **VI01**: Find Files (;)
- **VI02**: Project (l)
- **VI03**: Live Grep (j)
- **VI04**: Buffers (b)
- **VI05**: Resume picker (')
- **VI06**: File Browser (k)
- **VI07**: Emmet Tab (Ctrl+J)
- **VI08**: DiffviewOpen (r)
- **VI09**: DiffviewFileHistory (f)
- **VI10**: Notes (i)

*Optimized for Neovim with Snacks and other plugins*

---

## FUNCTION LAYER (FN4)
*Hold FN4 to access*

.-----------------------------.           .-----------------------------.
| F1  | F2  | F3  | F4  | F5  |           | F6  | F7  | F8  | F9  | F10 |
|-----------------------------|           |-----------------------------|
|     |     |CLEAR| F11 | F12 |           |Bri▼ |Bri▲ |Vol▼ |Vol▲ |     |
|-----------------------------------------------------------------------|
|     |     |     |HTML |     |     |     |     |     |Mute |     |     |
|-----------------------------------------------------------------------|
|     |RESET|     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'

- **CLEAR**: Terminal clear (Ctrl + ` + Ctrl + L)
- **HTML**: Copy as HTML (Cmd + Shift + C)
- **RESET**: Reset keyboard firmware

---

# ADVANCED FEATURES

## KEY OVERRIDES

When on the MOUSE layer (FN1), holding modifier keys changes what certain keys do:

### Command Key Overrides:
- Cmd + Mouse Wheel Right = Cmd + S
- Cmd + Mouse Wheel Up = Cmd + D
- Cmd + Mouse Wheel Down = Cmd + F
- Cmd + Mouse Wheel Left = Cmd + G
- Cmd + Mouse Left = Cmd + H
- Cmd + Mouse Down = Cmd + J
- Cmd + Mouse Up = Cmd + K
- Cmd + Mouse Right = Cmd + L
- Cmd + Mouse Button 1 = Cmd + T
- Cmd + Mouse Button 2 = Cmd + Y
- Cmd + Delete = Cmd + O

### Control Key Overrides:
- Ctrl + Mouse Left = Ctrl + H
- Ctrl + Mouse Down = Ctrl + J
- Ctrl + Mouse Up = Ctrl + K
- Ctrl + Mouse Right = Ctrl + L
- Ctrl + Delete = Ctrl + O

### GUI Key Overrides (on NUMBERS layer):
- Cmd + 7 = Dock (Ctrl + F3)
- Cmd + 8 = Language Toggle (Ctrl + Space)
- Cmd + 9 = Delete
- Cmd + 0 = Backspace

---

# SETUP AND INSTALLATION

## Requirements
- QMK firmware environment
- macOS (keymap optimized for macOS shortcuts)
- BetterTouchTool (optional, for screen movement shortcuts)
- Neovim with Snacks plugin (for Vim commands)

## Building and Flashing

```bash
# Compile the keymap
qmk compile -kb keyboardio/atreus -km ryenguyen7411

# Flash to keyboard
qmk flash -kb keyboardio/atreus -km ryenguyen7411
```

## Quick Start Guide

1. **Start typing** - Base layer works like normal QWERTY
2. **Try mouse control** - Tap MOUSE key, then use M ◀/▼/▲/▶ keys. Hold Shift/Ctrl + MOUSE to disable mouse layer.
3. **Access numbers** - Hold FN2 for number row
4. **Use Vim shortcuts** - Hold FN3 for quick Vim commands
5. **Function keys** - Hold FN4 for F-keys and media controls

*This keymap has a learning curve but significantly improves productivity once mastered.*
