; ModuleID = 'BitCount.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @bitCount(i32 %value) #0 {
  %1 = alloca i32, align 4
  %count = alloca i32, align 4
  store i32 %value, i32* %1, align 4
  store i32 0, i32* %count, align 4
  br label %2

; <label>:2                                       ; preds = %12, %0
  %3 = load i32, i32* %1, align 4
  %4 = icmp ugt i32 %3, 0
  br i1 %4, label %5, label %15

; <label>:5                                       ; preds = %2
  %6 = load i32, i32* %1, align 4
  %7 = and i32 %6, 1
  %8 = icmp eq i32 %7, 1
  br i1 %8, label %9, label %12

; <label>:9                                       ; preds = %5
  %10 = load i32, i32* %count, align 4
  %11 = add i32 %10, 1
  store i32 %11, i32* %count, align 4
  br label %12

; <label>:12                                      ; preds = %9, %5
  %13 = load i32, i32* %1, align 4
  %14 = lshr i32 %13, 1
  store i32 %14, i32* %1, align 4
  br label %2

; <label>:15                                      ; preds = %2
  %16 = load i32, i32* %count, align 4
  ret i32 %16
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @bitCount(i32 9)
  %3 = icmp eq i32 %2, 2
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
