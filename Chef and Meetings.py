def time_in_range(start, end, x):
    if start <= end:
        return start <= x <= end
    else:
        return start <= x or x <= end
from datetime import *
for _ in range(int(input())):
    a=''
    P = datetime.strptime(input(), '%I:%M %p')
    n=int(input())
    for j in range(n):
        t=input()
        t1=datetime.strptime(t[:8], '%I:%M %p')
        t2=datetime.strptime(t[9:], '%I:%M %p')
        if(time_in_range(t1, t2,P)):
            a+='1'
        else:
            a+='0'
    print(a)
