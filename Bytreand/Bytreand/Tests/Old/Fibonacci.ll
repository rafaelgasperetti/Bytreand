; ModuleID = 'Fibonacci.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @fibonacci(i32 %n) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 %n, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = icmp slt i32 %3, 2
  br i1 %4, label %5, label %7

; <label>:5                                       ; preds = %0
  %6 = load i32, i32* %2, align 4
  store i32 %6, i32* %1, align 4
  br label %15

; <label>:7                                       ; preds = %0
  %8 = load i32, i32* %2, align 4
  %9 = sub nsw i32 %8, 2
  %10 = call i32 @fibonacci(i32 %9)
  %11 = load i32, i32* %2, align 4
  %12 = sub nsw i32 %11, 1
  %13 = call i32 @fibonacci(i32 %12)
  %14 = add nsw i32 %10, %13
  store i32 %14, i32* %1, align 4
  br label %15

; <label>:15                                      ; preds = %7, %5
  %16 = load i32, i32* %1, align 4
  ret i32 %16
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @fibonacci(i32 10)
  %3 = icmp eq i32 %2, 55
  br i1 %3, label %4, label %5

; <label>:4                                       ; preds = %0
  store i32 1, i32* %1, align 4
  br label %6

; <label>:5                                       ; preds = %0
  store i32 0, i32* %1, align 4
  br label %6

; <label>:6                                       ; preds = %5, %4
  %7 = load i32, i32* %1, align 4
  ret i32 %7
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu3 (tags/RELEASE_380/final)"}
