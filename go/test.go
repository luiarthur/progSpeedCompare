//Go Tour:                https://tour.golang.org/welcome/1
//Setting up a workspace: http://golang.org/doc/code.html
//gonum Gist: 						https://github.com/gonum
//mat64 Documentation: 		https://godoc.org/github.com/gonum/matrix/mat64
package main

import (
	"fmt"
	m "github.com/gonum/matrix/mat64"
)

func matrix(row, col int) m.Dense {
	v := make([]float64, row*col)
	M := m.NewDense(row, col, v)
	return *M
}

func main() {
	/*
		row := make([]float64, 3)
		for i := 0; i < 3; i++ {
			row[i] = .1
		}

		ma := make([][]float64, 3)
		for i := 0; i < 3; i++ {
			ma[i] = row
		}
		fmt.Println(ma)
	*/

	/*
		var b m.Dense
		fmt.Println("b", b)
		var c m.Matrix
		fmt.Println("c", c)
		d := m.NewDense
		fmt.Println("d", d)
	*/

	n := 20
	v := make([]float64, n)

	fmt.Println(m.NewDense(3, 3, []float64{0, 0, 0, 0, 0, 0, 0, 0, 0}))
	fmt.Println(m.NewDense(5, 4, v))
	fmt.Println(matrix(3, 5))
	//m.Format(matrix(3, 5), 1, '.', '?', 'v')//how do i print matrices?
}
