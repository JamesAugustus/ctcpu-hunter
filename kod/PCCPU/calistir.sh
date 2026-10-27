#!/usr/bin/env bash
# Requires Bash, a C11 compiler and GMP development headers.
set -euo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"
build_dir=$(mktemp -d)
cleanup() { rm -f -- "$build_dir/pccpu_model"; rmdir -- "$build_dir"; }
trap cleanup EXIT
printf 'C / GMP derleniyor...\n'
"${CC:-cc}" -std=c11 -O2 -Wall -Wextra -Werror -pedantic \
    pccpu_address_model.c -lgmp -o "$build_dir/pccpu_model"
"$build_dir/pccpu_model" --test
printf '\n'
"$build_dir/pccpu_model" --demo
