source_filename = "../../examples/codegen_test1.cs"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"
define dso_local i32 @main() #0 {
%1 = alloca i32
store i32 32, i32* %1
%2 = alloca i32
store i32 24, i32* %2
%3 = alloca i32
store i32 12, i32* %3
%4 = alloca i32
%5 = load i32, i32* %2
%6 = load i32, i32* %1
%7 = add i32 %5, %6
store i32 %7, i32* %4
%8 = load i32, i32* %3
%9 = sub i32 12, %8
store i32 %9, i32* %1
%10 = load i32, i32* %1
ret i32 %10
}
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
