#!/bin/bash

app="bb01"
fn="${app}.tar.gz"

cd ../src
tar -zcvf ${fn} ${app}
mv ${fn} ../
cp ../${fn} ../web/src/res
