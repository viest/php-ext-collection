--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'languages' => [
        'php', 'c'
    ]
]);

$flattened = $collection1->flatten();

var_dump($flattened);

$collection2 = \Vtiful\Kernel\Collection::init([
    'Apple' => [
        ['name' => 'iPhone 6S', 'brand' => 'Apple'],
    ],
    'Samsung' => [
        ['name' => 'Galaxy S7', 'brand' => 'Samsung']
    ],
]);

$products = $collection2->flatten(2);

var_dump($products);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (3) {
  [0]=>
  string(5) "viest"
  [1]=>
  string(3) "php"
  [2]=>
  string(1) "c"
}
object(Vtiful\Kernel\Collection)#4 (4) {
  [0]=>
  string(9) "iPhone 6S"
  [1]=>
  string(5) "Apple"
  [2]=>
  string(9) "Galaxy S7"
  [3]=>
  string(7) "Samsung"
}
