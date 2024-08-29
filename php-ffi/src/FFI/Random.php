<?php
declare(strict_types=1);

namespace Somrlik\FfiExperiments\FFI;

abstract class Random
{
	abstract public function randomInt();

	abstract public function randomIntBetween(int $max, int $min);

	abstract public function randomIntReset(): void;
}
