; ModuleID = 'Dotprod.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %a = alloca [5 x double], align 16
  %b = alloca [5 x double], align 16
  %length = alloca i32, align 4
  %index = alloca i32, align 4
  %runningSum = alloca double, align 8
  store i32 0, i32* %1, align 4
  %2 = bitcast [5 x double]* %a to i8*
  call void @llvm.memset.p0i8.i64(i8* %2, i8 0, i64 40, i32 16, i1 false)
  %3 = bitcast i8* %2 to [5 x double]*
  %4 = getelementptr [5 x double], [5 x double]* %3, i32 0, i32 0
  store double 2.000000e+00, double* %4
  %5 = getelementptr [5 x double], [5 x double]* %3, i32 0, i32 1
  store double 3.000000e+00, double* %5
  %6 = getelementptr [5 x double], [5 x double]* %3, i32 0, i32 2
  store double 1.000000e+00, double* %6
  %7 = getelementptr [5 x double], [5 x double]* %3, i32 0, i32 3
  store double 5.000000e+00, double* %7
  %8 = getelementptr [5 x double], [5 x double]* %3, i32 0, i32 4
  store double 4.000000e+00, double* %8
  %9 = bitcast [5 x double]* %b to i8*
  call void @llvm.memset.p0i8.i64(i8* %9, i8 0, i64 40, i32 16, i1 false)
  %10 = bitcast i8* %9 to [5 x double]*
  %11 = getelementptr [5 x double], [5 x double]* %10, i32 0, i32 1
  store double 3.000000e+00, double* %11
  %12 = getelementptr [5 x double], [5 x double]* %10, i32 0, i32 2
  store double 2.000000e+00, double* %12
  %13 = getelementptr [5 x double], [5 x double]* %10, i32 0, i32 3
  store double 1.000000e+00, double* %13
  %14 = getelementptr [5 x double], [5 x double]* %10, i32 0, i32 4
  store double 4.000000e+00, double* %14
  store i32 5, i32* %length, align 4
  store double 0.000000e+00, double* %runningSum, align 8
  store i32 0, i32* %index, align 4
  br label %15

; <label>:15                                      ; preds = %31, %0
  %16 = load i32, i32* %index, align 4
  %17 = load i32, i32* %length, align 4
  %18 = icmp slt i32 %16, %17
  br i1 %18, label %19, label %34

; <label>:19                                      ; preds = %15
  %20 = load i32, i32* %index, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds [5 x double], [5 x double]* %a, i64 0, i64 %21
  %23 = load double, double* %22, align 8
  %24 = load i32, i32* %index, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [5 x double], [5 x double]* %b, i64 0, i64 %25
  %27 = load double, double* %26, align 8
  %28 = fmul double %23, %27
  %29 = load double, double* %runningSum, align 8
  %30 = fadd double %29, %28
  store double %30, double* %runningSum, align 8
  br label %31

; <label>:31                                      ; preds = %19
  %32 = load i32, i32* %index, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %index, align 4
  br label %15

; <label>:34                                      ; preds = %15
  %35 = load double, double* %runningSum, align 8
  %36 = fcmp oeq double %35, 3.200000e+01
  br i1 %36, label %37, label %38

; <label>:37                                      ; preds = %34
  store i32 1, i32* %1, align 4
  br label %39

; <label>:38                                      ; preds = %34
  store i32 0, i32* %1, align 4
  br label %39

; <label>:39                                      ; preds = %38, %37
  %40 = load i32, i32* %1, align 4
  ret i32 %40
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu3 (tags/RELEASE_380/final)"}
