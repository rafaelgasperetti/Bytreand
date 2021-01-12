; ModuleID = 'Autocorrelation.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.x = private unnamed_addr constant [5 x i32] [i32 5, i32 3, i32 2, i32 4, i32 1], align 16

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %x = alloca [5 x i32], align 16
  %vet = alloca [5 x i32], align 16
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %n = alloca i32, align 4
  %sum = alloca i32, align 4
  %sumTotal = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = bitcast [5 x i32]* %x to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* bitcast ([5 x i32]* @main.x to i8*), i64 20, i32 16, i1 false)
  store i32 5, i32* %n, align 4
  store i32 0, i32* %sumTotal, align 4
  store i32 0, i32* %i, align 4
  br label %3

; <label>:3                                       ; preds = %39, %0
  %4 = load i32, i32* %i, align 4
  %5 = load i32, i32* %n, align 4
  %6 = icmp slt i32 %4, %5
  br i1 %6, label %7, label %42

; <label>:7                                       ; preds = %3
  store i32 0, i32* %sum, align 4
  store i32 0, i32* %j, align 4
  br label %8

; <label>:8                                       ; preds = %28, %7
  %9 = load i32, i32* %j, align 4
  %10 = load i32, i32* %n, align 4
  %11 = load i32, i32* %i, align 4
  %12 = sub nsw i32 %10, %11
  %13 = icmp slt i32 %9, %12
  br i1 %13, label %14, label %31

; <label>:14                                      ; preds = %8
  %15 = load i32, i32* %j, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [5 x i32], [5 x i32]* %x, i64 0, i64 %16
  %18 = load i32, i32* %17, align 4
  %19 = load i32, i32* %j, align 4
  %20 = load i32, i32* %i, align 4
  %21 = add nsw i32 %19, %20
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [5 x i32], [5 x i32]* %x, i64 0, i64 %22
  %24 = load i32, i32* %23, align 4
  %25 = mul nsw i32 %18, %24
  %26 = load i32, i32* %sum, align 4
  %27 = add nsw i32 %26, %25
  store i32 %27, i32* %sum, align 4
  br label %28

; <label>:28                                      ; preds = %14
  %29 = load i32, i32* %j, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, i32* %j, align 4
  br label %8

; <label>:31                                      ; preds = %8
  %32 = load i32, i32* %sum, align 4
  %33 = load i32, i32* %i, align 4
  %34 = sext i32 %33 to i64
  %35 = getelementptr inbounds [5 x i32], [5 x i32]* %vet, i64 0, i64 %34
  store i32 %32, i32* %35, align 4
  %36 = load i32, i32* %sum, align 4
  %37 = load i32, i32* %sumTotal, align 4
  %38 = add nsw i32 %37, %36
  store i32 %38, i32* %sumTotal, align 4
  br label %39

; <label>:39                                      ; preds = %31
  %40 = load i32, i32* %i, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %i, align 4
  br label %3

; <label>:42                                      ; preds = %3
  %43 = load i32, i32* %sumTotal, align 4
  %44 = srem i32 %43, 5
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds [5 x i32], [5 x i32]* %vet, i64 0, i64 %45
  %47 = load i32, i32* %46, align 4
  ret i32 %47
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu3 (tags/RELEASE_380/final)"}
