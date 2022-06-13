source_filename = "../../examples/codegen_test1.cs"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"
@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%c\0A\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
define dso_local i32 @main() #0 {
%v1 = alloca double
store double 3.0, double* %v1
%v2 = load double, double* %v1
%v3 = fcmp une double %v2, 3.2
br i1 %v3, label %v4, label %v5
v4:
%v6 = alloca double
store double 0.0, double* %v6
br label %v7
v7:
%v10 = load double , double* %v1
%v9 = load double, double* %v6
%v11 = fcmp olt double %v9, %v10
br i1 %v11, label %v12, label %v8
v12:
%v14 = load double, double* %v1
%v15 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), double noundef %v14)
br label %v13
v13:
%v16 = load double, double* %v6
%v17 = fadd double %v16, 1.000000
store double %v17, double* %v6
br label %v7
v8:
br label %v5
v5:
ret i32 0
}
declare i32 @printf(i8* noundef, ...) #1
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn }
