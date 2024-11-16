function bigval(val1,val2)
{
  if(val1>val2){
    return val1;
  } else {
    return val2;
  }
}

debugPrint.output_invoke(bigval(1,10));
debugPrint.output_invoke(bigval(99,10));

