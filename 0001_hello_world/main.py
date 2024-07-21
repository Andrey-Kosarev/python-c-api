import hello_c_api
from timeit import timeit

hello_c_api.hello()

_sum = hello_c_api.add_two_nums(2, 3)
print(_sum)


test_array = [4,8,15,16,23,42]

def loop_sum(arr: list):
    result = 0
    for i in arr:
        result += i
    
    return i



python_sum_time = timeit(lambda: sum(test_array), number=10000)
print(python_sum_time)

c_api_sum_time = timeit(lambda: hello_c_api.sum_list(test_array), number=10000)
print(c_api_sum_time)

python_loop_sum_time = timeit(lambda: loop_sum(test_array), number=10000)
print(python_loop_sum_time)


