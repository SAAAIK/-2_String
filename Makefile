CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJ = s21_string
TEST= tests.sh
TEST_FLAGS = -std=c11 -g
GCOVFLAGS = -L. -ls21_string --coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck 
endif

UTIL = -fsanitize=address

TEST_COMPILE = $(CC) $(TEST_FLAGS) tests/test*.c libs21_string.a $(CHECK_FLAGS) -L. -ls21_string


all: clean style leaks cppcheck gcov_report s21_string.a

peer: gcov_report

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug *.txt ./tests/make* ./report/*

style:
	clang-format -i ./*.c ./*.h ./tests/*.c ./tests/*.h
	clang-format -n ./*.c ./*.h ./tests/*.c ./tests/*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

leaks:
	gcc s21*.c ./tests/valgrind_test.c -lm
	valgrind --leak-check=full --tool=memcheck --show-leak-kinds=all --track-origins=yes --verbose -q ./a.out
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug *.txt ./tests/make* ./report/*

good: clean all test
	sleep 3
	clear

me:
	gcc ./tests/test_maker.c -o ./tests/makesometest
	./tests/makesometest

rebuild: clean all

test: s21_string.a
	$(TEST_COMPILE)
	-./a.out
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug *.txt ./tests/make* ./report/*

s21_string.a: s21_string.o
	ar rcs libs21_string.a *.o
	rm -rf *.o
	ranlib libs21_string.a
	cp libs21_string.a s21_string.a
	cp libs21_string.a ls21_string.a

s21_string.o:
	$(CC) $(CC_FLAGS) -c s21*.c

gcov_report: 
	$(CC) $(CC_FLAGS) -c s21*.c $(GCOVFLAGS)
	ar rcs libs21_string.a *.o
	rm -rf *.o
	ranlib libs21_string.a
	cp libs21_string.a s21_string.a
	cp libs21_string.a ls21_string.a
	gcc $(TEST_FLAGS) tests/test_*.c libs21_string.a $(CHECK_FLAGS) $(GCOVFLAGS)
	-./a.out
	lcov -t a.out -o all_test.info -c -d .
	genhtml -o report all_test.info
	rm -rf *.gcda *.gcno ./a.out *.info ./tests/*.a ./tests/*.o ./*.a
	-open ./report/index.html


