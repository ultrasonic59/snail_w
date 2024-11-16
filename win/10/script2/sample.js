function bigval(val1,val2)
{
  if(val1>val2){
    return val1;
  } else {
    return val2;
  }
}

debugPrint.output(bigval(1,10));
debugPrint.output(bigval(99,10));

