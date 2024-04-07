define i32 @main() {
%some-variable = add i32 1, 1 ; integer with the value 1+1
%some-other-variable = add i32 %some-variable, 1
ret i32 %some-other-variable
}
