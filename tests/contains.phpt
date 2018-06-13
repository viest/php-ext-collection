--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init(['name' => 'Desk', 'price' => 100]);

$true = $collection->contains('Desk');

var_dump($true);

$false = $collection->contains('New York');

var_dump($false);

$collection = \Vtiful\Kernel\Collection::init([
    ['product' => 'Desk', 'price' => 200, 'VV'],
    ['product' => 'Chair', 'price' => 100, 'BB'],
]);

$true2 = $collection->contains('product', 'Desk');

var_dump($true2);

$false2 = $collection->contains('product', 'Bookcase');

var_dump($false2);
?>
--EXPECT--
bool(true)
bool(false)
bool(true)
bool(false)
