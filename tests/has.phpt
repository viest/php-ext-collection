--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    'name' => 'viest',
    'age'  => 21
]);

$true  = $collection->has('age');
$false = $collection->has('address');

var_dump($true, $false);
?>
--EXPECT--
bool(true)
bool(false)
