#!/usr/bin/env php
<?php declare(strict_types=1);

include_once __DIR__ . "/vendor/autoload.php";

use Somrlik\FfiExperiments\FFILoader;

$ffiLoader = new FFILoader();
$ffiLoader->load('meddle-c', __DIR__ . '/c-lib/pfx/include/meddle_ffi.h', __DIR__ . '/c-lib/pfx/lib/libmeddle-c.so');
$ffiLoader->load('meddle-cpp', __DIR__ . '/c-lib/pfx/include/meddle_ffi.h', __DIR__ . '/c-lib/pfx/lib/libmeddle-cpp.so');

echo sprintf("Meddle from C: %d", $ffiLoader->get('meddle-c')->meddle(1)) . PHP_EOL;
echo sprintf("Meddle from CPP: %d", $ffiLoader->get('meddle-cpp')->meddle(1)) . PHP_EOL;
