source_filename = "../../examples/scope_test.cs"
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
%v12 = alloca [11 x i8]
%v13 = bitcast [11 x i8]* %v12 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v13, i8* align 1 getelementptr inbounds ([11 x i8], [11 x i8]* @__const.func.funcprint, i32 0, i32 0), i64 11, i1 false)
%v15 = getelementptr inbounds [11 x i8], [11 x i8]* %v12, i64 0, i64 0
%v16 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v15)
%v17 = alloca i32
store i32 151, i32* %v17
%v18 = load i32, i32* %v17
%v19 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v18)
%v20 = load i32, i32* %v11
%v21 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v20)
%v22 = load double, double* %v10
%v23 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i64 0, i64 0), double noundef %v22)
%v24 = load i8, i8* %v9
%v25 = sext i8 %v24 to i32
%v26 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 noundef %v25)
%v27 = alloca [9 x i8]
%v28 = bitcast [9 x i8]* %v27 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v28, i8* align 1 getelementptr inbounds ([9 x i8], [9 x i8]* @__const.func.funcprintend, i32 0, i32 0), i64 9, i1 false)
%v30 = getelementptr inbounds [9 x i8], [9 x i8]* %v27, i64 0, i64 0
%v31 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v30)
ret i32 0
}
define dso_local double @main() #0 {
%v33 = alloca i32
store i32 3, i32* %v33
%v34 = alloca i32
store i32 15, i32* %v34
%v35 = alloca i8
store i8 65, i8* %v35
%v36 = alloca double
store double 24.2, double* %v36
%v37 = load i32, i32* %v33
%v38 = add i32 %v37, 1
store i32 %v38, i32* %v34
br label %v39
v39:
%v42 = load i32 , i32* %v34
%v41 = load i32, i32* %v33
%v43 = icmp slt i32 %v41, %v42
br i1 %v43, label %v44, label %v40
v44:
%v46 = alloca [9 x i8]
%v47 = bitcast [9 x i8]* %v46 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v47, i8* align 1 getelementptr inbounds ([9 x i8], [9 x i8]* @__const.main.message, i32 0, i32 0), i64 9, i1 false)
%v49 = getelementptr inbounds [9 x i8], [9 x i8]* %v46, i64 0, i64 0
%v50 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v49)
%v51 = load i32, i32* @g0
%v52 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v51)
%v53 = alloca i32
store i32 1, i32* %v53
%v54 = alloca i32
store i32 2, i32* %v54
%v55 = alloca i32
store i32 3, i32* %v55
%v56 = alloca i32
store i32 1, i32* %v56
%v57 = load i32, i32* %v33
%v58 = icmp eq i32 %v57, 3
br i1 %v58, label %v59, label %v60
v59:
store i32 5, i32* %v54
%v61 = alloca i32
store i32 4, i32* %v61
store i32 4444, i32* %v56
br label %v60
v60:
%v62 = alloca [8 x i8]
%v63 = bitcast [8 x i8]* %v62 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v63, i8* align 1 getelementptr inbounds ([8 x i8], [8 x i8]* @__const.main.message1, i32 0, i32 0), i64 8, i1 false)
%v65 = getelementptr inbounds [8 x i8], [8 x i8]* %v62, i64 0, i64 0
%v66 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v65)
%v67 = load i32, i32* %v56
%v68 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v67)
%v69 = alloca i32
store i32 2, i32* %v69
store i32 5, i32* %v54
br label %v45
v45:
%v70 = load i32, i32* %v33
%v71 = add i32 %v70, 1
store i32 %v71, i32* %v33
br label %v39
v40:
%v72 = alloca [9 x i8]
%v73 = bitcast [9 x i8]* %v72 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v73, i8* align 1 getelementptr inbounds ([9 x i8], [9 x i8]* @__const.main.message3, i32 0, i32 0), i64 9, i1 false)
%v75 = getelementptr inbounds [9 x i8], [9 x i8]* %v72, i64 0, i64 0
%v76 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v75)
%v77 = load i32, i32* @g1
%v78 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v77)
br label %v79
v79:
%v81 = load i32, i32* %v33
%v82 = icmp slt i32 %v81, 51
br i1 %v82, label %v83, label %v80
v83:
%v85 = alloca i32
store i32 6, i32* %v85
%v86 = alloca i32
store i32 7, i32* %v86
store i32 8, i32* @g1
br label %v84
v84:
%v87 = load i32, i32* %v33
%v88 = add i32 %v87, 1
store i32 %v88, i32* %v33
br label %v79
v80:
%v90 = getelementptr inbounds [9 x i8], [9 x i8]* %v72, i64 0, i64 0
%v91 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v90)
%v92 = load i32, i32* @g1
%v93 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v92)
%v94 = load i32, i32* %v33
%v95 = icmp eq i32 %v94, 2
br i1 %v95, label %v96, label %v97
v96:
%v99 = alloca i32
store i32 242, i32* %v99
br label %v98
v97:
%v100 = alloca i32
store i32 2, i32* %v100
br label %v98
v98:
%v101 = load i32, i32* %v34
%v102 = load double, double* %v36
%v103 = load i8, i8* %v35
call i32 @func(i32 noundef %v101, double noundef %v102, i8 noundef %v103)
%v104 = alloca [9 x i8]
%v105 = bitcast [9 x i8]* %v104 to i8*
call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 1 %v105, i8* align 1 getelementptr inbounds ([9 x i8], [9 x i8]* @__const.main.message4, i32 0, i32 0), i64 9, i1 false)
%v107 = getelementptr inbounds [9 x i8], [9 x i8]* %v104, i64 0, i64 0
%v108 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0), i8* noundef %v107)
%v109 = load i32, i32* @g0
%v110 = call i32 (i8*, ...) @printf(i8* noundef getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 noundef %v109)
ret double 0.0
}
@__const.func.funcprint = private unnamed_addr constant [11 x i8] c"func START\00"

@__const.func.funcprintend = private unnamed_addr constant [9 x i8] c"func END\00"

@__const.main.message = private unnamed_addr constant [9 x i8] c"Global a\00"

@__const.main.message1 = private unnamed_addr constant [8 x i8] c"Local j\00"

@__const.main.message3 = private unnamed_addr constant [9 x i8] c"Global j\00"

@__const.main.message4 = private unnamed_addr constant [9 x i8] c"Global a\00"

declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #2
declare i32 @printf(i8* noundef, ...) #1
attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { argmemonly nofree nounwind willreturn }
