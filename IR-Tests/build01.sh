#!/bin/sh

clean() {
  rm foo.ll \
     main01 \
     main01.s \
     main01.ll \
     example-reg \
     example-reg.s \
     example-mem_stack \
     example-mem_stack.s
}



# ------------
# main01
# ------------
main01() {
  clang++ main01.cpp -o main01
  ./main01
  echo $?

  clang++ main01.cpp -S -emit-llvm
  #opt main01.ll -S -o foo.ll -reg2mem
  #opt main01.ll -S -analyze

  llc main01.ll -o main01.s
  gcc main01.s -o main01
  ./main01
  echo $?
}


# ------------
# example-reg
# ------------
example_reg() {
  llc example-reg.ll -o example-reg.s
  gcc example-reg.s -o example-reg
  ./example-reg
  echo $?
}


# ------------
# example-mem_stack
# ------------
example_mem() {
  llc example-mem_stack.ll -o example-mem_stack.s
  gcc example-mem_stack.s -o example-mem_stack
  ./example-mem_stack
  echo $?
  opt example-mem_stack.ll  -S -o foo.ll -mem2reg
  #opt example-mem_stack.ll -dot-cfg
  #dot example-mem_stack.ll -Tpdf > example-mem_stack.pdf
}

clean
example_mem

