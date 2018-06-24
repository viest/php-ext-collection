--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([
    1, 'a'
]);

$result1 = $collection1->implode('-');

$collection2 = \Vtiful\Kernel\Collection::init([
    ['name' => 'viest', 'age' => 21],
    ['name' => 'vikin', 'age' => 20],
    ['name' => 'wjx',   'age' => 22],
]);

$result2 = $collection2->implode('name', '-');

var_dump($result1, $result2);
?>
--EXPECT--
string(3) "1-a"
string(15) "viest-vikin-wjx"
