#!/usr/bin/env bash

cd "$(dirname "$0")" || return 1

# Step 1 - Build base web
cd astro && \
    pnpm install && \
    pnpm run build

cd ..

# Step 2 - Build apps
mkdir -p tmp
cd tmp || return 1

# Step 2a - Build american-fugitive-save-editor
git clone git@github.com:Somrlik/american-fugitive-save-editor.git american-fugitive-save-editor
cd american-fugitive-save-editor || return 1
pnpm install && pnpm build --base=./
mkdir -p ../../dist/apps/american-fugitive-save-editor
cp -R ./dist/* ../../dist/apps/american-fugitive-save-editor
cd ../../

# Step 3 - Done
rm -fr ./tmp
echo "Done!"
