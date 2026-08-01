#!/bin/bash
set -euo pipefail

CC="${CC:-x86_64-w64-mingw32-gcc}"
OUT_DIR="dist"
SERVER_URL="https://jb-ecast.klucva.ru"

mkdir -p "$OUT_DIR"

# Real exe name -> launcher output name
declare -a GAMES=(
  "The Jackbox Naughty Pack"
  "Drawful 2"
  "Jackbox Party Pack 6"
  "Jackbox Party Pack 7"
  "Jackbox Party Pack 8"
  "Jackbox Party Pack 11"
)

for name in "${GAMES[@]}"; do
  out="${OUT_DIR}/${name} (Custom Server).exe"
  echo "Building launcher for: ${name}"
  "$CC" -mwindows -O2 \
    -DTARGET_EXE="\"${name}.exe\"" \
    -DSERVER_ARG="\"-jbg.config serverUrl=${SERVER_URL}\"" \
    src/launcher.c \
    -o "$out" \
    -lshell32
done

echo "Done. Built $(ls -1 "$OUT_DIR" | wc -l) launcher(s) into ${OUT_DIR}/"
