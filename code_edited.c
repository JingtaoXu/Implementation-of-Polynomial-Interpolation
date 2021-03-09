#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double f(double x){
  return(sin(x*x));
}

// write LATEX-code to fileTEX:
void fileRecord_TEX(FILE *fileTEX, double(*fun)(double x), double a, double b, double n){
  fprintf(fileTEX, "\\documentclass{article}\n");
  fprintf(fileTEX, "\\usepackage{pgfplots}\n");
  fprintf(fileTEX, "\\usepackage{pst-plot}\n");
  fprintf(fileTEX, "\\usepackage{pstricks}\n");
  fprintf(fileTEX, "\\usepgfplotslibrary{fillbetween}\n");

  fprintf(fileTEX, "\\begin{document}\n");

  fprintf(fileTEX, "\\begin{minipage}[c]{0.7\\textwidth}\n");
  fprintf(fileTEX, "\\begin{tikzpicture}\n");
  fprintf(fileTEX, "\\begin{axis}[axis lines=middle, grid=major, xlabel = {$x$}, ylabel = {$y$}, title={$S = \\int\\limits_a^b f(x)\\,dx$}]\n");

  fprintf(fileTEX, "\\legend{$f(x)$};\n");
  fprintf(fileTEX, "\\addplot[name path=A, mark =*, mark size=0.5pt] table {\n");
  fprintf(fileTEX, "x\ty\n");

  // write your f(x_i):
  double s,h,y;
  double i;

  s = 0;
  h=(b - a)/n;  /*积分步长*/
  for(i=a;i<b;i+=h){
      fprintf(fileTEX, "%lf\t%lf\n", i, fun(i));
      s += h * fabs(fun(i));
  }


  fprintf(fileTEX, "};\n");

  fprintf(fileTEX, "\\addplot[name path=B, domain=%lf:%lf] {0};\n", a, b);
  fprintf(fileTEX, "\\addplot[gray, opacity=0.5] fill between[of=A and B,split];\n");

  fprintf(fileTEX, "\\end{axis}\n");
  fprintf(fileTEX, "\\end{tikzpicture}\n");
  fprintf(fileTEX, "\\end{minipage}\n");

  fprintf(fileTEX, "\\begin{minipage}[c]{0.3\\textwidth}\n");
  fprintf(fileTEX, "\\texttt{in:\\\\ a = %lf,\\\\ b = %lf,\\\\ delta = %lf;}\\\\\n", a, b, n);
  fprintf(fileTEX, "\\texttt{out:\\\\s = %lf.}\n", s);
  fprintf(fileTEX, "\\end{minipage}\n");
  fprintf(fileTEX, "\\end{document}\n");
}

// main:
int main(){
  FILE *file = fopen("latex.tex", "wb");         // create LATEX-file in tmp-dir and open it


  double S;         //square
  double a, b;      //range of f(x)
  double steps;     //steps

  printf("input a:\n");
  scanf("%lf", &a);
  printf("input b:\n");
  scanf("%lf", &b);
  printf("input steps:\n");
  scanf("%lf", &steps);



  fileRecord_TEX(file, f, a, b, steps);                          // write to LATEX-file
  fclose(file);                                  // close file

  system ("pdflatex latex.tex");              // compile LATEX-file
  system ("rm latex.log");                    // and remove log of LATEX-compile
  system ("rm latex.aux");
  system ("rm latex.tex");

  // You can see pdf-file with "Hello world!" in the directory where you started the program.
  return 0;
}
