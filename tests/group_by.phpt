--TEST--
Check Collection operations
--SKIPIF--
<?php if (!extension_loaded("collection")) print "skip"; ?>
--FILE--
<?php 
$collection = \Vtiful\Kernel\Collection::init([
    ['account_id' => 'account-x10', 'product' => 'Chair'],
    ['account_id' => 'account-x10', 'product' => 'Bookcase'],
    ['account_id' => 'account-x11', 'product' => 'Desk'],
]);

$grouped = $collection->groupBy(function ($item, $key) {
    return substr($item['account_id'], -3);
});

var_dump($grouped->toArray());

$grouped = $collection->groupBy('account_id');

var_dump($grouped->toArray());
?>
--EXPECT--
array(2) {
  ["x10"]=>
  array(2) {
    [0]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x10"
      ["product"]=>
      string(5) "Chair"
    }
    [1]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x10"
      ["product"]=>
      string(8) "Bookcase"
    }
  }
  ["x11"]=>
  array(1) {
    [0]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x11"
      ["product"]=>
      string(4) "Desk"
    }
  }
}
array(2) {
  ["account-x10"]=>
  array(2) {
    [0]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x10"
      ["product"]=>
      string(5) "Chair"
    }
    [1]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x10"
      ["product"]=>
      string(8) "Bookcase"
    }
  }
  ["account-x11"]=>
  array(1) {
    [0]=>
    array(2) {
      ["account_id"]=>
      string(11) "account-x11"
      ["product"]=>
      string(4) "Desk"
    }
  }
}
