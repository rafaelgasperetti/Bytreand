; ModuleID = 'VectorSum.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.a = private unnamed_addr constant [3 x i32] [i32 3, i32 4, i32 1], align 4
@main.b = private unnamed_addr constant [3 x i32] [i32 5, i32 2, i32 7], align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca [3 x i32], align 4
  %b = alloca [3 x i32], align 4
  %c = alloca [3 x i32], align 4
  %tamanho = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = bitcast [3 x i32]* %a to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* bitcast ([3 x i32]* @main.a to i8*), i64 12, i32 4, i1 false)
  %3 = bitcast [3 x i32]* %b to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* bitcast ([3 x i32]* @main.b to i8*), i64 12, i32 4, i1 false)
  store i32 3, i32* %tamanho, align 4
  store i32 0, i32* %i, align 4
  br label %4

; <label>:4                                       ; preds = %21, %0
  %5 = load i32, i32* %i, align 4
  %6 = load i32, i32* %tamanho, align 4
  %7 = icmp slt i32 %5, %6
  br i1 %7, label %8, label %24

; <label>:8                                       ; preds = %4
  %9 = load i32, i32* %i, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds [3 x i32], [3 x i32]* %a, i64 0, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = load i32, i32* %i, align 4
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds [3 x i32], [3 x i32]* %b, i64 0, i64 %14
  %16 = load i32, i32* %15, align 4
  %17 = add nsw i32 %12, %16
  %18 = load i32, i32* %i, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [3 x i32], [3 x i32]* %c, i64 0, i64 %19
  store i32 %17, i32* %20, align 4
  br label %21

; <label>:21                                      ; preds = %8
  %22 = load i32, i32* %i, align 4
  %23 = add nsw i32 %22, 1
  store i32 %23, i32* %i, align 4
  br label %4

; <label>:24                                      ; preds = %4
  %25 = getelementptr inbounds [3 x i32], [3 x i32]* %c, i64 0, i64 0
  %26 = load i32, i32* %25, align 4
  %27 = icmp eq i32 %26, 8
  br i1 %27, label %28, label %37

; <label>:28                                      ; preds = %24
  %29 = getelementptr inbounds [3 x i32], [3 x i32]* %c, i64 0, i64 1
  %30 = load i32, i32* %29, align 4
  %31 = icmp eq i32 %30, 6
  br i1 %31, label %32, label %37

; <label>:32                                      ; preds = %28
  %33 = getelementptr inbounds [3 x i32], [3 x i32]* %c, i64 0, i64 2
  %34 = load i32, i32* %33, align 4
  %35 = icmp eq i32 %34, 8
  br i1 %35, label %36, label %37

; <label>:36                                      ; preds = %32
  store i32 1, i32* %1, align 4
  br label %38

; <label>:37                                      ; preds = %32, %28, %24
  store i32 0, i32* %1, align 4
  br label %38

; <label>:38                                      ; preds = %37, %36
  %39 = load i32, i32* %1, align 4
  ret i32 %39
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu3 (tags/RELEASE_380/final)"}
