source_filename = "../../tests/codegen-tests-cs/test1.cs"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str.6 = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.7 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
define dso_local i32 @main() #0 {
%v0 = alloca i32
store i32 10, i32* %v0
%v1 = alloca i32
%v2 = load i32, i32* %v1
store i32 %v2, i32* %v1
%v3 = alloca i32
%v4 = load i32, i32* %v0
%v5 = load i32, i32* %v1
%v6 = add i32 %v4, %v5
store i32 %v6, i32* %v3
%v7 = alloca double
store double 2.1, double* %v7
%v8 = alloca double
%v9 = load double, double* %v8
store double %v9, double* %v8
%v10 = alloca double
%v11 = load double, double* %v7
%v12 = load double, double* %v8
%v13 = fadd double %v11, %v12
store double %v13, double* %v10
%14 = load i32, i32* %v0
ret i32 %14
}
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn }
