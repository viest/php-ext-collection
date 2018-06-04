--TEST--
Check Collection initialization
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([1]);

var_dump($collection);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#1 (1) {
  [0]=>
  int(1)
}
