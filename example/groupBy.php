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