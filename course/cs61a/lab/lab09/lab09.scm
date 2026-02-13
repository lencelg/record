(define (over-or-under num1 num2) 
        (cond 
          ((< num1 num2) -1)
          ((= num1 num2) 0)
          (else 1)
          )
)

(define (make-adder num) 
    (lambda (another) (+ another num))    
)

(define (composed f g) 
    (lambda (x) (f (g x)))
)

(define (repeat f n)
    (lambda (inc) 
      (if (> n 0)
          ((repeat f (- n 1)) (f inc))
          inc 
      )
    )
)

(define (max a b)
  (if (> a b)
      a
      b))

(define (min a b)
  (if (> a b)
      b
      a))

(define (gcd a b)
      (if (zero? (modulo (max a b) (min a b)))
          (min a b)
          (gcd b (modulo a b)))
)
