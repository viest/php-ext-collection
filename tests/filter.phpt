--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php
$collection1 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, 4
]);

$callbackRes = $collection1->filter(function ($value, $key) {
    return $value > 2;
});

$collection2 = \Vtiful\Kernel\Collection::init([
    1, 2, 3, null, false, '', 0, []
]);

$noCallback = $collection2->filter();

var_dump($callbackRes);
var_dump($noCallback);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#3 (2) {
  [0]=>
  int(3)
  [1]=>
  int(4)
}
object(Vtiful\Kernel\Collection)#4 (3) {
  [0]=>
  int(1)
  [1]=>
  int(2)
  [2]=>
  int(3)
}
