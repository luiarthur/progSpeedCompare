//https://github.com/scalanlp/breeze/wiki/Linear-Algebra-Cheat-Sheet
//http://www.scalanlp.org/api/breeze/index.html#breeze.linalg.package

import scala.io.Source
import java.io.File // write to file. new File("file.txt")
import scala.util.Random
import breeze.linalg._ // put breeze.jar in the scala lib
import breeze.numerics._
import breeze._
//import mybreeze.breeze.linalg._
//import mybreeze.breeze.linalg.DenseVector

object bayesMLR{
  val file = new File("temp.csv")
  val m = breeze.linalg.csvread(file)

  val x = DenseVector.zeros[Double](5)
}


