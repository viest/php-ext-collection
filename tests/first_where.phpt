--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    ['name' => 'Regena', 'age' => 12],
    ['name' => 'Linda', 'age' => 14],
    ['name' => 'Diego', 'age' => 23],
    ['name' => 'Linda', 'age' => 84],
]);

$result1 = $collection->firstWhere('name', 'Linda');
$result2 = $collection->firstWhere('age', '>=', 18);

var_dump($result1);
var_dump($result2);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["name"]=>
  string(5) "Linda"
  ["age"]=>
  int(14)
}
object(Vtiful\Kernel\Collection)#3 (2) {
  ["name"]=>
  string(5) "Diego"
  ["age"]=>
  int(23)
}
