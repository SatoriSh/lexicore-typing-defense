# LexiCore — Typing Defense Game

## 📸 Video gameplay
https://github.com/user-attachments/assets/1e2583b2-65ba-4a9e-b2af-a80c181fd198

<div align="center">
<table align="center">

</table>

[![Itch.io](https://img.shields.io/badge/Play_on_Itch.io-FA5C5C?style=for-the-badge&logo=itch.io&logoColor=white)](https://satorish.itch.io/asteroids-raylib)

</div>

A fast-paced typing defense game built with **C++ and SFML 3**. Words fly toward your heart from all sides — type them correctly to destroy the incoming circles before they reach you. Survive as many waves as you can.

---

## Gameplay

- Circles spawn from the edges of the screen and move toward the heart at the center
- Type the word displayed on a circle to destroy it before it hits
- Every 5th wave is a **unique wave** — faster spawns, longer words, and a full heal on completion
- Difficulty scales with each wave: spawn rate increases, words get harder
- Your best wave is saved as a **checkpoint** and can be continued later
- The game tracks your score and current wave in real time

## Features

- Dynamic difficulty — spawn intervals decrease each wave, capped at a minimum
- 4 word difficulty tiers: simple, medium, hard, and unique (used on milestone waves)
- Checkpoint system — progress is saved after every 5th wave
- Explosion animations on circle destruction
- Background music and sound effects for hits, successes, wave completions and game over
- Heart health system with visual feedback (sprite changes per hit)
- Pause menu with continue and return to main menu options

## Building from source

**Requirements:** CMake 3.16+, SFML 3, C++17 compiler

```bash
git clone https://github.com/satorish/lexicore-typing-defense
cd lexicore-typing-defense
mkdir build && cd build
cmake ..
make -j$(nproc)       # Linux
cmake --build .       # Windows
```

The binary must be run from the `build/` directory so relative asset paths resolve correctly.

## Platform support

Tested and confirmed working on:
- Windows 10 / 11
- EndeavourOS (Arch-based Linux)

## Tech stack

- **C++17**
- **SFML 3** — graphics, audio, windowing
- CMake build system
