; Case 1: ai bj ai bj (i, j > 0).
; Input: a string of a's and b's

#Q = {start, search_b, search_a, rewind, cp, ml, cmp, at, ar, au, ae, clear, clear1, rf, ra, rl, rs, re, accept, reject}

#F = {accept}

#q0 = start

#S = {a, b}

#G = {b, _, t, r, u, e, f, a, l, s}

#B = _

#N = 2

; State start
start __ __ ** rf           ; empty input
start a_ a_ r* search_b
start b_ b_ ** clear        ; input started with b

; State search_b : aa... -> b
search_b a_ a_ r* search_b
search_b b_ b_ r* search_a  ; find b, now search a
search_b __ __ l* clear1    ; b not found, reject

; State search_a : a...b... -> a
search_a a_ a_ ** cp        ; find a, now copy the rest part to tape 2 (if accept should be aibj)
search_a b_ b_ r* search_a
search_a __ __ l* clear1    ; a not found, reject

; State cp : copy rest to tape2 and erase tape1
cp a_ _a rr cp
cp b_ _b rr cp
cp __ __ ll rewind          ; copy end, move 2 heads to left

; State rewind : move tape1's head to symbol
rewind _a _a l* rewind
rewind _b _b l* rewind
rewind aa aa ** ml
rewind ab ab ** ml
rewind ba ba ** ml
rewind bb bb ** ml

; State ml : move 2 heads to left
ml aa aa ll ml
ml ab ab ll ml
ml a_ a_ l* ml
ml ba ba ll ml
ml bb bb ll ml
ml b_ b_ l* ml
ml _a _a *l ml
ml _b _b *l ml
ml __ __ rr cmp             ; 2 heads of tapes now at begin of string

; State cmp
cmp aa __ rr cmp
cmp bb __ rr cmp
cmp ab __ rr clear
cmp a_ __ rr clear
cmp ba __ rr clear
cmp b_ __ rr clear
cmp _a __ ** rf
cmp _b __ ** rf
cmp __ __ ** at             ; tape1 = aibj = tape2

; State clear : clear 2 tapes for 'false'
clear aa __ rr clear
clear ab __ rr clear
clear a_ __ rr clear
clear ba __ rr clear
clear bb __ rr clear
clear b_ __ rr clear
clear _a __ rr clear
clear _b __ rr clear
clear __ __ ** rf

; State clear1 : only clear tape1 (left part)
clear1 a_ __ l* clear1
clear1 b_ __ l* clear1
clear1 __ __ ** rf

; State rf, ra, rs, rl, re : write 'false'
rf __ f_ r* ra
rf _a f_ r* ra
rf _b f_ r* ra
ra __ a_ r* rl
rl __ l_ r* rs
rs __ s_ r* re
re __ e_ r* reject

; State at, ar, au, ae : write 'true'
at __ t_ rr ar
ar __ r_ rr au
au __ u_ rr ae
ae __ e_ rr accept