#!/bin/bash

PNFS_PATH=$1

DATASET_NAME=$2
DATASET_TITLE=$3
DATE=$4
DIR=$5
FILES=$PNFS_PATH/$DATASET_NAME/$DATASET_TITLE/$DATE/$DIR/*
filename=$DATASET_TITLE"_"$DIR
rm $filename".txt"
rm $filename.root
echo $filename
for f in $FILES
do
 echo dcap://cmsrm-se01$f  >> $filename".txt"
done
 
hadd ../rootfiles/$filename.root `tr '\n' ' ' < $filename.txt`