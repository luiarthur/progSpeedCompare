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
import breeze.stats.mean

object bayesMLR{
  // Objects
  val afile = new File("../data/dat.txt")
  val rnorm = Gaussian(0,1)
  //val runif = new Random // runif.nextDouble

  // Other Constants
  val m = csvread(afile,' ') //requires breeze.linalg
  val n = m.rows
  val k = m.cols-1

  val X = m(::,1 to k)
  val Xt = X.t
  var XXi = inv(Xt*X)
  val y = m(::,0)
  val s2 = 10.0
  val a = 1.0
  val b = 1.0
  val B = 100000
  val r = log(DenseVector.rand(B*2))

  // Posteriors:
  var bb = DenseMatrix.zeros[Double](B,k)
  var ss = DenseVector.ones[Double](B)
  
  // Candidate Sigmas:
  val csb = XXi(::,*) * 4.0
  val css = 1.0

  // Acceptance Counters:
  var accb, accs = 0

  def chol(x: DenseMatrix[Double]): DenseMatrix[Double] = {
    // Make sure breeze cholesky returns upper triangle (like R and C++)
    //val up = upperTriangular(x)
    //val lo = up.t
    //val out = up + lo - diag(diag(x))
    //cholesky(out).t
    cholesky(x).t
  }

  def ll(be: DenseVector[Double], sig2: Double): Double = {
    val c = y-X*be
    val out = (c.t*c/sig2 + n*log(sig2)) / -2.0
    out
  }

  def lpb(be: DenseVector[Double]): Double = {
    be.t*XXi*be / (-2.0*s2)
  }
  
  def lps(sig2: Double): Double = {
    (a-1)*log(sig2) - sig2/b
  }

  def round(x: Double, figs: Int=3): Double = {
    BigDecimal(x).setScale(figs,BigDecimal.RoundingMode.HALF_UP).toDouble
  }
  
  def mvrnorm(M: DenseVector[Double], S: DenseMatrix[Double]): DenseVector[Double] = {
    M + chol(S).t * DenseVector(rnorm.sample(k).toArray)
  }

  def main(args: Array[String]) = {
    (1 to 10).foreach(s => println())
    println("Starting...") // Takes about 2 seconds to compile, and 6 seconds to run.
    val t1 = System.currentTimeMillis / 1000.0
      // current values:
      var bc = bb(0,::).t
      var sc = ss(0)

      // Candidate Values:
      var cb = bc
      var cs = sc
      var q = 0.0

      for (i <- 1 to (B-1)) {
        bb(i,::) := bc.t
        ss(i) = sc

        //Update Beta:
        cb = mvrnorm(bc,csb)
        q = ll(cb,sc)+lpb(cb) - ll(bc,sc)-lpb(bc)
        if (q > r(i)) {
          bc = cb
          accb += 1
        }

        //Update sigma2:
        cs = rnorm.draw()*sqrt(css) + sc
        if (cs > 0) {
          q = ll(bc,cs)+lps(cs) -ll(bc,sc)-lps(sc) 
          if (q > r(i+B)) {
            sc = cs
            accs += 1
          }
        }
        //print("\rProgress: "+round(i*100.0/B,0)+"%")//This slows down by half the time
      } // End of Metropolis
    val t2 = System.currentTimeMillis / 1000.0
    println("Acceptance beta: "+100.0*accb/B+"%")
    println("Acceptance sig2: "+100.0*accs/B+"%\n")
    println("Posterior sig2: "+round(sum(ss(90000 to 99999)) / (B*.1)))
    println("Posterior beta:")
    //(sum(bb(::,*)).t / (B*1.0)).toArray.foreach(s => println("\t"+s))
    (mean(bb(90000 to 99999,*)).t).foreach(s => println("\t"+s))
    println("Gibbs Time: "+round(t2-t1,3)+"s\n")
    println()
  }
}
// TO launch REPL:
//sbt ~console
