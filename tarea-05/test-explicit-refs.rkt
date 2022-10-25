#lang racket

let x = newref(0)
in letrec even(dummy)
  = if zero?(deref(x ))
    then 1
    else begin setref(x , -(deref(x ),1)); (odd 666) end
  odd(dummy)
  = if zero?(deref(x ))
    then 0
    else begin setref(x , -(deref(x ),1)); (even 666) end
  in begin setref(x ,13); (odd 666) end



let g = let counter = newref(0)
   in proc (dummy)
     begin
       setref(counter, -(deref(counter), -1));
       deref(counter)
     end
 in let a = (g 11)
  in let b = (g 11)
   in -(a, b)