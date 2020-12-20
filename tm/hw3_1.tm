#Q = {q1, q2, q3, q4, q5, qacc, qrej}
#S = {0}
#G = {0, 1, B}
#B = B
#N = 1
#q0 = q1
#F = {qacc}

q1 B B r qrej
q1 0 B r q2
q1 1 1 r qrej

q2 B B r qacc
q2 0 1 r q3
q2 1 1 r q2

q3 B B l q5
q3 0 0 r q4
q3 1 1 r q3

q4 B B r qrej
q4 0 1 r q3
q4 1 1 r q4

q5 B B r q2
q5 0 0 l q5
q5 1 1 l q5
