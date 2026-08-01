# Jackbox Custom-Server Launchers

Builds small `.exe` launchers that start each Jackbox game with:

```
-jbg.config serverUrl=https://jb-ecast.klucva.ru
```

## Games covered
- The Jackbox Naughty Pack
- Drawful 2
- Jackbox Party Pack 6
- Jackbox Party Pack 7
- Jackbox Party Pack 8
- Jackbox Party Pack 11

## How it works
Each launcher is a tiny Win32 program (`src/launcher.c`) compiled once per
game with the target exe name baked in via `-DTARGET_EXE`. At runtime it
finds its own folder, looks for the real game exe next to it, and starts
it with the server argument.

Launcher output is named `"<Game> (Custom Server).exe"` so it never
overwrites the real game executable — drop it in the same folder as
`<Game>.exe` and run the launcher instead.

## Build locally (Linux/macOS/WSL with mingw-w64 installed)
```bash
sudo apt-get install mingw-w64   # or brew install mingw-w64 on macOS
make
```
Output goes to `dist/`.

## Build via GitHub Actions
1. Push this folder to a GitHub repo.
2. The `Build Jackbox Launchers` workflow runs automatically on push to
   `main`, or trigger it manually from the Actions tab (workflow_dispatch).
3. Download the `jackbox-launchers` artifact from the completed run — it
   contains all six `.exe` files.

## Changing the server URL
Edit `SERVER_URL` in `build-all.sh` and re-run `make`.
