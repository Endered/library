#!/bin/bash 
 make 
 for i in *in 
 do 
 echo $i 
 ./a.out < $i 
 done
