set term png notransparent giant size 1024,768 enh
set output "fisheye1.png"

set xrange [0:pi/2]
set yrange [0:2.5]

set samples 500

p_ed(f, x)=f*x
p_es(f, x)=2*f*sin(x/2)
p_o(f, x)=f*sin(x)
p_s(f, x)=2*f*tan(x/2)
p_r(f, x)=f*tan(x)

f1=9.2
f2=f1/sqrt(2.0)*pi/2.0
f3=f1/2.0*pi/2.0
f4=f1*pi/2.0

set xlabel 'Inclination angle'
set ylabel 'r/f'

plot p_r(f1,x)/f1 ti 'Rectilinear',\
  p_ed(f1,x)/f1 ti 'Equidistant',\
  p_es(f1,x)/f1 ti 'Equisolid',\
  p_s(f1,x)/f1 ti 'Stereographic',\
  p_o(f1,x)/f1 ti 'Orthographic'

set output "fisheye2.png"

set yrange [0:2.1]
set ylabel "r/f1"

plot p_ed(f1,x)/f1 ti 'Equidistant (f1=  9.2mm)',\
  p_es(f2,x)/f1 ti 'Equisolid (f2=10.2mm)',\
  p_s(f3,x)/f1 ti 'Stereographic (f3=  7.2mm)',\
  p_o(f4,x)/f1 ti 'Orthographic (f4=14.5mm)'
