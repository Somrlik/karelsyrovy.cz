<?php
declare(strict_types=1);

namespace Somrlik\FfiExperiments\FFI;

use FFI\CData;

abstract class Maze
{
	public int $MAZE_TILE_WALL;
	public int $MAZE_TILE_PATH;

	abstract public function generateMaze(int $width, int $height, ?CData $maze): bool;

	abstract public function mazeToString(CData $maze, ?CData $buffer, int $bufferLength): bool;
}