<?php
declare(strict_types=1);

namespace Somrlik\FfiExperiments\Test;

use PHPUnit\Framework\TestCase;
use Somrlik\FfiExperiments\FFI\Random;
use Somrlik\FfiExperiments\FFILoader;

class FFIRandomTest extends TestCase
{
	private function loadRandom(): \FFI|Random {
		$loader = new FFILoader();
		$loader->load(
			'random',
			__DIR__ . '/../c-lib/pfx/include/random_ffi.h',
			__DIR__ . '/../c-lib/pfx/lib/libmeddle-c.so'
		);

		return $loader->get('random');
	}

	public function testSmoke() {
		$random = $this->loadRandom();

		$random->randomIntReset();
		self::assertEquals(8, $random->randomInt());
		self::assertEquals(109, $random->randomInt());
		self::assertEquals(220, $random->randomInt());
		self::assertEquals(222, $random->randomInt());
		self::assertEquals(241, $random->randomInt());

		$random->randomIntReset();
		self::assertEquals(8, $random->randomInt());
		self::assertEquals(109, $random->randomInt());
		self::assertEquals(220, $random->randomInt());
		self::assertEquals(222, $random->randomInt());
		self::assertEquals(241, $random->randomInt());
	}

	public function testUnexpectedValues() {
		$random = $this->loadRandom();

		$random->randomIntReset();
		self::assertEquals(0, $random->randomIntBetween(0, 0));
		self::assertEquals(0, $random->randomIntBetween(-1, 1));
		self::assertEquals(1, $random->randomIntBetween(1, -1));
		self::assertEquals(-1, $random->randomIntBetween(-1, -1));
		self::assertEquals(-241, $random->randomIntBetween(0, -100));
		self::assertEquals(-51, $random->randomIntBetween(-100, 0));
	}

	public function testInBetween() {
		$random = $this->loadRandom();

		$random->randomIntReset();
		self::assertEquals(2, $random->randomIntBetween(0, 100));
		self::assertEquals(36, $random->randomIntBetween(0, 100));
		self::assertEquals(73, $random->randomIntBetween(0, 100));
		self::assertEquals(74, $random->randomIntBetween(0, 100));

		$random->randomIntReset();
		self::assertEquals(2, $random->randomIntBetween(0, 100));
		self::assertEquals(36, $random->randomIntBetween(0, 100));
		self::assertEquals(73, $random->randomIntBetween(0, 100));
		self::assertEquals(74, $random->randomIntBetween(0, 100));
	}

	public function testRepeatsAfter256() {
		$random = $this->loadRandom();

		$ints1 = [];
		for ($i = 0; $i < 256; $i++) {
			$ints1[] = $random->randomInt();
		}

		$ints2 = [];
		for ($i = 0; $i < 256; $i++) {
			$ints2[] = $random->randomInt();
		}

		self::assertEquals($ints1, $ints2);
	}

}
