--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4, 5, 6, 7, 8, 9
]);

$chunk = $collection->forPage(2, 3);

var_dump($chunk);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (3) {
  [0]=>
  int(4)
  [1]=>
  int(5)
  [2]=>
  int(6)
}
