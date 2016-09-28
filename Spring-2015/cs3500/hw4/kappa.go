//Chris Peabody
//5-11-2015
//file: kappa.go

package main

import "fmt"

type student struct {
  name string
  score int
}

func foo(x int) int {
  return int((0.02 * float64(x*x*x)) - float64(2 * (x*x)) + float64(3 * x) + float64(3000))
}

func main() {
  var T, score int
  var roster [128]student
  var name string
  var tstudent student

  fmt.Printf("Hello Kappa!\n")

  fmt.Scanln(&T)

  for i := 0; i<T; i++ {
    fmt.Scanln(&name, &score)
    tstudent.name = name
    tstudent.score = score

    roster[i] = tstudent
  }

  for i := T-1; i >= 0; i-- {
    val := foo(roster[i].score)

    if val > 2000 {
      fmt.Println(roster[i].name + "'s score is too large!")
    } else {
      fmt.Println(roster[i].name, val)
    }
  }
}

