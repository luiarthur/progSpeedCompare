//https://github.com/scalanlp/breeze/wiki/Linear-Algebra-Cheat-Sheet
//http://www.scalanlp.org/api/breeze/index.html#breeze.linalg.package
//https://github.com/scalanlp/breeze/wiki/Installation
//http://www.scala-sbt.org/0.12.2/docs/Getting-Started/Hello.html

import scala.io.Source
import java.io.File // write to file. new File("file.txt")
import scala.util.Random

// put breeze.jar in the scala lib
import breeze.linalg._
import breeze.numerics._
import breeze.stats.distributions._

object bayesMLR{
  val afile = new File("temp.csv")
  //val m = breeze.linalg.csvread(afile)

  val x = DenseMatrix.ones[Double](5,1)
  //val y = Gaussian(0,1).sample(20)
  //val v = DenseVector(y.toArray)
}


