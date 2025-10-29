#!/usr/bin/env bash
set -e
find src tests -type f -name '*.cpp' -print0 | \
  xargs -0 -n1 clang-tidy --p=build