# ryenguyen7411 — Keyboardio Atreus

macOS keymap for programming without leaving the keyboard: mouse and window control,
digitizer cursor jumps, and one-key Neovim/tmux shortcuts.

```bash
qmk compile -kb keyboardio/atreus -km ryenguyen7411
qmk flash   -kb keyboardio/atreus -km ryenguyen7411
```

Needs macOS. Optional: Neovim with Snacks + Diffview and tmux (FN3).

## Layers

| Layer | Reach it by | For |
|---|---|---|
| BASE | — | Typing |
| FN1 Mouse | Hold the right Space thumb, or tap **MOUSE** (stays on) | Mouse, cursor jumps, windows |
| FN2 Numbers | Hold the left Space thumb | Numbers, symbols |
| FN3 Vim | Hold the Space key right of FN1 | Neovim / tmux shortcuts |
| FN4 Function | Hold **FN4** (Enter) | F-keys, media, bootloader |

Blank cells in the diagrams fall through to the base layer.

---

## BASE

```
.-----------------------------.           .-----------------------------.
|  Q  |  W  |  E  |  R  |  T  |           |  Y  |  U  |  I  |  O  |  P  |
|-----------------------------|           |-----------------------------|
|  A  |  S  |  D  |  F  |  G  |           |  H  |  J  |  K  |  L  | FN4 |
|-----------------------------------------------------------------------|
|ShEsc|  Z  |  X  |  C  |  V  |DRAG |MOUSE|  B  |  N  |  M  |     |CtEsc|
|-----------------------------------------------------------------------|
|Ctrl |     | Opt | Cmd |xxxxx| FN2 | FN1 | FN3 |  ◀  |  ▼  |  ▲  |  ▶  |
'-----------------------------------------------------------------------'
```

