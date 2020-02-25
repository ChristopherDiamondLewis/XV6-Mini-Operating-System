echo ----------------------------------
echo Running Test Script
echo ----------------------------------
echo Script usage message
script
echo Script argc error checking 
script 1 1 1 
echo ----------------------------------
echo Script file error checking
script test.zh
script test
script test.shh
echo ----------------------------------
echo Run Sample Program
sample
echo ----------------------------------
echo Test Script Done!
