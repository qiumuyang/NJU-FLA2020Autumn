; uu^R u \in {a, b}*

#Q = {cmp, mra, mrb, cmpa, cmpb, ml, clr, at, ar, au, ae, rf, ra, rl, rs, re, accept, reject}
#S = {a, b}
#G = {a, b, t, r, u, e, f, l, s, B}
#B = B
#N = 1
#q0 = cmp
#F = {accept}

cmp a B r mra
cmp b B r mrb
cmp B B r at

mra a a r mra
mra b b r mra
mra B B l cmpa

mrb a a r mrb
mrb b b r mrb
mrb B B l cmpb

cmpa a B l ml
cmpa b B l clr
cmpa B B l clr

cmpb a B l clr
cmpb b B l ml
cmpb B B l clr

ml a a l ml
ml b b l ml
ml B B r cmp

clr a B l clr
clr b B l clr
clr B B l rf

rf B f r ra
ra B a r rl
rl B l r rs
rs B s r re
re B e r reject

at B t r ar
ar B r r au
au B u r ae
ae B e r accept