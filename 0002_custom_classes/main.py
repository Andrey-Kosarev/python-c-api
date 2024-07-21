import timeit
import mini_numpy as mnp
from mini_numpy import PyVector

array = [x for x in range(1_000_000)]
# array = [x/2 for x in range(1_000_000)]   # if we make it x/2, python performs significantly better. For C++ no change

pyv = PyVector(array)

TEST_ITERATIONS = 1000

cpp_sum_time = timeit.timeit(lambda: pyv.sum(), number=TEST_ITERATIONS)
print("CPP sum time          :", cpp_sum_time)


python_sum_time = timeit.timeit(lambda: sum(array), number=TEST_ITERATIONS)
print("Python sum time       :", python_sum_time)


print(sum(array)==pyv.sum())

