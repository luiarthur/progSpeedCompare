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
	//"io"        // Readmatrix
	//"io/ioutil" // Readmatrix
	//"strconv"   // Readmatrix
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
	m0 := my.M0(5, 3)
	m1 := my.M0(5, 3)
	my.PrintMatrix(m0)
	fmt.Println(m1) // m1 is of Type mat64.Dense

	//v := make([]float64, 10)
	//var a mat64.MulTranser

	//a.MulTrans(&m0, true, &m1, false)
	//fmt.Println(a.MulTrans(m0, true, m1, false))
	//fmt.Println(a)

	//fmt.Printf("%T", A)
	//my.PrintMatrix(A)

	/*
		dat, _ := ioutil.ReadFile("../data/dat.txt")
		fmt.Printf("%T", dat)
	*/
	//fmt.Print(string(dat))
	fmt.Println()
}
