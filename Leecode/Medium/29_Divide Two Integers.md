#### Description

Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part. For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note:

Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−$$2^{31}$$,  $$2^{31}$$ − 1]. For this problem, assume that your function returns $$2^{31}$$ − 1 when the division result overflows.


Example 1:

Input: dividend = 10, divisor = 3
Output: 3
Explanation: 10/3 = truncate(3.33333..) = 3.
Example 2:

Input: dividend = 7, divisor = -3
Output: -2
Explanation: 7/-3 = truncate(-2.33333..) = -2.
Example 3:

Input: dividend = 0, divisor = 1
Output: 0
Example 4:

Input: dividend = 1, divisor = 1
Output: 1


Constraints:

-$$2^{31}$$ <= dividend, divisor <= $$2^{31}$$ - 1
divisor != 0

#### Solution

```c++
class Solution:
    def divide(self, dividend: int, divisor: int) -> int:
        if divisor == 1:
            return dividend
        if dividend == 0:
            return 0
        if divisor == 1:
            return dividend;
        if divisor == -1:
            if dividend > -2147483648:
                return -dividend
            else: 
                return 2147483647
        is_neg =  False
        if dividend < 0: is_neg, dividend = not is_neg, -dividend
        if divisor < 0: is_neg, divisor = not is_neg, -divisor
        count = 0
        while divisor <= dividend:
            temp = divisor
            res = 1
            while temp + temp < dividend:
                temp = temp + temp
                res += res
            dividend -= temp
            count += res
        if is_neg: 
            count = -count
        if count < -2147483648:
            return -2147483648
        elif count > 2147483647:
            return 2147483647
        else:
            return count
```



#### Note

1. 特殊情况单独先判断可节省时间
2. 有时候别想着有很简便的方法，应从正确思路着手。如此题想递推关系。
