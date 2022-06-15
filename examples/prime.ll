source_filename = "../../examples/prime.cs"
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
define dso_local i32 @isprime(i32 noundef %v0) #0 {
%v2 = alloca i32
store i32 %v0, i32* %v2
%v3 = alloca i32
store i32 1, i32* %v3
%v4 = alloca i32
%v5 = load i32, i32* %v2
store i32 %v5, i32* %v4
%v6 = alloca i32
store i32 0, i32* %v6
%v7 = alloca i32
store i32 4, i32* %v7
%v8 = alloca i32
store i32 2, i32* %v8
br label %v9
v9:
%v12 = load i32 , i32* %v4
%v11 = load i32, i32* %v7
%v13 = icmp sle i32 %v11, %v12
br i1 %v13, label %v14, label %v10
v14:
%v16 = load i32, i32* %v2
%v17 = load i32, i32* %v8
%v18 = srem i32 %v16, %v17
store i32 %v18, i32* %v6
%v19 = load i32, i32* %v6
%v20 = icmp eq i32 %v19, 0
br i1 %v20, label %v21, label %v22
v21:
%v23 = load i32, i32* %v4
store i32 %v23, i32* %v8
store i32 0, i32* %v3
br label %v22
v22:
%v24 = load i32, i32* %v8
%v25 = add i32 %v24, 1
store i32 %v25, i32* %v8
%v26 = load i32, i32* %v8
%v27 = load i32, i32* %v8
%v28 = mul i32 %v26, %v27
store i32 %v28, i32* %v7
%v29 = load i32, i32* %v8
%v30 = sub i32 %v29, 1
store i32 %v30, i32* %v8
br label %v15
v15:
%v31 = load i32, i32* %v8
%v32 = add i32 %v31, 1
store i32 %v32, i32* %v8
br label %v9
v10:
%v33 = load i32, i32* %v3
ret i32 %v33
}
define dso_local i32 @main() #0 {
%v34 = alloca i32
%v35 = alloca i32
store i32 0, i32* %v35
%v36 = alloca i32
store i32 0, i32* %v36
%v37 = call i32 (i8*, ...) @scanf(i8* noundef getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i64 0, i64 0), i32* noundef %v34)
%v38 = alloca i32
store i32 2, i32* %v38
br label %v39
v39:
%v42 = load i32 , i32* %v34
%v41 = load i32, i32* %v35
%v43 = icmp slt i32 %v41, %v42
br i1 %v43, label %v44, label %v40
v44:
%v46 = load i32, i32* %v38
%v47 = call i32 @isprime(i32 noundef %v46)
store i32 %v47, i32* %v36
%v48 = load i32, i32* %v36
%v49 = icmp eq i32 %v48, 1
br i1 %v49, label %v50, label %v51
v50:
%v52 = load i32, i32* %v38
%v53 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v52)
%v54 = load i32, i32* %v35
%v55 = add i32 %v54, 1
store i32 %v55, i32* %v35
br label %v51
v51:
br label %v45
v45:
%v56 = load i32, i32* %v38
%v57 = add i32 %v56, 1
store i32 %v57, i32* %v38
br label %v39
v40:
ret i32 0
}
declare i32 @printf(i8* noundef, ...) #1
declare i32 @scanf(i8* noundef, ...) #1
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn }
