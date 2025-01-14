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
pnpm install && pnpm build --base=/apps/american-fugitive-save-editor/
mkdir -p ../../dist/apps/american-fugitive-save-editor
cp -R ./dist/* ../../dist/apps/american-fugitive-save-editor
cd .. || return 1

# Step 2b - Build assorted-web-tools
git clone git@github.com:Somrlik/assorted-tools-web.git assorted-tools-web
cd assorted-tools-web || return 1
touch fake.pfx || return 1
HTTPS_PFX_FILE=fake.pfx pnpm install && HTTPS_PFX_FILE=fake.pfx pnpm build --base=/apps/assorted-tools-web/
mkdir -p ../../dist/apps/assorted-tools-web
cp -R ./dist/* ../../dist/apps/assorted-tools-web
cd .. || return 1

# Step 3 - Done
cd .. || return 1
rm -fr ./tmp
echo "Done!"
