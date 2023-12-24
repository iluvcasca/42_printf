clang -g -O2 test_ft_printf.c ft*.c -L . -lft 
(./a.out | cat -e) out> test_ft_printf.txt
clang -g -O2 test_printf.c ft*.c -L . -lft 
(./a.out | cat -e) out> test_printf.txt
diff test_ft_printf.txt test_printf.txt

