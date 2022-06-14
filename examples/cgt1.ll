source_filename = "../../examples/test3.cs"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@g0 = global i32 243
@g1 = global i32 5
@g2 = global i32 0
define dso_local i32 @func(i32 noundef %v3, double noundef %v5, i8 noundef %v7) #0 {
%v9 = alloca i8
store i8 %v7, i8* %v9
%v10 = alloca double
store double %v5, double* %v10
%v11 = alloca i32
store i32 %v3, i32* %v11
%v12 = alloca i32
%v13 = alloca i32
%v14 = load i32, i32* %v11
store i32 %v14, i32* %v13
ret i32 0
}
define dso_local double @main(i32 noundef %v16) #0 {
%v18 = alloca i32
store i32 %v16, i32* %v18
%v19 = alloca i32
%v20 = alloca i32
store i32 15, i32* %v20
%v21 = load i32, i32* %v18
%v22 = add i32 10, %v21
store i32 %v22, i32* %v19
br label %v23
v23:
%v26 = load i32 , i32* %v19
%v25 = load i32, i32* %v19
%v27 = icmp slt i32 %v25, %v26
br i1 %v27, label %v28, label %v24
v28:
%v30 = alloca i32
store i32 1, i32* %v30
%v31 = alloca i32
store i32 2, i32* %v31
%v32 = alloca i32
store i32 3, i32* %v32
%v33 = alloca i32
store i32 1, i32* %v33
%v34 = load i32, i32* %v19
%v35 = icmp eq i32 %v34, 3
br i1 %v35, label %v36, label %v37
v36:
store i32 5, i32* %v31
%v38 = alloca i32
store i32 4, i32* %v38
br label %v37
v37:
%v39 = alloca i32
store i32 2, i32* %v39
store i32 5, i32* %v31
store i32 2, i32* %v19
br label %v29
v29:
%v40 = load i32, i32* %v19
%v41 = add i32 %v40, 1
store i32 %v41, i32* %v19
br label %v23
v24:
br label %v42
v42:
%v44 = load i32, i32* %v19
%v45 = icmp slt i32 %v44, 51
br i1 %v45, label %v46, label %v43
v46:
%v48 = alloca i32
store i32 6, i32* %v48
%v49 = alloca i32
store i32 7, i32* %v49
store i32 8, i32* %v33
br label %v47
v47:
%v50 = load i32, i32* %v19
%v51 = add i32 %v50, 1
store i32 %v51, i32* %v19
br label %v42
v43:
%v52 = load i32, i32* %v19
%v53 = icmp eq i32 %v52, 2
br i1 %v53, label %v54, label %v55
v54:
%v57 = alloca i32
store i32 242, i32* %v57
br label %v56
v55:
%v58 = alloca i32
store i32 2, i32* %v58
br label %v56
v56:
ret double 0.0
}
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn }
