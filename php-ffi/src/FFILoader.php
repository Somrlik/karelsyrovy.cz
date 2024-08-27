<?php
declare(strict_types=1);

namespace Somrlik\FfiExperiments;

class FFILoader
{
	/** @var \FFI|null[] */
	private array $instances = [];

	public function load(string $name, string $header, string $library): bool {
		if (array_key_exists($name, $this->instances)) {
			return false;
		}

		$source = fopen($header, 'r+x');
		if ($source === false) return false;
		$temp = tmpfile();
		if ($temp === false) {
			fclose($source);
			return false;
		}

		$written = fwrite($temp, sprintf("#define FFI_LIB \"%s\"\n", $library));
		if (!$written) {
			fclose($temp);
			fclose($source);
			return false;
		}

		if (false === stream_copy_to_stream($source, $temp)) {
			fclose($temp);
			fclose($source);
			return false;
		}
		fclose($source);

		$oldCwd = getcwd();
		try {
			if (fflush($temp) === false) {
				return false;
			}
			$newCwd = dirname($library);

			if (chdir($newCwd) === false) {
				return false;
			}
			$ffi = \FFI::load(stream_get_meta_data($temp)['uri']);

			if ($ffi === null) return false;
			$this->instances[$name] = $ffi;
			return true;
		} finally {
			chdir($oldCwd);
			fclose($temp);
		}
	}

	public function get(string $name): \FFI|null {
		return $this->instances[$name] ?? null;
	}
}