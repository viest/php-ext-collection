--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection1 = \Vtiful\Kernel\Collection::init([
    ['product_id' => 'prod-100', 'name' => 'Desk'],
    ['product_id' => 'prod-200', 'name' => 'Chair'],
]);

$keyed1 = $collection1->keyBy('product_id');

$collection2 = \Vtiful\Kernel\Collection::init([
    ['product_id' => 'prod-100', 'name' => 'Desk'],
    ['product_id' => 'prod-200', 'name' => 'Chair'],
]);

$keyed2 = $collection2->keyBy(function ($item) {
    return strtoupper($item['product_id']);
});

var_dump($keyed1, $keyed2);
?>
--EXPECT--
object(Vtiful\Kernel\Collection)#2 (2) {
  ["prod-100"]=>
  array(2) {
    ["product_id"]=>
    string(8) "prod-100"
    ["name"]=>
    string(4) "Desk"
  }
  ["prod-200"]=>
  array(2) {
    ["product_id"]=>
    string(8) "prod-200"
    ["name"]=>
    string(5) "Chair"
  }
}
object(Vtiful\Kernel\Collection)#5 (2) {
  ["PROD-100"]=>
  array(2) {
    ["product_id"]=>
    string(8) "prod-100"
    ["name"]=>
    string(4) "Desk"
  }
  ["PROD-200"]=>
  array(2) {
    ["product_id"]=>
    string(8) "prod-200"
    ["name"]=>
    string(5) "Chair"
  }
}
