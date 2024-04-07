define i32 @main() {
%some-pointer = alloca i32 ; declares an int in memory (stack)
store i32 42, i32* %some-pointer
store i32 54, i32* %some-pointer
%retval = load i32, i32* %some-pointer
ret i32 %retval
}

