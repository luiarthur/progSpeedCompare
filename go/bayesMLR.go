//Go Tour:                https://tour.golang.org/welcome/1
//Setting up a workspace: http://golang.org/doc/code.html
//gonum Gist: 						https://github.com/gonum
//mat64 Documentation: 		https://godoc.org/github.com/gonum/matrix/mat64
package main

import (
	//"bufio" // Readmatrix
	"fmt"
	//"github.com/gonum/matrix/mat64"
	//"github.com/gonum/blas/blas64"
	my "github.com/myStat"
	//"strconv"
	"time"
)

/*
func Readmatrix(r io.Reader) mat64.Dense {
	scanner := bufio.NewScanner(r)
	scanner.Split(bufio.ScanWords)
	var result mat64.Dense
	for scanner.Scan() {
		x, err := strconv.Atoi(scanner.Text())
		if err != nil {
			return result, err
		}
		result = append(result, x)
	}
	return result
}
*/

func main() {

	//a := my.M0(3, 3)
	//a.MulTrans(&m0, true, &m1, false)
	//fmt.Println(a)

	fmt.Println()
	t1 := time.Now()
	dat := my.ReadMatrix("../data/dat.txt")
	t2 := time.Now()
	readtime := (t2.Sub(t1)).Seconds()

	n, k := dat.Caps()
	k = k - 1

	X := dat.View(0, 1, n, k)
	//fmt.Print(X)
	y := dat.View(0, 0, n, 1)
	//fmt.Println(y)
	//yy := my.M0(1, 1)
	//yy.MulTrans(y, true, y, false)
	//fmt.Println(yy)

	yx := my.M0(1, k)
	yx.MulTrans(y, true, X, false)
	xy := my.M0(k, 1)
	//fmt.Println(yx)
	xy.TCopy(&yx)
	my.PrintMatrix(xy)

	fmt.Println()
	//fmt.Print(X)
	//fmt.Print(y)
	fmt.Println("Rows in dataset:", n)
	fmt.Println("Columns in dataset:", k+1)
	fmt.Printf("Time taken to read data:  %f%s", readtime, "s")
	fmt.Println()

}
