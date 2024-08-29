<?php
declare(strict_types=1);

namespace Somrlik\FfiExperiments\Test;

use PHPUnit\Framework\TestCase;
use Somrlik\FfiExperiments\FFI\Maze;
use Somrlik\FfiExperiments\FFI\Random;
use Somrlik\FfiExperiments\FFILoader;

class FFIMazeTest extends TestCase
{
	const EXPECTED_10x10_MAZE = "##########\n#     # ##\n# ### # ##\n# # # # ##\n# # # # ##\n# #   # ##\n### ### ##\n#       ##\n##########\n##########\n";
	const EXPECTED_50x50_MAZE_FILE = __DIR__ . '/../c-lib/test/resources/maze_50x50.txt';
	const EXPECTED_100x5_MAZE_FILE = __DIR__ . '/../c-lib/test/resources/maze_100x5.txt';

	private function loadMaze(): \FFI|Maze {
		$loader = new FFILoader();
		$loader->load(
			'maze',
			__DIR__ . '/../c-lib/pfx/include/maze_ffi.h',
			__DIR__ . '/../c-lib/pfx/lib/libmeddle-c.so'
		);

		return $loader->get('maze');
	}

	private function loadRandom(): \FFI|Random {
		$loader = new FFILoader();
		$loader->load(
			'random',
			__DIR__ . '/../c-lib/pfx/include/random_ffi.h',
			__DIR__ . '/../c-lib/pfx/lib/libmeddle-c.so'
		);

		return $loader->get('random');
	}

	public function testMazeGenerator() {
		$mazeLib = $this->loadMaze();
		$randomLib = $this->loadRandom();

		self::assertFalse($mazeLib->generateMaze(10, 10, null));

		$maze = $mazeLib->new('Maze');
		$maze->width = 0;
		$maze->height = 0;
		$maze->layout = null;

		self::assertFalse($mazeLib->generateMaze(-1, -1, \FFI::addr($maze)));
		self::assertFalse($mazeLib->generateMaze(0, 0, \FFI::addr($maze)));
		self::assertFalse($mazeLib->generateMaze(2, 2, \FFI::addr($maze)));
		self::assertTrue($mazeLib->generateMaze(3, 3, \FFI::addr($maze)));

		$buffer = $mazeLib->new('char[1024 * 1024]');
		$bufferSize = 1024 * 1024;
		self::assertTrue($mazeLib->mazeToString($maze, $buffer, $bufferSize));
		self::assertEquals("###\n# #\n###\n", \FFI::string($buffer));

		$randomLib->randomIntReset();
		self::assertTrue($mazeLib->generateMaze(10, 10, \FFI::addr($maze)));
		self::assertTrue($mazeLib->mazeToString($maze, $buffer, $bufferSize));
		self::assertEquals(self::EXPECTED_10x10_MAZE, \FFI::string($buffer));

		$randomLib->randomIntReset();
		self::assertTrue($mazeLib->generateMaze(50, 50, \FFI::addr($maze)));
		self::assertEquals(50, $maze->width);
		self::assertEquals(50, $maze->height);
		self::assertTrue($mazeLib->mazeToString($maze, $buffer, $bufferSize));
		self::assertEquals(file_get_contents(self::EXPECTED_50x50_MAZE_FILE), \FFI::string($buffer));

		$randomLib->randomIntReset();
		self::assertTrue($mazeLib->generateMaze(100, 5, \FFI::addr($maze)));
		self::assertEquals(100, $maze->width);
		self::assertEquals(5, $maze->height);
		self::assertTrue($mazeLib->mazeToString($maze, $buffer, $bufferSize));
		self::assertEquals(file_get_contents(self::EXPECTED_100x5_MAZE_FILE), \FFI::string($buffer));
	}

	public function testEnums() {
		$mazeLib = $this->loadMaze();
		$mazeTile = $mazeLib->new('MazeTile');
		$mazeTile->cdata = $mazeLib->MAZE_TILE_PATH;
		self::assertEquals(1, $mazeTile->cdata);
	}
}
