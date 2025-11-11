#!/usr/bin/env bash
set -e
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
find "$DIR/src" "$DIR/tests" -type f -name '*.cpp' -print0 | \
  xargs -0 -I{} -P8 clang-tidy "{}" --p="$DIR/build"