| Key | Tap | Hold |
|---|---|---|
| ShEsc | Esc | Left Shift |
| CtEsc | Esc | Right Ctrl |
| FN1 / FN2 / FN3 | Space | Layer FN1 / FN2 / FN3 |
| FN4 | Enter | Layer FN4 |
| MOUSE | Mouse layer on (stays on) | — |
| DRAG | Mouse layer on + [drag lock](#drag-lock) | — |
| Shift/Ctrl + MOUSE | Mouse layer off | — |

`xxxxx` is a dead switch.

---

## FN1 — Mouse

```
.-----------------------------.           .-----------------------------.
|     |Slow |Widg |Save |Clk L|           |Clk R|Dock |Lang | Del |Bspc |
|-----------------------------|           |-----------------------------|
|RCmd |Whl ▶|Whl ▲|Whl ▼|Whl ◀|           | M ◀ | M ▼ | M ▲ | M ▶ |Enter|
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |Scr1 |Peek |Win ◀|Win ▶|Scr2 |
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'
```

| Key | Does |
|---|---|
| M ◀ ▼ ▲ ▶ | Move the cursor (accelerates while held) |
| Slow | Hold for slow, precise movement |
| Whl ▶ ▲ ▼ ◀ | Scroll wheel right / up / down / left |
| Clk L / Clk R | Left / right click |
| RCmd | Right Cmd. Hold it for [cursor jumps](#cursor-jumps). With left Cmd held: A (Cmd+A) |
| DRAG | [Drag lock](#drag-lock) |
| Save | Neovim save: Esc, Space, w |
| Widg | Ctrl+Shift+Z (Notification Centre / widgets) |
| Dock | Show/hide Dock (Ctrl+F3) |
| Lang | Switch input language (Ctrl+Space) |
| Peek | Mission Control (Ctrl+↑) |
| Win ◀ / Win ▶ | Previous / next Space (Ctrl+← / Ctrl+→) |
| Scr1 / Scr2 | Window to left / right screen (Cmd+Shift+[ / ]), via BetterTouchTool |

### Cursor jumps

Hold **RCmd**, then press M ◀ ▼ ▲ ▶ (H J K L). Each press keeps that half of the
current area and puts the cursor in its middle:

| While holding RCmd | Cursor at (x, y) |
|---|---|
| ◀ | 25%, 50% |
| ◀ | 12.5%, 50% |
| ▼ | 12.5%, 75% |
| Enter | 50%, 50%, and the next jump starts from the whole screen again |

Release and press RCmd again to start over from the whole screen. Jumps use a
digitizer (absolute position), so they land on the display macOS maps it to,
normally the main one.

### Drag lock

**DRAG** holds the left button down so you can move the cursor (or jump) while dragging.
DRAG sits in the same spot on BASE and FN1; on BASE it also turns the mouse layer on.
It lets go when you press DRAG again, click Clk L, tap Esc, or leave the mouse layer.
Esc reaches macOS while the button is still down, so it cancels the drag rather than dropping.

### Leaving the mouse layer

The layer turns itself off when you press keys that usually mean you're about to type:

- `` ` `` or Z with no modifiers
- Ctrl + Z, C or L
- Left Cmd (and nothing else) + L, F, T, or any Space key
- Shift/Ctrl + MOUSE

### Modifier variants

| Key | Alone | Left Cmd or Shift held | Right Cmd held |
|---|---|---|---|
| Peek | Ctrl+↑ | `n` (Cmd+N / N) | Cmd+Ctrl+, |
| Win ◀ | Ctrl+← | `m` (Cmd+M / M) | Cmd+Ctrl+. |
| Win ▶ | Ctrl+→ | — | Cmd+Ctrl+/ |
| Scr1 | Cmd+Shift+[ | `b` (Cmd+B / B) | Cmd+[ |
| Scr2 | Cmd+Shift+] | — | Cmd+] |
| Save | Esc, Space, w | Left Cmd only: Cmd+R | `r` (Cmd dropped) |

### Key overrides

With **left** Cmd or Ctrl held, mouse keys send the letter printed underneath instead:

| Held | Keys | Sends |
|---|---|---|
| Left Cmd | Slow, Whl ▶ ▲ ▼ ◀, Clk L, Clk R, M ◀ ▼ ▲ ▶ | Cmd + W, S D F G, T, Y, H J K L |
| Left Cmd | Del (not with Shift) | Cmd+O |
| Ctrl | M ◀ ▼ ▲ ▶, Del | Ctrl + H J K L, O |
| Ctrl+Shift | Whl ▼ | Ctrl+Shift+F |

Ctrl + the other wheel keys stays Ctrl + scroll, for zoom in maps and Figma.

The mod has to go down first. Press the mouse key first and then Cmd/Ctrl to get the real
modified mouse action (e.g. hold M ▶, then Cmd, to move with Cmd held).

Right Cmd + M ◀ ▼ ▲ ▶ is a [cursor jump](#cursor-jumps), not Cmd+H/J/K/L.

---

## FN2 — Numbers

```
.-----------------------------.           .-----------------------------.
|  1  |  2  |  3  |  4  |  5  |           |  6  |  7  |  8  |  9  |  0  |
|-----------------------------|           |-----------------------------|
| Cmd |Shift| Opt |  `  | Tab |           |  -  |  =  | ; : |  '  |  \  |
|-----------------------------------------------------------------------|
|     |     |     |     |     |Save |     |  [  |  ,  |  .  |  /  |  ]  |
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'
```

| Key | Does |
|---|---|
| `; :` | Tap `;`, double-tap `:` |
| Save | Same as FN1 Save |
| Cmd + 7 / 8 / 9 / 0 | Dock / Lang / Delete / Backspace (either Cmd) |

---

## FN3 — Vim / tmux

```
.-----------------------------.           .-----------------------------.
|     |M_OF |Emmet|Diff |     |           |Resum|     |Notes|OpenC|Curs |
|-----------------------------|           |-----------------------------|
|M_ON |     |     |     |FHist|           |     |Grep |Brows|Proj |Files|
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |Bufs |     |     |     |Paste|
|-----------------------------------------------------------------------|
|     |     |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'
```

Most keys send Esc, then `<leader>` (Space) + a key:

| Key | Sends | Neovim action |
|---|---|---|
| Files | `<leader>;` | Find files |
| Proj | `<leader>l` | Projects |
| Grep | `<leader>j` | Live grep |
| Bufs | `<leader>b` | Buffers |
| Resum | `<leader>'` | Resume picker |
| Brows | `<leader>k` | File browser |
| Diff | `<leader>r` | DiffviewOpen |
| FHist | `<leader>f` | DiffviewFileHistory |
| Notes | `<leader>i` | Notes |
| Emmet | Ctrl+J | Emmet expand |
| OpenC | Ctrl+O | tmux: Opencode |
| Curs | Ctrl+P | tmux: Cursor |
| Paste | Cmd+V | |
| M_OF | | Turn off the mouse layer |
| M_ON | | Turn on the mouse layer |

---

## FN4 — Function

```
.-----------------------------.           .-----------------------------.
| F1  | F2  | F3  | F4  | F5  |           | F6  | F7  | F8  | F9  | F10 |
|-----------------------------|           |-----------------------------|
|     |     |Clear| F11 | F12 |           |Bri▼ |Bri▲ |Vol▼ |Vol▲ |     |
|-----------------------------------------------------------------------|
|     |     |     |HTML |     |     |     |     |     |Mute |     |     |
|-----------------------------------------------------------------------|
|     |Boot |     |     |     |     |     |     |     |     |     |     |
'-----------------------------------------------------------------------'
```

| Key | Does |
|---|---|
| Clear | Terminal clear: Ctrl+`, then Ctrl+L |
| HTML | Copy as HTML (Cmd+Shift+C) |
| Boot | Reboot into the bootloader for flashing |
