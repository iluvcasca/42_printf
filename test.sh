make -s
clang -g -O2 test_ft_printf.c -L. -lftprintf 
(./a.out | cat -e) out> test_ft_printf.txt
clang -g -O2 test_printf.c -L. -lftprintf 
(./a.out | cat -e) out> test_printf.txt
diff test_ft_printf.txt test_printf.txt
make clean -s
