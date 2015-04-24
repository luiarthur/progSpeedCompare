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
	"strconv"
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
	readtime := strconv.FormatFloat((t2.Sub(t1)).Seconds(), 'f', 2, 32)

	my.PrintMatrix(dat)
	fmt.Println("Time taken to read data: " + readtime + "s")
	fmt.Println()

}
