find Software/Produkt/{src,include,tests} -name '*.cpp' -print0 | xargs -0 -n1 clang-tidy --p=Software/Produkt/build || true
