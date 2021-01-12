; ModuleID = 'BubbleSort.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.vetor = private unnamed_addr constant [5 x i32] [i32 10, i32 9, i32 8, i32 7, i32 6], align 16

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %vetor = alloca [5 x i32], align 16
  %tamanho = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %r = alloca i32, align 4
  %aux = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = bitcast [5 x i32]* %vetor to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* bitcast ([5 x i32]* @main.vetor to i8*), i64 20, i32 16, i1 false)
  store i32 5, i32* %tamanho, align 4
  %3 = load i32, i32* %tamanho, align 4
  %4 = sub nsw i32 %3, 1
  store i32 %4, i32* %i, align 4
  br label %5

; <label>:5                                       ; preds = %47, %0
  %6 = load i32, i32* %i, align 4
  %7 = icmp sge i32 %6, 1
  br i1 %7, label %8, label %50

; <label>:8                                       ; preds = %5
  store i32 0, i32* %j, align 4
  br label %9

; <label>:9                                       ; preds = %43, %8
  %10 = load i32, i32* %j, align 4
  %11 = load i32, i32* %i, align 4
  %12 = icmp slt i32 %10, %11
  br i1 %12, label %13, label %46

; <label>:13                                      ; preds = %9
  %14 = load i32, i32* %j, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %15
  %17 = load i32, i32* %16, align 4
  %18 = load i32, i32* %j, align 4
  %19 = add nsw i32 %18, 1
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %20
  %22 = load i32, i32* %21, align 4
  %23 = icmp sgt i32 %17, %22
  br i1 %23, label %24, label %42

; <label>:24                                      ; preds = %13
  %25 = load i32, i32* %j, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %26
  %28 = load i32, i32* %27, align 4
  store i32 %28, i32* %aux, align 4
  %29 = load i32, i32* %j, align 4
  %30 = add nsw i32 %29, 1
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %31
  %33 = load i32, i32* %32, align 4
  %34 = load i32, i32* %j, align 4
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %35
  store i32 %33, i32* %36, align 4
  %37 = load i32, i32* %aux, align 4
  %38 = load i32, i32* %j, align 4
  %39 = add nsw i32 %38, 1
  %40 = sext i32 %39 to i64
  %41 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 %40
  store i32 %37, i32* %41, align 4
  br label %42

; <label>:42                                      ; preds = %24, %13
  br label %43

; <label>:43                                      ; preds = %42
  %44 = load i32, i32* %j, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %j, align 4
  br label %9

; <label>:46                                      ; preds = %9
  br label %47

; <label>:47                                      ; preds = %46
  %48 = load i32, i32* %i, align 4
  %49 = add nsw i32 %48, -1
  store i32 %49, i32* %i, align 4
  br label %5

; <label>:50                                      ; preds = %5
  %51 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 0
  %52 = load i32, i32* %51, align 16
  %53 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 1
  %54 = load i32, i32* %53, align 4
  %55 = icmp sle i32 %52, %54
  br i1 %55, label %56, label %75

; <label>:56                                      ; preds = %50
  %57 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 1
  %58 = load i32, i32* %57, align 4
  %59 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 2
  %60 = load i32, i32* %59, align 8
  %61 = icmp sle i32 %58, %60
  br i1 %61, label %62, label %75

; <label>:62                                      ; preds = %56
  %63 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 2
  %64 = load i32, i32* %63, align 8
  %65 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 3
  %66 = load i32, i32* %65, align 4
  %67 = icmp sle i32 %64, %66
  br i1 %67, label %68, label %75

; <label>:68                                      ; preds = %62
  %69 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 3
  %70 = load i32, i32* %69, align 4
  %71 = getelementptr inbounds [5 x i32], [5 x i32]* %vetor, i64 0, i64 4
  %72 = load i32, i32* %71, align 16
  %73 = icmp sle i32 %70, %72
  br i1 %73, label %74, label %75

; <label>:74                                      ; preds = %68
  store i32 1, i32* %1, align 4
  br label %76

; <label>:75                                      ; preds = %68, %62, %56, %50
  store i32 0, i32* %1, align 4
  br label %76

; <label>:76                                      ; preds = %75, %74
  %77 = load i32, i32* %1, align 4
  ret i32 %77
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu3 (tags/RELEASE_380/final)"}
