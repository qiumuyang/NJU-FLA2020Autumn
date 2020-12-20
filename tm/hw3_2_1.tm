; f(x) = x / 2,     x is even,
;        (x+1) / 2, x is odd.

#Q = {start, mr, div, div2, fin}
#S = {0, 1}
#G = {0, 1, B}
#B = B
#N = 1
#q0 = start
#F = {fin}

start 0 0 r fin
start 1 1 r mr
start B B r fin

mr 0 0 r mr
mr 1 1 r mr
mr B B l div

div 0 B l fin
div 1 0 l div2
div B B r fin

div2 0 1 r mr
div2 1 0 l div2
div2 B 1 r mr
